#include <QTextEdit>
#include <QTextCodec>

#include "txt.h"

TXT::TXT(QString name, AbstractFile *p_parent)
:AbstractFile(false, name, p_parent)
{
	mp_layout = new QVBoxLayout;
	mp_edit = new QTextEdit;

	mp_edit->setReadOnly(true);
	mp_codec = QTextCodec::codecForName("Windows-1250");
	mp_status = new QStatusBar;
	mp_layout->addWidget(mp_edit);
	mp_layout->addWidget(mp_status);
	mp_widget->setLayout(mp_layout);

}

TXT::~TXT()
{
	delete mp_edit;
	delete mp_status;
	delete mp_layout;
}

bool TXT::setData(uint8_t *data, size_t size, QProgressDialog *p_progress)
{
	char *buff;

	m_str.clear();
	mp_status->clearMessage();

	buff = new char[size + 1];
	memcpy(buff, data, size);
	buff[size] = '\0';

	m_str = mp_codec->toUnicode(buff);
	mp_edit->setText(m_str);
	mp_status->showMessage(QString("Bytes total: ") + QString::number(size) +
		QString("; Chars total: ") + QString::number(m_str.size()));

	delete[] buff;
}
