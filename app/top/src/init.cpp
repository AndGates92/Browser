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

#include "macros.h"
#include "global_enums.h"
#include "main_window_wrapper.h"
#include "init.h"
#include "browser_settings.h"

// Categories
LOGGING_CONTEXT(initGraphicsOverall, init.graphics.overall, TYPE_LEVEL, INFO_VERBOSITY)

void init::initializeSettings(int & argc, char** argv) {
	browser_settings::BrowserSettings::getInstance()->initialize(argc, argv);
}

void init::initializeGraphics(int & argc, char** argv) {
	QApplication app(argc, argv);

	LOG_INFO(logger::info_level_e::ZERO, initGraphicsOverall,  "Create Application");

	std::unique_ptr<main_window_wrapper::MainWindowWrapper> window = std::make_unique<main_window_wrapper::MainWindowWrapper>(Q_NULLPTR, Qt::Window);
	window->show();

	app.exec();
}

void init::initializeBrowser(int & argc, char** argv) {
	init::initializeSettings(argc, argv);
	init::initializeGraphics(argc, argv);
}
