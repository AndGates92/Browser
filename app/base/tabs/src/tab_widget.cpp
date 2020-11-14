/**
 * @copyright
 * @file tab_widget.cpp
 * @author Andrea Gianarda
 * @date 02nd October 2019
 * @brief Tab Widget functions
 */

// Qt libraries
#include <QtGui/QResizeEvent>
#include <QtGui/QKeyEvent>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/function_macros.h"
#include "common/include/exception_macros.h"
#include "base/tabs/include/tab_widget.h"

// Categories
LOGGING_CONTEXT(tabWidgetOverall, tabWidget.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabWidgetSize, tabWidget.size, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabWidgetSearch, tabWidget.search, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabWidgetVisibility, tabWidget.visibility, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabWidgetTabs, tabWidget.tabs, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {
	namespace base {
		namespace tab {
			namespace tab_widget {

				namespace {
					/**
					 * @brief minimum height of the tab widget
					 *
					 */
					static constexpr int tabMinHeight = 200;// px

					/**
					 * @brief minimum width of the tab widget
					 *
					 */
					static constexpr int tabMinWidth = 100;// px
				}

			}
		}
	}
}

app::base::tab::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->setMovable(true);
	this->setMinimumHeight(app::base::tab::tab_widget::tabMinHeight);
	this->setMinimumWidth(app::base::tab::tab_widget::tabMinWidth);

	this->bar = std::make_shared<app::base::tab::TabBar>(this, this->size().width());
	this->setTabBar(this->bar);

	this->setVisibleAttribute();

	this->tabs = std::vector<std::shared_ptr<app::base::tab::Tab>>();

}

app::base::tab::TabWidget::~TabWidget() {
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetOverall,  "Tab widget destructor");
}

void app::base::tab::TabWidget::setTabBar(std::shared_ptr<app::base::tab::TabBar> newTabBar) {
	QTabWidget::setTabBar(newTabBar.get());
}

CONST_GETTER(app::base::tab::TabWidget::tabBar, std::shared_ptr<app::base::tab::TabBar> &, this->bar)

void app::base::tab::TabWidget::resizeEvent(QResizeEvent * event) {
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetSize,  "Tab widget resize from " << previousSize << " to " << newSize);
	int widgetWidth = this->size().width();
	this->bar->setWidth(widgetWidth);

	if (this->count() > 0) {
		// Resize current tab
		std::shared_ptr<app::base::tab::Tab> currentTab = this->widget(this->currentIndex(), true);
		if (currentTab != Q_NULLPTR) {
			currentTab->resize(newSize);
		}
	}

	QTabWidget::resizeEvent(event);
}

void app::base::tab::TabWidget::keyPressEvent(QKeyEvent * event) {

	QString userText(event->text());
	if (userText.isEmpty()) {
		userText = "No text provided";
	}

	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetSearch,  "User typed text " << userText << " to search");

	QTabWidget::keyPressEvent(event);

}

int app::base::tab::TabWidget::addTab(const std::shared_ptr<app::base::tab::Tab> & newTab, const QString & label, const QIcon & icon) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetTabs,  "Open tab with label " << label);

	const int index = this->count();

	int tabIndex = this->insertTab(index, newTab, label, icon);

	return tabIndex;
}

int app::base::tab::TabWidget::insertTab(const int & index, const std::shared_ptr<app::base::tab::Tab> & newTab, const QString & label, const QIcon & icon) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	int tabIndex = -1;

	EXCEPTION_ACTION_COND((index > this->count()), throw,  "Unable to add tab at index " << index << ". Valid range for argument index is 0 to " << this->count());

	// Inserting tab into the vector before inserting to the QTabWidget because it will trigger an update of the status bar
	std::vector<std::shared_ptr<app::base::tab::Tab>>::const_iterator tabsBegin = this->tabs.cbegin();
	this->tabs.insert((tabsBegin + index), newTab);

	if (icon.isNull()) {
		tabIndex = QTabWidget::insertTab(index, newTab.get(), icon, label);
	} else {
		tabIndex = QTabWidget::insertTab(index, newTab.get(), label);
	}

	EXCEPTION_ACTION_COND((this->tabs.size() != static_cast<std::vector<std::shared_ptr<app::base::tab::Tab>>::size_type>(this->count())), throw,  "Number of tabs is not synchronized between QTabWidget and TabWidget. Number of tabs in QTabWidget is " << this->count() << ". Number of tabs in TabWidget is " << this->tabs.size());

	this->setVisibleAttribute();

	return tabIndex;
}

void app::base::tab::TabWidget::removeTab(const int & index) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetTabs,  "Close tab " << index);
	QTabWidget::removeTab(index);
	this->setVisibleAttribute();
}

void app::base::tab::TabWidget::setVisibleAttribute() {
	int tabCount = this->count();
	bool visibleFlag = false;
	if (tabCount == 0) {
		visibleFlag = false;
	} else {
		visibleFlag = true;
	}
	LOG_INFO(app::logger::info_level_e::ZERO, tabWidgetVisibility,  "Set visibility of tab widget to " << visibleFlag);
	this->setVisible(visibleFlag);
}

std::shared_ptr<app::base::tab::Tab> app::base::tab::TabWidget::widget(const int & index, const bool & checkError) const {
	std::shared_ptr<app::base::tab::Tab> requestedWidget = nullptr;
	try {
		requestedWidget = this->tabs.at(index);
	} catch (std::out_of_range const & outOfRangeE) {
		EXCEPTION_ACTION(throw, outOfRangeE.what());
	}

	EXCEPTION_ACTION_COND(((checkError == true) && (requestedWidget == nullptr)), throw,  "Unable to get widget for the tab at index " << index);

	return requestedWidget;
}
