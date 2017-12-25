#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include "abstractfile.h"

class Directory: public AbstractFile {
protected:
	QTextEdit *m_edit;
	QStatusBar *m_status;
	QVBoxLayout *m_layout;
public:
	Directory(QString name, AbstractFile *p_parent,
		QStandardItem *p_item = NULL);
};

#endif
