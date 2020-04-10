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
#include "global_functions.h"

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
		const main_window_shared_types::tab_type_e type = this->getTabType(idx);

		Q_ASSERT_X(((type == main_window_shared_types::tab_type_e::TEXT) || (type == main_window_shared_types::tab_type_e::WEB_CONTENT)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
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
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->widgetView->page();
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
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->widgetView->page();
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

const main_window_tab_data::MainWindowTabData * main_window_tab_widget::MainWindowTabWidget::getTabData(const int & index) const {

	const int tabCount = this->count();

	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	const main_window_tab_data::MainWindowTabData * tabData = nullptr;

	if (tabCount > 0) {
		try {
			const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
			const main_window_web_engine_page::MainWindowWebEnginePage * page = tab->widgetView->page();
			tabData = page->getTabData();
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return tabData;
}

main_window_shared_types::tab_type_e main_window_tab_widget::MainWindowTabWidget::getTabType(const int & index) const {
	const main_window_tab_data::MainWindowTabData * tabData = this->getTabData(index);
	return tabData->getType();
}

const void * main_window_tab_widget::MainWindowTabWidget::getTabExtraData(const int & index) const {
	const main_window_tab_data::MainWindowTabData * tabData = this->getTabData(index);
	return tabData->getData();
}

void main_window_tab_widget::MainWindowTabWidget::changeTabData(const int & index, const main_window_shared_types::tab_type_e newType, const void * data) {

	const main_window_shared_types::tab_type_e currentType = this->getTabType(index);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and it is of type " << currentType << ". Desired type is " << newType);

	if (currentType != newType) {
		this->removeTab(index);
		const QString content(QString::null);
		const int tabIndex = this->insertTab(index, QString::null, &content, newType, data);
		QEXCEPTION_ACTION_COND((tabIndex != index), throw, "Requested index (" << index << ") is different from tab index (" << tabIndex);
	}
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data, const QIcon & icon) {

	this->disconnectTab();

	main_window_tab::MainWindowTab * tab = new main_window_tab::MainWindowTab(type, data, content, this->parentWidget());

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	const int tabIndex = tab_widget::TabWidget::insertTab(index, tab, label, icon);

	// Move to the newly opened tab
	this->setCurrentIndex(tabIndex);

	this->connectTab();

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data, const QIcon & icon) {

	const int index = this->count();
	int tabIndex = this->insertTab(index, label, content, type, data, icon);

	return tabIndex;
}

void main_window_tab_widget::MainWindowTabWidget::changeTabContent(const int & index, const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data) {
	// Change tab type and extra data
	this->changeTabData(index, type, data);

	// Change tab title
	this->setTabText(index, label);

	try {
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		main_window_web_engine_page::MainWindowWebEnginePage * page = tab->widgetView->page();
		// Set tab body
		page->setBody(type, content);
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_tab_widget::MainWindowTabWidget::processTabUrlChanged(const QUrl & url) {
	const int idx = this->currentIndex();
	const main_window_shared_types::tab_type_e type = this->getTabType(idx);

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if (type == main_window_shared_types::tab_type_e::WEB_CONTENT) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		emit tabUrlChanged(urlStr);
	}
}

void main_window_tab_widget::MainWindowTabWidget::processTabTitleChanged(const QString & title) {
	const int idx = this->currentIndex();
	const main_window_shared_types::tab_type_e type = this->getTabType(idx);

	// for pages whose type is TEXT, the title already contains the path, hence forwarding it
	if (type == main_window_shared_types::tab_type_e::TEXT) {
		emit tabTitleChanged(title);
	}
}

void main_window_tab_widget::MainWindowTabWidget::reloadTabContent(const int & index) {
	try {
		main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		tab->reload();
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}
