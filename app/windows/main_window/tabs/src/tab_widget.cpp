/**
 * @copyright
 * @file tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

#include "utility/stl/include/cpp_operator.h"
#include "windows/main_window/common/include/shared_functions.h"
#include "windows/main_window/common/include/constants.h"
#include "common/include/type_print_macros.h"
#include "common/include/exception_macros.h"
#include "windows/main_window/tabs/include/web_engine_page.h"
#include "windows/main_window/tabs/include/tab_widget.h"

// Categories
LOGGING_CONTEXT(mainWindowTabWidgetOverall, mainWindowTabWidget.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowTabWidgetTabs, mainWindowTabWidget.tabs, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::TabWidget::TabWidget(QWidget * parent): app::base::tab::TabWidget(parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");
}

app::main_window::tab::TabWidget::~TabWidget() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

	const int idx = 0;

	// Delete all tabs until the count reaches 0
	// Always delete the first tab as for every deletion, all subsequents are shifted back
	while(this->count() > 0) {
		const app::main_window::page_type_e type = this->getPageType(idx);

		Q_ASSERT_X(((type == app::main_window::page_type_e::TEXT) || (type == app::main_window::page_type_e::WEB_CONTENT)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
		this->removeTab(idx);
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetOverall,  "Removing tab type " << type);
	}
}

void app::main_window::tab::TabWidget::removeTab(const int & index) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	this->disconnectTab(this->currentIndex());
	app::base::tab::TabWidget::removeTab(index);
	const int currIndex = this->currentIndex();
	this->connectTab(currIndex);
	emit this->numberTabsChanged(currIndex);
}

void app::main_window::tab::TabWidget::moveTab(const int & indexFrom, const int & indexTo) {
	if (indexFrom != indexTo) {
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
		this->disconnectTab(this->currentIndex());
		this->bar->moveTab(indexFrom, indexTo);
		this->connectTab(this->currentIndex());
	}
}

void app::main_window::tab::TabWidget::disconnectTab(const int & index) {

	const int tabCount = this->count();

	if (tabCount > 0) {
		try {
			if (this->tabSourceConnection) {
				disconnect(this->tabSourceConnection);
			}
			if (this->tabUrlConnection) {
				disconnect(this->tabUrlConnection);
			}
			if (this->tabTitleConnection) {
				disconnect(this->tabTitleConnection);
			}
			if (this->tabSearchDataConnection) {
				disconnect(this->tabSearchDataConnection);
			}
			if (this->tabFindTextConnection) {
				disconnect(this->tabFindTextConnection);
			}
			if (this->tabHistoryItemChangedConnection) {
				disconnect(this->tabHistoryItemChangedConnection);
			}

			emit this->tabNearlyDisconnected(index);
		} catch (const std::bad_cast & badCastE) {
			EXCEPTION_ACTION(throw, badCastE.what());
		}
	}
}

void app::main_window::tab::TabWidget::connectTab(const int & index) {

	const int tabCount = this->count();

	if (tabCount > 0) {
		std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);
		this->tabSourceConnection = connect(tab.get(), &app::main_window::tab::Tab::sourceChanged, this, &app::main_window::tab::TabWidget::processTabSourceChanged);
		this->tabUrlConnection = connect(tab.get(), &app::main_window::tab::Tab::urlChanged, this, &app::main_window::tab::TabWidget::processTabUrlChanged);
		this->tabTitleConnection = connect(tab.get(), &app::main_window::tab::Tab::titleChanged, this, &app::main_window::tab::TabWidget::processTabTitleChanged);
		this->tabSearchDataConnection = connect(tab.get(), &app::main_window::tab::Tab::searchResultChanged, this, &app::main_window::tab::TabWidget::processSearchResultData);
		this->tabFindTextConnection = connect(tab.get(), &app::main_window::tab::Tab::findTextFinished, this, &app::main_window::tab::TabWidget::processFindTextFinished);
		this->tabHistoryItemChangedConnection = connect(tab.get(), &app::main_window::tab::Tab::historyItemChanged, this, &app::main_window::tab::TabWidget::processHistoryItemChanged);

		// Move focus to the newly connected tab
		tab->setFocus();

		emit this->tabNearlyConnected(index);
	}
}

std::shared_ptr<app::main_window::tab::Tab> app::main_window::tab::TabWidget::widget(const int & index, bool checkError) const {
	std::shared_ptr<app::main_window::tab::Tab> requestedWidget = std::dynamic_pointer_cast<app::main_window::tab::Tab>(app::base::tab::TabWidget::widget(index, checkError));

	return requestedWidget;
}

void app::main_window::tab::TabWidget::setPageData(const int & index, const std::shared_ptr<app::main_window::tab::PageData> & pageData) {
	std::shared_ptr<app::main_window::tab::WebEnginePage> page = this->getPage(index);
	if (page != nullptr) {
		page->setData(pageData);
	}
}

std::shared_ptr<app::main_window::tab::WebEnginePage> app::main_window::tab::TabWidget::getPage(const int & index) const {

	const int tabCount = this->count();

	EXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	std::shared_ptr<app::main_window::tab::WebEnginePage> page = nullptr;

	if (tabCount > 0) {
		const std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);
		page = tab->getPage();
	}

	return page;
}

const std::shared_ptr<app::main_window::tab::PageData> app::main_window::tab::TabWidget::getPageData(const int & index) const {

	const int tabCount = this->count();

	EXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	std::shared_ptr<app::main_window::tab::PageData> pageData = nullptr;
	const std::shared_ptr<app::main_window::tab::WebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		pageData = page->getData();
	}

	return pageData;
}

app::main_window::page_type_e app::main_window::tab::TabWidget::getPageType(const int & index) const {
	const std::shared_ptr<app::main_window::tab::WebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		return page->getType();
	}

	return app::main_window::page_type_e::UNKNOWN;
}

const QString app::main_window::tab::TabWidget::getPageSource(const int & index) const {
	const std::shared_ptr<app::main_window::tab::WebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		return page->getSource();
	}
	return QString();
}

const void * app::main_window::tab::TabWidget::getPageExtraData(const int & index) const {
	const std::shared_ptr<app::main_window::tab::WebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		return page->getData().get();
	}
	return nullptr;
}

void app::main_window::tab::TabWidget::changePageData(const int & index, const app::main_window::page_type_e & type, const QString & source, const void * data) {

	const std::shared_ptr<app::main_window::tab::PageData> currentData = this->getPageData(index);
	std::shared_ptr<app::main_window::tab::PageData> newData = app::main_window::tab::PageData::makePageData(type, source.toStdString(), data);
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Current data of tab at index " << index << " is " << *(currentData.get()));
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "New data of tab at index " << index << " is " << *(newData.get()));

	if (currentData != newData) {
		this->setPageData(index, newData);
	}
}

int app::main_window::tab::TabWidget::insertTab(const int & index, const app::main_window::page_type_e & type, const void * data, const QIcon & icon) {

	this->disconnectTab(this->currentIndex());

	const QString source = QString();
	const QString search = QString();
	std::shared_ptr<app::main_window::tab::Tab> tab = std::make_shared<app::main_window::tab::Tab>(this, search);
	tab->configure(this->tabBar(), type, source, data);

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab of type " << type << " with source " << source << " at position " << index);

	const QString label = QString();
	const int currIndex = app::base::tab::TabWidget::insertTab(index, tab, label, icon);

	this->connectTab(currIndex);

	// Move to the newly opened tab
		this->setCurrentIndex(currIndex);

	return currIndex;
}

void app::main_window::tab::TabWidget::findInTab(const int & index, const app::windows::shared::FindSettings & settings) {
	const std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);

	// Find text in tab
	tab->find(settings);
}

void app::main_window::tab::TabWidget::scrollTab(const int & index, const app::shared::offset_type_e & direction) {
	const std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);
	// Scroll tab
	switch (direction) {
		case app::shared::offset_type_e::UP:
			tab->scrollUp();
			break;
		case app::shared::offset_type_e::DOWN:
			tab->scrollDown();
			break;
		case app::shared::offset_type_e::LEFT:
			tab->scrollLeft();
			break;
		case app::shared::offset_type_e::RIGHT:
			tab->scrollRight();
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to scroll in direction " << direction);
			break;
	}
}

void app::main_window::tab::TabWidget::goToHistoryItem(const int & index, const app::main_window::navigation_type_e & direction) {
	const std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);
	// Go through history in tab
	switch (direction) {
		case app::main_window::navigation_type_e::UNDEFINED:
		{
			EXCEPTION_ACTION(throw, "Unable to go to history item for direction " << direction);
			break;
		}
		case app::main_window::navigation_type_e::NEXT:
			tab->historyNext();
			break;
		case app::main_window::navigation_type_e::PREVIOUS:
			tab->historyPrev();
			break;
		default:
			EXCEPTION_ACTION(throw,  "Undefined direction of history item " << direction);
			break;
	}
}

QString app::main_window::tab::TabWidget::createSource(const app::main_window::page_type_e & type, const QString & userInput) {

	QString source = QString();

	switch (type) {
		case app::main_window::page_type_e::WEB_CONTENT:
			// User can provide either a URL or a sequence of keywords to search in the search engine
			source = this->searchToUrl(userInput);
			break;
		case app::main_window::page_type_e::TEXT:
			// User provides the path towards the files, hence the source fo the page content is the user input itself
			source = userInput;
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to create source string for tab from user input " << userInput << " because tab type " << type << " is not recognised");
			break;
	}

	return source;
}

QString app::main_window::tab::TabWidget::createLabel(const app::main_window::page_type_e & type, const QString & userInput) {

	QString label = QString();

	switch (type) {
		case app::main_window::page_type_e::WEB_CONTENT:
			// label is the string the user searched
			label = userInput;
			break;
		case app::main_window::page_type_e::TEXT:
			// User provides the path towards the files, hence the source fo the page content is the user input itself
			label = QString(app::main_window::filePrefix) + userInput;
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to create label for tab from user input " << userInput << " because tab type " << type << " is not recognised");
			break;
	}

	return label;
}

int app::main_window::tab::TabWidget::addTab(const app::main_window::page_type_e & type, const void * data, const QIcon & icon) {

	const int index = this->count();
	int tabIndex = this->insertTab(index, type, data, icon);

	return tabIndex;
}

void app::main_window::tab::TabWidget::changeTabContent(const int & index, const app::main_window::page_type_e & type, const QString & userInput, const void * data) {
	// Change tab type and extra data
	const QString source(this->createSource(type, userInput));
	this->changePageData(index, type, source, data);

	const QString label(this->createLabel(type, userInput));
	// Change tab label
	this->setTabText(index, label);

	std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);

	// Update text searched by the user
	tab->setSearchText(userInput);

	std::shared_ptr<app::main_window::tab::WebEnginePage> page = tab->getPage();
	// Set tab body
	page->setBody();

	// Set focus to the tab in case it was lost or changed
	tab->setFocus();
}

void app::main_window::tab::TabWidget::processTabUrlChanged(const QUrl & url) {
	const int idx = this->currentIndex();
	const app::main_window::page_type_e type = this->getPageType(idx);

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if ((type == app::main_window::page_type_e::WEB_CONTENT) && (url.isValid())) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		emit this->tabUrlChanged(type, urlStr);
	}
}

void app::main_window::tab::TabWidget::processTabTitleChanged(const QString & title) {
	emit tabTitleChanged(title);
}

void app::main_window::tab::TabWidget::processTabSourceChanged(const QString & source) {
	const int idx = this->currentIndex();
	const app::main_window::page_type_e type = this->getPageType(idx);

	emit this->tabSourceChanged(type, source);
}

void app::main_window::tab::TabWidget::processSearchResultData(const app::main_window::tab::search_data_s & data) const {
	emit this->searchResultChanged(data);
}

void app::main_window::tab::TabWidget::processHistoryItemChanged(const app::shared::element_position_e & position) {
	emit this->historyItemChanged(position);
}

void app::main_window::tab::TabWidget::processFindTextFinished(const bool & found) {
	emit this->findTextFinished(found);
}

void app::main_window::tab::TabWidget::reloadTabContent(const int & index) {
	std::shared_ptr<app::main_window::tab::Tab> tab = this->widget(index, true);
	tab->reload();
}

void app::main_window::tab::TabWidget::setTabTitle(const int & index, const QString & source) {
	this->setTabText(index, source);

	std::shared_ptr<app::main_window::tab::WebEnginePage> page = this->getPage(index);
	if (page != nullptr) {
		page->setSource(source);
	}
}

void app::main_window::tab::TabWidget::openFileInCurrentTab(const QString & filepath, const void * data) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs,  "Print content of file " << filepath << " in tab");

	const app::main_window::page_type_e desiredTabType = app::main_window::page_type_e::TEXT;

	// Disable events while updating tabs
	this->setUpdatesEnabled(false);

	int tabCount = this->count();

	// Get current tab index
	int index = this->currentIndex();

	// If not tabs, then create one
	if (tabCount == 0) {
		index = this->addTab(desiredTabType, data);
		tabCount = this->count();
		EXCEPTION_ACTION_COND((index >= tabCount), throw,  "Current tab index " << index << " must be larger than the number of tabs " << tabCount);
	}

	this->changeTabContent(index, desiredTabType, filepath, data);

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and the tab widget has " << tabCount << " tabs");

	// Enable events after updating tabs
	this->setUpdatesEnabled(true);

}

QString app::main_window::tab::TabWidget::searchToUrl(const QString & search) const {
	QString url = QString();

	if (app::main_window::isUrl(search) == true) {

		const bool containsHttps = search.contains(app::shared::https);
		if (containsHttps == false) {
			url += app::shared::https;
		}

		const bool containsWww = search.contains(app::shared::www);
		if (containsWww == false) {
			url += app::shared::www;
		}

		url += search;
	} else if (app::main_window::isText(search) == true) {
		url = app::shared::https + app::shared::www + app::main_window::defaultSearchEngine.arg(search);
	} else {
		EXCEPTION_ACTION(throw, "Unable to associate a  page type to search " << search);
	}

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Converting search " << search << " to the following URL " << url);

	return url;
}
