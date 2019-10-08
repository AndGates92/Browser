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

// Categories
Q_LOGGING_CATEGORY(tabWidgetOverall, "tabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetResize, "tabWidget.resize", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetSearch, "tabWidget.search", MSG_TYPE_LEVEL)

tab_widget::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->tabBar = new tab_bar::TabBar(this);
	this->setTabBar(this->tabBar);

	this->setFocusPolicy(Qt::StrongFocus);
	this->setMinimumHeight(tab_widget::minHeight);
	this->setMinimumWidth(tab_widget::minWidth);

	// Resize tab to ensure that it is as wide as the main widget
	int widgetWidth = this->size().width();
	this->tabBar->setWidth(widgetWidth);

}

void tab_widget::TabWidget::resizeEvent(QResizeEvent * event) {
	QTabWidget::resizeEvent(event);
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetResize,  "Tab widget resize from " << previousSize << " to " << newSize);
	int widgetWidth = this->size().width();
	this->tabBar->setWidth(widgetWidth);
}

void tab_widget::TabWidget::keyPressEvent(QKeyEvent * event) {

	QTabWidget::keyPressEvent(event);

	QString userText(event->text());
	if (userText.isEmpty()) {
		userText = "No text provided";
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetSearch,  "User typed text " << userText << " to search");

}
