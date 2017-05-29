#include <iostream>
#include <sstream>

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

CBF::CBF(std::ifstream *input, QStandardItem *item)
throw (CBFException)
{
	struct CBFHeader header;
	std::vector<struct CBFFile *> files;
	uint8_t *table = NULL;
	uint8_t *fd = NULL;
	AbstractFile *ff;

	input->exceptions(std::ifstream::eofbit | std::ifstream::failbit |
		std::ifstream::badbit);
	try {
		input->read((char *) &header, sizeof(struct CBFHeader));
		if (header.sig1 != 0x46474942 ||	// BIGF
		header.sig2 != 0x4C425A01) {		// .ZBL
			throw CBFException("Not a CBF file");
		}
		table = new uint8_t[header.tableSize];
		input->ignore(header.tableOffset - sizeof(struct CBFHeader));
		input->read((char *) table, header.tableSize);
	} catch (std::ios_base::failure &e) {
		if (table)
			delete table;
		throw CBFException("Invalid CBF file");
	}

	files = getFileList(table, header.tableSize);

	for(std::vector<struct CBFFile *>::iterator fit = files.begin();
	fit != files.end(); ++fit) {
		std::vector<std::string> path = splitPath(
			((struct CBFFile *) *fit)->name);
		QStandardItem *nitem = item;
		for(std::vector<std::string>::iterator file = path.begin();
		file != path.end(); ++file) {
			ff = AbstractFile::createFile(*file, file + 1 != path.end());
			if (!ff->isDir()) {
				if (((struct CBFFile *) *fit)->compressed)
					ff->setCompressed(true);
				else {
					input->seekg(((struct CBFFile *) *fit)->offset, input->beg);
					fd = new uint8_t[((struct CBFFile *) *fit)->size];
					input->read((char *) fd, ((struct CBFFile *) *fit)->size);
					decryptFile(fd, ((struct CBFFile *) *fit)->size);
					ff->setData(fd, ((struct CBFFile *) *fit)->size);
				}
			}

			nitem = addFile(ff, nitem);
		}
	}
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

QStandardItem *CBF::addFile(AbstractFile *file, QStandardItem *parent)
{
	bool found = false;

	for (int i = 0; i < parent->rowCount(); i++) {
		if (parent->child(parent->rowCount() - 1)->text() ==
		QString(file->getName().c_str())) {
			parent = parent->child(parent->rowCount() - 1);
			found = true;
		}
	}

	if (!found) {
		QStandardItem *item = new QStandardItem(QString(file->getName().c_str()));
		item->setData(QVariant::fromValue(file));
		parent->appendRow(item);
		parent = parent->child(parent->rowCount() - 1);
		if (file->isCompressed())
			parent->setBackground(QBrush(QColor(150, 0, 0)));
	}

	return parent;
}

std::vector<std::string> CBF::splitPath(const std::string &path) {
	std::vector<std::string> files;
	std::string file;
	std::stringstream ss;

	ss.str(path);
	while (std::getline(ss, file, '\\'))
		files.push_back(file);

	return files;
}
