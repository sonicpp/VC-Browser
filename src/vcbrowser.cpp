#include <QtGui>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>

#include "vcbrowser.h"
#include "cbf.h"
#include "abstractfile.h"

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
	connect(treeView->selectionModel(),
		SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
		this, SLOT(select(QItemSelection, QItemSelection)));

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
	std::ifstream *file;

	if (fileName != "") {
		file = new std::ifstream(fileName.toStdString(),
			std::ios::in | std::ios::binary);
		if (!file->is_open()) {
			QMessageBox::critical(this, tr("Error"),
				tr("File can not be opened"));
			return;
		}

		QFileInfo fi(fileName);
		QList<QStandardItem *> rowItems;
		rowItems << new QStandardItem(fi.fileName());;
		root->appendRow(rowItems);

		try {
			CBF cbf(file, rowItems.first());
		} catch (CBFException &e) {
			QMessageBox::critical(this, tr("Error"),
				tr(e.what()));
		} /* TODO catch bad_alloc */

		file->close();

		treeView->expandAll();

		delete file;
	}
}

void VCBrowser::quit()
{
	qApp->quit();
}

void VCBrowser::select(const QItemSelection & selected, const QItemSelection & deselected)
{
	QModelIndexList indexes = selected.indexes();
	foreach(const QModelIndex &index, indexes) {
		AbstractFile *f = index.data(Qt::UserRole + 1).value<AbstractFile *>();
		textEdit->setText(f->getData().c_str());
	}
}
