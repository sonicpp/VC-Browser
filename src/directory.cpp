#include "directory.h"

Directory::Directory(QString name, QStandardItem *p_item)
:AbstractFile(true, name, p_item)
{
	mp_edit = new QTextEdit;
	mp_status = new QStatusBar;
	mp_layout = new QVBoxLayout;

	mp_edit->setReadOnly(true);

	mp_layout->addWidget(mp_edit);
	mp_layout->addWidget(mp_status);
	mp_widget->setLayout(mp_layout);

	redrawWidget();
}

Directory::~Directory()
{
	delete mp_edit;
	delete mp_status;
	delete mp_layout;
}

bool Directory::setData(uint8_t *p_data, size_t size,
			QProgressDialog *p_progress)
{
	return false;
}

bool Directory::addFile(AbstractFile *p_file, QString name)
{
	bool ret;

	ret = AbstractFile::addFile(p_file, name);
	if (ret) {
		redrawWidget();
	}

	return ret;
}

void Directory::newFileNotify(bool dir)
{
	AbstractFile::newFileNotify(dir);
	redrawWidget();
}

void Directory::redrawWidget(void)
{
	mp_status->clearMessage();
	mp_status->showMessage(QString("Subdirectories : ") +
			       QString::number(getDirCnt()) +
			       QString("; files: ") +
			       QString::number(getFileCnt()));
}
