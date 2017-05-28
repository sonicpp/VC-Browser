#include "directory.h"

Directory::Directory(std::string name)
:AbstractFile(name)
{
	setDir(true);
	setCompressed(false);
}

std::string Directory::getData()
{
	return getName();
}
