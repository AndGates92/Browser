/**
 * @copyright
 * @file main_window_tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "main_window_tab.h"
#include "main_window_tab_scroll_manager.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabScrollManagerOverall, "mainWindowTabScrollManager.overall", MSG_TYPE_LEVEL)

main_window_tab_scroll_manager::MainWindowTabScrollManager::MainWindowTabScrollManager(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> browserTab, std::shared_ptr<tab_bar::TabBar> tabBar): tab_scroll_manager::TabScrollManager(parent, browserTab, tabBar) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabScrollManagerOverall,  "MainWindowTabScrollManager constructor");

}

main_window_tab_scroll_manager::MainWindowTabScrollManager::~MainWindowTabScrollManager() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabScrollManagerOverall,  "MainWindowTabScrollManager destructor");

}

CASTED_SHARED_PTR_GETTER(main_window_tab_scroll_manager::MainWindowTabScrollManager::getTab, main_window_tab::MainWindowTab, tab_scroll_manager::TabScrollManager::getTab())
