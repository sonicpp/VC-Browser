#ifndef _ABSTRACTFILE_H
#define _ABSTRACTFILE_H

#include <vector>
#include <QWidget>
#include <QStandardItem>
#include <QProgressDialog>

class AbstractFile {
private:
	bool m_dir;
	bool m_ext_item;
	void addFile(AbstractFile *p_file);
protected:
	bool m_compressed;
	QString m_name;
	QWidget *mp_widget;
	QStandardItem *mp_item;
	AbstractFile *mp_parent;
	std::vector<AbstractFile *> mp_children;
public:
	static AbstractFile *createFile(QString name);
	static AbstractFile *createDirectory(QString name, QStandardItem *p_item = NULL);
	AbstractFile(bool dir, QString name, QStandardItem *p_item = NULL);
	virtual ~AbstractFile();
	virtual bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL) = 0;
	virtual bool addFile(AbstractFile *p_file, QString name);
	virtual void newFileNotify(bool dir);
	bool isDir();
	void setCompressed(bool compressed);
	bool isCompressed();
	QString getName();
	QWidget *getWidget();
	QStandardItem *getItem();
	void setParent(AbstractFile *p_parent);
	uint32_t getDirCnt();
	uint32_t getFileCnt();
};

Q_DECLARE_METATYPE(AbstractFile *)

#endif
