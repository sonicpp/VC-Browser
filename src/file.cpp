#include <QTextEdit>

#include "file.h"

File::File(std::string name)
:AbstractFile(name)
{
	setDir(false);
	setCompressed(false);
	m_widget = new QTextEdit;
	((QTextEdit *) m_widget)->setText(name.c_str());
}

void File::setData(uint8_t *data, size_t size)
{
	AbstractFile::setData(data, size);
	if (data != NULL)
		((QTextEdit *) m_widget)->setText(QString((char *) data));
}

QWidget *File::getWidget()
{
	return m_widget;
}
