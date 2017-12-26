#ifndef _FILE_H
#define _FILE_H

#include <string>
#include "abstractfile.h"

class UnknownFile: public AbstractFile {
public:
	UnknownFile(QString name, AbstractFile *p_parent);
	bool setData(std::ifstream *p_file, QProgressDialog *p_progress = NULL);
	bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL);
};

#endif
