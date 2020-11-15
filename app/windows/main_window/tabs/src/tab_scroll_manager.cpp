/**
 * @copyright
 * @file tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "windows/main_window/tabs/include/tab.h"
#include "windows/main_window/tabs/include/tab_scroll_manager.h"

// Categories
LOGGING_CONTEXT(mainWindowTabScrollManagerOverall, mainWindowTabScrollManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::TabScrollManager::TabScrollManager(QWidget * parent, std::weak_ptr<main_window::Tab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar): tab_scroll_manager::TabScrollManager(parent, browserTab, tabBar) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabScrollManagerOverall,  "TabScrollManager constructor");

}

main_window::TabScrollManager::~TabScrollManager() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabScrollManagerOverall,  "TabScrollManager destructor");

}

CASTED_SHARED_PTR_GETTER(main_window::TabScrollManager::getTab, main_window::Tab, tab_scroll_manager::TabScrollManager::getTab())
