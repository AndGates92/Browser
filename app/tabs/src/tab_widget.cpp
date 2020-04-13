/**
 * @copyright
 * @file tab_widget.cpp
 * @author Andrea Gianarda
 * @date 02rd October 2019
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

tab_widget::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->setMovable(true);
	this->setFocusPolicy(Qt::StrongFocus);
	this->setMinimumHeight(tab_widget::minHeight);
	this->setMinimumWidth(tab_widget::minWidth);

	this->bar = new tab_bar::TabBar(this, this->size().width());
	this->setTabBar(this->bar);

	this->setVisibleAttribute();

}

tab_widget::TabWidget::~TabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget destructor");

	if (this->bar != Q_NULLPTR) {
		delete this->bar;
	}
}

void tab_widget::TabWidget::setTabBar(tab_bar::TabBar * tabBar) {
	QTabWidget::setTabBar(static_cast<QTabBar *>(tabBar));
}

void tab_widget::TabWidget::resizeEvent(QResizeEvent * event) {
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetSize,  "Tab widget resize from " << previousSize << " to " << newSize);
	int widgetWidth = this->size().width();
	this->bar->setWidth(widgetWidth);

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

int tab_widget::TabWidget::addTab(QWidget * page, const QString & label, const QIcon & icon) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Open tab with label " << label);

	const int index = this->count();

	int tabIndex = this->insertTab(index, page, label, icon);

	return tabIndex;
}

int tab_widget::TabWidget::insertTab(const int & index, QWidget * page, const QString & label, const QIcon & icon) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	int tabIndex = -1;

	if (icon.isNull()) {
		tabIndex = QTabWidget::insertTab(index, page, icon, label);
	} else {
		tabIndex = QTabWidget::insertTab(index, page, label);
	}

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

QWidget * tab_widget::TabWidget::widget(const int & index, const bool & checkError) const {
	QWidget * requestedWidget = QTabWidget::widget(index);

	QEXCEPTION_ACTION_COND(((checkError == true) && (requestedWidget == nullptr)), throw,  "Unable to get widget for the tab at index " << index);

	return requestedWidget;
}
