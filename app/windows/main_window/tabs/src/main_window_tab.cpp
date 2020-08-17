/**
 * @copyright
 * @file main_window_tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main Window Tab functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "main_window_tab.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabOverall, "mainWindowTab.overall", MSG_TYPE_LEVEL)

main_window_tab::MainWindowTab::MainWindowTab(QWidget * parent, const QString & search): tab::Tab(parent), searchText(search) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabOverall,  "MainWindowTab constructor");

}

void main_window_tab::MainWindowTab::configure(std::shared_ptr<tab_bar::TabBar> tabBar, const main_window_shared_types::page_type_e type, const QString & src, const void * data) {
	std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> tabView = std::make_shared<main_window_web_engine_view::MainWindowWebEngineView>(this, type, src, data);
	this->updateView(tabView);

	std::shared_ptr<main_window_tab_load_manager::MainWindowTabLoadManager> tabLoadManager = std::make_shared<main_window_tab_load_manager::MainWindowTabLoadManager>(this);
	this->setLoadManager(tabLoadManager);

	std::shared_ptr<main_window_tab_search::MainWindowTabSearch> tabSearch = std::make_shared<main_window_tab_search::MainWindowTabSearch>(this, this->weak_from_this());
	this->setSearch(tabSearch);

	std::shared_ptr<main_window_tab_scroll_manager::MainWindowTabScrollManager> tabScrollManager = std::make_shared<main_window_tab_scroll_manager::MainWindowTabScrollManager>(this, this->weak_from_this(), tabBar);
	this->setScrollManager(tabScrollManager);

	this->connectSignals();
}

main_window_tab::MainWindowTab::~MainWindowTab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabOverall,  "MainWindowTab destructor");

}

std::shared_ptr<main_window_tab::MainWindowTab> main_window_tab::MainWindowTab::shared_from_this() {
	return std::static_pointer_cast<main_window_tab::MainWindowTab>(tab::Tab::shared_from_this());
}

std::weak_ptr<main_window_tab::MainWindowTab> main_window_tab::MainWindowTab::weak_from_this() {
	return this->shared_from_this();
}

void main_window_tab::MainWindowTab::reload() {
	this->getView()->page()->reload();
}

void main_window_tab::MainWindowTab::updateView(std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> view) {
	this->setView(view);

	std::shared_ptr<main_window_tab_history::MainWindowTabHistory> tabHistory = std::make_shared<main_window_tab_history::MainWindowTabHistory>(this, this->weak_from_this(), this->getView()->history());
	this->setHistory(tabHistory);

	std::shared_ptr<main_window_web_engine_settings::MainWindowWebEngineSettings> tabSettings = std::make_shared<main_window_web_engine_settings::MainWindowWebEngineSettings>(this->getView()->settings());
	this->setSettings(tabSettings);


}

CONST_SETTER_GETTER(main_window_tab::MainWindowTab::setSearchText, main_window_tab::MainWindowTab::getSearchText, QString, this->searchText)

CASTED_SHARED_PTR_GETTER(main_window_tab::MainWindowTab::getView, main_window_web_engine_view::MainWindowWebEngineView, tab::Tab::getView())

CASTED_SHARED_PTR_GETTER(main_window_tab::MainWindowTab::getLoadManager, main_window_tab_load_manager::MainWindowTabLoadManager, tab::Tab::getLoadManager())

CASTED_SHARED_PTR_GETTER(main_window_tab::MainWindowTab::getSearch, main_window_tab_search::MainWindowTabSearch, tab::Tab::getSearch())

CASTED_SHARED_PTR_GETTER(main_window_tab::MainWindowTab::getHistory, main_window_tab_history::MainWindowTabHistory, tab::Tab::getHistory())

CASTED_SHARED_PTR_GETTER(main_window_tab::MainWindowTab::getSettings, main_window_web_engine_settings::MainWindowWebEngineSettings, tab::Tab::getSettings())

CASTED_SHARED_PTR_GETTER(main_window_tab::MainWindowTab::getScrollManager, main_window_tab_scroll_manager::MainWindowTabScrollManager, tab::Tab::getScrollManager())

void main_window_tab::MainWindowTab::connectSignals() {
	const std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> view = this->getView();
	const std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = view->page();
	const main_window_shared_types::page_type_e tabType = page->getType();
	const std::shared_ptr<main_window_tab_load_manager::MainWindowTabLoadManager> loadManager = this->getLoadManager();
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabOverall,  "Connect signals from page of type " << tabType << " to load manager");
	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::loadStarted, loadManager.get(), &main_window_tab_load_manager::MainWindowTabLoadManager::startLoading);
	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::loadProgress, loadManager.get(), &main_window_tab_load_manager::MainWindowTabLoadManager::setProgress);

	const std::shared_ptr<main_window_tab_scroll_manager::MainWindowTabScrollManager> scrollManager = this->getScrollManager();
	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::contentsSizeChanged, scrollManager.get(), &main_window_tab_scroll_manager::MainWindowTabScrollManager::updateContentsSize);
	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::scrollPositionChanged, scrollManager.get(), &main_window_tab_scroll_manager::MainWindowTabScrollManager::updateScrollPosition);
	connect(scrollManager.get(), &main_window_tab_scroll_manager::MainWindowTabScrollManager::scrollRequest, page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::applyScrollRequest);

	const std::shared_ptr<main_window_tab_search::MainWindowTabSearch> searchManager = this->getSearch();
	connect(searchManager.get(), &main_window_tab_search::MainWindowTabSearch::searchResultChanged, [this] (const main_window_tab_search::search_data_s & data) {
		emit this->searchResultChanged(data);
	});

	connect(searchManager.get(), &main_window_tab_search::MainWindowTabSearch::findTextFinished, [this] (bool found) {
		emit this->findTextFinished(found);
	});

	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::loadFinished, this, &main_window_tab::MainWindowTab::postprocessLoadFinished);

	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::sourceChanged,  [this] (const QString & source) {
		emit this->sourceChanged(source);
	});

	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::urlChanged, [this] (const QUrl & url) {
		emit this->urlChanged(url);
	});

	connect(page.get(), &main_window_web_engine_page::MainWindowWebEnginePage::titleChanged, [this] (const QString & title) {
		emit this->titleChanged(title);
	});

}

void main_window_tab::MainWindowTab::postprocessLoadFinished(const bool & success) {
	std::shared_ptr<main_window_tab_load_manager::MainWindowTabLoadManager> loadManager = this->getLoadManager();
	loadManager->endLoading(success);

	std::shared_ptr<main_window_tab_scroll_manager::MainWindowTabScrollManager> scrollManager = this->getScrollManager();
	scrollManager->emptyRequestQueue();

	std::shared_ptr<main_window_tab_search::MainWindowTabSearch> tabSearch = this->getSearch();
	tabSearch->emptyRequestQueue();
}

std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> main_window_tab::MainWindowTab::getPage() const {
	std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> view = this->getView();
	return view->page();
}
