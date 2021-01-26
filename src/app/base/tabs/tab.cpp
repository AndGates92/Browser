/**
 * @copyright
 * @file tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/base/tabs/tab.h"
#include "app/base/tabs/web_engine_view.h"
#include "app/base/tabs/web_engine_settings.h"
#include "app/base/tabs/search.h"
#include "app/base/tabs/load_manager.h"
#include "app/base/tabs/scroll_manager.h"
#include "app/base/tabs/history.h"

// Categories
LOGGING_CONTEXT(tabOverall, tab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabSize, tab.size, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::Tab::Tab(QWidget * parent): QWidget(parent), view(Q_NULLPTR), loadManager(Q_NULLPTR), search(Q_NULLPTR), history(Q_NULLPTR), settings(Q_NULLPTR), scrollManager(Q_NULLPTR) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabOverall, "Tab constructor");
}

void app::base::tab::Tab::configure(std::shared_ptr<app::base::tab::TabBar> tabBar) {
	std::shared_ptr<app::base::tab::WebEngineView> tabView = std::make_shared<app::base::tab::WebEngineView>(this, this->weak_from_this());
	this->setView(tabView);

	std::shared_ptr<app::base::tab::LoadManager> tabLoadManager = std::make_shared<app::base::tab::LoadManager>(this);
	this->setLoadManager(tabLoadManager);

	std::shared_ptr<app::base::tab::Search> tabSearch = std::make_shared<app::base::tab::Search>(this, this->weak_from_this());
	this->setSearch(tabSearch);

	std::shared_ptr<app::base::tab::History> tabHistory = std::make_shared<app::base::tab::History>(this, this->weak_from_this(), this->getView()->history());
	this->setHistory(tabHistory);

	std::shared_ptr<app::base::tab::WebEngineSettings> tabSettings = std::make_shared<app::base::tab::WebEngineSettings>(this->getView()->settings());
	this->setSettings(tabSettings);

	std::shared_ptr<app::base::tab::ScrollManager> tabScrollManager = std::make_shared<app::base::tab::ScrollManager>(this, this->weak_from_this(), tabBar);
	this->setScrollManager(tabScrollManager);
}

app::base::tab::Tab::~Tab() {
	LOG_INFO(app::logger::info_level_e::ZERO, tabOverall, "Tab destructor");
}

void app::base::tab::Tab::setLoadManager(const std::shared_ptr<app::base::tab::LoadManager> & value) {
	if (this->loadManager != value) {
		if (this->progressValueConnection) {
			disconnect(this->progressValueConnection);
		}

		this->loadManager = value;

		this->progressValueConnection = connect(this->loadManager.get(), &base::tab::LoadManager::progressChanged, [this] (const int & value) {
			this->loadProgressChanged(value);
		});
	}
}

CONST_GETTER(app::base::tab::Tab::getLoadManager, std::shared_ptr<app::base::tab::LoadManager>, this->loadManager)

CONST_GETTER(app::base::tab::Tab::getView, std::shared_ptr<app::base::tab::WebEngineView>, this->view)
CONST_REF_SETTER(app::base::tab::Tab::setView, std::shared_ptr<app::base::tab::WebEngineView>, this->view)

CONST_GETTER(app::base::tab::Tab::getSearch, std::shared_ptr<app::base::tab::Search>, this->search)
CONST_REF_SETTER(app::base::tab::Tab::setSearch, std::shared_ptr<app::base::tab::Search>, this->search)

void app::base::tab::Tab::setHistory(const std::shared_ptr<app::base::tab::History> & value) {
	if (this->history != value) {

		if (this->historyItemChangedConnection) {
			disconnect(this->historyItemChangedConnection);
		}

		this->history = value;

		this->historyItemChangedConnection = connect(this->history.get(), &base::tab::History::historyItemChanged, [this] (const app::shared::element_position_e & position) {
			emit this->historyItemChanged(position);
		});
	}
}

CONST_GETTER(app::base::tab::Tab::getHistory, std::shared_ptr<app::base::tab::History>, this->history)

void app::base::tab::Tab::setScrollManager(const std::shared_ptr<app::base::tab::ScrollManager> & value) {
	if (this->scrollManager != value) {
		if (this->vScrollValueConnection) {
			disconnect(this->vScrollValueConnection);
		}

		if (this->hScrollValueConnection) {
			disconnect(this->hScrollValueConnection);
		}

		this->scrollManager = value;

		this->vScrollValueConnection = connect(this->scrollManager.get(), &base::tab::ScrollManager::verticalScrollChanged, [this] (const int & value) {
			this->verticalScrollChanged(value);
		});

		this->hScrollValueConnection = connect(this->scrollManager.get(), &base::tab::ScrollManager::horizontalScrollChanged, [this] (const int & value) {
			this->horizontalScrollChanged(value);
		});
	}
}

CONST_GETTER(app::base::tab::Tab::getScrollManager, std::shared_ptr<app::base::tab::ScrollManager>, this->scrollManager)

CONST_GETTER(app::base::tab::Tab::getSettings, std::shared_ptr<app::base::tab::WebEngineSettings>, this->settings)
CONST_REF_SETTER(app::base::tab::Tab::setSettings, std::shared_ptr<app::base::tab::WebEngineSettings>, this->settings)

void app::base::tab::Tab::resize(const QSize size) {
	// Resize view
	if (this->view != Q_NULLPTR) {
		LOG_INFO(app::logger::info_level_e::ZERO, tabSize, "Resize view to" << size);
		this->view->resize(size);
	}
	QWidget::resize(size);
}

void app::base::tab::Tab::find(const app::windows::shared::FindSettings & settings) const {
	this->search->execute(settings);
}

void app::base::tab::Tab::historyNext() const {
	this->history->execute(app::base::tab::stepping_e::NEXT);
}

void app::base::tab::Tab::historyPrev() const {
	this->history->execute(app::base::tab::stepping_e::PREVIOUS);
}

void app::base::tab::Tab::scrollUp() const {
	this->scrollManager->execute(app::base::tab::direction_e::UP);
}

void app::base::tab::Tab::scrollDown() const {
	this->scrollManager->execute(app::base::tab::direction_e::DOWN);
}

void app::base::tab::Tab::scrollLeft() const {
	this->scrollManager->execute(app::base::tab::direction_e::LEFT);
}

void app::base::tab::Tab::scrollRight() const {
	this->scrollManager->execute(app::base::tab::direction_e::RIGHT);
}

int app::base::tab::Tab::getLoadProgress() const {
	return this->loadManager->getProgress();
}

int app::base::tab::Tab::getVerticalScroll() const {
	return this->scrollManager->getVerticalScrollPercentage();
}

int app::base::tab::Tab::getHorizontalScroll() const {
	return this->scrollManager->getHorizontalScrollPercentage();
}

app::base::tab::load_status_e app::base::tab::Tab::getLoadStatus() const {
	const std::shared_ptr<app::base::tab::LoadManager> loadManager = this->getLoadManager();
	return loadManager->getStatus();
}

std::shared_ptr<app::base::tab::WebEnginePage> app::base::tab::Tab::getPage() const {
	const std::shared_ptr<app::base::tab::WebEngineView> view = this->getView();
	return view->page();
}
