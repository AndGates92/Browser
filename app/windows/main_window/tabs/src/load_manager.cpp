/**
 * @copyright
 * @file load_manager.cpp
 * @author Andrea Gianarda
 * @date 09th April 2020
 * @brief Main Window Tab Load Manager functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/load_manager.h"

// Categories
LOGGING_CONTEXT(mainWindowTabLoadManagerOverall, mainWindowTabLoadManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::LoadManager::LoadManager(QWidget * parent): app::base::tab::LoadManager(parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabLoadManagerOverall,  "LoadManager constructor");

}

app::main_window::tab::LoadManager::~LoadManager() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabLoadManagerOverall,  "LoadManager destructor");

}
