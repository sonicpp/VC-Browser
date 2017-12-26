#include <QTextEdit>

#include "file.h"

UnknownFile::UnknownFile(QString name)
:AbstractFile(false, name, NULL)
{
	mp_layout = new QVBoxLayout;
	mp_edit = new QTextEdit;

	mp_edit->setReadOnly(true);
	mp_status = new QStatusBar;
	mp_layout->addWidget(mp_edit);
	mp_layout->addWidget(mp_status);
	mp_widget->setLayout(mp_layout);
}

UnknownFile::~UnknownFile()
{
	delete mp_edit;
	delete mp_status;
	delete mp_layout;
}

bool UnknownFile::setData(uint8_t *data, size_t size, QProgressDialog *p_progress)
{
	mp_status->clearMessage();
	mp_status->showMessage(QString("Bytes total: ") + QString::number(size));

	return false;
}
