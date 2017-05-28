#ifndef _FILE_H
#define _FILE_H

#include <string>

#include <QMetaType>

class File {
private:
	std::string m_name;
	bool m_dir;
	bool m_compressed;
public:
	File(std::string name);
	void setDir(bool dir);
	void setCompressed(bool compressed);
	std::string getName();
	bool isDir();
	bool isCompressed();
};

Q_DECLARE_METATYPE(File *)

#endif
