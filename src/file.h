#ifndef _FILE_H
#define _FILE_H

#include <string>

#include <QMetaType>

#include "abstractfile.h"

class File: public AbstractFile{
private:
	QWidget *m_widget;
public:
	File(std::string name);
	virtual void setData(uint8_t *data);
	virtual QWidget *getWidget();
};

#endif
