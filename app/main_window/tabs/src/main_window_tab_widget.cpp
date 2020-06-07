/**
 * @copyright
 * @file main_window_tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_web_engine_page.h"
#include "main_window_tab_widget.h"
#include "main_window_tab.h"
#include "main_window_shared_functions.h"
#include "type_print_macros.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

namespace main_window_tab_widget {

	namespace {

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		static const QString defaultSearchEngine(global_constants::https + global_constants::www + "duckduckgo.com/?q=%1");

	}

}

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): tab_widget::TabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");
}

main_window_tab_widget::MainWindowTabWidget::~MainWindowTabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

	const int idx = 0;

	// Delete all tabs until the count reaches 0
	// Always delete the first tab as for every deletion, all subsequents are shifted back
	while(this->count() > 0) {
		const main_window_shared_types::page_type_e type = this->getPageType(idx);

		Q_ASSERT_X(((type == main_window_shared_types::page_type_e::TEXT) || (type == main_window_shared_types::page_type_e::WEB_CONTENT)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
		this->removeTab(idx);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Removing tab type " << type);
	}
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(const int & index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	this->disconnectTab(this->currentIndex());
	tab_widget::TabWidget::removeTab(index);
	const int currIndex = this->currentIndex();
	this->connectTab(currIndex);
	emit this->numberTabsChanged(currIndex);
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(const int & indexFrom, const int & indexTo) {
	if (indexFrom != indexTo) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
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

			emit this->tabNearlyDisconnected(index);
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}
}

void main_window_tab_widget::MainWindowTabWidget::connectTab(const int & index) {

	const int tabCount = this->count();

	if (tabCount > 0) {
		try {
			main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
			this->tabSourceConnection = connect(tab, &main_window_tab::MainWindowTab::sourceChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabSourceChanged);
			this->tabUrlConnection = connect(tab, &main_window_tab::MainWindowTab::urlChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged);
			this->tabTitleConnection = connect(tab, &main_window_tab::MainWindowTab::titleChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged);

			// Move focus to the newly connected tab
			tab->setFocus();

			emit this->tabNearlyConnected(index);
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}
}

QWidget * main_window_tab_widget::MainWindowTabWidget::widget(const int & index, bool checkError) const {
	QWidget * requestedWidget = tab_widget::TabWidget::widget(index, checkError);

	return requestedWidget;
}

void main_window_tab_widget::MainWindowTabWidget::setPageData(const int & index, const main_window_page_data::MainWindowPageData * pageData) {

	const int tabCount = this->count();

	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	if (tabCount > 0) {
		try {
			const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
			main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
			page->setData(pageData);
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}
}

const main_window_page_data::MainWindowPageData * main_window_tab_widget::MainWindowTabWidget::getPageData(const int & index) const {

	const int tabCount = this->count();

	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	const main_window_page_data::MainWindowPageData * pageData = nullptr;

	if (tabCount > 0) {
		try {
			const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
			pageData = page->getData();
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return pageData;
}

main_window_shared_types::page_type_e main_window_tab_widget::MainWindowTabWidget::getPageType(const int & index) const {
	const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
	const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
	return page->getType();
}

const QString main_window_tab_widget::MainWindowTabWidget::getPageSource(const int & index) const {
	const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
	const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
	return page->getSource();
}

const void * main_window_tab_widget::MainWindowTabWidget::getPageExtraData(const int & index) const {
	const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
	const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
	return page->getData();
}

void main_window_tab_widget::MainWindowTabWidget::changePageData(const int & index, const main_window_shared_types::page_type_e & type, const QString & source, const void * data) {

	const main_window_page_data::MainWindowPageData * currentData = this->getPageData(index);
	main_window_page_data::MainWindowPageData * newData = main_window_page_data::MainWindowPageData::makePageData(type, source.toStdString(), data);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current data of tab at index " << index << " is " << *currentData);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "New data of tab at index " << index << " is " << *newData);

	if (currentData != newData) {
		this->setPageData(index, newData);
	}
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, const main_window_shared_types::page_type_e & type, const void * data, const QIcon & icon) {

	this->disconnectTab(this->currentIndex());

	const QString source(QString::null);
	const QString search(QString::null);
	main_window_tab::MainWindowTab * tab = new main_window_tab::MainWindowTab(this, this->tabBar(), search, type, source, data);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab of type " << type << " with source " << source << " at position " << index);

	const QString label(QString::null);
	const int currIndex = tab_widget::TabWidget::insertTab(index, tab, label, icon);

	this->connectTab(currIndex);

	// Move to the newly opened tab
	this->setCurrentIndex(currIndex);


	return currIndex;
}

void main_window_tab_widget::MainWindowTabWidget::findInTab(const int & index, const QString & text, const main_window_shared_types::navigation_type_e & direction) {
	try {
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		// Find text in tab
		switch (direction) {
			case main_window_shared_types::navigation_type_e::UNDEFINED:
				tab->find(text, false, false);
				break;
			case main_window_shared_types::navigation_type_e::NEXT:
				tab->findNext();
				break;
			case main_window_shared_types::navigation_type_e::PREVIOUS:
				tab->findPrev();
				break;
			default:
				QEXCEPTION_ACTION(throw,  "Undefined direction of search " << direction);
				break;
		}
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::scrollTab(const int & index, const main_window_shared_types::offset_type_e direction) {
	try {
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		// Scroll tab
		switch (direction) {
			case main_window_shared_types::offset_type_e::UP:
				tab->scrollUp();
				break;
			case main_window_shared_types::offset_type_e::DOWN:
				tab->scrollDown();
				break;
			case main_window_shared_types::offset_type_e::LEFT:
				tab->scrollLeft();
				break;
			case main_window_shared_types::offset_type_e::RIGHT:
				tab->scrollRight();
				break;
			default:
				QEXCEPTION_ACTION(throw, "Unable to scroll in direction " << direction);
				break;
		}
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}


void main_window_tab_widget::MainWindowTabWidget::goToHistoryItem(const int & index, const main_window_shared_types::navigation_type_e & direction) {
	try {
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		// Go through history in tab
		switch (direction) {
			case main_window_shared_types::navigation_type_e::UNDEFINED:
			{
				QEXCEPTION_ACTION(throw, "Unable to go to history item for direction " << direction);
				break;
			}
			case main_window_shared_types::navigation_type_e::NEXT:
				tab->historyNext();
				break;
			case main_window_shared_types::navigation_type_e::PREVIOUS:
				tab->historyPrev();
				break;
			default:
				QEXCEPTION_ACTION(throw,  "Undefined direction of history item " << direction);
				break;
		}
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

QString main_window_tab_widget::MainWindowTabWidget::createSource(const main_window_shared_types::page_type_e & type, const QString & userInput) {

	QString source(QString::null);

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
			QEXCEPTION_ACTION(throw, "Unable to create source string for tab from user input " << userInput << " because tab type " << type << " is not recognised");
			break;
	}

	return source;
}

QString main_window_tab_widget::MainWindowTabWidget::createLabel(const main_window_shared_types::page_type_e & type, const QString & userInput) {

	QString label(QString::null);

	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
			// label is the string the user searched
			label = userInput;
			break;
		case main_window_shared_types::page_type_e::TEXT:
			// User provides the path towards the files, hence the source fo the page content is the user input itself
			label = QString("file: ") + userInput;
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to create label for tab from user input " << userInput << " because tab type " << type << " is not recognised");
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

	try {
		main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));

		// Update text searched by the user
		tab->setSearchText(userInput);

		main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
		// Set tab body
		page->setBody();

		// Set focus to the tab in case it was lost or changed
		tab->setFocus();
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged(const QUrl & url) {
	const int idx = this->currentIndex();
	const main_window_shared_types::page_type_e type = this->getPageType(idx);

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if ((type == main_window_shared_types::page_type_e::WEB_CONTENT) && (url.isValid())) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		emit tabUrlChanged(type, urlStr);
	}
}

void main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged(const QString & title) {
	emit tabTitleChanged(title);
}

void main_window_tab_widget::MainWindowTabWidget::processTabSourceChanged(const QString & source) {
	const int idx = this->currentIndex();
	const main_window_shared_types::page_type_e type = this->getPageType(idx);

	emit tabSourceChanged(type, source);
}

void main_window_tab_widget::MainWindowTabWidget::reloadTabContent(const int & index) {
	try {
		main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		tab->reload();
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::setTabTitle(const int & index, const QString & source) {
	this->setTabText(index, source);
	try {
		// Set tab title
		main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getPage();
		page->setSource(source);
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::openFileInCurrentTab(const QString & filepath, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Print content of file " << filepath << " in tab");

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
		QEXCEPTION_ACTION_COND((index >= tabCount), throw,  "Current tab index " << index << " must be larger than the number of tabs " << tabCount);
	}

	this->changeTabContent(index, desiredTabType, filepath, data);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and the tab widget has " << tabCount << " tabs");

	// Enable events after updating tabs
	this->setUpdatesEnabled(true);

}

QString main_window_tab_widget::MainWindowTabWidget::searchToUrl(const QString & search) const {
	QString url(QString::null);

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
		url = main_window_tab_widget::defaultSearchEngine.arg(search);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to associate a  page type to search " << search);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Converting search " << search << " to the following URL " << url);

	return url;
}
