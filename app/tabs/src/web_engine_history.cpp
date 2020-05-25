/**
 * @copyright
 * @file web_engine_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Web engine history functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "web_engine_history.h"

// Categories
Q_LOGGING_CATEGORY(webEngineHistoryOverall, "webEngineHistory.overall", MSG_TYPE_LEVEL)

web_engine_history::WebEngineHistory::WebEngineHistory(QWebEngineHistory * newHistory): history(newHistory) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineHistoryOverall,  "Web engine history constructor");

}

web_engine_history::WebEngineHistory::WebEngineHistory(const web_engine_history::WebEngineHistory & rhs) : history(rhs.history) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineHistoryOverall,  "Copy constructor web engine history");

}

web_engine_history::WebEngineHistory & web_engine_history::WebEngineHistory::operator=(const web_engine_history::WebEngineHistory & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineHistoryOverall,  "Copy assignment operator for web engine history");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	if (this->history != rhs.history) {
		this->history = rhs.history;
	}

	return *this;
}

web_engine_history::WebEngineHistory::WebEngineHistory(web_engine_history::WebEngineHistory && rhs) : history(std::exchange(rhs.history, Q_NULLPTR)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineHistoryOverall,  "Move constructor web engine history");
}

web_engine_history::WebEngineHistory & web_engine_history::WebEngineHistory::operator=(web_engine_history::WebEngineHistory && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineHistoryOverall,  "Move assignment operator for web engine history");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->history = std::exchange(rhs.history, Q_NULLPTR);
	}

	return *this;
}

web_engine_history::WebEngineHistory::~WebEngineHistory() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineHistoryOverall,  "Web engine history destructor");

}

void web_engine_history::WebEngineHistory::back() const {
	if (this->history->canGoBack()) {
		this->history->back();
	}
}

void web_engine_history::WebEngineHistory::forward() const {
	if (this->history->canGoForward()) {
		this->history->forward();
	}
}
