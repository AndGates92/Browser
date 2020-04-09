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

#include "logging_macros.h"
#include "tab.h"

// Categories
Q_LOGGING_CATEGORY(tabOverall, "tab.overall", MSG_TYPE_LEVEL)

tab::Tab::Tab(QWidget * parent): QWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab constructor");

	tab_load_manager::TabLoadManager * lMgr = new tab_load_manager::TabLoadManager(this);
	this->setLoadManager(lMgr);
}

tab::Tab::~Tab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabOverall,  "Tab destructor");

	delete this->loadManager;

}

void tab::Tab::setLoadManager(tab_load_manager::TabLoadManager * mgr) {
	// Do nothing if old and new managers are the same pointer
	if (this->loadManager != mgr) {
		if (this->loadManager != Q_NULLPTR) {
			delete this->loadManager;
		}

		this->loadManager = mgr;

	}

}

tab_load_manager::TabLoadManager * tab::Tab::getLoadManager() const {
	return this->loadManager;
}
