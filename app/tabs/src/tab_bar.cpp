/**
 * @copyright
 * @file tab_bar.cpp
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Bar functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "tab_bar.h"

// Categories
Q_LOGGING_CATEGORY(tabBarOverall, "tabBar.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabBarSize, "tabBar.size", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabBarSearch, "tabBar.search", MSG_TYPE_LEVEL)

tab_bar::TabBar::TabBar(QWidget * parent, int width): QTabBar(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarOverall,  "Tab bar constructor");

	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	this->setExpanding(true);
	this->setFocusPolicy(Qt::StrongFocus);

	this->setFixedHeight(tab_bar::height);
	this->setMinimumWidth(tab_bar::minWidth);

	this->setElideMode(Qt::ElideRight);

	this->setWidth(width);
}

QSize tab_bar::TabBar::tabSizeHint(int index) const {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSize,  "Tab bar size hint for tab " << index);

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
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSize,  "Tab bar dimensions: width " << barWidth << " height " << barHeight << " Tab width " << tabWidth << " height " << tabHeight << " number of tabs " << tabNumber);
	QSize tabSize(tabWidth, tabHeight);

	return tabSize;
}

void tab_bar::TabBar::setWidth(int newWidth) {
	int tabHeight = tab_bar::height;
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSize,  "Tab bar size width: " << newWidth << " height " << tabHeight);
	this->resize(QSize(newWidth, tabHeight));
}

void tab_bar::TabBar::keyPressEvent(QKeyEvent * event) {

	QString userText(event->text());
	if (userText.isEmpty()) {
		userText = "No text provided";
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSearch,  "User typed text " << userText << " to search");

	QTabBar::keyPressEvent(event);

}

void tab_bar::TabBar::resizeEvent(QResizeEvent * event) {
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabBarSize,  "Tab bar resize from " << previousSize << " to " << newSize);
	QTabBar::resizeEvent(event);
}
