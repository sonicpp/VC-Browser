#include <QtGui>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>

#include "vcbrowser.h"

VCBrowser::VCBrowser()
{
	openAction = new QAction(tr("&Open"), this);
	exitAction = new QAction(tr("E&xit"), this);

	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	treeView = new QTreeView;

	QStandardItemModel *standardModel = new QStandardItemModel;
	root = standardModel->invisibleRootItem();

	treeView->setModel(standardModel);
	treeView->expandAll();

	textEdit = new QTextEdit;

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(treeView);
	layout->addWidget(textEdit);

	central = new QWidget;
	central->setLayout(layout);

	setCentralWidget(central);

	setWindowTitle(tr("VietCong Browser"));
}

void VCBrowser::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), "", tr("CBF Files (*.cbf)"));

	if (fileName != "") {
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"),
				tr("Could not open file"));
		return;
		}

		QTextStream in(&file);
		textEdit->setText(in.readAll());

		QFileInfo fi(fileName);

		QList<QStandardItem *> rowItems;
		rowItems << new QStandardItem(fi.fileName());;
		root->appendRow(rowItems);

		file.close();
	}
}

void VCBrowser::quit()
{
	qApp->quit();
}
