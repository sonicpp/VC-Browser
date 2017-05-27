#ifndef _VCBROWSER_H_
#define _VCBROWSER_H_

#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QTreeView>
#include <QStandardItem>

class VCBrowser: public QMainWindow
{
	Q_OBJECT
public:
	VCBrowser();
private slots:
	void open();
	void quit();
private:
	QWidget *central;
	QTreeView *treeView;
	QStandardItem *root;
	QTextEdit *textEdit;
	QMenu *fileMenu;
	QAction *openAction;
	QAction *exitAction;
};

#endif
