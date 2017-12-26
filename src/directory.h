#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include "abstractfile.h"

class Directory: public AbstractFile {
protected:
	QTextEdit *mp_edit;
	QStatusBar *mp_status;
	QVBoxLayout *mp_layout;
public:
	Directory(QString name, QStandardItem *p_item = NULL);
	~Directory();
	bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL);
	bool addFile(AbstractFile *p_file, QString name);
	void newFileNotify(bool dir);
};

#endif
