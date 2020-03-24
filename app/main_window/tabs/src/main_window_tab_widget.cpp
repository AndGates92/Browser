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
#include <qt5/QtWebEngineWidgets/QWebEngineView>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_tab_widget.h"
#include "type_print_macros.h"
#include "exception_macros.h"
#include "global_functions.h"

// Categories
Q_LOGGING_CATEGORY(tabDataPrint, "tabData.print", MSG_TYPE_LEVEL)

Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

main_window_tab_widget::tab_data_s::tab_data_s(main_window_shared_types::tab_type_e tabType, const void * tabData): type(tabType), data(tabData) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabDataPrint,  "Tab Data structure constructor. Data " << this->qprint());

}

const QString main_window_tab_widget::tab_data_s::qprint() const {
	const std::string tabDataInfo = this->print();
	const QString qStr (tabDataInfo.c_str());

	return qStr;
}

std::string main_window_tab_widget::tab_data_s::print() const {
	std::string structInfo;

	main_window_shared_types::tab_type_e thisType = this->type;

	structInfo = structInfo + " type: " + type;

	const void * thisData = this->data;

	try {
		if (thisData != nullptr) {
			if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
				QEXCEPTION_ACTION(throw, "Unexpected non-null pointer for type " << type);
			} else if (type == main_window_shared_types::tab_type_e::LABEL) {
				const QString * filenamePtr = reinterpret_cast<const QString *>(data);
				const QString filename(*filenamePtr);

				structInfo = structInfo + " filename: " + filename.toStdString();
			} else {
				QEXCEPTION_ACTION(throw, "Unknown type " << type << ". Cannot get extra data.");
			}
		} else {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabDataPrint,  "Data pointer is null therefore no available extra data for type " << thisType);
		}
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return structInfo;
}

static main_window_tab_widget::tab_data_s makeTabData(main_window_shared_types::tab_type_e & type, const void * data) {
	main_window_tab_widget::tab_data_s newData({type, data});
	return newData;
}

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): tab_widget::TabWidget(parent), tabData(std::list<main_window_tab_widget::tab_data_s>()) {
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

	for(std::list<main_window_tab_widget::tab_data_s>::const_iterator it = this->tabData.cbegin(); it != this->tabData.cend(); it++) {
		QWARNING_PRINT(mainWindowTabWidgetOverall,  "Tab type still not deleted - Content: " << (*it).qprint());
	}

	Q_ASSERT_X((this->tabData.empty() == true), "tab type list not empty", "List of tab types is not empty");

	this->tabData.clear();
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	try {
		this->tabData.emplace_back(makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}
	int tabIndex = tab_widget::TabWidget::addTab(page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	try {
		this->tabData.emplace_back(makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}
	int tabIndex = tab_widget::TabWidget::addTab(page, icon, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(int index, QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	try {
		std::list<main_window_tab_widget::tab_data_s>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		this->tabData.insert(iter, makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}

	int tabIndex = tab_widget::TabWidget::insertTab(index, page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(int index, QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	try {
		std::list<main_window_tab_widget::tab_data_s>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		this->tabData.insert(iter, makeTabData(type, data));
	} catch (const std::bad_alloc & badAllocE) {
		QEXCEPTION_ACTION(throw, badAllocE.what());
	}

	int tabIndex = tab_widget::TabWidget::insertTab(index, page, icon, label);

	return tabIndex;
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	tab_widget::TabWidget::removeTab(index);
	this->deleteListElement(index);
}

void main_window_tab_widget::MainWindowTabWidget::deleteListElement(int index) {

	int tabDataSize = this->tabData.size();
	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabDataSize)), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << tabDataSize << ". Got " << index << ".");

	if (this->tabData.empty() == false) {
		std::list<main_window_tab_widget::tab_data_s>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		this->tabData.erase(iter);
	}
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(int indexFrom, int indexTo) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
	this->bar->moveTab(indexFrom, indexTo);
	PRINT_LIST(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, main_window_tab_widget::tab_data_s, "tabData before", this->tabData);
	global_functions::moveListElements<main_window_tab_widget::tab_data_s>(this->tabData, indexFrom, indexTo);
	PRINT_LIST(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, main_window_tab_widget::tab_data_s, "tabData after", this->tabData);
}

QWidget * main_window_tab_widget::MainWindowTabWidget::widget(int index, bool checkError) {
	QWidget * requestedWidget = tab_widget::TabWidget::widget(index, checkError);

	return requestedWidget;
}

main_window_shared_types::tab_type_e main_window_tab_widget::MainWindowTabWidget::getTabType(int index) {

	main_window_shared_types::tab_type_e tabType = main_window_shared_types::tab_type_e::UNKNOWN;

	int tabDataSize = this->tabData.size();
	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabDataSize)), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << tabDataSize << ". Got " << index << ".");

	if (this->tabData.empty() == false) {
		std::list<main_window_tab_widget::tab_data_s>::iterator iter = this->tabData.begin();
		std::advance(iter, index);
		tabType = iter->type;
	}

	return tabType;
}

void main_window_tab_widget::MainWindowTabWidget::changeTabType(int index, main_window_shared_types::tab_type_e newType, const void * data) {

	main_window_shared_types::tab_type_e currentType = this->getTabType(index);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and it is of type " << currentType << ". Desired type is " << newType);

	if (currentType != newType) {
		this->removeTab(index);
		int tabIndex = this->insertEmptyTab(index, QString::null, newType, data);
		QEXCEPTION_ACTION_COND((tabIndex != index), throw, "Requested index (" << index << ") is different from tab index (" << tabIndex);

		// Move to the newly recreated tab
		this->setCurrentIndex(index);

	}
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(int index, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(int index, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type, const void * data) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, icon, label, type, data);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type, data);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}
