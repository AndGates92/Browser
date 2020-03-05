/**
 * @copyright
 * @file progress_bar.cpp
 * @author Andrea Gianarda
 * @date 04th of March 2020
 * @brief Progress bar functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "progress_bar.h"
#include "global_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(progressBarOverall, "progressBar.overall", MSG_TYPE_LEVEL)

progress_bar::ProgressBar::ProgressBar(QWidget * parent) : QProgressBar(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, progressBarOverall,  "Progress bar constructor");

	this->setAlignment(progress_bar::progressAlignment);

	this->setInvertedAppearance(progress_bar::invertedProgress);

	this->setFormat(progress_bar::barTextFormat);
	this->setTextVisible(progress_bar::progressTextVisible);
	this->setTextDirection(progress_bar::progressTextDirection);

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

	// Hide the bar at the start
	this->setVisible(false);
}

progress_bar::ProgressBar::~ProgressBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, progressBarOverall,  "Progress bar destructor");
}

void progress_bar::ProgressBar::startLoading() {
	this->setVisible(true);
}

void progress_bar::ProgressBar::endLoading(bool success) {

	QEXCEPTION_ACTION_COND((!success), throw,  "Operation didn't complete succesfully");

	// Hide progress bar after operation completes
	this->setVisible(false);
}
