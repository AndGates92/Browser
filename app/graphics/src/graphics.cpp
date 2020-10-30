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

#include "macros.h"
#include "global_enums.h"
#include "main_window_wrapper.h"
#include "graphics.h"
#include "logger.h"

// Categories
LOGGING_CONTEXT(graphicsOverall, graphics.overall, TYPE_LEVEL, INFO_VERBOSITY)

void graphics::init_graphics(int & argc, char** argv) {
	QApplication app(argc, argv);

	LOG_INFO(logger::info_level_e::ZERO, graphicsOverall,  "Create Application");

	std::unique_ptr<main_window_wrapper::MainWindowWrapper> window = std::make_unique<main_window_wrapper::MainWindowWrapper>(Q_NULLPTR, Qt::Window);
	window->show();

	app.exec();
}
