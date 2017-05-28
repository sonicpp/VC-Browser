#ifndef _ABSTRACTFILE_H
#define _ABSTRACTFILE_H

#include <string>

#include <QMetaType>

class AbstractFile {
protected:
	std::string m_name;
	bool m_dir;
	bool m_compressed;
	void setDir(bool dir);
public:
	AbstractFile(std::string name);
	virtual void abstract() = 0;
	static AbstractFile *createFile(std::string name, bool dir);
	void setCompressed(bool compressed);
	std::string getName();
	bool isDir();
	bool isCompressed();
};

Q_DECLARE_METATYPE(AbstractFile *)

#endif
