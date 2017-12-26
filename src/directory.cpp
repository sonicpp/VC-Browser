#include "abstractfile.h"
#include "directory.h"

Directory::Directory(QString name, AbstractFile *p_parent,
		     QStandardItem *p_item)
:AbstractFile(true, name, p_parent, p_item)
{
	mp_edit = new QTextEdit;
	mp_status = new QStatusBar;
	mp_layout = new QVBoxLayout;

	mp_edit->setReadOnly(true);

	mp_layout->addWidget(mp_edit);
	mp_layout->addWidget(mp_status);
	mp_widget->setLayout(mp_layout);
}

Directory::~Directory()
{
	delete mp_edit;
	delete mp_status;
	delete mp_layout;
}

bool Directory::setData(uint8_t *data, size_t size, QProgressDialog *p_progress)
{
	return false;
}
