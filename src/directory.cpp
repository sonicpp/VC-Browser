#include <QTextEdit>

#include "directory.h"

Directory::Directory(std::string name)
:AbstractFile(name)
{
	setDir(true);
	setCompressed(false);
	m_widget = new QTextEdit;
	((QTextEdit *) m_widget)->setText(name.c_str());
}

QWidget *Directory::getWidget()
{
	return m_widget;
}
