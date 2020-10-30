/**
 * @copyright
 * @file tab_search.cpp
 * @author Andrea Gianarda
 * @date 02nd April 2020
 * @brief Tab search functions
 */

#include <QtWidgets/QMessageBox>

// Qt libraries
#include <QtGui/QKeyEvent>

#include "macros.h"
#include "tab_search.h"
#include "exception_macros.h"

// Categories
LOGGING_CONTEXT(tabSearchOverall, tabSearch.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabSearchFind, tabSearch.find, TYPE_LEVEL, INFO_VERBOSITY)

tab_search::TabSearch::TabSearch(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab): tab_component_widget::TabComponentWidget<find_settings::FindSettings>(parent, attachedTab), settings(QString(), global_enums::offset_type_e::IDLE, false, false), callback(nullptr) {
	LOG_INFO(logger::info_level_e::ZERO, tabSearchOverall,  "Tab search constructor");
}

tab_search::TabSearch::~TabSearch() {
	LOG_INFO(logger::info_level_e::ZERO, tabSearchOverall,  "Tab search destructor");

}

void tab_search::TabSearch::execute(const find_settings::FindSettings & newSettings) {

	this->settings = newSettings;
	this->setCallback();

	this->search();
}

void tab_search::TabSearch::search() {

	if (this->canProcessRequests() == true) {
		try {
			std::shared_ptr<tab::Tab> currentTab = this->getTab();
			std::shared_ptr<web_engine_page::WebEnginePage> currentTabPage = currentTab->getPage();

			const QString text = this->settings.getText();
			const bool caseSensitive = this->settings.getCaseSensitive();
			const global_enums::offset_type_e direction = this->settings.getDirection();

			EXCEPTION_ACTION_COND(((direction != global_enums::offset_type_e::DOWN) && (direction != global_enums::offset_type_e::UP)), throw, "Unable to perform search with direction set to " << direction);

			// No flag set by default
			// Available search flags are:
			// - QWebEnginePage::FindBackward
			// - QWebEnginePage::FindCaseSensitively
			QWebEnginePage::FindFlags flags = QWebEnginePage::FindFlag(0);
			if (direction == global_enums::offset_type_e::UP) {
				flags |= QWebEnginePage::FindBackward;
			} else {
				flags &= ~QWebEnginePage::FindBackward;
			}
			if (caseSensitive == true) {
				flags |= QWebEnginePage::FindCaseSensitively;
			} else {
				flags &= ~QWebEnginePage::FindCaseSensitively;
			}

			currentTabPage->findText(text, flags,
				[=](bool found) {
					if (this->callback) {
						this->callback(found);
					}
				}
			);
		} catch (const std::bad_cast & badCastE) {
			EXCEPTION_ACTION(throw, badCastE.what());
		}

	} else {
		this->pushRequestQueue(this->settings);
	}
}

bool tab_search::TabSearch::canProcessRequests() const {
	const std::shared_ptr<tab::Tab> currentTab = this->getTab();
	const tab_shared_types::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	return ((loadManagerStatus == tab_shared_types::load_status_e::FINISHED) || (loadManagerStatus == tab_shared_types::load_status_e::ERROR));
}

void tab_search::TabSearch::setCallback() {

	this->callback = nullptr;

}
