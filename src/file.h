#ifndef _FILE_H
#define _FILE_H

#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QString>
#include <QProgressBar>

#include "abstractfile.h"

class UnknownFile: public AbstractFile {
public:
	UnknownFile(QString name);
	~UnknownFile();
	bool setData(uint8_t *p_data, size_t size,
		     QProgressDialog *p_progress = NULL);
private:
	size_t m_size;
	QTextEdit *mp_edit;
	QStatusBar *mp_status;
	QVBoxLayout *mp_layout;
	void redrawWidget();
};

#endif	// _FILE_H
