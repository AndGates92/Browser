/**
 * @copyright
 * @file tab_load_manager.cpp
 * @author Andrea Gianarda
 * @date 09rd April 2020
 * @brief Tab Load Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "tab_load_manager.h"

// Categories
Q_LOGGING_CATEGORY(tabLoadManagerOverall, "tabLoadManager.overall", MSG_TYPE_LEVEL)

tab_load_manager::TabLoadManager::TabLoadManager(QWidget * parent): QWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabLoadManagerOverall,  "TabLoadManager constructor");

	this->progress = 0;

}

tab_load_manager::TabLoadManager::~TabLoadManager() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabLoadManagerOverall,  "TabLoadManager destructor");

}

void tab_load_manager::TabLoadManager::resetProgress() {
	this->setProgress(0);
}

void tab_load_manager::TabLoadManager::setProgress(int value) {
	this->progress = value;
	emit progressChanged(this->progress);
}

int tab_load_manager::TabLoadManager::getProgress() const {
	return this->progress;
}
