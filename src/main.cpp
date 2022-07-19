#include "src/dndk.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWidgets>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	DNDK window;
	window.initialize();
	window.show();

	// finally run
	auto res = app.exec(); // blocking function until GUI closes

	return res;
}
