/**
 * @copyright
 * @file main_window_tab_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Main window tab history functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_tab_history.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabHistoryOverall, "mainWindowTabHistory.overall", MSG_TYPE_LEVEL)

main_window_tab_history::MainWindowTabHistory::MainWindowTabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory): tab_history::TabHistory(parent, browserTab, newHistory) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history constructor");

}

main_window_tab_history::MainWindowTabHistory::~MainWindowTabHistory() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history destructor");

}
