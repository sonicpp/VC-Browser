#include "abstractfile.h"
#include "directory.h"

Directory::Directory(QString name, AbstractFile *p_parent,
		     QStandardItem *p_item)
:AbstractFile(true, name, p_parent, p_item)
{
	m_edit = new QTextEdit;
	m_status = new QStatusBar;
	m_layout = new QVBoxLayout;

	m_edit->setReadOnly(true);

	m_layout->addWidget(m_edit);
	m_layout->addWidget(m_status);
	mp_widget->setLayout(m_layout);
}

bool Directory::setData(std::ifstream *p_file, QProgressDialog *p_progress)
{
	return false;
}

bool Directory::setData(uint8_t *data, size_t size, QProgressDialog *p_progress)
{
	return false;
}
