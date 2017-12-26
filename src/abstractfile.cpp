#include "directory.h"
#include "cbf.h"
#include "txt.h"
#include "file.h"
#include "abstractfile.h"

AbstractFile *AbstractFile::createFile(QString name)
{
	AbstractFile *file = NULL;
	std::string nm = name.toStdString();

	if (nm.substr(nm.find_last_of(".") + 1)== "TXT")
		file = new TXT(name);
	else if (nm.substr(nm.find_last_of(".") + 1) == "cbf")
		file = new CBF(name);
	else
		file = new UnknownFile(name);

	return file;
}

AbstractFile *AbstractFile::createDirectory(QString name, QStandardItem *p_item)
{
	AbstractFile *p_file = new Directory(name, p_item);

	return p_file;
}

AbstractFile::AbstractFile(bool dir, QString name, QStandardItem *p_item)
:m_dir(dir), m_name(name), mp_parent(NULL)
{
	mp_widget = new QWidget();

	if (p_item == NULL) {
		mp_item = new QStandardItem(name);
		m_ext_item = false;
	}
	else {
		mp_item = p_item;
		m_ext_item = true;
	}

	mp_item->setData(QVariant::fromValue(this));
}

AbstractFile::~AbstractFile()
{
	AbstractFile *p_child;

	while (!mp_children.empty()) {
		p_child = mp_children.back();
		mp_children.pop_back();
		delete p_child;
	}

	delete mp_widget;
	if (!m_ext_item)
		delete mp_item;
}

void AbstractFile::newFileNotify(bool dir)
{
	if (mp_parent)
		mp_parent->newFileNotify(dir);
}

void AbstractFile::addFile(AbstractFile *p_file)
{
	mp_children.push_back(p_file);
	mp_item->appendRow(p_file->getItem());
	p_file->setParent(this);
	newFileNotify(p_file->isDir());
}

bool AbstractFile::addFile(AbstractFile *p_file, QString name)
{
	QStringList path = name.split('\\');
	QString suffix;
	AbstractFile *p_child = NULL;

	if (!isDir())
		return false;

	/* Check if new item already exist */
	for (int i = 0; i < mp_children.size(); i++) {
		if (mp_children[i]->getName() == path[0])
			p_child = mp_children[i];
	}

	/* Add file to current directory*/
	if (path.size() == 1) {
		/* File (or directory) with this name already exist */
		if (p_child != NULL)
			return false;
		addFile(p_file);
		return true;
	}
	/* Add file to sub directory */
	else
	{
		/* Sub directory does not exist yet */
		if (p_child == NULL) {
			p_child = createDirectory(path[0]);
			addFile(p_child);
		}
		for (int i = 1; i < path.size() - 1; i++)
			suffix += path[i] + QString('\\');
		suffix += path[path.size() - 1];
		return p_child->addFile(p_file, suffix);
	}
}

bool AbstractFile::isDir()
{
	return m_dir;
}

void AbstractFile::setCompressed(bool compressed)
{
	m_compressed = compressed;
}

bool AbstractFile::isCompressed()
{
	return m_compressed;
}

QString AbstractFile::getName()
{
	return m_name;
}

QWidget *AbstractFile::getWidget()
{
	return mp_widget;
}

QStandardItem *AbstractFile::getItem()
{
	return mp_item;
}

void AbstractFile::setParent(AbstractFile *p_parent)
{
	mp_parent = p_parent;
}

uint32_t AbstractFile::getDirCnt()
{
	uint32_t res = 0;

	if (m_dir) {
		for (int i = 0; i < mp_children.size(); i++) {
			if (mp_children[i]->isDir())
				res += mp_children[i]->getDirCnt() + 1u;
		}
	}

	return res;
}

uint32_t AbstractFile::getFileCnt()
{
	uint32_t res = 0;

	if (m_dir) {
		for (int i = 0; i < mp_children.size(); i++) {
			if (mp_children[i]->isDir())
				res += mp_children[i]->getFileCnt();
			else
				res += 1u;
		}
	}

	return res;
}
