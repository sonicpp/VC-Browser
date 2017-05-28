#include "directory.h"

Directory::Directory(std::string name)
:AbstractFile(name)
{
	setDir(true);
	setCompressed(false);
}

void Directory::abstract()
{
}
