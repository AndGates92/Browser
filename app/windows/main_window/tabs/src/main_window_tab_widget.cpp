/**
 * @copyright
 * @file main_window_tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

#include "cpp_operator.h"
#include "main_window_shared_functions.h"
#include "main_window_constants.h"
#include "type_print_macros.h"
#include "exception_macros.h"
#include "main_window_web_engine_page.h"
#include "main_window_tab_widget.h"

// Categories
LOGGING_CONTEXT(mainWindowTabWidgetOverall, mainWindowTabWidget.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowTabWidgetTabs, mainWindowTabWidget.tabs, TYPE_LEVEL, INFO_VERBOSITY)

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): tab_widget::TabWidget(parent) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");
}

main_window_tab_widget::MainWindowTabWidget::~MainWindowTabWidget() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

	const int idx = 0;

	// Delete all tabs until the count reaches 0
	// Always delete the first tab as for every deletion, all subsequents are shifted back
	while(this->count() > 0) {
		const main_window_shared_types::page_type_e type = this->getPageType(idx);

		Q_ASSERT_X(((type == main_window_shared_types::page_type_e::TEXT) || (type == main_window_shared_types::page_type_e::WEB_CONTENT)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
		this->removeTab(idx);
		LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetOverall,  "Removing tab type " << type);
	}
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(const int & index) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	this->disconnectTab(this->currentIndex());
	tab_widget::TabWidget::removeTab(index);
	const int currIndex = this->currentIndex();
	this->connectTab(currIndex);
	emit this->numberTabsChanged(currIndex);
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(const int & indexFrom, const int & indexTo) {
	if (indexFrom != indexTo) {
		LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
		this->disconnectTab(this->currentIndex());
		this->bar->moveTab(indexFrom, indexTo);
		this->connectTab(this->currentIndex());
	}
}

void main_window_tab_widget::MainWindowTabWidget::disconnectTab(const int & index) {

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

void main_window_tab_widget::MainWindowTabWidget::connectTab(const int & index) {

	const int tabCount = this->count();

	if (tabCount > 0) {
		std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);
		this->tabSourceConnection = connect(tab.get(), &main_window_tab::MainWindowTab::sourceChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabSourceChanged);
		this->tabUrlConnection = connect(tab.get(), &main_window_tab::MainWindowTab::urlChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged);
		this->tabTitleConnection = connect(tab.get(), &main_window_tab::MainWindowTab::titleChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged);
		this->tabSearchDataConnection = connect(tab.get(), &main_window_tab::MainWindowTab::searchResultChanged, this, &main_window_tab_widget::MainWindowTabWidget::processSearchResultData);
		this->tabFindTextConnection = connect(tab.get(), &main_window_tab::MainWindowTab::findTextFinished, this, &main_window_tab_widget::MainWindowTabWidget::processFindTextFinished);
		this->tabHistoryItemChangedConnection = connect(tab.get(), &main_window_tab::MainWindowTab::historyItemChanged, this, &main_window_tab_widget::MainWindowTabWidget::processHistoryItemChanged);

		// Move focus to the newly connected tab
		tab->setFocus();

		emit this->tabNearlyConnected(index);
	}
}

std::shared_ptr<main_window_tab::MainWindowTab> main_window_tab_widget::MainWindowTabWidget::widget(const int & index, bool checkError) const {
	std::shared_ptr<main_window_tab::MainWindowTab> requestedWidget = std::dynamic_pointer_cast<main_window_tab::MainWindowTab>(tab_widget::TabWidget::widget(index, checkError));

	return requestedWidget;
}

void main_window_tab_widget::MainWindowTabWidget::setPageData(const int & index, const std::shared_ptr<main_window_page_data::MainWindowPageData> & pageData) {
	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = this->getPage(index);
	if (page != nullptr) {
		page->setData(pageData);
	}
}

std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> main_window_tab_widget::MainWindowTabWidget::getPage(const int & index) const {

	const int tabCount = this->count();

	EXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = nullptr;

	if (tabCount > 0) {
		const std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);
		page = tab->getPage();
	}

	return page;
}

const std::shared_ptr<main_window_page_data::MainWindowPageData> main_window_tab_widget::MainWindowTabWidget::getPageData(const int & index) const {

	const int tabCount = this->count();

	EXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	std::shared_ptr<main_window_page_data::MainWindowPageData> pageData = nullptr;
	const std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		pageData = page->getData();
	}

	return pageData;
}

main_window_shared_types::page_type_e main_window_tab_widget::MainWindowTabWidget::getPageType(const int & index) const {
	const std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		return page->getType();
	}

	return main_window_shared_types::page_type_e::UNKNOWN;
}

const QString main_window_tab_widget::MainWindowTabWidget::getPageSource(const int & index) const {
	const std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		return page->getSource();
	}
	return QString();
}

const void * main_window_tab_widget::MainWindowTabWidget::getPageExtraData(const int & index) const {
	const std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = this->getPage(index);

	if (page != nullptr) {
		return page->getData().get();
	}
	return nullptr;
}

void main_window_tab_widget::MainWindowTabWidget::changePageData(const int & index, const main_window_shared_types::page_type_e & type, const QString & source, const void * data) {

	const std::shared_ptr<main_window_page_data::MainWindowPageData> currentData = this->getPageData(index);
	std::shared_ptr<main_window_page_data::MainWindowPageData> newData = main_window_page_data::MainWindowPageData::makePageData(type, source.toStdString(), data);
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Current data of tab at index " << index << " is " << *(currentData.get()));
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "New data of tab at index " << index << " is " << *(newData.get()));

	if (currentData != newData) {
		this->setPageData(index, newData);
	}
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, const main_window_shared_types::page_type_e & type, const void * data, const QIcon & icon) {

	this->disconnectTab(this->currentIndex());

	const QString source = QString();
	const QString search = QString();
	std::shared_ptr<main_window_tab::MainWindowTab> tab = std::make_shared<main_window_tab::MainWindowTab>(this, search);
	tab->configure(this->tabBar(), type, source, data);

	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab of type " << type << " with source " << source << " at position " << index);

	const QString label = QString();
	const int currIndex = tab_widget::TabWidget::insertTab(index, tab, label, icon);

	this->connectTab(currIndex);

	// Move to the newly opened tab
		this->setCurrentIndex(currIndex);

	return currIndex;
}

void main_window_tab_widget::MainWindowTabWidget::findInTab(const int & index, const find_settings::FindSettings & settings) {
	const std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);

	// Find text in tab
	tab->find(settings);
}

void main_window_tab_widget::MainWindowTabWidget::scrollTab(const int & index, const global_enums::offset_type_e & direction) {
	const std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);
	// Scroll tab
	switch (direction) {
		case global_enums::offset_type_e::UP:
			tab->scrollUp();
			break;
		case global_enums::offset_type_e::DOWN:
			tab->scrollDown();
			break;
		case global_enums::offset_type_e::LEFT:
			tab->scrollLeft();
			break;
		case global_enums::offset_type_e::RIGHT:
			tab->scrollRight();
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to scroll in direction " << direction);
			break;
	}
}

void main_window_tab_widget::MainWindowTabWidget::goToHistoryItem(const int & index, const main_window_shared_types::navigation_type_e & direction) {
	const std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);
	// Go through history in tab
	switch (direction) {
		case main_window_shared_types::navigation_type_e::UNDEFINED:
		{
			EXCEPTION_ACTION(throw, "Unable to go to history item for direction " << direction);
			break;
		}
		case main_window_shared_types::navigation_type_e::NEXT:
			tab->historyNext();
			break;
		case main_window_shared_types::navigation_type_e::PREVIOUS:
			tab->historyPrev();
			break;
		default:
			EXCEPTION_ACTION(throw,  "Undefined direction of history item " << direction);
			break;
	}
}

QString main_window_tab_widget::MainWindowTabWidget::createSource(const main_window_shared_types::page_type_e & type, const QString & userInput) {

	QString source = QString();

	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
			// User can provide either a URL or a sequence of keywords to search in the search engine
			source = this->searchToUrl(userInput);
			break;
		case main_window_shared_types::page_type_e::TEXT:
			// User provides the path towards the files, hence the source fo the page content is the user input itself
			source = userInput;
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to create source string for tab from user input " << userInput << " because tab type " << type << " is not recognised");
			break;
	}

	return source;
}

QString main_window_tab_widget::MainWindowTabWidget::createLabel(const main_window_shared_types::page_type_e & type, const QString & userInput) {

	QString label = QString();

	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
			// label is the string the user searched
			label = userInput;
			break;
		case main_window_shared_types::page_type_e::TEXT:
			// User provides the path towards the files, hence the source fo the page content is the user input itself
			label = QString(main_window_constants::filePrefix) + userInput;
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to create label for tab from user input " << userInput << " because tab type " << type << " is not recognised");
			break;
	}

	return label;
}

int main_window_tab_widget::MainWindowTabWidget::addTab(const main_window_shared_types::page_type_e & type, const void * data, const QIcon & icon) {

	const int index = this->count();
	int tabIndex = this->insertTab(index, type, data, icon);

	return tabIndex;
}

void main_window_tab_widget::MainWindowTabWidget::changeTabContent(const int & index, const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data) {
	// Change tab type and extra data
	const QString source(this->createSource(type, userInput));
	this->changePageData(index, type, source, data);

	const QString label(this->createLabel(type, userInput));
	// Change tab label
	this->setTabText(index, label);

	std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);

	// Update text searched by the user
	tab->setSearchText(userInput);

	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = tab->getPage();
	// Set tab body
	page->setBody();

	// Set focus to the tab in case it was lost or changed
	tab->setFocus();
}

void main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged(const QUrl & url) {
	const int idx = this->currentIndex();
	const main_window_shared_types::page_type_e type = this->getPageType(idx);

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if ((type == main_window_shared_types::page_type_e::WEB_CONTENT) && (url.isValid())) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		emit this->tabUrlChanged(type, urlStr);
	}
}

void main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged(const QString & title) {
	emit tabTitleChanged(title);
}

void main_window_tab_widget::MainWindowTabWidget::processTabSourceChanged(const QString & source) {
	const int idx = this->currentIndex();
	const main_window_shared_types::page_type_e type = this->getPageType(idx);

	emit this->tabSourceChanged(type, source);
}

void main_window_tab_widget::MainWindowTabWidget::processSearchResultData(const main_window_tab_search::search_data_s & data) const {
	emit this->searchResultChanged(data);
}

void main_window_tab_widget::MainWindowTabWidget::processHistoryItemChanged(const global_enums::element_position_e & position) {
	emit this->historyItemChanged(position);
}

void main_window_tab_widget::MainWindowTabWidget::processFindTextFinished(const bool & found) {
	emit this->findTextFinished(found);
}

void main_window_tab_widget::MainWindowTabWidget::reloadTabContent(const int & index) {
	std::shared_ptr<main_window_tab::MainWindowTab> tab = this->widget(index, true);
	tab->reload();
}

void main_window_tab_widget::MainWindowTabWidget::setTabTitle(const int & index, const QString & source) {
	this->setTabText(index, source);

	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page = this->getPage(index);
	if (page != nullptr) {
		page->setSource(source);
	}
}

void main_window_tab_widget::MainWindowTabWidget::openFileInCurrentTab(const QString & filepath, const void * data) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs,  "Print content of file " << filepath << " in tab");

	const main_window_shared_types::page_type_e desiredTabType = main_window_shared_types::page_type_e::TEXT;

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

	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and the tab widget has " << tabCount << " tabs");

	// Enable events after updating tabs
	this->setUpdatesEnabled(true);

}

QString main_window_tab_widget::MainWindowTabWidget::searchToUrl(const QString & search) const {
	QString url = QString();

	if (main_window_shared_functions::isUrl(search) == true) {

		const bool containsHttps = search.contains(global_constants::https);
		if (containsHttps == false) {
			url += global_constants::https;
		}

		const bool containsWww = search.contains(global_constants::www);
		if (containsWww == false) {
			url += global_constants::www;
		}

		url += search;
	} else if (main_window_shared_functions::isText(search) == true) {
		url = global_constants::https + global_constants::www + main_window_constants::defaultSearchEngine.arg(search);
	} else {
		EXCEPTION_ACTION(throw, "Unable to associate a  page type to search " << search);
	}

	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabWidgetTabs, "Converting search " << search << " to the following URL " << url);

	return url;
}
