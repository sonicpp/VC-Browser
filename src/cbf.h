#ifndef _CBF_H
#define _CBF_H

#include <string>
#include <vector>
#include <fstream>

#include <QStandardItem>
#include <QProgressDialog>

#include "abstractfile.h"

struct CBFException : public std::exception
{
	std::string m_msg;
	CBFException(std::string msg) : m_msg(msg) {}
	const char* what() const throw() { return m_msg.c_str(); }
};

class CBF {
public:
	CBF(std::ifstream *file, QStandardItem *item,
		QProgressDialog *progress) throw (CBFException);
private:
	std::vector<struct CBFFile *> getFileList(uint8_t *fileTable,
		uint32_t tableSize);
	void decryptTable(uint8_t *data, uint16_t size);
	void decryptFile(uint8_t *data, uint32_t size);
	QStandardItem *addFile(AbstractFile *file, QStandardItem *parent);
	std::vector<std::string> splitPath(const std::string &path);
};

#endif
