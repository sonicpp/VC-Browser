#ifndef _CBF_H
#define _CBF_H

#include <string>
#include <vector>
#include <fstream>
#include <QStandardItem>
#include <QProgressDialog>
#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include "abstractfile.h"

struct CBFException : public std::exception
{
	std::string m_msg;
	CBFException(std::string msg) : m_msg(msg) {}
	const char* what() const throw() { return m_msg.c_str(); }
};

class CBF: public AbstractFile {
private:
/*	QTextEdit *m_edit;
	QStatusBar *m_status;
	QVBoxLayout *m_layout;*/
	std::vector<struct CBFFile *> getFileList(uint8_t *fileTable,
		uint32_t tableSize);
	void decryptTable(uint8_t *data, uint16_t size);
	void decryptFile(uint8_t *data, uint32_t size);
public:
	CBF(QString name, AbstractFile *p_parent, uint8_t *data, size_t size);
};

#endif
