/**
 * @copyright
 * @file main_window_web_engine_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Web engine history functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_web_engine_history.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineHistoryOverall, "mainWindowWebEngineHistory.overall", MSG_TYPE_LEVEL)

main_window_web_engine_history::MainWindowWebEngineHistory::MainWindowWebEngineHistory(QWebEngineHistory * newHistory): web_engine_history::WebEngineHistory(newHistory) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineHistoryOverall,  "Web engine history constructor");

}

main_window_web_engine_history::MainWindowWebEngineHistory::MainWindowWebEngineHistory(const main_window_web_engine_history::MainWindowWebEngineHistory & rhs) : web_engine_history::WebEngineHistory(rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineHistoryOverall,  "Copy constructor web engine history");

}

main_window_web_engine_history::MainWindowWebEngineHistory & main_window_web_engine_history::MainWindowWebEngineHistory::operator=(const main_window_web_engine_history::MainWindowWebEngineHistory & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineHistoryOverall,  "Copy assignment operator for web engine history");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	this->web_engine_history::WebEngineHistory::operator=(rhs);

	return *this;
}

main_window_web_engine_history::MainWindowWebEngineHistory::MainWindowWebEngineHistory(main_window_web_engine_history::MainWindowWebEngineHistory && rhs) :  web_engine_history::WebEngineHistory(rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineHistoryOverall,  "Move constructor web engine history");
}

main_window_web_engine_history::MainWindowWebEngineHistory & main_window_web_engine_history::MainWindowWebEngineHistory::operator=(main_window_web_engine_history::MainWindowWebEngineHistory && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineHistoryOverall,  "Move assignment operator for web engine history");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->web_engine_history::WebEngineHistory::operator=(rhs);
	}

	return *this;
}

main_window_web_engine_history::MainWindowWebEngineHistory::~MainWindowWebEngineHistory() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineHistoryOverall,  "Web engine history destructor");

}
