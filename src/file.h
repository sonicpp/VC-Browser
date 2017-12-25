#ifndef _FILE_H
#define _FILE_H

#include <string>
#include "abstractfile.h"

class UnknownFile: public AbstractFile {
public:
	UnknownFile(QString name, AbstractFile *p_parent);
};

#endif
