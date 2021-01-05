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

#include "app/utility/logger/macros.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/setters_getters.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/windows/main_window/tabs/web_engine_view.h"
#include "app/windows/main_window/tabs/web_engine_page.h"
#include "app/windows/main_window/tabs/web_engine_settings.h"
#include "app/windows/main_window/tabs/history.h"
#include "app/windows/main_window/tabs/search.h"
#include "app/windows/main_window/tabs/load_manager.h"
#include "app/windows/main_window/tabs/scroll_manager.h"
#include "app/widgets/commands/key_sequence.h"

// Categories
LOGGING_CONTEXT(mainWindowTabOverall, mainWindowTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowTabUserInput, mainWindowTab.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::Tab::Tab(QWidget * parent, const QString & search): app::base::tab::Tab(parent), searchText(search) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabOverall,  "Tab constructor");

}

void app::main_window::tab::Tab::configure(const std::shared_ptr<app::base::tab::TabBar> & tabBar, const app::main_window::page_type_e & type, const QString & src, const void * data) {
	std::shared_ptr<app::main_window::tab::WebEngineView> tabView = std::make_shared<app::main_window::tab::WebEngineView>(this, this->weak_from_this(), type, src, data);
	this->updateView(tabView);

	std::shared_ptr<app::main_window::tab::LoadManager> tabLoadManager = std::make_shared<app::main_window::tab::LoadManager>(this);
	this->setLoadManager(tabLoadManager);

	std::shared_ptr<app::main_window::tab::Search> tabSearch = std::make_shared<app::main_window::tab::Search>(this, this->weak_from_this());
	this->setSearch(tabSearch);

	std::shared_ptr<app::main_window::tab::ScrollManager> tabScrollManager = std::make_shared<app::main_window::tab::ScrollManager>(this, this->weak_from_this(), tabBar);
	this->setScrollManager(tabScrollManager);

	this->connectSignals();
}

app::main_window::tab::Tab::~Tab() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabOverall,  "Tab destructor");

}

std::shared_ptr<app::main_window::tab::Tab> app::main_window::tab::Tab::shared_from_this() {
	return std::static_pointer_cast<app::main_window::tab::Tab>(app::base::tab::Tab::shared_from_this());
}

std::weak_ptr<app::main_window::tab::Tab> app::main_window::tab::Tab::weak_from_this() {
	return this->shared_from_this();
}

void app::main_window::tab::Tab::reload() {
	this->getView()->page()->reload();
}

void app::main_window::tab::Tab::updateView(const std::shared_ptr<app::main_window::tab::WebEngineView> & view) {
	this->setView(view);

	std::shared_ptr<app::main_window::tab::History> tabHistory = std::make_shared<app::main_window::tab::History>(this, this->weak_from_this(), this->getView()->history());
	this->setHistory(tabHistory);

	std::shared_ptr<app::main_window::tab::WebEngineSettings> tabSettings = std::make_shared<app::main_window::tab::WebEngineSettings>(this->getView()->settings());
	this->setSettings(tabSettings);


}

CONST_SETTER_GETTER(app::main_window::tab::Tab::setSearchText, app::main_window::tab::Tab::getSearchText, QString &, this->searchText)
BASE_GETTER(app::main_window::tab::Tab::getVerticalScrollPercentage, int, this->getScrollManager()->getVerticalScrollPercentage())
CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::Tab::getView, app::main_window::tab::WebEngineView, app::base::tab::Tab::getView())
CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::Tab::getLoadManager, app::main_window::tab::LoadManager, app::base::tab::Tab::getLoadManager())
CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::Tab::getSearch, app::main_window::tab::Search, app::base::tab::Tab::getSearch())
CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::Tab::getHistory, app::main_window::tab::History, app::base::tab::Tab::getHistory())
CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::Tab::getSettings, app::main_window::tab::WebEngineSettings, app::base::tab::Tab::getSettings())
CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::Tab::getScrollManager, app::main_window::tab::ScrollManager, app::base::tab::Tab::getScrollManager())

CONST_GETTER(app::main_window::tab::Tab::getType, app::main_window::page_type_e &, this->getPage()->getType())
CONST_GETTER(app::main_window::tab::Tab::getSource, QString, this->getPage()->getSource())

void app::main_window::tab::Tab::connectSignals() {
	const std::shared_ptr<app::main_window::tab::WebEngineView> view = this->getView();
	const std::shared_ptr<app::main_window::tab::WebEnginePage> page = view->page();
	const app::main_window::page_type_e tabType = page->getType();
	const std::shared_ptr<app::main_window::tab::LoadManager> loadManager = this->getLoadManager();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabOverall,  "Connect signals from page of type " << tabType << " to load manager");
	connect(page.get(), &app::main_window::tab::WebEnginePage::loadStarted, loadManager.get(), &app::main_window::tab::LoadManager::startLoading);
	connect(page.get(), &app::main_window::tab::WebEnginePage::loadProgress, loadManager.get(), &app::main_window::tab::LoadManager::setProgress);

	const std::shared_ptr<app::main_window::tab::ScrollManager> scrollManager = this->getScrollManager();
	connect(page.get(), &app::main_window::tab::WebEnginePage::contentsSizeChanged, scrollManager.get(), &app::main_window::tab::ScrollManager::updateContentsSize);
	connect(page.get(), &app::main_window::tab::WebEnginePage::scrollPositionChanged, scrollManager.get(), &app::main_window::tab::ScrollManager::updateScrollPosition);
	connect(scrollManager.get(), &app::main_window::tab::ScrollManager::scrollRequest, page.get(), &app::main_window::tab::WebEnginePage::applyScrollRequest);

	const std::shared_ptr<app::main_window::tab::Search> searchManager = this->getSearch();
	connect(searchManager.get(), &app::main_window::tab::Search::searchResultChanged, [this] (const app::main_window::tab::search_data_s & data) {
		emit this->searchResultChanged(data);
	});

	connect(searchManager.get(), &app::main_window::tab::Search::findTextFinished, [this] (const bool & found) {
		emit this->findTextFinished(found);
	});

	connect(page.get(), &app::main_window::tab::WebEnginePage::loadFinished, this, &app::main_window::tab::Tab::postprocessLoadFinished);

	connect(page.get(), &app::main_window::tab::WebEnginePage::sourceChanged,  [this] (const QString & source) {
		emit this->sourceChanged(source);
	});

	connect(page.get(), &app::main_window::tab::WebEnginePage::urlChanged, [this] (const QUrl & url) {
		emit this->urlChanged(url);
	});

	connect(page.get(), &app::main_window::tab::WebEnginePage::titleChanged, [this] (const QString & title) {
		emit this->titleChanged(title);
	});

}

void app::main_window::tab::Tab::postprocessLoadFinished(const bool & success) {
	std::shared_ptr<app::main_window::tab::LoadManager> loadManager = this->getLoadManager();
	loadManager->endLoading(success);

	std::shared_ptr<app::main_window::tab::ScrollManager> scrollManager = this->getScrollManager();
	scrollManager->emptyRequestQueue();

	std::shared_ptr<app::main_window::tab::Search> tabSearch = this->getSearch();
	tabSearch->emptyRequestQueue();
}

std::shared_ptr<app::main_window::tab::WebEnginePage> app::main_window::tab::Tab::getPage() const {
	std::shared_ptr<app::main_window::tab::WebEngineView> view = this->getView();
	return view->page();
}

void app::main_window::tab::Tab::keyReleaseEvent(QKeyEvent * event) {

	if (event->type() == QEvent::KeyRelease) {

		const int releasedKey = event->key();
		const Qt::KeyboardModifiers keyModifiers = event->modifiers();

		const app::commands::KeySequence keySeq(releasedKey | keyModifiers);

		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabUserInput, "Key released: " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->window()->setFocus();
				break;
			default:
				break;
		}

	}
}
