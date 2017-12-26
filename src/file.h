#ifndef _FILE_H
#define _FILE_H

#include <string>
#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include "abstractfile.h"

class UnknownFile: public AbstractFile {
private:
	QTextEdit *mp_edit;
	QStatusBar *mp_status;
	QVBoxLayout *mp_layout;
public:
	UnknownFile(QString name, AbstractFile *p_parent);
	~UnknownFile();
	bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL);
};

#endif
