#ifndef _TXT_H
#define _TXT_H

#include <string>

#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>

#include "abstractfile.h"

class TXT: public AbstractFile{
private:
	QString m_str;
	QWidget *m_widget;
	QTextCodec *m_codec;
	QTextEdit *m_edit;
	QStatusBar *m_status;
	QVBoxLayout *m_layout;
public:
	TXT(std::string name);
	virtual void setData(uint8_t *data, size_t size);
	virtual QWidget *getWidget();
};

#endif
