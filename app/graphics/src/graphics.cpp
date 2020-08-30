/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Graphics functions
 */

#include <memory>

// Qt libraries
#include <QtWidgets/QApplication>

// Required by qInfo
#include <QtCore/QtDebug>

#include "logging_macros.h"
#include "global_enums.h"
#include "main_window_wrapper.h"
#include "graphics.h"


// Categories
Q_LOGGING_CATEGORY(graphicsOverall, "graphics.overall", MSG_TYPE_LEVEL)

void graphics::init_graphics(int & argc, char** argv) {
	QApplication app(argc, argv);

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, graphicsOverall,  "Create Application");

	std::unique_ptr<main_window_wrapper::MainWindowWrapper> window = std::make_unique<main_window_wrapper::MainWindowWrapper>(Q_NULLPTR, Qt::Window);
	window->show();

	app.exec();
}
