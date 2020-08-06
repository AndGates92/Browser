/**
 * @copyright
 * @file tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "function_macros.h"
#include "logging_macros.h"
#include "tab.h"

// Categories
Q_LOGGING_CATEGORY(tabOverall, "tab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabSize, "tab.size", MSG_TYPE_LEVEL)

tab::Tab::Tab(QWidget * parent): QWidget(parent), view(Q_NULLPTR), loadManager(Q_NULLPTR), search(Q_NULLPTR), history(Q_NULLPTR), settings(Q_NULLPTR), scrollManager(Q_NULLPTR) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabOverall,  "Tab constructor");
}

void tab::Tab::configure(std::shared_ptr<tab_bar::TabBar> tabBar) {
	std::shared_ptr<web_engine_view::WebEngineView> tabView = std::make_shared<web_engine_view::WebEngineView>(this);
	this->setView(tabView);

	std::shared_ptr<tab_load_manager::TabLoadManager> tabLoadManager = std::make_shared<tab_load_manager::TabLoadManager>(this);
	this->setLoadManager(tabLoadManager);

	std::shared_ptr<tab_search::TabSearch> tabSearch = std::make_shared<tab_search::TabSearch>(this, this->weak_from_this());
	this->setSearch(tabSearch);

	std::shared_ptr<web_engine_history::WebEngineHistory> tabHistory = std::make_shared<web_engine_history::WebEngineHistory>(this->getView()->history());
	this->setHistory(tabHistory);

	std::shared_ptr<web_engine_settings::WebEngineSettings> tabSettings = std::make_shared<web_engine_settings::WebEngineSettings>(this->getView()->settings());
	this->setSettings(tabSettings);

	std::shared_ptr<tab_scroll_manager::TabScrollManager> tabScrollManager = std::make_shared<tab_scroll_manager::TabScrollManager>(this, this->weak_from_this(), tabBar);
	this->setScrollManager(tabScrollManager);
}

tab::Tab::~Tab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabOverall,  "Tab destructor");
}

void tab::Tab::setLoadManager(std::shared_ptr<tab_load_manager::TabLoadManager> value) {
	if (this->loadManager != value) {
		if (this->progressValueConnection) {
			disconnect(this->progressValueConnection);
		}

		this->loadManager = value;

		this->progressValueConnection = connect(this->loadManager.get(), &tab_load_manager::TabLoadManager::progressChanged, [this] (const int & value) {
			this->loadProgressChanged(value);
		});
	}
}

BASE_GETTER(tab::Tab::getLoadManager, std::shared_ptr<tab_load_manager::TabLoadManager>, this->loadManager)

BASE_SETTER_GETTER(tab::Tab::setView, tab::Tab::getView, std::shared_ptr<web_engine_view::WebEngineView>, this->view)

BASE_SETTER_GETTER(tab::Tab::setSearch, tab::Tab::getSearch, std::shared_ptr<tab_search::TabSearch>, this->search)

BASE_SETTER_GETTER(tab::Tab::setHistory, tab::Tab::getHistory, std::shared_ptr<web_engine_history::WebEngineHistory>, this->history)

void tab::Tab::setScrollManager(std::shared_ptr<tab_scroll_manager::TabScrollManager> value) {
	if (this->scrollManager != value) {
		if (this->vScrollValueConnection) {
			disconnect(this->vScrollValueConnection);
		}

		if (this->hScrollValueConnection) {
			disconnect(this->hScrollValueConnection);
		}

		this->scrollManager = value;

		this->vScrollValueConnection = connect(this->scrollManager.get(), &tab_scroll_manager::TabScrollManager::verticalScrollChanged, [this] (const int & value) {
			this->verticalScrollChanged(value);
		});

		this->hScrollValueConnection = connect(this->scrollManager.get(), &tab_scroll_manager::TabScrollManager::horizontalScrollChanged, [this] (const int & value) {
			this->horizontalScrollChanged(value);
		});
	}
}

BASE_GETTER(tab::Tab::getScrollManager, std::shared_ptr<tab_scroll_manager::TabScrollManager>, this->scrollManager)

BASE_SETTER_GETTER(tab::Tab::setSettings, tab::Tab::getSettings, std::shared_ptr<web_engine_settings::WebEngineSettings>, this->settings)

void tab::Tab::resize(const QSize size) {
	// Resize view
	if (this->view != Q_NULLPTR) {
		QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabSize,  "Resize view to" << size);
		this->view->resize(size);
	}
	QWidget::resize(size);
}

void tab::Tab::find(const find_settings::FindSettings & settings) const {
	this->search->find(settings);
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
	std::shared_ptr<tab_load_manager::TabLoadManager> loadManager = this->getLoadManager();
	return loadManager->getStatus();
}

std::shared_ptr<web_engine_page::WebEnginePage> tab::Tab::getPage() const {
	std::shared_ptr<web_engine_view::WebEngineView> view = this->getView();
	return view->page();
}
