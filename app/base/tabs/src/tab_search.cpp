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

tab_search::TabSearch::TabSearch(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab): tab_component_widget::TabComponentWidget<QWebEnginePage::FindFlags>(parent, attachedTab), text(QString::null), flags(QWebEnginePage::FindFlag(0)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search constructor");
}

tab_search::TabSearch::~TabSearch() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search destructor");

}

void tab_search::TabSearch::find(const tab_shared_types::stepping_e step, const QString & searchText, const bool & reverse, const bool & caseSensitive, std::function<void(bool)> cb) {

	switch (step) {
		case tab_shared_types::stepping_e::PREVIOUS:
			// Set backward flag to 1 while keeping the other flags to the same value
			this->flags |= QWebEnginePage::FindBackward;
			break;
		case tab_shared_types::stepping_e::NEXT:
			// Set backward flag to 0 while keeping the other flags to the same value
			this->flags &= ~QWebEnginePage::FindBackward;
			break;
		case tab_shared_types::stepping_e::ITEM:
			this->text = searchText;

			// No flag set by default
			// Available search flags are:
			// - QWebEnginePage::FindBackward
			// - QWebEnginePage::FindCaseSensitively
			this->flags = QWebEnginePage::FindFlag(0);
			if (reverse == true) {
				this->flags |= QWebEnginePage::FindBackward;
			}
			if (caseSensitive == true) {
				this->flags |= QWebEnginePage::FindCaseSensitively;
			}

			this->callback = cb;
			break;
		default:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Unable to set up a search when stepping is set to " << step);
			break;
	}

	this->search();
}

void tab_search::TabSearch::search() {

	if (this->canProcessRequests() == true) {
		try {
			std::shared_ptr<tab::Tab> currentTab = this->getTab();
			std::shared_ptr<web_engine_page::WebEnginePage> currentTabPage = currentTab->getPage();

			currentTabPage->findText(this->text, this->flags,
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
		this->pushRequestQueue(this->flags);
	}
}

void tab_search::TabSearch::findNext() {
	// Set backward flag to 0 while keeping the other flags to the same value
	this->flags &= ~QWebEnginePage::FindBackward;

	this->search();
}

void tab_search::TabSearch::findPrev() {
	// Set backward flag to 1 while keeping the other flags to the same value
	this->flags |= QWebEnginePage::FindBackward;

	this->search();
}

bool tab_search::TabSearch::canProcessRequests() const {
	const std::shared_ptr<tab::Tab> currentTab = this->getTab();
	const tab_shared_types::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	return ((loadManagerStatus == tab_shared_types::load_status_e::FINISHED) || (loadManagerStatus == tab_shared_types::load_status_e::ERROR));
}

void tab_search::TabSearch::pushRequestQueue(const QWebEnginePage::FindFlags & direction) {
	this->requestQueue.push(direction);
}

void tab_search::TabSearch::popRequestQueue() {
	const std::shared_ptr<tab::Tab> currentTab = this->getTab();
	const tab_shared_types::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	QEXCEPTION_ACTION_COND((this->canProcessRequests() == false), throw,  "Function " << __func__ << " cannot be called when load manager is in state " << loadManagerStatus << ". It can only be called if a page is not loading");

	if ((this->requestQueue.empty() == false) && (this->canProcessRequests() == true)) {
		QWebEnginePage::FindFlags searchFlag = this->requestQueue.front();

		bool reverseSearch = (searchFlag & QWebEnginePage::FindBackward);
		bool caseSensitive = (searchFlag & QWebEnginePage::FindCaseSensitively);

		this->find(tab_shared_types::stepping_e::ITEM, this->text, reverseSearch, caseSensitive, nullptr);

		this->requestQueue.pop();
	}
}
