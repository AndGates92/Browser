/**
 * @copyright
 * @file main_window_tab_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main window tab search functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_tab_search.h"
#include "main_window_web_engine_view.h"
#include "main_window_tab.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabSearchOverall, "mainWindowTabSearch.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabSearchFind, "mainWindowTabSearch.find", MSG_TYPE_LEVEL)

main_window_tab_search::MainWindowTabSearch::MainWindowTabSearch(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> attachedTab): tab_search::TabSearch(parent, attachedTab) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabSearchOverall,  "Tab search constructor");

}

main_window_tab_search::MainWindowTabSearch::~MainWindowTabSearch() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabSearchOverall,  "Tab search destructor");

}

