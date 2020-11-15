/**
 * @copyright
 * @file tab_load_manager.cpp
 * @author Andrea Gianarda
 * @date 09th April 2020
 * @brief Main Window Tab Load Manager functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/tab_load_manager.h"

// Categories
LOGGING_CONTEXT(mainWindowTabLoadManagerOverall, mainWindowTabLoadManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::TabLoadManager::TabLoadManager(QWidget * parent): tab_load_manager::TabLoadManager(parent) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabLoadManagerOverall,  "TabLoadManager constructor");

}

main_window::TabLoadManager::~TabLoadManager() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabLoadManagerOverall,  "TabLoadManager destructor");

}
