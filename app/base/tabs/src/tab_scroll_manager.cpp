/**
 * @copyright
 * @file tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager functions
 */

#include "cpp_operator.h"
#include "macros.h"
#include "function_macros.h"
#include "tab_scroll_manager.h"
#include "exception_macros.h"

// Categories
LOGGING_CONTEXT(tabScrollManagerOverall, tabScrollManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace tab_scroll_manager {

	namespace {
		/**
		 * @brief minimum value of scroll percentage
		 *
		 */
		static constexpr int minScrollPercentage = 0;

		/**
		 * @brief maximum value of scroll percentage
		 *
		 */
		static constexpr int maxScrollPercentage = 100;

		/**
		 * @brief vertical scroll position increase when typing key shortcut
		 *
		 */
		static constexpr int vScrollStep = 100;

		/**
		 * @brief horitontal scroll position increase when typing key shortcut
		 *
		 */
		static constexpr int hScrollStep = 100;
	}

}

tab_scroll_manager::TabScrollManager::TabScrollManager(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar): tab_component_widget::TabComponentWidget<tab_shared_types::direction_e>(parent, browserTab), horizontalScroll(0), verticalScroll(0), scrollPosition(QPointF(0.0, 0.0)), contentsSize(QSizeF(0.0, 0.0)), bar(tabBar) {
	LOG_INFO(logger::info_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager constructor");
}

tab_scroll_manager::TabScrollManager::~TabScrollManager() {
	LOG_INFO(logger::info_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager destructor");
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
	if (this->canProcessRequests() == true) {
		const qreal & height = this->contentsSize.rheight();
		// Take out parent widget height and tab bar height from content size as scroll position will never be able to span this range
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

void tab_scroll_manager::TabScrollManager::checkScrollValue(const int & scroll, const QString & direction) const {
	EXCEPTION_ACTION_COND(((scroll < tab_scroll_manager::minScrollPercentage) || (scroll > tab_scroll_manager::maxScrollPercentage)), throw,  "Invalid value of " << direction << " scroll: " << scroll << ". Valid range is between " << tab_scroll_manager::minScrollPercentage << " and " << tab_scroll_manager::maxScrollPercentage);
}

void tab_scroll_manager::TabScrollManager::execute(const tab_shared_types::direction_e & direction) {

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
		const int xScroll = static_cast<int>(this->scrollPosition.rx()) + (xAxisFactor * tab_scroll_manager::hScrollStep);

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
		const int yScroll = static_cast<int>(this->scrollPosition.ry()) + (yAxisFactor * tab_scroll_manager::vScrollStep);

		emit this->scrollRequest(xScroll, yScroll);
	} else {
		this->pushRequestQueue(direction);
	}
}

bool tab_scroll_manager::TabScrollManager::canProcessRequests() const {
	const std::shared_ptr<tab::Tab> currentTab = this->getTab();
	const tab_shared_types::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	return (loadManagerStatus == tab_shared_types::load_status_e::FINISHED);
}
