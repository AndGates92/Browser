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

main_window_tab::MainWindowTab::MainWindowTab(const main_window_shared_types::tab_type_e type, const void * data, const void * tabContent, QWidget * parent): tab::Tab(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabOverall,  "MainWindowTab constructor");

	main_window_web_engine_view::MainWindowWebEngineView * tabView = new main_window_web_engine_view::MainWindowWebEngineView(type, data, tabContent, this);
	this->setView(tabView);

	main_window_tab_load_manager::MainWindowTabLoadManager * tabLoadManager = new main_window_tab_load_manager::MainWindowTabLoadManager(this);
	this->setLoadManager(tabLoadManager);

	main_window_web_engine_search::MainWindowWebEngineSearch * tabSearch = new main_window_web_engine_search::MainWindowWebEngineSearch(this, this);
	this->setSearch(tabSearch);

	this->connectSignals();
}

main_window_tab::MainWindowTab::~MainWindowTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabOverall,  "MainWindowTab destructor");

}

void main_window_tab::MainWindowTab::reload() {
	this->getView()->page()->reload();
}

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getView, main_window_web_engine_view::MainWindowWebEngineView, tab::Tab::getView())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getLoadManager, main_window_tab_load_manager::MainWindowTabLoadManager, tab::Tab::getLoadManager())

CASTED_PTR_GETTER(main_window_tab::MainWindowTab::getSearch, main_window_web_engine_search::MainWindowWebEngineSearch, tab::Tab::getSearch())

void main_window_tab::MainWindowTab::connectSignals() {
	const main_window_web_engine_page::MainWindowWebEnginePage * page = this->getView()->page();
	const main_window_shared_types::tab_type_e tabType = page->getTabType();
	const main_window_tab_load_manager::MainWindowTabLoadManager * loadManager = this->getLoadManager();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabOverall,  "Connect signals from page of type " << tabType << " to load manager");
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::loadStarted, loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::startLoading);
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::loadProgress, loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::setProgress);
	connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::loadFinished, loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::endLoading);
}
