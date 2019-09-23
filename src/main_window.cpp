/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QLoggingCategory>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)

main_window::MainWindow() {

	QWidget * mainWidget = new QWidget();
	setCentralWidget(mainWidget);

}
