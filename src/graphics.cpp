/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Graphics functions
 */

// Qt libraries
#include <qt5/QtWidgets/QApplication>
//#include <qt5/QtWidgets/QPushButton>
//#include <qt5/QtWidgets/QGridLayout>
//#include <qt5/QtWidgets/QLabel>
//#include <qt5/QtWidgets/QWidget>
//#include <qt5/QtCore/QSize>
#include <qt5/QtCore/QLoggingCategory>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"
#include "graphics.h"


// Categories
Q_LOGGING_CATEGORY(graphicsOverall, "graphics.overall", MSG_TYPE_LEVEL)

void graphics::init_graphics(int argc, char** argv) {
	QApplication app(argc, argv);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, graphicsOverall,  "Create Application");

	main_window::MainWindow window;
	window.show();

	app.exec();
}
