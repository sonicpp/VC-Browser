#include "abstractfile.h"
#include "file.h"
#include "directory.h"

AbstractFile::AbstractFile(std::string name)
:m_name(name), m_dir(false), m_compressed(false)
{
}

void AbstractFile::abstract()
{
}

AbstractFile *AbstractFile::createFile(std::string name, bool dir)
{
	AbstractFile *file;

	if (dir)
		file = new Directory(name);
	else
		file = new File(name);

	return file;
}

void AbstractFile::setCompressed(bool compressed)
{
	m_compressed = compressed;
}

std::string AbstractFile::getName()
{
	return m_name;
}

bool AbstractFile::isDir()
{
	return m_dir;
}

bool AbstractFile::isCompressed()
{
	return m_compressed;
}

void AbstractFile::setDir(bool dir)
{
	m_dir = dir;
}
