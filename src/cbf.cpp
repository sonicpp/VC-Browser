#include <iostream>
#include <sstream>

#include "cbf.h"

struct CBFFile {
	uint16_t structSize;	// size of the rest of this struct
	uint32_t unk[10];
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

CBF::CBF(std::ifstream *file, QStandardItem *item)
throw (CBFException)
{
	struct CBFHeader header;
	std::vector<std::string> files;
	uint8_t *table = NULL;

	file->exceptions(std::ifstream::eofbit | std::ifstream::failbit |
		std::ifstream::badbit);
	try {
		file->read((char *) &header, sizeof(struct CBFHeader));
		if (header.sig1 != 0x46474942 ||	// BIGF
		header.sig2 != 0x4C425A01) {		// .ZBL
			throw CBFException("Not a CBF file");
		}
		table = new uint8_t[header.tableSize];
		file->ignore(header.tableOffset - sizeof(struct CBFHeader));
		file->read((char *) table, header.tableSize);
	} catch (std::ios_base::failure &e) {
		if (table)
			delete table;
		throw CBFException("Invalid CBF file");
	}

	files = getFileList(table, header.tableSize);

	for(std::vector<std::string>::iterator fit = files.begin();
	fit != files.end(); ++fit) {
		std::vector<std::string> path = splitPath(*fit);
		QStandardItem *nitem = item;
		for(std::vector<std::string>::iterator file = path.begin();
		file != path.end(); ++file) {
			nitem = addFile(*file, nitem);
		}
	}
}

std::vector<std::string> CBF::getFileList(uint8_t *fileTable,
	uint32_t tableSize)
{
	std::vector<std::string> fileList;
	struct CBFFile *file;

	for (uint32_t pos = 0; pos + 2 < tableSize; pos += sizeof_CBF(file))
	{
		file = (struct CBFFile *) (fileTable + pos);
		decryptFile((uint8_t *) file, file->structSize);

		fileList.push_back(std::string(file->name));
	}

	return fileList;
}

void CBF::decryptFile(uint8_t *data, uint16_t size)
{
	uint8_t lookUpTable[16] = {
		0x32, 0xF3, 0x1E, 0x06, 0x45, 0x70, 0x32, 0xAA,
		0x55, 0x3F, 0xF1, 0xDE, 0xA3, 0x44, 0x21, 0xB4};
	uint8_t key = size;
	uint8_t cryptedData;

	data += sizeof(((struct CBFFile *) data)->structSize);

	for (uint16_t ptr = 0; ptr < size; ptr++)
	{
		cryptedData = data[ptr];
		data[ptr] ^= lookUpTable[key & 15];
		key = cryptedData;
	}
}

QStandardItem *CBF::addFile(std::string file, QStandardItem *item)
{
	bool found = false;

	for (int i = 0; i < item->rowCount(); i++) {
		if (item->child(item->rowCount() - 1)->text() ==
		QString(file.c_str())) {
			item = item->child(item->rowCount() - 1);
			found = true;
		}
	}

	if (!found) {
		QList<QStandardItem *> rowItems;
		rowItems << new QStandardItem(QString(file.c_str()));
		item->appendRow(rowItems);
		item = item->child(item->rowCount() - 1);
	}

	return item;
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
