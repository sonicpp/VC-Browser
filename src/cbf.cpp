#include <QApplication>
#include <QBrush>
#include <QColor>

#include "cbf.h"

/* CBF Header */
struct CBF_Header {
	uint32_t sig1;
	uint32_t sig2;
	uint32_t fileSize;	/**< Size of this CBF file */
	uint32_t unk2;
	uint32_t unk3;
	uint32_t tableOffset;
	uint32_t unk4;
	uint32_t tableSize;
} __attribute__((packed));

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

#define _getHeader(data, size) ((struct CBF_Header *) \
	getHeader((p_data), (size)))

CBF::CBF(QString name)
:AbstractFile(true, name)
{
}

CBF::~CBF()
{
}

bool CBF::setData(uint8_t *p_data, size_t size, QProgressDialog *p_progress)
{
	struct CBF_Header *p_header;
	std::vector<struct CBFFile *> *p_files;
	struct CBFFile *p_cbf_file;
	uint8_t *p_table = NULL;
	AbstractFile *ff;
	QStringList path;

	/* Get CBF header */
	if ((p_header = _getHeader(p_data, size)) == NULL)
		return false;

	/* Get CBF file list */
	p_table = p_data + p_header->tableOffset;
	p_files = getFileList(p_table, p_header->tableSize);

	if (p_progress) {
		p_progress->setMaximum(p_files->size());
		p_progress->setValue(0);
		p_progress->show();
	}

	/* Loop through all CBF files */
	for(std::vector<struct CBFFile *>::iterator fit = p_files->begin();
	fit != p_files->end(); ++fit) {
		if (p_progress && p_progress->wasCanceled())
			break;
		QString n(((struct CBFFile *) *fit)->name);
		path = n.split('\\');

		ff = AbstractFile::createFile(path[path.size() - 1]);
		if (((struct CBFFile *) *fit)->compressed) {

			ff->setCompressed(true);
			/* Show compressed files as unsupported */
			ff->getItem()->setBackground(QBrush(QColor("red")));
		}
		else {
			decryptFile(p_data + ((struct CBFFile *) *fit)->offset, ((struct CBFFile *) *fit)->size);
			ff->setCompressed(false);
			if (!ff->setData(p_data + ((struct CBFFile *) *fit)->offset, ((struct CBFFile *) *fit)->size))
				/* Setting file data failed, mark file as unsupported */
				ff->getItem()->setBackground(QBrush(QColor("red")));
		}
		addFile(ff, n);
		if (p_progress)
			p_progress->setValue(p_progress->value() + 1);
		qApp->processEvents();
	}

	while (!p_files->empty()) {
		p_cbf_file = p_files->back();
		p_files->pop_back();
		free(p_cbf_file);
	}
	delete p_files;

	if (p_progress && p_progress->wasCanceled()) {
		while (!mp_children.empty()) {
			ff = mp_children.back();
			mp_children.pop_back();
			delete ff;
		}
	}

	return true;
}

void *CBF::getHeader(uint8_t *p_data, size_t size)
{
	struct CBF_Header *p_header;

	if (size < sizeof(struct CBF_Header))
		return NULL;

	p_header = (struct CBF_Header *) p_data;
	if (p_header->sig1 != 0x46474942 ||	// BIGF
	p_header->sig2 != 0x4C425A01) {		// .ZBL
		return NULL;
	}

	return (void *) p_header;
}

std::vector<struct CBFFile *> *CBF::getFileList(uint8_t *p_fileTable,
					       uint32_t tableSize)
{
	std::vector<struct CBFFile *> *p_fileList =
			new std::vector<struct CBFFile *>();
	struct CBFFile *p_file;

	for (uint32_t pos = 0; pos + 2 < tableSize; pos += sizeof_CBF(p_file))
	{
		p_file = (struct CBFFile *) malloc(
			sizeof_CBF((struct CBFFile *) (p_fileTable + pos)));
		memcpy(p_file, (p_fileTable + pos),
		       sizeof_CBF((struct CBFFile *) (p_fileTable + pos)));
		decryptTable((uint8_t *) p_file, p_file->structSize);

		p_fileList->push_back(p_file);
	}

	return p_fileList;
}

void CBF::decryptTable(uint8_t *p_data, uint16_t size)
{
	uint8_t p_lookUpTable[16] = {
		0x32, 0xF3, 0x1E, 0x06, 0x45, 0x70, 0x32, 0xAA,
		0x55, 0x3F, 0xF1, 0xDE, 0xA3, 0x44, 0x21, 0xB4};
	uint16_t key = size;
	uint8_t cryptedData;

	p_data += sizeof(((struct CBFFile *) p_data)->structSize);

	for (uint16_t ptr = 0; ptr < size; ptr++)
	{
		cryptedData = p_data[ptr];
		p_data[ptr] ^= p_lookUpTable[key & 15];
		key = cryptedData;
	}
}

void CBF::decryptFile(uint8_t *p_data, uint32_t size)
{
	uint8_t key = size & 0xFF;

	for(uint32_t i = 0; i < size; i++)
		p_data[i] = (p_data[i] - 0x5A + key) ^ key;
}
