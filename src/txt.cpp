#include <QTextEdit>
#include <QTextCodec>

#include "txt.h"

TXT::TXT(QString name, AbstractFile *p_parent, uint8_t *data, size_t size)
:AbstractFile(false, name, p_parent)
{
	m_layout = new QVBoxLayout;
	m_edit = new QTextEdit;

	m_edit->setReadOnly(true);
	m_codec = QTextCodec::codecForName("Windows-1250");
	m_status = new QStatusBar;
	m_layout->addWidget(m_edit);
	m_layout->addWidget(m_status);
	mp_widget->setLayout(m_layout);

	m_str.clear();
	m_status->clearMessage();

	if (data != NULL) {
		/* TODO set \0 */
		m_str = m_codec->toUnicode((char *) data);

		m_edit->setText(m_str);
		m_status->showMessage(QString("Bytes total: ") + QString::number(size) +
			QString("; Chars total: ") + QString::number(m_str.size()));
	}
}
