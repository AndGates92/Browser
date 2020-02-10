/**
 * @copyright
 * @file main_window_tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWebEngineWidgets/QWebEngineView>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_tab_widget.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): TabWidget(parent), tabTypes(QList<main_window_shared_types::tab_type_e>()) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");

}

main_window_tab_widget::MainWindowTabWidget::~MainWindowTabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	this->tabTypes.append(type);
	int tabIndex = TabWidget::addTab(page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	this->tabTypes.append(type);
	int tabIndex = TabWidget::addTab(page, icon, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(int index, QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	this->tabTypes.insert(index, type);
	int tabIndex = TabWidget::insertTab(index, page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(int index, QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	this->tabTypes.insert(index, type);
	int tabIndex = TabWidget::insertTab(index, page, icon, label);

	return tabIndex;
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	TabWidget::removeTab(index);
	this->deleteListElement(index);
}

void main_window_tab_widget::MainWindowTabWidget::deleteListElement(int index) {

	QCRITICAL_PRINT(((index < 0) || (index >= this->tabTypes.count())), mainWindowTabWidgetTabs, "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << this->tabTypes.count() << ". Got " << index << ".");
	if (this->tabTypes.isEmpty() == false) {
		this->tabTypes.removeAt(index);
	}
}

QWidget * main_window_tab_widget::MainWindowTabWidget::widget(int index, bool checkError) {
	QWidget * requestedWidget = TabWidget::widget(index, checkError);

	return requestedWidget;
}

main_window_shared_types::tab_type_e main_window_tab_widget::MainWindowTabWidget::getTabType(int index) {

	main_window_shared_types::tab_type_e tabType = main_window_shared_types::tab_type_e::UNKNOWN;

	QCRITICAL_PRINT(((index < 0) || (index >= this->tabTypes.count())), mainWindowTabWidgetTabs, "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << this->tabTypes.count() << ". Got " << index << ".");

	if (this->tabTypes.isEmpty() == false) {
		tabType = this->tabTypes.at(index);
	}

	return tabType;
}

void main_window_tab_widget::MainWindowTabWidget::changeTabType(int index, main_window_shared_types::tab_type_e newType) {

	main_window_shared_types::tab_type_e currentType = this->getTabType(index);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and it is of type " << currentType << ". Desired type is " << newType);

	if (currentType != newType) {
		this->removeTab(index);
		int tabIndex = this->insertEmptyTab(index, QString::null, newType);
		QCRITICAL_PRINT((tabIndex != index), mainWindowTabWidgetTabs, "Requested index (" << index << ") is different from tab index (" << tabIndex);

		// Move to the newly recreated tab
		this->setCurrentIndex(index);

	}
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(int index, const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type);
	} else {
		QCRITICAL_PRINT(1, mainWindowTabWidgetTabs, "Unknown tab type");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(int index, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type);
	} else {
		QCRITICAL_PRINT(1, mainWindowTabWidgetTabs, "Unknown tab type");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type);
	} else {
		QCRITICAL_PRINT(1, mainWindowTabWidgetTabs, "Unknown tab type");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, icon, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type);
	} else {
		QCRITICAL_PRINT(1, mainWindowTabWidgetTabs, "Unknown tab type");
	}

	return tabIndex;
}
