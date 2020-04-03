/**
 * @copyright
 * @file main_window_tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_web_engine_page.h"
#include "main_window_tab.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabOverall, "mainWindowTab.overall", MSG_TYPE_LEVEL)

main_window_tab::MainWindowTab::MainWindowTab(QWidget * parent): tab::Tab(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "MainWindowTab constructor");

}

main_window_tab::MainWindowTab::~MainWindowTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "MainWindowTab destructor");

}
