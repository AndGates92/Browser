/**
 * @copyright
 * @file main_window_tab_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Main window tab history functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "macros.h"
#include "main_window_tab_history.h"

// Categories
LOGGING_CONTEXT(mainWindowTabHistoryOverall, mainWindowTabHistory.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_tab_history::MainWindowTabHistory::MainWindowTabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory): tab_history::TabHistory(parent, browserTab, newHistory) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history constructor");

}

main_window_tab_history::MainWindowTabHistory::~MainWindowTabHistory() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history destructor");

}
