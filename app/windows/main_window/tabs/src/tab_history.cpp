/**
 * @copyright
 * @file tab_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Main window tab history functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/tab_history.h"

// Categories
LOGGING_CONTEXT(mainWindowTabHistoryOverall, mainWindowTabHistory.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::TabHistory::TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory): tab_history::TabHistory(parent, browserTab, newHistory) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history constructor");

}

main_window::TabHistory::~TabHistory() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history destructor");

}
