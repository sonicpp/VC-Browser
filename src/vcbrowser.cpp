#include <fstream>
#include <QtGui>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>

#include "abstractfile.h"
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
	root_item = standardModel->invisibleRootItem();

	root_file = AbstractFile::createDirectory(QString("root"), NULL, root_item);
	treeView->setModel(standardModel);
	treeView->expandAll();
	connect(treeView->selectionModel(),
		SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
		this, SLOT(select(QItemSelection, QItemSelection)));

	file = new QStackedWidget;
	edit = new QTextEdit;
	file->addWidget(edit);
	file->setCurrentWidget(edit);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(treeView);
	layout->addWidget(file);

	central = new QWidget;
	central->setLayout(layout);

	setCentralWidget(central);

	setWindowTitle(tr("VietCong Browser"));

	progress = new QProgressDialog(this);
	progress->setModal(true);
	progress->setMinimumDuration(500);
	progress->reset();
}

void VCBrowser::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), "", tr("CBF Files (*.cbf)"));
	std::ifstream *file;
	AbstractFile *af;
	QStringList path = fileName.split('\\');

	if (fileName != "") {
		file = new std::ifstream(fileName.toStdString(),
			std::ios::in | std::ios::binary);
		if (!file->is_open()) {
			QMessageBox::critical(this, tr("Error"),
				tr("File can not be opened"));
			return;
		}

		progress->setLabelText(QString("Opening file:\n") + fileName);
		af = AbstractFile::createFile(path[path.size() - 1], root_file, file, progress);
		if (progress->wasCanceled())
			delete af;
		else
			root_file->addFile(af, fileName);
		progress->reset();
#if 0
		QFileInfo fi(fileName);
		//try {
			af = Directory::addFile(fi.fileName(), root);
		/*} catch (CBFException &e) {
			QMessageBox::critical(this, tr("Error"),
				tr(e.what()));
		} *//* TODO catch bad_alloc */
#endif
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
		if (file->indexOf(f->getWidget()) == -1)
			file->addWidget(f->getWidget());
		file->setCurrentWidget(f->getWidget());
	}
}
