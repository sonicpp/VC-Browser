#ifndef _CBF_H
#define _CBF_H

#include <string>
#include <vector>
#include <fstream>

#include <QStandardItem>

struct CBFException : public std::exception
{
	std::string m_msg;
	CBFException(std::string msg) : m_msg(msg) {}
	const char* what() const throw() { return m_msg.c_str(); }
};

class CBF {
public:
	CBF(std::ifstream *file, QStandardItem *item) throw (CBFException);
private:
	std::vector<std::string> getFileList(uint8_t *fileTable,
		uint32_t tableSize);
	void decryptFile(uint8_t *data, uint16_t size);
	QStandardItem *addFile(std::string file, QStandardItem *item);
	std::vector<std::string> splitPath(const std::string &path);
};

#endif
