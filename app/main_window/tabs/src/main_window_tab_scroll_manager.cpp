/**
 * @copyright
 * @file main_window_tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_tab_scroll_manager.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabScrollManagerOverall, "mainWindowTabScrollManager.overall", MSG_TYPE_LEVEL)

main_window_tab_scroll_manager::MainWindowTabScrollManager::MainWindowTabScrollManager(QWidget * parent, QWidget * tabBar): tab_scroll_manager::TabScrollManager(parent, tabBar) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabScrollManagerOverall,  "MainWindowTabScrollManager constructor");

}

main_window_tab_scroll_manager::MainWindowTabScrollManager::~MainWindowTabScrollManager() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabScrollManagerOverall,  "MainWindowTabScrollManager destructor");

}
