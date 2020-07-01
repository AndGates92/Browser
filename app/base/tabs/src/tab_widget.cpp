/**
 * @copyright
 * @file tab_widget.cpp
 * @author Andrea Gianarda
 * @date 02nd October 2019
 * @brief Tab Widget functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QResizeEvent>
#include <qt5/QtGui/QKeyEvent>

#include "tab_widget.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(tabWidgetOverall, "tabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetSize, "tabWidget.size", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetSearch, "tabWidget.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetVisibility, "tabWidget.visibility", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetTabs, "tabWidget.tabs", MSG_TYPE_LEVEL)

namespace tab_widget {

	namespace {
		/**
		 * @brief minimum height
		 *
		 */
		static constexpr int minHeight = 200;// px

		/**
		 * @brief minimum width
		 *
		 */
		static constexpr int minWidth = 100;// px
	}

}

tab_widget::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->setMovable(true);
	this->setMinimumHeight(tab_widget::minHeight);
	this->setMinimumWidth(tab_widget::minWidth);

	this->bar = std::make_shared<tab_bar::TabBar>(this, this->size().width());
	this->setTabBar(this->bar);

	this->setVisibleAttribute();

	this->tabs = std::vector<std::shared_ptr<tab::Tab>>();

}

tab_widget::TabWidget::~TabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget destructor");
}

void tab_widget::TabWidget::setTabBar(std::shared_ptr<tab_bar::TabBar> newTabBar) {
	QTabWidget::setTabBar(newTabBar.get());
}

BASE_GETTER(tab_widget::TabWidget::tabBar, std::shared_ptr<tab_bar::TabBar>, this->bar)

void tab_widget::TabWidget::resizeEvent(QResizeEvent * event) {
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetSize,  "Tab widget resize from " << previousSize << " to " << newSize);
	int widgetWidth = this->size().width();
	this->bar->setWidth(widgetWidth);

	if (this->count() > 0) {
		// Resize current tab
		std::shared_ptr<tab::Tab> currentTab = this->widget(this->currentIndex(), true);
		if (currentTab != Q_NULLPTR) {
			currentTab->resize(newSize);
		}
	}

	QTabWidget::resizeEvent(event);
}

void tab_widget::TabWidget::keyPressEvent(QKeyEvent * event) {

	QString userText(event->text());
	if (userText.isEmpty()) {
		userText = "No text provided";
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetSearch,  "User typed text " << userText << " to search");

	QTabWidget::keyPressEvent(event);

}

int tab_widget::TabWidget::addTab(std::shared_ptr<tab::Tab> newTab, const QString & label, const QIcon & icon) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Open tab with label " << label);

	const int index = this->count();

	int tabIndex = this->insertTab(index, newTab, label, icon);

	return tabIndex;
}

int tab_widget::TabWidget::insertTab(const int & index, std::shared_ptr<tab::Tab> newTab, const QString & label, const QIcon & icon) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	int tabIndex = -1;

	QEXCEPTION_ACTION_COND((index > this->count()), throw,  "Unable to add tab at index " << index << ". Valid range for argument index is 0 to " << this->count());

	// Inserting tab into the vector before inserting to the QTabWidget because it will trigger an update of the status bar
	std::vector<std::shared_ptr<tab::Tab>>::const_iterator tabsBegin = this->tabs.cbegin();
	this->tabs.insert((tabsBegin + index), newTab);

	if (icon.isNull()) {
		tabIndex = QTabWidget::insertTab(index, newTab.get(), icon, label);
	} else {
		tabIndex = QTabWidget::insertTab(index, newTab.get(), label);
	}

	QEXCEPTION_ACTION_COND((this->tabs.size() != static_cast<std::vector<std::shared_ptr<tab::Tab>>::size_type>(this->count())), throw,  "Number of tabs is not synchronized between QTabWidget and TabWidget. Number of tabs in QTabWidget is " << this->count() << ". Number of tabs in TabWidget is " << this->tabs.size());

	this->setVisibleAttribute();

	return tabIndex;
}

void tab_widget::TabWidget::removeTab(const int & index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Close tab " << index);
	QTabWidget::removeTab(index);
	this->setVisibleAttribute();
}

void tab_widget::TabWidget::setVisibleAttribute() {
	int tabCount = this->count();
	bool visibleFlag = false;
	if (tabCount == 0) {
		visibleFlag = false;
	} else {
		visibleFlag = true;
	}
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetVisibility,  "Set visibility of tab widget to " << visibleFlag);
	this->setVisible(visibleFlag);
}

std::shared_ptr<tab::Tab> tab_widget::TabWidget::widget(const int & index, const bool & checkError) const {
	std::shared_ptr<tab::Tab> requestedWidget = nullptr;
	try {
		requestedWidget = this->tabs.at(index);
	} catch (std::out_of_range const & outOfRangeE) {
		QEXCEPTION_ACTION(throw, outOfRangeE.what());
	}

	QEXCEPTION_ACTION_COND(((checkError == true) && (requestedWidget == nullptr)), throw,  "Unable to get widget for the tab at index " << index);

	return requestedWidget;
}
