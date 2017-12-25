#include <QApplication>

#include "vcbrowser.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	VCBrowser browser;

	browser.show();

	return app.exec();
}
