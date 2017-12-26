#ifndef _CBF_H
#define _CBF_H

#include <vector>

#include <QString>
#include <QProgressDialog>

#include "abstractfile.h"

class CBF: public AbstractFile {
public:
	CBF(QString name);
	~CBF();
	bool setData(uint8_t *p_data, size_t size,
		     QProgressDialog *p_progress = NULL);
private:
	std::vector<struct CBFFile *> *getFileList(uint8_t *p_fileTable,
						   uint32_t tableSize);
	void decryptTable(uint8_t *p_data, uint16_t size);
	void decryptFile(uint8_t *p_data, uint32_t size);

};

#endif	// _CBF_H
