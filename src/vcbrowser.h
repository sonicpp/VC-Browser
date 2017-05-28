#ifndef _VCBROWSER_H_
#define _VCBROWSER_H_

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenu>
#include <QTreeView>
#include <QTextEdit>
#include <QStandardItem>

class VCBrowser: public QMainWindow
{
	Q_OBJECT
public:
	VCBrowser();
private slots:
	void open();
	void quit();
	void select(const QItemSelection & selected, const QItemSelection & deselected);
private:
	QWidget *central;
	QTreeView *treeView;
	QStandardItem *root;
	QStackedWidget *file;
	QTextEdit *edit;
	QMenu *fileMenu;
	QAction *openAction;
	QAction *exitAction;
};

#endif
