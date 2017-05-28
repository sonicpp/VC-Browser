#ifndef _ABSTRACTFILE_H
#define _ABSTRACTFILE_H

#include <string>

#include <QMetaType>

class AbstractFile {
protected:
	std::string m_name;
	bool m_dir;
	bool m_compressed;
	uint8_t *m_data;
	uint8_t *getRawData();
	void setDir(bool dir);
public:
	AbstractFile(std::string name);
	static AbstractFile *createFile(std::string name, bool dir);
	void setData(uint8_t *data);
	void setCompressed(bool compressed);
	std::string getName();
	virtual std::string getData() = 0;
	bool isDir();
	bool isCompressed();
};

Q_DECLARE_METATYPE(AbstractFile *)

#endif
