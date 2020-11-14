/**
 * @copyright
 * @file main_window_tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "windows/main_window/tabs/include/main_window_tab.h"
#include "windows/main_window/tabs/include/main_window_tab_scroll_manager.h"

// Categories
LOGGING_CONTEXT(mainWindowTabScrollManagerOverall, mainWindowTabScrollManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_tab_scroll_manager::MainWindowTabScrollManager::MainWindowTabScrollManager(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar): tab_scroll_manager::TabScrollManager(parent, browserTab, tabBar) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabScrollManagerOverall,  "MainWindowTabScrollManager constructor");

}

main_window_tab_scroll_manager::MainWindowTabScrollManager::~MainWindowTabScrollManager() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabScrollManagerOverall,  "MainWindowTabScrollManager destructor");

}

CASTED_SHARED_PTR_GETTER(main_window_tab_scroll_manager::MainWindowTabScrollManager::getTab, main_window_tab::MainWindowTab, tab_scroll_manager::TabScrollManager::getTab())
