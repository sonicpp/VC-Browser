#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include "abstractfile.h"

class Directory: public AbstractFile {
public:
	Directory(std::string name);
	virtual void abstract();
};

#endif
