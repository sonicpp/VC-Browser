#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include "abstractfile.h"

class Directory: public AbstractFile {
private:
	QWidget *m_widget;
public:
	Directory(std::string name);
	virtual QWidget *getWidget();
};

#endif
