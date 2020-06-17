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

tab::Tab::Tab(QWidget * parent, QWidget * tabBar): QWidget(parent), view(Q_NULLPTR), loadManager(Q_NULLPTR), search(Q_NULLPTR), history(Q_NULLPTR), settings(Q_NULLPTR), scrollManager(Q_NULLPTR) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab constructor");

	web_engine_view::WebEngineView * tabView = new web_engine_view::WebEngineView(this);
	this->setView(tabView);

	tab_load_manager::TabLoadManager * tabLoadManager = new tab_load_manager::TabLoadManager(this);
	this->setLoadManager(tabLoadManager);

	tab_search::TabSearch * tabSearch = new tab_search::TabSearch(this, this);
	this->setSearch(tabSearch);

	web_engine_history::WebEngineHistory * tabHistory = new web_engine_history::WebEngineHistory(this->getView()->history());
	this->setHistory(tabHistory);

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

	if (this->settings != Q_NULLPTR) {
		delete this->settings;
	}

	if (this->history != Q_NULLPTR) {
		delete this->history;
	}
}

void tab::Tab::setLoadManager(tab_load_manager::TabLoadManager * value) {
	if (this->loadManager != value) {
		if (this->loadManager != nullptr) {
			delete this->loadManager;
		}

		if (this->progressValueConnection) {
			disconnect(this->progressValueConnection);
		}

		this->loadManager = value;

		this->progressValueConnection = connect(this->loadManager, &tab_load_manager::TabLoadManager::progressChanged, [this] (const int & value) {
			this->loadProgressChanged(value);
		});
	}
}

PTR_GETTER(tab::Tab::getLoadManager, tab_load_manager::TabLoadManager, this->loadManager)

PTR_SETTER_GETTER(tab::Tab::setView, tab::Tab::getView, web_engine_view::WebEngineView, this->view)

PTR_SETTER_GETTER(tab::Tab::setSearch, tab::Tab::getSearch, tab_search::TabSearch, this->search)

PTR_SETTER_GETTER(tab::Tab::setHistory, tab::Tab::getHistory, web_engine_history::WebEngineHistory, this->history)

void tab::Tab::setScrollManager(tab_scroll_manager::TabScrollManager * value) {
	if (this->scrollManager != value) {
		if (this->scrollManager != nullptr) {
			delete this->scrollManager;
		}

		if (this->vScrollValueConnection) {
			disconnect(this->vScrollValueConnection);
		}

		if (this->hScrollValueConnection) {
			disconnect(this->hScrollValueConnection);
		}

		this->scrollManager = value;

		this->vScrollValueConnection = connect(this->scrollManager, &tab_scroll_manager::TabScrollManager::verticalScrollChanged, [this] (const int & value) {
			this->verticalScrollChanged(value);
		});

		this->hScrollValueConnection = connect(this->scrollManager, &tab_scroll_manager::TabScrollManager::horizontalScrollChanged, [this] (const int & value) {
			this->horizontalScrollChanged(value);
		});
	}
}

PTR_GETTER(tab::Tab::getScrollManager, tab_scroll_manager::TabScrollManager, this->scrollManager)

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
	this->search->find(tab_shared_types::stepping_e::ITEM, searchText, reverse, caseSensitive);
}

void tab::Tab::findNext() const {
	this->search->find(tab_shared_types::stepping_e::NEXT);
}

void tab::Tab::findPrev() const {
	this->search->find(tab_shared_types::stepping_e::PREVIOUS);
}

void tab::Tab::historyNext() const {
	this->history->goToItem(tab_shared_types::stepping_e::NEXT);
}

void tab::Tab::historyPrev() const {
	this->history->goToItem(tab_shared_types::stepping_e::PREVIOUS);
}

void tab::Tab::scrollUp() const {
	this->scrollManager->scroll(tab_shared_types::direction_e::UP);
}

void tab::Tab::scrollDown() const {
	this->scrollManager->scroll(tab_shared_types::direction_e::DOWN);
}

void tab::Tab::scrollLeft() const {
	this->scrollManager->scroll(tab_shared_types::direction_e::LEFT);
}

void tab::Tab::scrollRight() const {
	this->scrollManager->scroll(tab_shared_types::direction_e::RIGHT);
}

int tab::Tab::getLoadProgress() const {
	return this->loadManager->getProgress();
}

int tab::Tab::getVerticalScroll() const {
	return this->scrollManager->getVerticalScrollPercentage();
}

int tab::Tab::getHorizontalScroll() const {
	return this->scrollManager->getHorizontalScrollPercentage();
}

tab_shared_types::load_status_e tab::Tab::getLoadStatus() const {
	tab_load_manager::TabLoadManager * loadManager = this->getLoadManager();
	return loadManager->getStatus();
}

web_engine_page::WebEnginePage * tab::Tab::getPage() const {
	web_engine_view::WebEngineView * view = this->getView();
	return view->page();
}
