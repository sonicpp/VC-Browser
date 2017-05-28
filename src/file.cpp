#include "file.h"

File::File(std::string name)
:m_name(name), m_dir(false), m_compressed(false)
{
	return;
}

void File::setDir(bool dir)
{
	m_dir = dir;
}

void File::setCompressed(bool compressed)
{
	m_compressed = compressed;
}

std::string File::getName()
{
	return m_name;
}

bool File::isDir()
{
	return m_dir;
}

bool File::isCompressed()
{
	return m_compressed;
}
