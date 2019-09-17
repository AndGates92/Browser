/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Graphics functions
 */

// Qt libraries
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QSize>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "graphics.h"

void graphics::init_graphics(int argc, char** argv) {
	QApplication app(argc, argv);

	qInfo() << "Create Application";

	QSize winSize(320,400);
	QWidget window;
	window.setWindowTitle("Test");
	window.resize(winSize);
	QLabel hello("Welcome to Qt");
	hello.setAlignment(Qt::AlignCenter);
	hello.show();
	QGridLayout layout;
	layout.addWidget(&hello, 0, 0, Qt::AlignCenter);
	window.setLayout(&layout);
	window.show();

	app.exec();
}
