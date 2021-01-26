/**
 * @copyright
 * @file init.cpp
 * @author Andrea Gianarda
 * @date 11th of November 2020
 * @brief Initialization functions of the program
 */
#include <memory>

// Qt libraries
#include <QtWidgets/QApplication>

#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/windows/main_window/window/wrapper.h"
#include "app/top/init.h"
#include "app/settings/global.h"

// Categories
LOGGING_CONTEXT(initGraphicsOverall, init.graphics.overall, TYPE_LEVEL, INFO_VERBOSITY)

void app::init::initializeSettings(int & argc, char** argv) {
	app::settings::Global::getInstance()->initialize(argc, argv);
}

void app::init::initializeGraphics(int & argc, char** argv) {
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(true);

	LOG_INFO(app::logger::info_level_e::ZERO, initGraphicsOverall, "Create Application");

	std::unique_ptr<app::main_window::window::Wrapper> window = std::make_unique<app::main_window::window::Wrapper>(Q_NULLPTR, Qt::Window);
	window->show();

	app.exec();
}

void app::init::initializeBrowser(int & argc, char** argv) {
	app::init::initializeSettings(argc, argv);
	app::init::initializeGraphics(argc, argv);
}
