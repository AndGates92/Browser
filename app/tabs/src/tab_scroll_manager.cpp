/**
 * @copyright
 * @file tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>

#include "logging_macros.h"
#include "function_macros.h"
#include "tab.h"
#include "tab_scroll_manager.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(tabScrollManagerOverall, "tabScrollManager.overall", MSG_TYPE_LEVEL)

tab_scroll_manager::TabScrollManager::TabScrollManager(QWidget * parent, QWidget * browserTab, QWidget * tabBar): tab_component_widget::TabComponentWidget<tab_shared_types::direction_e>(parent, browserTab), horizontalScroll(0), verticalScroll(0), scrollPosition(QPointF(0.0, 0.0)), contentsSize(QSizeF(0.0, 0.0)), bar(dynamic_cast<QTabBar *>(tabBar)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager constructor");
	this->setTab(dynamic_cast<tab::Tab *>(browserTab));
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

	this->popRequestQueue();
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

	this->checkScrollValue(this->verticalScroll, "vertical");

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

	this->checkScrollValue(this->horizontalScroll, "horizontal");

	emit this->horizontalScrollChanged(this->horizontalScroll);
}

const int & tab_scroll_manager::TabScrollManager::getVerticalScrollPercentage() const {
	return this->verticalScroll;
}

const int & tab_scroll_manager::TabScrollManager::getHorizontalScrollPercentage() const {
	return this->horizontalScroll;
}

void tab_scroll_manager::TabScrollManager::checkScrollValue(const int & scroll, const QString direction) const {
	QEXCEPTION_ACTION_COND(((scroll < tab_scroll_manager::minScrollPercentage) || (scroll > tab_scroll_manager::maxScrollPercentage)), throw,  "Invalid value of " << direction << " scroll: " << scroll << ". Valid range is between " << tab_scroll_manager::minScrollPercentage << " and " << tab_scroll_manager::maxScrollPercentage);
}

// TODO: Add mutex
void tab_scroll_manager::TabScrollManager::scrollDown() {
	this->tabScroll(tab_shared_types::direction_e::DOWN);
}

void tab_scroll_manager::TabScrollManager::scrollUp() {
	this->tabScroll(tab_shared_types::direction_e::UP);
}

void tab_scroll_manager::TabScrollManager::scrollRight() {
	this->tabScroll(tab_shared_types::direction_e::RIGHT);
}

void tab_scroll_manager::TabScrollManager::scrollLeft() {
	this->tabScroll(tab_shared_types::direction_e::LEFT);
}

void tab_scroll_manager::TabScrollManager::tabScroll(const tab_shared_types::direction_e direction) {

	if (this->canProcessRequests() == true) {
		int xAxisFactor = 0;
		switch (direction) {
			case tab_shared_types::direction_e::LEFT:
				xAxisFactor = -1;
				break;
			case tab_shared_types::direction_e::RIGHT:
				xAxisFactor = 1;
				break;
			default:
				xAxisFactor = 0;
				break;
		}
		const int xScroll = this->scrollPosition.rx() + (xAxisFactor * tab_scroll_manager::hScrollStep);

		int yAxisFactor = 0;
		switch (direction) {
			case tab_shared_types::direction_e::UP:
				yAxisFactor = -1;
				break;
			case tab_shared_types::direction_e::DOWN:
				yAxisFactor = 1;
				break;
			default:
				yAxisFactor = 0;
				break;
		}
		const int yScroll = this->scrollPosition.ry() + (yAxisFactor * tab_scroll_manager::vScrollStep);

		emit this->scrollRequest(xScroll, yScroll);
	} else {
		this->pushRequestQueue(direction);
	}
}

void tab_scroll_manager::TabScrollManager::pushRequestQueue(const tab_shared_types::direction_e & direction) {
	this->requestQueue.push(direction);
}

void tab_scroll_manager::TabScrollManager::popRequestQueue() {
	const tab::Tab * castedTab(this->getTab());
	const tab_shared_types::load_status_e & loadManagerStatus = castedTab->getLoadStatus();

	QEXCEPTION_ACTION_COND((this->canProcessRequests() == false), throw,  "Function " << __func__ << " cannot be called when load manager is in state " << loadManagerStatus << ". It can only be called if a page is not loading");

	if ((this->requestQueue.empty() == false) && (this->canProcessRequests() == true)) {
		this->tabScroll(this->requestQueue.front());
		this->requestQueue.pop();
	}
}

bool tab_scroll_manager::TabScrollManager::canProcessRequests() const {
	const tab::Tab * castedTab(this->getTab());
	const tab_shared_types::load_status_e & loadManagerStatus = castedTab->getLoadStatus();

	return ((loadManagerStatus == tab_shared_types::load_status_e::FINISHED) || (loadManagerStatus == tab_shared_types::load_status_e::ERROR));
}
