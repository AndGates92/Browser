/**
 * @copyright
 * @file tab_history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab history functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "logging_macros.h"
#include "tab_history.h"

// Categories
Q_LOGGING_CATEGORY(tabHistoryOverall, "tabHistory.overall", MSG_TYPE_LEVEL)

tab_history::TabHistory::TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory): tab_component_widget::TabComponentWidget<tab_shared_types::stepping_e>(parent, browserTab), history(newHistory) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabHistoryOverall,  "Tab history constructor");

}

tab_history::TabHistory::~TabHistory() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabHistoryOverall,  "Tab history destructor");

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
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabHistoryOverall,  "Unable to step across items of the history list with direcion set to " << step);
			break;
	}
}

bool tab_history::TabHistory::canProcessRequests() const {
	return false;
}
