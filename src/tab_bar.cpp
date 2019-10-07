/**
 * @copyright
 * @file tab_bar.cpp
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Bar functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>

#include "tab_bar.h"

// Categories
Q_LOGGING_CATEGORY(tabBarOverall, "tabBar.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabBarSizeHint, "tabBar.sizeHint", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabBarSetWidth, "tabBar.setWidth", MSG_TYPE_LEVEL)

tab_bar::TabBar::TabBar(QWidget * parent): QTabBar(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarOverall,  "Tab bar constructor");
//	this->resize(this->size());
}

QSize tab_bar::TabBar::tabSizeHint(int index) const {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSizeHint,  "Tab bar size hint for tab " << index);

	//int barWidth = this->size().width();
	int barWidth = this->size().width();
	int barHeight = this->size().height();
	int tabNumber = this->count();

	int tabWidth = 0;
	if (tabNumber == 0) {
		// If no tabs in the tab bar return its total width
		tabWidth = barWidth;
	} else {
		// Share equally width for every tab
		tabWidth = barWidth/tabNumber;
	}
	int tabHeight = barHeight;
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSizeHint,  "Tab bar dimensions: width " << barWidth << " height " << barHeight << " Tab width " << tabWidth << " height " << tabHeight << " number of tabs " << tabNumber);
	QSize tabSize(tabWidth, tabHeight);

	return tabSize;
}

void tab_bar::TabBar::setWidth(int newWidth) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSetWidth,  "Tab bar set width to " << newWidth);
	int tabHeight = this->size().height();
	QSize tabBarSize(newWidth, tabHeight);
	QTabBar::resize(tabBarSize);
}
