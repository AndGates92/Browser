/**
 * @copyright
 * @file tab_widget.cpp
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Widget functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>

#include "tab_widget.h"

// Categories
Q_LOGGING_CATEGORY(tabWidgetOverall, "tabWidget.overall", MSG_TYPE_LEVEL)

tab_widget::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->tabBar = new tab_bar::TabBar(this);
	this->setTabBar(this->tabBar);
}

void tab_widget::TabWidget::resizeEvent(QResizeEvent * event) {
	this->tabBar->resize(this->size());
	QTabWidget::resizeEvent(event);
}
