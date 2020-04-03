/**
 * @copyright
 * @file main_window_tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QLabel>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_tab_widget.h"
#include "main_window_web_engine_view.h"
#include "type_print_macros.h"
#include "exception_macros.h"
#include "global_functions.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): tab_widget::TabWidget(parent), tabData(std::list<main_window_tab_data::MainWindowTabData>()) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");

}

main_window_tab_widget::MainWindowTabWidget::~MainWindowTabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

	const int idx = 0;

	// Delete all tabs until the count reaches 0
	// Always delete the first tab as for every deletion, all subsequents are shifted back
	while(this->count() > 0) {
		const main_window_shared_types::tab_type_e type = this->getTabType(idx);

		Q_ASSERT_X(((type == main_window_shared_types::tab_type_e::LABEL) || (type == main_window_shared_types::tab_type_e::WEB_ENGINE)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
		this->removeTab(idx);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Removing tab type " << type);
	}

	for(std::list<main_window_tab_data::MainWindowTabData>::const_iterator it = this->tabData.cbegin(); it != this->tabData.cend(); it++) {
		QWARNING_PRINT(mainWindowTabWidgetOverall,  "Tab type still not deleted - Content: " << it->qprint());
	}

	Q_ASSERT_X((this->tabData.empty() == true), "tab type list not empty", "List of tab types is not empty");

	this->tabData.clear();
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	try {
		this->tabData.emplace_back(main_window_tab_data::MainWindowTabData::makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}
	const int tabIndex = tab_widget::TabWidget::addTab(page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	try {
		this->tabData.emplace_back(main_window_tab_data::MainWindowTabData::makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}
	const int tabIndex = tab_widget::TabWidget::addTab(page, icon, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, QWidget * page, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	try {
		std::list<main_window_tab_data::MainWindowTabData>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		this->tabData.insert(iter, main_window_tab_data::MainWindowTabData::makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}

	const int tabIndex = tab_widget::TabWidget::insertTab(index, page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, QWidget * page, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	try {
		std::list<main_window_tab_data::MainWindowTabData>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		this->tabData.insert(iter, main_window_tab_data::MainWindowTabData::makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}

	const int tabIndex = tab_widget::TabWidget::insertTab(index, page, icon, label);

	return tabIndex;
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(const int & index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	tab_widget::TabWidget::removeTab(index);
	this->deleteListElement(index);
}

void main_window_tab_widget::MainWindowTabWidget::deleteListElement(const int & index) {

	const int tabDataSize = this->tabData.size();
	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabDataSize)), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << tabDataSize << ". Got " << index << ".");

	if (this->tabData.empty() == false) {
		std::list<main_window_tab_data::MainWindowTabData>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		this->tabData.erase(iter);
	}
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(const int & indexFrom, const int & indexTo) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
	this->bar->moveTab(indexFrom, indexTo);
	global_functions::moveListElements<main_window_tab_data::MainWindowTabData>(this->tabData, indexFrom, indexTo);
}

QWidget * main_window_tab_widget::MainWindowTabWidget::widget(const int & index, bool checkError) {
	QWidget * requestedWidget = tab_widget::TabWidget::widget(index, checkError);

	return requestedWidget;
}

main_window_shared_types::tab_type_e main_window_tab_widget::MainWindowTabWidget::getTabType(const int & index) {

	main_window_shared_types::tab_type_e tabType = main_window_shared_types::tab_type_e::UNKNOWN;

	const int tabDataSize = this->tabData.size();
	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabDataSize)), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << tabDataSize << ". Got " << index << ".");

	if (this->tabData.empty() == false) {
		std::list<main_window_tab_data::MainWindowTabData>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		tabType = iter->type;
	}

	return tabType;
}

const void * main_window_tab_widget::MainWindowTabWidget::getTabData(const int & index) {

	const void * tabData = nullptr;

	const int tabDataSize = this->tabData.size();
	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabDataSize)), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << tabDataSize << ". Got " << index << ".");

	if (this->tabData.empty() == false) {
		std::list<main_window_tab_data::MainWindowTabData>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		tabData = iter->data;
	}

	return tabData;
}

void main_window_tab_widget::MainWindowTabWidget::changeTabType(const int & index, const main_window_shared_types::tab_type_e newType, const void * data) {

	const main_window_shared_types::tab_type_e currentType = this->getTabType(index);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and it is of type " << currentType << ". Desired type is " << newType);

	if (currentType != newType) {
		this->removeTab(index);
		const int tabIndex = this->insertEmptyTab(index, QString::null, newType, data);
		QEXCEPTION_ACTION_COND((tabIndex != index), throw, "Requested index (" << index << ") is different from tab index (" << tabIndex);

		// Move to the newly recreated tab
		this->setCurrentIndex(index);

	}
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(const int & index, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		main_window_web_engine_view::MainWindowWebEngineView * centerWindow = new main_window_web_engine_view::MainWindowWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(const int & index, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		main_window_web_engine_view::MainWindowWebEngineView * centerWindow = new main_window_web_engine_view::MainWindowWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		main_window_web_engine_view::MainWindowWebEngineView * centerWindow = new main_window_web_engine_view::MainWindowWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		main_window_web_engine_view::MainWindowWebEngineView * centerWindow = new main_window_web_engine_view::MainWindowWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, icon, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}
