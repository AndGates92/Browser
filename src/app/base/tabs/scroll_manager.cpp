/**
 * @copyright
 * @file scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager functions
 */

// Qt libraries
#include <QtWidgets/QTabBar>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/exception.h"
#include "app/shared/setters_getters.h"
#include "app/base/tabs/tab_bar.h"
#include "app/base/tabs/scroll_manager.h"

// Categories
LOGGING_CONTEXT(tabScrollManagerOverall, tabScrollManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {
	namespace base {
		namespace tab {
			namespace scroll_manager {

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
		}
	}
}

app::base::tab::ScrollManager::ScrollManager(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, const std::shared_ptr<app::base::tab::TabBar> & tabBar): app::base::tab::TabComponentWidget<app::base::tab::direction_e>(parent, browserTab), horizontalScroll(0), verticalScroll(0), scrollPosition(QPointF(0.0, 0.0)), contentsSize(QSizeF(0.0, 0.0)), bar(tabBar) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabScrollManagerOverall,  "ScrollManager constructor");
}

app::base::tab::ScrollManager::~ScrollManager() {
	LOG_INFO(app::logger::info_level_e::ZERO, tabScrollManagerOverall,  "ScrollManager destructor");
}

CONST_GETTER(app::base::tab::ScrollManager::getContentsSize, QSizeF &, this->contentsSize)

CONST_GETTER(app::base::tab::ScrollManager::getScrollPosition, QPointF &, this->scrollPosition)

void app::base::tab::ScrollManager::updateContentsSize(const QSizeF & value) {
	this->contentsSize = value;
	this->updateVerticalScrollPercentage();
	this->updateHorizontalScrollPercentage();
}

void app::base::tab::ScrollManager::updateScrollPosition(const QPointF & value) {
	this->scrollPosition = value;
	this->updateVerticalScrollPercentage();
	this->updateHorizontalScrollPercentage();
}

void app::base::tab::ScrollManager::updateVerticalScrollPercentage() {
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

void app::base::tab::ScrollManager::updateHorizontalScrollPercentage() {
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

const int & app::base::tab::ScrollManager::getVerticalScrollPercentage() const {
	return this->verticalScroll;
}

const int & app::base::tab::ScrollManager::getHorizontalScrollPercentage() const {
	return this->horizontalScroll;
}

void app::base::tab::ScrollManager::checkScrollValue(const int & scroll, const QString & direction) const {
	EXCEPTION_ACTION_COND(((scroll < app::base::tab::scroll_manager::minScrollPercentage) || (scroll > app::base::tab::scroll_manager::maxScrollPercentage)), throw,  "Invalid value of " << direction << " scroll: " << scroll << ". Valid range is between " << app::base::tab::scroll_manager::minScrollPercentage << " and " << app::base::tab::scroll_manager::maxScrollPercentage);
}

void app::base::tab::ScrollManager::execute(const app::base::tab::direction_e & direction) {

	if (this->canProcessRequests() == true) {
		int xAxisFactor = 0;
		switch (direction) {
			case app::base::tab::direction_e::LEFT:
				xAxisFactor = -1;
				break;
			case app::base::tab::direction_e::RIGHT:
				xAxisFactor = 1;
				break;
			default:
				xAxisFactor = 0;
				break;
		}
		const int xScroll = static_cast<int>(this->scrollPosition.rx()) + (xAxisFactor * app::base::tab::scroll_manager::hScrollStep);

		int yAxisFactor = 0;
		switch (direction) {
			case app::base::tab::direction_e::UP:
				yAxisFactor = -1;
				break;
			case app::base::tab::direction_e::DOWN:
				yAxisFactor = 1;
				break;
			default:
				yAxisFactor = 0;
				break;
		}
		const int yScroll = static_cast<int>(this->scrollPosition.ry()) + (yAxisFactor * app::base::tab::scroll_manager::vScrollStep);

		emit this->scrollRequest(xScroll, yScroll);
	} else {
		this->pushRequestQueue(direction);
	}
}

bool app::base::tab::ScrollManager::canProcessRequests() const {
	const std::shared_ptr<app::base::tab::Tab> currentTab = this->getTab();
	const app::base::tab::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	return (loadManagerStatus == app::base::tab::load_status_e::FINISHED);
}
