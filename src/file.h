#ifndef _FILE_H
#define _FILE_H

#include <string>

#include <QMetaType>

#include "abstractfile.h"

class File: public AbstractFile{
public:
	File(std::string name);
	virtual void abstract();
};

#endif
