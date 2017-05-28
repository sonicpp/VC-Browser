#include "file.h"

File::File(std::string name)
:AbstractFile(name)
{
	setDir(false);
	setCompressed(false);
}

void File::abstract()
{
}
