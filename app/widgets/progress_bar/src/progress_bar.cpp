/**
 * @copyright
 * @file progress_bar.cpp
 * @author Andrea Gianarda
 * @date 04th of March 2020
 * @brief Progress bar functions
*/

// Qt libraries
#include <QtCore/QtGlobal>

#include "progress_bar.h"
#include "exception_macros.h"
#include "logging_macros.h"
#include "global_enums.h"

// Categories
Q_LOGGING_CATEGORY(progressBarOverall, "progressBar.overall", MSG_TYPE_LEVEL)

namespace progress_bar {

	namespace {
		/**
		 * @brief default progres bar alignment
		 *
		 */
		static constexpr Qt::Alignment progressAlignment = (Qt::AlignHCenter | Qt::AlignVCenter);

		/**
		 * @brief default direction of the text
		 *
		 */
		static constexpr QProgressBar::Direction progressTextDirection = QProgressBar::TopToBottom;

		/**
		 * @brief default visible text flag
		 *
		 */
		static constexpr bool progressTextVisible = true;

		/**
		 * @brief default format of the text
		 *
		 */
		static const QString barTextFormat("%p%");

		/**
		 * @brief default inverted progress flag
		 *
		 */
		static constexpr bool invertedProgress = false;
	}

}


progress_bar::ProgressBar::ProgressBar(QWidget * parent) : QProgressBar(parent) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, progressBarOverall,  "Progress bar constructor");

	this->setAlignment(progress_bar::progressAlignment);

	this->setInvertedAppearance(progress_bar::invertedProgress);

	this->setFormat(progress_bar::barTextFormat);
	this->setTextVisible(progress_bar::progressTextVisible);
	this->setTextDirection(progress_bar::progressTextDirection);

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

	// range
	this->setMinimum(progress_bar::ProgressBar::getMinimumValue());
	this->setMaximum(progress_bar::ProgressBar::getMaximumValue());

	// Hide the bar at the start
	this->setVisible(false);
}

void progress_bar::ProgressBar::setMaximum(const int value) {
	QProgressBar::setMaximum(value);
}

int progress_bar::ProgressBar::getMaximumValue() {
	return 100;
}

void progress_bar::ProgressBar::setMinimum(const int value) {
	QProgressBar::setMinimum(value);
}

int progress_bar::ProgressBar::getMinimumValue() {
	return 0;
}

progress_bar::ProgressBar::~ProgressBar() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, progressBarOverall,  "Progress bar destructor");
}

void progress_bar::ProgressBar::startLoading() {
	this->setValue(this->minimum());
}

void progress_bar::ProgressBar::setValue(const int & value) {
	this->setVisible(true);
	QProgressBar::setValue(value);

	// When tabs are refreshed, loadFinished is not send therefore endLoading slot is not called
	// Forcing call endLoading
	if (value == this->maximum()) {
		this->endLoading(true);
	}
}

void progress_bar::ProgressBar::endLoading(const bool & success) {

	QEXCEPTION_ACTION_COND((!success), throw,  "Operation didn't complete succesfully");

	// Hide progress bar after operation completes
	this->setVisible(false);
}

QSize progress_bar::ProgressBar::minimumSizeHint() {
	return this->sizeHint();
}

QSize progress_bar::ProgressBar::sizeHint() {
	const QWidget * parent = this->parentWidget();
	int width;
	if (parent == Q_NULLPTR) {
		width = QWidget::sizeHint().width();
	} else {
		width = parent->sizeHint().width();
	}

	const int height = this->fontMetrics().height();

	return QSize(width,height);
}
