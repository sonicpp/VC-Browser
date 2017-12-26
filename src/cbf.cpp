#include <iostream>
#include <sstream>

#include <QApplication>

#include "abstractfile.h"
#include "cbf.h"

struct CBFFile {
	uint16_t structSize;	// size of the rest of this struct
	uint32_t offset;
	uint32_t unk1[4];
	uint32_t size;
	uint32_t unk2[2];
	uint32_t compressed;
	uint32_t unk3;
	char name[1];
} __attribute__((packed));
#define sizeof_CBF(file) ((file)->structSize + sizeof((file)->structSize))

struct CBFHeader {
	uint32_t sig1;
	uint32_t sig2;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint32_t tableOffset;
	uint32_t unk4;
	uint32_t tableSize;
} __attribute__((packed));

CBF::CBF(QString name)
:AbstractFile(true, name)
{
}

CBF::~CBF()
{
}

std::vector<struct CBFFile *> CBF::getFileList(uint8_t *fileTable,
	uint32_t tableSize)
{
	std::vector<struct CBFFile *> fileList;
	struct CBFFile *file;

	for (uint32_t pos = 0; pos + 2 < tableSize; pos += sizeof_CBF(file))
	{
		file = (struct CBFFile *) malloc(
			sizeof_CBF((struct CBFFile *) (fileTable + pos)));
		memcpy(file, (fileTable + pos),
		       sizeof_CBF((struct CBFFile *) (fileTable + pos)));
		decryptTable((uint8_t *) file, file->structSize);

		fileList.push_back(file);
	}

	return fileList;
}

void CBF::decryptTable(uint8_t *data, uint16_t size)
{
	uint8_t lookUpTable[16] = {
		0x32, 0xF3, 0x1E, 0x06, 0x45, 0x70, 0x32, 0xAA,
		0x55, 0x3F, 0xF1, 0xDE, 0xA3, 0x44, 0x21, 0xB4};
	uint16_t key = size;
	uint8_t cryptedData;

	data += sizeof(((struct CBFFile *) data)->structSize);

	for (uint16_t ptr = 0; ptr < size; ptr++)
	{
		cryptedData = data[ptr];
		data[ptr] ^= lookUpTable[key & 15];
		key = cryptedData;
	}
}

void CBF::decryptFile(uint8_t *data, uint32_t size)
{
	uint8_t key = size & 0xFF;

	for(uint32_t i = 0; i < size; i++)
		data[i] = (data[i] - 0x5A + key) ^ key;
}

bool CBF::setData(uint8_t *data, size_t size, QProgressDialog *p_progress)
{
	struct CBFHeader *p_header;
	std::vector<struct CBFFile *> files;
	uint8_t *table = NULL;
	uint8_t *fd = NULL;
	AbstractFile *ff;
	QStringList path;

	p_header = (struct CBFHeader *) data;
	if (p_header->sig1 != 0x46474942 ||	// BIGF
	p_header->sig2 != 0x4C425A01) {		// .ZBL
			throw CBFException("Not a CBF file");
	}
	table = data + p_header->tableOffset;

	files = getFileList(table, p_header->tableSize);

	if (p_progress) {
		p_progress->setMaximum(files.size());
		p_progress->setValue(0);
		p_progress->show();
	}

	for(std::vector<struct CBFFile *>::iterator fit = files.begin();
	fit != files.end(); ++fit) {
		if (p_progress && p_progress->wasCanceled())
			break;
		QString n(((struct CBFFile *) *fit)->name);
		path = n.split('\\');

		ff = AbstractFile::createFile(path[path.size() - 1]);
		if (((struct CBFFile *) *fit)->compressed) {

			ff->setCompressed(true);
		}
		else {
			decryptFile(data + ((struct CBFFile *) *fit)->offset, ((struct CBFFile *) *fit)->size);
			ff->setCompressed(false);
			ff->setData(data + ((struct CBFFile *) *fit)->offset, ((struct CBFFile *) *fit)->size);
		}
		addFile(ff, n);
		if (p_progress)
			p_progress->setValue(p_progress->value() + 1);
		qApp->processEvents();
	}

	if (p_progress && p_progress->wasCanceled()) {
		while (!mp_children.empty()) {
			ff = mp_children.back();
			mp_children.pop_back();
			delete ff;
		}
	}
}
