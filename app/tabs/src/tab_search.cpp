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

tab_search::TabSearch::TabSearch(QWidget * attachedTab, QObject * parent): QObject(parent), tab(attachedTab), text(QString::null), flags(QWebEnginePage::FindFlag(0)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search constructor");
}

tab_search::TabSearch::~TabSearch() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search destructor");

}

void tab_search::TabSearch::findTabContent(const QString & searchText, const bool & reverse, const bool & caseSensitive) {
	this->findTabContent(searchText, reverse, caseSensitive, std::function<void(bool)>());
}

void tab_search::TabSearch::findTabContent(const QString & searchText, const bool & reverse, const bool & caseSensitive, std::function<void(bool)> cb) {

	this->text = searchText;

	// No flag set by default
	// Available search flags are:
	// - QWebEnginePage::FindBackward
	// - QWebEnginePage::FindCaseSensitively
	QWebEnginePage::FindFlags options = QWebEnginePage::FindFlag(0);
	if (reverse == true) {
		options |= QWebEnginePage::FindBackward;
	}

	if (caseSensitive == true) {
		options |= QWebEnginePage::FindCaseSensitively;
	}

	this->flags = options;

	this->callback = cb;

	this->search();
}

void tab_search::TabSearch::search() {

	try {
		tab::Tab * currentTab = dynamic_cast<tab::Tab *>(this->tab);
		web_engine_view::WebEngineView * currentTabView = currentTab->getView();
		web_engine_page::WebEnginePage * currentTabPage = currentTabView->page();

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
