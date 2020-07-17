/**
 * @copyright
 * @file tab_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab search functions
 */

#include <qt5/QtWidgets/QMessageBox>

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "tab.h"
#include "tab_search.h"
#include "web_engine_view.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(tabSearchOverall, "tabSearch.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabSearchFind, "tabSearch.find", MSG_TYPE_LEVEL)

tab_search::TabSearch::TabSearch(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab): tab_component_widget::TabComponentWidget<find_settings::FindSettings>(parent, attachedTab), settings(QString::null, global_enums::offset_type_e::IDLE, false, false) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search constructor");
}

tab_search::TabSearch::~TabSearch() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search destructor");

}

void tab_search::TabSearch::find(const find_settings::FindSettings & newSettings, std::function<void(bool)> cb) {

	this->settings = newSettings;
	this->callback = cb;

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

			QEXCEPTION_ACTION_COND(((direction != global_enums::offset_type_e::DOWN) && (direction != global_enums::offset_type_e::UP)), throw, "Unable to perform search with direction set to " << direction);

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
			QEXCEPTION_ACTION(throw, badCastE.what());
		}

		this->popRequestQueue();

	} else {
		this->pushRequestQueue(this->settings);
	}
}

bool tab_search::TabSearch::canProcessRequests() const {
	const std::shared_ptr<tab::Tab> currentTab = this->getTab();
	const tab_shared_types::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	return ((loadManagerStatus == tab_shared_types::load_status_e::FINISHED) || (loadManagerStatus == tab_shared_types::load_status_e::ERROR));
}

void tab_search::TabSearch::pushRequestQueue(const find_settings::FindSettings & newSettings) {
	this->requestQueue.push(newSettings);
}

void tab_search::TabSearch::popRequestQueue() {
	const std::shared_ptr<tab::Tab> currentTab = this->getTab();
	const tab_shared_types::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	QEXCEPTION_ACTION_COND((this->canProcessRequests() == false), throw,  "Function " << __func__ << " cannot be called when load manager is in state " << loadManagerStatus << ". It can only be called if a page is not loading");

	if ((this->requestQueue.empty() == false) && (this->canProcessRequests() == true)) {
		const find_settings::FindSettings & currentSettings = this->requestQueue.front();

		this->find(currentSettings, nullptr);

		this->requestQueue.pop();
	}
}
