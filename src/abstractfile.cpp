#include "abstractfile.h"
#include "file.h"
#include "directory.h"
#include "txt.h"

AbstractFile::AbstractFile(std::string name)
:m_name(name), m_dir(false), m_compressed(false), m_data(NULL)
{
}

AbstractFile *AbstractFile::createFile(std::string name, bool dir)
{
	AbstractFile *file;

	if (dir)
		file = new Directory(name);
	else if (name.substr(name.find_last_of(".") + 1) == "TXT")
		file = new TXT(name);
	else
		file = new File(name);

	return file;
}

void AbstractFile::setData(uint8_t *data, size_t size)
{
	m_data = data;
}

void AbstractFile::setCompressed(bool compressed)
{
	m_compressed = compressed;
}

QWidget *AbstractFile::getWidget()
{
	return NULL;
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

uint8_t *AbstractFile::getData()
{
	return m_data;
}

void AbstractFile::setDir(bool dir)
{
	m_dir = dir;
}
