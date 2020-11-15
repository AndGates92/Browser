/**
 * @copyright
 * @file tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main Window Tab functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "windows/main_window/tabs/include/tab.h"

// Categories
LOGGING_CONTEXT(mainWindowTabOverall, mainWindowTab.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::Tab::Tab(QWidget * parent, const QString & search): tab::Tab(parent), searchText(search) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabOverall,  "Tab constructor");

}

void main_window::Tab::configure(const std::shared_ptr<tab_bar::TabBar> & tabBar, const main_window::page_type_e & type, const QString & src, const void * data) {
	std::shared_ptr<main_window::WebEngineView> tabView = std::make_shared<main_window::WebEngineView>(this, type, src, data);
	this->updateView(tabView);

	std::shared_ptr<main_window::TabLoadManager> tabLoadManager = std::make_shared<main_window::TabLoadManager>(this);
	this->setLoadManager(tabLoadManager);

	std::shared_ptr<main_window::TabSearch> tabSearch = std::make_shared<main_window::TabSearch>(this, this->weak_from_this());
	this->setSearch(tabSearch);

	std::shared_ptr<main_window::TabScrollManager> tabScrollManager = std::make_shared<main_window::TabScrollManager>(this, this->weak_from_this(), tabBar);
	this->setScrollManager(tabScrollManager);

	this->connectSignals();
}

main_window::Tab::~Tab() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabOverall,  "Tab destructor");

}

std::shared_ptr<main_window::Tab> main_window::Tab::shared_from_this() {
	return std::static_pointer_cast<main_window::Tab>(tab::Tab::shared_from_this());
}

std::weak_ptr<main_window::Tab> main_window::Tab::weak_from_this() {
	return this->shared_from_this();
}

void main_window::Tab::reload() {
	this->getView()->page()->reload();
}

void main_window::Tab::updateView(const std::shared_ptr<main_window::WebEngineView> & view) {
	this->setView(view);

	std::shared_ptr<main_window::TabHistory> tabHistory = std::make_shared<main_window::TabHistory>(this, this->weak_from_this(), this->getView()->history());
	this->setHistory(tabHistory);

	std::shared_ptr<main_window::WebEngineSettings> tabSettings = std::make_shared<main_window::WebEngineSettings>(this->getView()->settings());
	this->setSettings(tabSettings);


}

CONST_SETTER_GETTER(main_window::Tab::setSearchText, main_window::Tab::getSearchText, QString &, this->searchText)
BASE_GETTER(main_window::Tab::getVerticalScrollPercentage, int, this->getScrollManager()->getVerticalScrollPercentage())
CASTED_SHARED_PTR_GETTER(main_window::Tab::getView, main_window::WebEngineView, tab::Tab::getView())
CASTED_SHARED_PTR_GETTER(main_window::Tab::getLoadManager, main_window::TabLoadManager, tab::Tab::getLoadManager())
CASTED_SHARED_PTR_GETTER(main_window::Tab::getSearch, main_window::TabSearch, tab::Tab::getSearch())
CASTED_SHARED_PTR_GETTER(main_window::Tab::getHistory, main_window::TabHistory, tab::Tab::getHistory())
CASTED_SHARED_PTR_GETTER(main_window::Tab::getSettings, main_window::WebEngineSettings, tab::Tab::getSettings())
CASTED_SHARED_PTR_GETTER(main_window::Tab::getScrollManager, main_window::TabScrollManager, tab::Tab::getScrollManager())

void main_window::Tab::connectSignals() {
	const std::shared_ptr<main_window::WebEngineView> view = this->getView();
	const std::shared_ptr<main_window::WebEnginePage> page = view->page();
	const main_window::page_type_e tabType = page->getType();
	const std::shared_ptr<main_window::TabLoadManager> loadManager = this->getLoadManager();
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabOverall,  "Connect signals from page of type " << tabType << " to load manager");
	connect(page.get(), &main_window::WebEnginePage::loadStarted, loadManager.get(), &main_window::TabLoadManager::startLoading);
	connect(page.get(), &main_window::WebEnginePage::loadProgress, loadManager.get(), &main_window::TabLoadManager::setProgress);

	const std::shared_ptr<main_window::TabScrollManager> scrollManager = this->getScrollManager();
	connect(page.get(), &main_window::WebEnginePage::contentsSizeChanged, scrollManager.get(), &main_window::TabScrollManager::updateContentsSize);
	connect(page.get(), &main_window::WebEnginePage::scrollPositionChanged, scrollManager.get(), &main_window::TabScrollManager::updateScrollPosition);
	connect(scrollManager.get(), &main_window::TabScrollManager::scrollRequest, page.get(), &main_window::WebEnginePage::applyScrollRequest);

	const std::shared_ptr<main_window::TabSearch> searchManager = this->getSearch();
	connect(searchManager.get(), &main_window::TabSearch::searchResultChanged, [this] (const main_window::search_data_s & data) {
		emit this->searchResultChanged(data);
	});

	connect(searchManager.get(), &main_window::TabSearch::findTextFinished, [this] (const bool & found) {
		emit this->findTextFinished(found);
	});

	connect(page.get(), &main_window::WebEnginePage::loadFinished, this, &main_window::Tab::postprocessLoadFinished);

	connect(page.get(), &main_window::WebEnginePage::sourceChanged,  [this] (const QString & source) {
		emit this->sourceChanged(source);
	});

	connect(page.get(), &main_window::WebEnginePage::urlChanged, [this] (const QUrl & url) {
		emit this->urlChanged(url);
	});

	connect(page.get(), &main_window::WebEnginePage::titleChanged, [this] (const QString & title) {
		emit this->titleChanged(title);
	});

}

void main_window::Tab::postprocessLoadFinished(const bool & success) {
	std::shared_ptr<main_window::TabLoadManager> loadManager = this->getLoadManager();
	loadManager->endLoading(success);

	std::shared_ptr<main_window::TabScrollManager> scrollManager = this->getScrollManager();
	scrollManager->emptyRequestQueue();

	std::shared_ptr<main_window::TabSearch> tabSearch = this->getSearch();
	tabSearch->emptyRequestQueue();
}

std::shared_ptr<main_window::WebEnginePage> main_window::Tab::getPage() const {
	std::shared_ptr<main_window::WebEngineView> view = this->getView();
	return view->page();
}
