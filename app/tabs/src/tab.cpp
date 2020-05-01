/**
 * @copyright
 * @file tab.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "function_macros.h"
#include "logging_macros.h"
#include "tab.h"

// Categories
Q_LOGGING_CATEGORY(tabOverall, "tab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabSize, "tab.size", MSG_TYPE_LEVEL)

tab::Tab::Tab(QWidget * parent): QWidget(parent), view(Q_NULLPTR), loadManager(Q_NULLPTR), search(Q_NULLPTR) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab constructor");

	web_engine_view::WebEngineView * tabView = new web_engine_view::WebEngineView(this);
	this->setView(tabView);

	tab_load_manager::TabLoadManager * tabLoadManager = new tab_load_manager::TabLoadManager(this);
	this->setLoadManager(tabLoadManager);

	tab_search::TabSearch * tabSearch = new tab_search::TabSearch(this, this);
	this->setSearch(tabSearch);
}

tab::Tab::~Tab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab destructor");

	if (this->view != Q_NULLPTR) {
		delete this->view;
	}

	if (this->loadManager != Q_NULLPTR) {
		delete this->loadManager;
	}

	if (this->search != Q_NULLPTR) {
		delete this->search;
	}
}

PTR_SETTER_GETTER(tab::Tab::setLoadManager, tab::Tab::getLoadManager, tab_load_manager::TabLoadManager, this->loadManager)

PTR_SETTER_GETTER(tab::Tab::setView, tab::Tab::getView, web_engine_view::WebEngineView, this->view)

PTR_SETTER_GETTER(tab::Tab::setSearch, tab::Tab::getSearch, tab_search::TabSearch, this->search)

void tab::Tab::resize(const QSize size) {
	// Resize view
	if (this->view != Q_NULLPTR) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSize,  "Resize view to" << size);
		this->view->resize(size);
	}
	QWidget::resize(size);
}
