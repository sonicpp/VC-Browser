#include "file.h"

File::File(std::string name)
:AbstractFile(name)
{
	setDir(false);
	setCompressed(false);
}

std::string File::getData()
{
	if (getRawData() == NULL)
		return getName();
	else
		return std::string((char *) getRawData());
}
