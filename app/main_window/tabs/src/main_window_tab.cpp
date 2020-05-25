/**
 * @copyright
 * @file main_window_tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main Window Tab functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "main_window_tab.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabOverall, "mainWindowTab.overall", MSG_TYPE_LEVEL)

main_window_tab::MainWindowTab::MainWindowTab(QWidget * parent, QWidget * tabBar, const main_window_shared_types::page_type_e type, const QString & src, const void * data): tab::Tab(parent, tabBar) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabOverall,  "MainWindowTab constructor");

	main_window_web_engine_view::MainWindowWebEngineView * tabView = new main_window_web_engine_view::MainWindowWebEngineView(this, type, src, data);
	this->updateView(tabView);

	main_window_tab_load_manager::MainWindowTabLoadManager * tabLoadManager = new main_window_tab_load_manager::MainWindowTabLoadManager(this);
	this->setLoadManager(tabLoadManager);

	main_window_tab_search::MainWindowTabSearch * tabSearch = new main_window_tab_search::MainWindowTabSearch(this, this);
	this->setSearch(tabSearch);

	main_window_tab_scroll_manager::MainWindowTabScrollManager * tabScrollManager = new main_window_tab_scroll_manager::MainWindowTabScrollManager(this, this, tabBar);
	this->setScrollManager(tabScrollManager);

	this->connectSignals();
}

main_window_tab::MainWindowTab::~MainWindowTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabOverall,  "MainWindowTab destructor");

}

void main_window_tab::MainWindowTab::reload() {
	this->getView()->page()->reload();
}

void main_window_tab::MainWindowTab::updateView(main_window_web_engine_view::MainWindowWebEngineView * view) {
	this->setView(view);

	main_window_web_engine_history::MainWindowWebEngineHistory * tabHistory = new main_window_web_engine_history::MainWindowWebEngineHistory(this->getView()->history());
	this->setHistory(tabHistory);

	main_window_web_engine_settings::MainWindowWebEngineSettings * tabSettings = new main_window_web_engine_settings::MainWindowWebEngineSettings(this->getView()->settings());
	this->setSettings(tabSettings);


}

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getView, main_window_web_engine_view::MainWindowWebEngineView, tab::Tab::getView())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getLoadManager, main_window_tab_load_manager::MainWindowTabLoadManager, tab::Tab::getLoadManager())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getSearch, main_window_tab_search::MainWindowTabSearch, tab::Tab::getSearch())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getHistory, main_window_web_engine_history::MainWindowWebEngineHistory, tab::Tab::getHistory())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getSettings, main_window_web_engine_settings::MainWindowWebEngineSettings, tab::Tab::getSettings())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getScrollManager, main_window_tab_scroll_manager::MainWindowTabScrollManager, tab::Tab::getScrollManager())

void main_window_tab::MainWindowTab::connectSignals() {
	const main_window_web_engine_view::MainWindowWebEngineView * view = this->getView();
	const main_window_web_engine_page::MainWindowWebEnginePage * page = view->page();
	const main_window_shared_types::page_type_e tabType = page->getType();
	const main_window_tab_load_manager::MainWindowTabLoadManager * loadManager = this->getLoadManager();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabOverall,  "Connect signals from page of type " << tabType << " to load manager");
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::loadStarted, loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::startLoading);
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::loadProgress, loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::setProgress);

	const main_window_tab_scroll_manager::MainWindowTabScrollManager * scrollManager = this->getScrollManager();
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::contentsSizeChanged, scrollManager, &main_window_tab_scroll_manager::MainWindowTabScrollManager::updateContentsSize);
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::scrollPositionChanged, scrollManager, &main_window_tab_scroll_manager::MainWindowTabScrollManager::updateScrollPosition);
	connect(scrollManager, &main_window_tab_scroll_manager::MainWindowTabScrollManager::scrollRequest, page, &main_window_web_engine_page::MainWindowWebEnginePage::applyScrollRequest);

	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::loadFinished, this, &main_window_tab::MainWindowTab::postprocessLoadFInished);


	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::sourceChanged,  [this] (const QString & source) {
		this->sourceChanged(source);
	});

	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::urlChanged, [this] (const QUrl & url) {
		this->urlChanged(url);
	});

	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::titleChanged, [this] (const QString & title) {
		this->titleChanged(title);
	});

}

void main_window_tab::MainWindowTab::postprocessLoadFInished(const bool & success) {
	main_window_tab_load_manager::MainWindowTabLoadManager * loadManager = this->getLoadManager();
	loadManager->endLoading(success);

	main_window_tab_scroll_manager::MainWindowTabScrollManager * scrollManager = this->getScrollManager();
	scrollManager->popRequestQueue();

	main_window_tab_search::MainWindowTabSearch * tabSearch = this->getSearch();
	tabSearch->popRequestQueue();
}

main_window_web_engine_page::MainWindowWebEnginePage * main_window_tab::MainWindowTab::getPage() const {
	main_window_web_engine_view::MainWindowWebEngineView * view = this->getView();
	return view->page();
}
