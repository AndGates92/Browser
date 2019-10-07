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

#include "tab_widget.h"

// Categories
Q_LOGGING_CATEGORY(tabWidgetOverall, "tabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetResize, "tabWidget.resize", MSG_TYPE_LEVEL)

tab_widget::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->tabBar = new tab_bar::TabBar(this);
	this->tabBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	this->tabBar->setExpanding(true);
	this->setTabBar(this->tabBar);
}

void tab_widget::TabWidget::resizeEvent(QResizeEvent * event) {
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetResize,  "Tab widget resize from " << previousSize << " to " << newSize);
	int widgetWidth = this->size().width();
	this->tabBar->setWidth(widgetWidth);
	QTabWidget::resizeEvent(event);
}
