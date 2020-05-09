/**
 * @copyright
 * @file tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "tab_scroll_manager.h"

// Categories
Q_LOGGING_CATEGORY(tabScrollManagerOverall, "tabScrollManager.overall", MSG_TYPE_LEVEL)

tab_scroll_manager::TabScrollManager::TabScrollManager(QWidget * parent, QWidget * tabBar): QWidget(parent), scrollPosition(QPointF(0.0, 0.0)), contentsSize(QSizeF(0.0, 0.0)), bar(dynamic_cast<QTabBar *>(tabBar)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager constructor");
}

tab_scroll_manager::TabScrollManager::~TabScrollManager() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager destructor");
}

CONST_GETTER(tab_scroll_manager::TabScrollManager::getContentsSize, QSizeF &, this->contentsSize)

CONST_GETTER(tab_scroll_manager::TabScrollManager::getScrollPosition, QPointF &, this->scrollPosition)

void tab_scroll_manager::TabScrollManager::updateContentsSize(const QSizeF & value) {
	this->contentsSize = value;
	this->updateVerticalScrollPercentage();
	this->updateHorizontalScrollPercentage();
}

void tab_scroll_manager::TabScrollManager::updateScrollPosition(const QPointF & value) {
	this->scrollPosition = value;
	this->updateVerticalScrollPercentage();
	this->updateHorizontalScrollPercentage();
}

void tab_scroll_manager::TabScrollManager::updateVerticalScrollPercentage() {
	const qreal & height = this->contentsSize.rheight();
	// Take out parent widget height and tab bar height from content size as scroll position wil never be able to span this range
	int tabBarHeight = 0;
	const QTabBar::Shape & barShape = this->bar->shape();
	if ((barShape == QTabBar::RoundedNorth) || (barShape == QTabBar::RoundedSouth) || (barShape == QTabBar::TriangularNorth) || (barShape == QTabBar::TriangularSouth)) {
		tabBarHeight = this->bar->size().height();
	}
	const qreal scrollableHeight = height - this->parentWidget()->size().rheight() - tabBarHeight;
	const qreal & vScroll = this->scrollPosition.ry();
	const qreal vScrollPercentage = 100.0 * vScroll/scrollableHeight;
	this->verticalScroll = qRound(vScrollPercentage);
QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "DADA heght " << height << " scrollableHeight " << scrollableHeight << " vScroll " << vScroll << " vScrollPercentage " << vScrollPercentage << " vertical scroll " << this->verticalScroll << " parent size " << this->parentWidget()->size());
	emit this->verticalScrollChanged(this->verticalScroll);
}

void tab_scroll_manager::TabScrollManager::updateHorizontalScrollPercentage() {
	const qreal & width = this->contentsSize.rwidth();
	int tabBarWidth = 0;
	const QTabBar::Shape & barShape = this->bar->shape();
	if ((barShape == QTabBar::RoundedWest) || (barShape == QTabBar::RoundedEast) || (barShape == QTabBar::TriangularWest) || (barShape == QTabBar::TriangularEast)) {
		tabBarWidth = this->bar->size().width();
	}
	const qreal scrollableWidth = width - this->parentWidget()->size().rwidth() - tabBarWidth;
	const qreal & hScroll = this->scrollPosition.rx();
	const qreal hScrollPercentage = 100.0 * hScroll/scrollableWidth;
	this->horizontalScroll = qRound(hScrollPercentage);
QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "DADA width " << width << " hScroll " << hScroll << " hScrollPercentage " << hScrollPercentage << " horizontal scroll " << this->horizontalScroll << " parent size " << this->parentWidget()->size());
	emit this->horizontalScrollChanged(this->horizontalScroll);
}

const int & tab_scroll_manager::TabScrollManager::getVerticalScrollPercentage() const {
	return this->verticalScroll;
}

const int & tab_scroll_manager::TabScrollManager::getHorizontalScrollPercentage() const {
	return this->horizontalScroll;
}
