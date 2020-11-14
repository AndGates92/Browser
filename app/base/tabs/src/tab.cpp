/**
 * @copyright
 * @file tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"
#include "base/tabs/include/tab.h"
#include "base/tabs/include/tab_search.h"
#include "base/tabs/include/tab_scroll_manager.h"
#include "base/tabs/include/tab_history.h"

// Categories
LOGGING_CONTEXT(tabOverall, tab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabSize, tab.size, TYPE_LEVEL, INFO_VERBOSITY)

tab::Tab::Tab(QWidget * parent): QWidget(parent), view(Q_NULLPTR), loadManager(Q_NULLPTR), search(Q_NULLPTR), history(Q_NULLPTR), settings(Q_NULLPTR), scrollManager(Q_NULLPTR) {
	LOG_INFO(logger::info_level_e::ZERO, tabOverall,  "Tab constructor");
}

void tab::Tab::configure(std::shared_ptr<tab_bar::TabBar> tabBar) {
	std::shared_ptr<web_engine_view::WebEngineView> tabView = std::make_shared<web_engine_view::WebEngineView>(this);
	this->setView(tabView);

	std::shared_ptr<tab_load_manager::TabLoadManager> tabLoadManager = std::make_shared<tab_load_manager::TabLoadManager>(this);
	this->setLoadManager(tabLoadManager);

	std::shared_ptr<tab_search::TabSearch> tabSearch = std::make_shared<tab_search::TabSearch>(this, this->weak_from_this());
	this->setSearch(tabSearch);

	std::shared_ptr<tab_history::TabHistory> tabHistory = std::make_shared<tab_history::TabHistory>(this, this->weak_from_this(), this->getView()->history());
	this->setHistory(tabHistory);

	std::shared_ptr<web_engine_settings::WebEngineSettings> tabSettings = std::make_shared<web_engine_settings::WebEngineSettings>(this->getView()->settings());
	this->setSettings(tabSettings);

	std::shared_ptr<tab_scroll_manager::TabScrollManager> tabScrollManager = std::make_shared<tab_scroll_manager::TabScrollManager>(this, this->weak_from_this(), tabBar);
	this->setScrollManager(tabScrollManager);
}

tab::Tab::~Tab() {
	LOG_INFO(logger::info_level_e::ZERO, tabOverall,  "Tab destructor");
}

void tab::Tab::setLoadManager(const std::shared_ptr<tab_load_manager::TabLoadManager> & value) {
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

BASE_GETTER(tab::Tab::getView, std::shared_ptr<web_engine_view::WebEngineView>, this->view)
CONST_REF_SETTER(tab::Tab::setView, std::shared_ptr<web_engine_view::WebEngineView>, this->view)

BASE_GETTER(tab::Tab::getSearch, std::shared_ptr<tab_search::TabSearch>, this->search)
CONST_REF_SETTER(tab::Tab::setSearch, std::shared_ptr<tab_search::TabSearch>, this->search)

void tab::Tab::setHistory(const std::shared_ptr<tab_history::TabHistory> & value) {
	if (this->history != value) {

		if (this->historyItemChangedConnection) {
			disconnect(this->historyItemChangedConnection);
		}

		this->history = value;

		this->historyItemChangedConnection = connect(this->history.get(), &tab_history::TabHistory::historyItemChanged, [this] (const global_enums::element_position_e & position) {
			emit this->historyItemChanged(position);
		});
	}
}

BASE_GETTER(tab::Tab::getHistory, std::shared_ptr<tab_history::TabHistory>, this->history)

void tab::Tab::setScrollManager(const std::shared_ptr<tab_scroll_manager::TabScrollManager> & value) {
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

BASE_GETTER(tab::Tab::getSettings, std::shared_ptr<web_engine_settings::WebEngineSettings>, this->settings)
CONST_REF_SETTER(tab::Tab::setSettings, std::shared_ptr<web_engine_settings::WebEngineSettings>, this->settings)

void tab::Tab::resize(const QSize size) {
	// Resize view
	if (this->view != Q_NULLPTR) {
		LOG_INFO(logger::info_level_e::ZERO, tabSize,  "Resize view to" << size);
		this->view->resize(size);
	}
	QWidget::resize(size);
}

void tab::Tab::find(const find_settings::FindSettings & settings) const {
	this->search->execute(settings);
}

void tab::Tab::historyNext() const {
	this->history->execute(tab_shared_types::stepping_e::NEXT);
}

void tab::Tab::historyPrev() const {
	this->history->execute(tab_shared_types::stepping_e::PREVIOUS);
}

void tab::Tab::scrollUp() const {
	this->scrollManager->execute(tab_shared_types::direction_e::UP);
}

void tab::Tab::scrollDown() const {
	this->scrollManager->execute(tab_shared_types::direction_e::DOWN);
}

void tab::Tab::scrollLeft() const {
	this->scrollManager->execute(tab_shared_types::direction_e::LEFT);
}

void tab::Tab::scrollRight() const {
	this->scrollManager->execute(tab_shared_types::direction_e::RIGHT);
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
	const std::shared_ptr<tab_load_manager::TabLoadManager> loadManager = this->getLoadManager();
	return loadManager->getStatus();
}

std::shared_ptr<web_engine_page::WebEnginePage> tab::Tab::getPage() const {
	const std::shared_ptr<web_engine_view::WebEngineView> view = this->getView();
	return view->page();
}
