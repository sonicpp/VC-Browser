#include <QTextEdit>

#include "txt.h"

TXT::TXT(std::string name)
:AbstractFile(name), m_str("")
{
	setDir(false);
	setCompressed(false);
	m_widget = new QTextEdit;
}

void TXT::setData(uint8_t *data, size_t size)
{
	AbstractFile::setData(data, size);
	m_str.clear();

	if (data != NULL)
		m_str.append((char *) data);

	((QTextEdit *) m_widget)->setText(m_str);
}

QWidget *TXT::getWidget()
{
	return m_widget;
}
