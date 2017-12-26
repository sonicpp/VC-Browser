#ifndef _VCBROWSER_H_
#define _VCBROWSER_H_

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenu>
#include <QTreeView>
#include <QTextEdit>
#include <QStandardItem>
#include <QProgressDialog>

#include "abstractfile.h"

class VCBrowser: public QMainWindow
{
	Q_OBJECT
public:
	VCBrowser();
	~VCBrowser();
private slots:
	void open();
	void quit();
	void select(const QItemSelection & selected, const QItemSelection & deselected);
private:
	QWidget *central;
	QTreeView *treeView;
	QStandardItem *root_item;
	AbstractFile *root_file;
	QStackedWidget *file;
	QTextEdit *edit;
	QProgressDialog *progress;
	QMenu *fileMenu;
	QAction *openAction;
	QAction *exitAction;
	void expandItem(QStandardItem *p_base);
};

#endif
