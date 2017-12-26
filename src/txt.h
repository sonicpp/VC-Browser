#ifndef _TXT_H
#define _TXT_H

#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include "abstractfile.h"

class TXT: public AbstractFile {
private:
	QString m_str;
	QTextCodec *mp_codec;
	QTextEdit *mp_edit;
	QStatusBar *mp_status;
	QVBoxLayout *mp_layout;
public:
	TXT(QString name);
	~TXT();
	bool setData(uint8_t *data, size_t size, QProgressDialog *p_progress = NULL);
};

#endif
