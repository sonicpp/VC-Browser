#ifndef _ABSTRACTFILE_H
#define _ABSTRACTFILE_H

#include <vector>
#include <QWidget>
#include <QStandardItem>
#include <QProgressDialog>

class AbstractFile {
private:
	bool m_dir;
protected:
	bool m_compressed;
	QString m_name;
	QWidget *mp_widget;
	QStandardItem *mp_item;
	AbstractFile *mp_parent;
	std::vector<AbstractFile *> mp_children;
public:
	static AbstractFile *createFile(QString name, AbstractFile *p_parent);
	static AbstractFile *createDirectory(QString name,
		AbstractFile *p_parent, QStandardItem *p_item = NULL);
	AbstractFile(bool dir, QString name, AbstractFile *p_parent,
		     QStandardItem *p_item = NULL);
	~AbstractFile();
	virtual bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL) = 0;
	bool addFile(AbstractFile *p_file, QString name);
	bool isDir();
	void setCompressed(bool compressed);
	bool isCompressed();
	QString getName();
	QWidget *getWidget();
	QStandardItem *getItem();
};

Q_DECLARE_METATYPE(AbstractFile *)

#endif
