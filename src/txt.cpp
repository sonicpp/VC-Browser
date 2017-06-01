#include <QTextEdit>
#include <QTextCodec>

#include "txt.h"

TXT::TXT(std::string name)
:AbstractFile(name), m_str("")
{
	setDir(false);
	setCompressed(false);
	m_widget = new QWidget;
	m_layout = new QVBoxLayout;
	m_edit = new QTextEdit;

	m_edit->setReadOnly(true);
	m_codec = QTextCodec::codecForName("Windows-1250");
	m_status = new QStatusBar;
	m_layout->addWidget(m_edit);
	m_layout->addWidget(m_status);
	m_widget->setLayout(m_layout);
}

void TXT::setData(uint8_t *data, size_t size)
{
	AbstractFile::setData(data, size);
	m_str.clear();
	m_status->clearMessage();

	if (data != NULL)
		m_str.append(m_codec->toUnicode((char *) data));

	m_edit->setText(m_str);
	m_status->showMessage(QString("Bytes total: ") + QString::number(size) +
		QString("; Chars total: ") + QString::number(m_str.size()));
}

QWidget *TXT::getWidget()
{
	return m_widget;
}
