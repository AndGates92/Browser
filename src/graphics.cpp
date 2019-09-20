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
#include <qt5/QtCore/QLoggingCategory>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "global_macros.h"
#include "graphics.h"


// Categories
Q_LOGGING_CATEGORY(graphicsOverall, "graphics.overall", MSG_TYPE_LEVEL)

void graphics::init_graphics(int argc, char** argv) {
	QApplication app(argc, argv);

	qInfo(graphicsOverall) << "Create Application";
	qDebug(graphicsOverall) << "graphics dont print me ";
	qDebug() << "Dont print me";

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
