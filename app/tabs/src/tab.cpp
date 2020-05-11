/**
 * @copyright
 * @file tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "function_macros.h"
#include "logging_macros.h"
#include "tab.h"

// Categories
Q_LOGGING_CATEGORY(tabOverall, "tab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabSize, "tab.size", MSG_TYPE_LEVEL)

tab::Tab::Tab(QWidget * parent, QWidget * tabBar): QWidget(parent), view(Q_NULLPTR), loadManager(Q_NULLPTR), search(Q_NULLPTR), history(Q_NULLPTR), settings(Q_NULLPTR) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab constructor");

	web_engine_view::WebEngineView * tabView = new web_engine_view::WebEngineView(this);
	this->setView(tabView);

	tab_load_manager::TabLoadManager * tabLoadManager = new tab_load_manager::TabLoadManager(this);
	this->setLoadManager(tabLoadManager);

	tab_search::TabSearch * tabSearch = new tab_search::TabSearch(this, this);
	this->setSearch(tabSearch);

	this->setHistory(this->getView()->history());

	web_engine_settings::WebEngineSettings * tabSettings = new web_engine_settings::WebEngineSettings(this->getView()->settings());
	this->setSettings(tabSettings);

	tab_scroll_manager::TabScrollManager * tabScrollManager = new tab_scroll_manager::TabScrollManager(this, this, tabBar);
	this->setScrollManager(tabScrollManager);

}

tab::Tab::~Tab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab destructor");

	if (this->view != Q_NULLPTR) {
		delete this->view;
	}

	if (this->loadManager != Q_NULLPTR) {
		delete this->loadManager;
	}

	if (this->scrollManager != Q_NULLPTR) {
		delete this->scrollManager;
	}

	if (this->search != Q_NULLPTR) {
		delete this->search;
	}
}

PTR_SETTER_GETTER(tab::Tab::setLoadManager, tab::Tab::getLoadManager, tab_load_manager::TabLoadManager, this->loadManager)

PTR_SETTER_GETTER(tab::Tab::setView, tab::Tab::getView, web_engine_view::WebEngineView, this->view)

PTR_SETTER_GETTER(tab::Tab::setSearch, tab::Tab::getSearch, tab_search::TabSearch, this->search)

PTR_SETTER_GETTER(tab::Tab::setHistory, tab::Tab::getHistory, QWebEngineHistory, this->history)
//PTR_SETTER(tab::Tab::setHistory, tab_history::TabHistory, this->history)
//CASTED_PTR_GETTER(tab::Tab::getHistory, tab_history::TabHistory, this->history)

PTR_SETTER_GETTER(tab::Tab::setScrollManager, tab::Tab::getScrollManager, tab_scroll_manager::TabScrollManager, this->scrollManager)

PTR_SETTER_GETTER(tab::Tab::setSettings, tab::Tab::getSettings, web_engine_settings::WebEngineSettings, this->settings)

void tab::Tab::resize(const QSize size) {
	// Resize view
	if (this->view != Q_NULLPTR) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSize,  "Resize view to" << size);
		this->view->resize(size);
	}
	QWidget::resize(size);
}

void tab::Tab::find(const QString & searchText, const bool & reverse, const bool & caseSensitive) const {
	this->search->findTabContent(searchText, reverse, caseSensitive);
}

void tab::Tab::findNext() const {
	this->search->findNext();
}

void tab::Tab::findPrev() const {
	this->search->findPrev();
}

void tab::Tab::historyNext() const {
	if (this->history->canGoForward()) {
		this->history->forward();
	}
}

void tab::Tab::historyPrev() const {
	if (this->history->canGoBack()) {
		this->history->back();
	}
}

void tab::Tab::scrollUp() const {
	this->scrollManager->scrollUp();
}

void tab::Tab::scrollDown() const {
	this->scrollManager->scrollDown();
}

void tab::Tab::scrollLeft() const {
	this->scrollManager->scrollLeft();
}

void tab::Tab::scrollRight() const {
	this->scrollManager->scrollRight();
}
