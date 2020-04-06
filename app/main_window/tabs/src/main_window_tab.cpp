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
#include "main_window_tab.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabOverall, "mainWindowTab.overall", MSG_TYPE_LEVEL)

main_window_tab::MainWindowTab::MainWindowTab(const main_window_shared_types::tab_type_e type, const void * data, const void * tabContent, QWidget * parent): tab::Tab(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "MainWindowTab constructor");

	this->widgetView = new main_window_web_engine_view::MainWindowWebEngineView(type, data, tabContent, this);
	this->search = new main_window_web_engine_search::MainWindowWebEngineSearch(this, this);

}

main_window_tab::MainWindowTab::~MainWindowTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "MainWindowTab destructor");

	delete widgetView;

}
