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
#include "type_print_macros.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

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
	this->disconnectTab();
	tab_widget::TabWidget::removeTab(index);
	this->connectTab();
	emit this->numberTabsChanged(this->currentIndex());
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(const int & indexFrom, const int & indexTo) {
	if (indexFrom != indexTo) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
		this->disconnectTab();
		this->bar->moveTab(indexFrom, indexTo);
		this->connectTab();
	}
}

void main_window_tab_widget::MainWindowTabWidget::disconnectTab() {

	const int tabCount = this->count();

	if (tabCount > 0) {
		try {
			const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(this->currentIndex(), true));
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getView()->page();
			disconnect(page, &main_window_web_engine_page::MainWindowWebEnginePage::sourceChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabSourceChanged);
			disconnect(page, &main_window_web_engine_page::MainWindowWebEnginePage::urlChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged);
			disconnect(page, &main_window_web_engine_page::MainWindowWebEnginePage::titleChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged);
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}
}

void main_window_tab_widget::MainWindowTabWidget::connectTab() {

	const int tabCount = this->count();

	if (tabCount > 0) {
		try {
			const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(this->currentIndex(), true));
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getView()->page();
			connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::sourceChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabSourceChanged, Qt::UniqueConnection);
			connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::urlChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged, Qt::UniqueConnection);
			connect(page, &main_window_web_engine_page::MainWindowWebEnginePage::titleChanged, this, &main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged, Qt::UniqueConnection);
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
			main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getView()->page();
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
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getView()->page();
			pageData = page->getData();
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return pageData;
}

main_window_shared_types::page_type_e main_window_tab_widget::MainWindowTabWidget::getPageType(const int & index) const {
	const main_window_page_data::MainWindowPageData * pageData = this->getPageData(index);
	return pageData->getType();
}

const QString main_window_tab_widget::MainWindowTabWidget::getPageSource(const int & index) const {
	const main_window_page_data::MainWindowPageData * pageData = this->getPageData(index);
	return QString::fromStdString(pageData->getSource());
}

const void * main_window_tab_widget::MainWindowTabWidget::getPageExtraData(const int & index) const {
	const main_window_page_data::MainWindowPageData * pageData = this->getPageData(index);
	return pageData->getData();
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

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data, const QIcon & icon) {

	this->disconnectTab();

	const QString source(this->createSource(type, userInput));
	main_window_tab::MainWindowTab * tab = new main_window_tab::MainWindowTab(type, source, data, this->parentWidget());

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab of type " << type << " with source " << source << " at position " << index);

	const QString label(this->createLabel(type, userInput));
	const int tabIndex = tab_widget::TabWidget::insertTab(index, tab, label, icon);

	// Move to the newly opened tab
	this->setCurrentIndex(tabIndex);

	this->connectTab();

	return tabIndex;
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

int main_window_tab_widget::MainWindowTabWidget::addTab(const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data, const QIcon & icon) {

	const int index = this->count();
	int tabIndex = this->insertTab(index, type, userInput, data, icon);

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
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getView()->page();
		// Set tab body
		page->setBody();
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged(const QUrl & url) {
	const int idx = this->currentIndex();
	const main_window_shared_types::page_type_e type = this->getPageType(idx);

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if (type == main_window_shared_types::page_type_e::WEB_CONTENT) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		emit tabUrlChanged(urlStr);
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
		main_window_web_engine_page::MainWindowWebEnginePage * page = tab->getView()->page();
		page->setSource(source);
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::openFileInCurrentTab(const QString & filepath, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Print content of file " << filepath << " in tab");

	const main_window_shared_types::page_type_e desiredTabType = main_window_shared_types::page_type_e::TEXT;

	// START -> data test
	const char * filename = static_cast<const char *>(data);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "data test filename: " << filename);
	// END -> data test

	// Disable events while updating tabs
	this->setUpdatesEnabled(false);

	int tabCount = this->count();

	// Get current tab index
	int index = this->currentIndex();

	// If not tabs, then create one
	if (tabCount == 0) {
		index = this->addTab(desiredTabType, filepath, data);
		tabCount = this->count();
		QEXCEPTION_ACTION_COND((index >= tabCount), throw,  "Current tab index " << index << " must be larger than the number of tabs " << tabCount);
	} else {
		this->changeTabContent(index, desiredTabType, filepath, data);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and the tab widget has " << tabCount << " tabs");

	// Enable events after updating tabs
	this->setUpdatesEnabled(true);

	// TODO: emit signal to disconnect previous tab from qprogress bar
}

QString main_window_tab_widget::MainWindowTabWidget::searchToUrl(const QString & search) const {
	const bool containsSpace = search.contains(" ");
	const bool containsWww = search.contains(main_window_tab_widget::www);
	const int numberDots = search.count(".");

	QString url(QString::null);

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		url = main_window_tab_widget::https;
		if (containsWww == true) {
			url += search;
		} else {
			url += main_window_tab_widget::www + search;
		}
	} else {
		url = main_window_tab_widget::defaultSearchEngine.arg(search);
	}

	return url;
}
