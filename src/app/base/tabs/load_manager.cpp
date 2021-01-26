/**
 * @copyright
 * @file load_manager.cpp
 * @author Andrea Gianarda
 * @date 09th April 2020
 * @brief Tab Load Manager functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/base/tabs/load_manager.h"

// Categories
LOGGING_CONTEXT(tabLoadManagerOverall, tabLoadManager.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabLoadManagerStatus, tabLoadManager.status, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::LoadManager::LoadManager(QWidget * parent): QWidget(parent), status(app::base::tab::load_status_e::IDLE), progress(0) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabLoadManagerOverall, "LoadManager constructor");

}

app::base::tab::LoadManager::~LoadManager() {
	LOG_INFO(app::logger::info_level_e::ZERO, tabLoadManagerOverall, "LoadManager destructor");

}

void app::base::tab::LoadManager::startLoading() {
	this->setProgress(0);
}

void app::base::tab::LoadManager::setProgress(const int & value) {
	if (this->progress != value) {
		this->progress = value;
		emit progressChanged(this->progress);
		this->setStatus(app::base::tab::load_status_e::LOADING);
	}
}

void app::base::tab::LoadManager::endLoading(const bool & success) {
	if (success == true) {
		this->setStatus(app::base::tab::load_status_e::FINISHED);
	} else {
		this->setStatus(app::base::tab::load_status_e::ERROR);
	}
}

void app::base::tab::LoadManager::setStatus(const app::base::tab::load_status_e & value) {
	if (this->status != value) {
		LOG_INFO(app::logger::info_level_e::ZERO, tabLoadManagerStatus, "tab load status changed from " << this->status << " to " << value);
		this->status = value;
		emit statusChanged(this->status);
	}
}

CONST_GETTER(app::base::tab::LoadManager::getProgress, int &, this->progress)

CONST_GETTER(app::base::tab::LoadManager::getStatus, app::base::tab::load_status_e &, this->status)
