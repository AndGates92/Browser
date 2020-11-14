/**
 * @copyright
 * @file tab_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab history functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "base/tabs/include/tab_history.h"

// Categories
LOGGING_CONTEXT(tabHistoryOverall, tabHistory.overall, TYPE_LEVEL, INFO_VERBOSITY)

tab_history::TabHistory::TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory): tab_component_widget::TabComponentWidget<tab_shared_types::stepping_e>(parent, browserTab), history(newHistory) {
	LOG_INFO(logger::info_level_e::ZERO, tabHistoryOverall,  "Tab history constructor");

}

tab_history::TabHistory::~TabHistory() {
	LOG_INFO(logger::info_level_e::ZERO, tabHistoryOverall,  "Tab history destructor");

}

void tab_history::TabHistory::back() {
	global_enums::element_position_e position = global_enums::element_position_e::UNKNOWN;
	if (this->history->canGoBack()) {
		this->history->back();
		position = global_enums::element_position_e::MIDDLE;
	} else {
		position = global_enums::element_position_e::BEGINNING;
	}

	emit this->historyItemChanged(position);
}

void tab_history::TabHistory::forward() {
	global_enums::element_position_e position = global_enums::element_position_e::UNKNOWN;
	if (this->history->canGoForward()) {
		this->history->forward();
		position = global_enums::element_position_e::MIDDLE;
	} else {
		position = global_enums::element_position_e::END;
	}

	emit this->historyItemChanged(position);
}

void tab_history::TabHistory::execute(const tab_shared_types::stepping_e & step) {
	switch (step) {
		case tab_shared_types::stepping_e::PREVIOUS:
			this->back();
			break;
		case tab_shared_types::stepping_e::NEXT:
			this->forward();
			break;
		default:
			LOG_INFO(logger::info_level_e::ZERO, tabHistoryOverall,  "Unable to step across items of the history list with direcion set to " << step);
			break;
	}
}

bool tab_history::TabHistory::canProcessRequests() const {
	return false;
}
