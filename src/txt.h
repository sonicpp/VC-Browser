#ifndef _TXT_H
#define _TXT_H

#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include "abstractfile.h"

class TXT: public AbstractFile {
private:
	QString m_str;
	QTextCodec *m_codec;
	QTextEdit *m_edit;
	QStatusBar *m_status;
	QVBoxLayout *m_layout;
public:
	TXT(QString name, AbstractFile *p_parent);
	bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL);
};

#endif
