/**
 * @copyright
 * @file history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Main window tab history functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/history.h"

// Categories
LOGGING_CONTEXT(mainWindowTabHistoryOverall, mainWindowTabHistory.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::History::History(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, QWebEngineHistory * newHistory): app::base::tab::History(parent, browserTab, newHistory) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history constructor");

}

app::main_window::tab::History::~History() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabHistoryOverall,  "Main window tab history destructor");

}
