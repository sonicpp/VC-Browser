#include "txt.h"

TXT::TXT(QString name)
:AbstractFile(false, name)
{
	mp_layout = new QVBoxLayout;
	mp_edit = new QTextEdit;

	mp_edit->setReadOnly(true);
	mp_codec = QTextCodec::codecForName("Windows-1250");
	mp_status = new QStatusBar;
	mp_layout->addWidget(mp_edit);
	mp_layout->addWidget(mp_status);
	mp_widget->setLayout(mp_layout);

	redrawWidget();
}

TXT::~TXT()
{
	delete mp_edit;
	delete mp_status;
	delete mp_layout;
}

bool TXT::setData(uint8_t *p_data, size_t size, QProgressDialog *p_progress)
{
	char *buff;

	buff = new char[size + 1];
	memcpy(buff, p_data, size);
	buff[size] = '\0';

	m_str = mp_codec->toUnicode(buff);

	delete[] buff;

	redrawWidget();

	return true;
}

void TXT::redrawWidget(void)
{
	mp_status->clearMessage();

	mp_edit->setText(m_str);
	mp_status->showMessage(QString("Chars total: ") +
			       QString::number(m_str.size()));
}
