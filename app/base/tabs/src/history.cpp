/**
 * @copyright
 * @file history.cpp
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab history functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "base/tabs/include/history.h"

// Categories
LOGGING_CONTEXT(tabHistoryOverall, tabHistory.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::History::History(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, QWebEngineHistory * newHistory): app::base::tab::TabComponentWidget<app::base::tab::stepping_e>(parent, browserTab), history(newHistory) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabHistoryOverall,  "Tab history constructor");

}

app::base::tab::History::~History() {
	LOG_INFO(app::logger::info_level_e::ZERO, tabHistoryOverall,  "Tab history destructor");

}

void app::base::tab::History::back() {
	app::shared::element_position_e position = app::shared::element_position_e::UNKNOWN;
	if (this->history->canGoBack()) {
		this->history->back();
		position = app::shared::element_position_e::MIDDLE;
	} else {
		position = app::shared::element_position_e::BEGINNING;
	}

	emit this->historyItemChanged(position);
}

void app::base::tab::History::forward() {
	app::shared::element_position_e position = app::shared::element_position_e::UNKNOWN;
	if (this->history->canGoForward()) {
		this->history->forward();
		position = app::shared::element_position_e::MIDDLE;
	} else {
		position = app::shared::element_position_e::END;
	}

	emit this->historyItemChanged(position);
}

void app::base::tab::History::execute(const app::base::tab::stepping_e & step) {
	switch (step) {
		case app::base::tab::stepping_e::PREVIOUS:
			this->back();
			break;
		case app::base::tab::stepping_e::NEXT:
			this->forward();
			break;
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, tabHistoryOverall,  "Unable to step across items of the history list with direcion set to " << step);
			break;
	}
}

bool app::base::tab::History::canProcessRequests() const {
	return false;
}
