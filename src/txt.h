#ifndef _TXT_H
#define _TXT_H

#include <QString>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QProgressBar>

#include "abstractfile.h"

class TXT: public AbstractFile {
public:
	TXT(QString name);
	~TXT();
	bool setData(uint8_t *p_data, size_t size,
		     QProgressDialog *p_progress = NULL);
private:
	QString m_str;
	QTextCodec *mp_codec;
	QTextEdit *mp_edit;
	QStatusBar *mp_status;
	QVBoxLayout *mp_layout;
	void redrawWidget();
};

#endif	// _TXT_H
