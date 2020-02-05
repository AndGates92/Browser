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
Q_LOGGING_CATEGORY(tabWidgetSize, "tabWidget.size", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetSearch, "tabWidget.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetVisibility, "tabWidget.visibility", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabWidgetTabs, "tabWidget.tabs", MSG_TYPE_LEVEL)

tab_widget::TabWidget::TabWidget(QWidget * parent): QTabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget constructor");
	this->setMovable(true);
	this->setFocusPolicy(Qt::StrongFocus);
	this->setMinimumHeight(tab_widget::minHeight);
	this->setMinimumWidth(tab_widget::minWidth);

	this->bar = new tab_bar::TabBar(this, this->size().width());
	this->setTabBar(this->bar);

	connect(this, &tab_widget::TabWidget::tabNumberChange, this, &tab_widget::TabWidget::visibility);

	emit this->tabNumberChange();

}

tab_widget::TabWidget::~TabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetOverall,  "Tab widget destructor");

	delete this->bar;
}

void tab_widget::TabWidget::resizeEvent(QResizeEvent * event) {
	QSize previousSize(event->oldSize());
	QSize newSize(event->size());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetSize,  "Tab widget resize from " << previousSize << " to " << newSize);
	int widgetWidth = this->size().width();
	this->bar->setWidth(widgetWidth);

	QTabWidget::resizeEvent(event);
}

void tab_widget::TabWidget::keyPressEvent(QKeyEvent * event) {

	QString userText(event->text());
	if (userText.isEmpty()) {
		userText = "No text provided";
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetSearch,  "User typed text " << userText << " to search");

	QTabWidget::keyPressEvent(event);

}

int tab_widget::TabWidget::addTab(QWidget * page, const QString & label) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Open tab with label " << label);
	int tabIndex = QTabWidget::addTab(page, label);
	emit this->tabNumberChange();

	return tabIndex;
}

int tab_widget::TabWidget::addTab(QWidget * page, const QIcon & icon, const QString & label) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Open tab with label " << label);
	int tabIndex = QTabWidget::addTab(page, icon, label);
	emit this->tabNumberChange();

	return tabIndex;
}

void tab_widget::TabWidget::removeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetTabs,  "Close tab " << index);
	QTabWidget::removeTab(index);
	emit this->tabNumberChange();
}

void tab_widget::TabWidget::visibility() {
	int tabCount = this->count();
	bool visibleFlag = false;
	if (tabCount == 0) {
		visibleFlag = false;
	} else {
		visibleFlag = true;
	}
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabWidgetVisibility,  "Set visibility of tab widget to " << visibleFlag);
	this->setVisible(visibleFlag);
}

QWidget * tab_widget::TabWidget::widget(int index, bool checkError) {
	QWidget * requestedWidget = QTabWidget::widget(index);

	if (checkError == true) {
		// Check if pointer is null only if error checking is true
		if (requestedWidget == nullptr) {
			qCritical(tabWidgetTabs) << "Unable to get tab page at index " << index;
			exit(EXIT_FAILURE);
		}
	}

	return requestedWidget;
}
