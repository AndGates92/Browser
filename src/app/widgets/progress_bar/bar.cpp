/**
 * @copyright
 * @file bar.cpp
 * @author Andrea Gianarda
 * @date 04th of March 2020
 * @brief Progress bar functions
*/

#include "app/widgets/progress_bar/bar.h"
#include "app/shared/exception.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"

// Categories
LOGGING_CONTEXT(progressBarOverall, progressBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

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

}

app::progress_bar::Bar::Bar(QWidget * parent) : QProgressBar(parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, progressBarOverall,  "Progress bar constructor");

	this->setAlignment(app::progress_bar::progressAlignment);

	this->setInvertedAppearance(app::progress_bar::invertedProgress);

	this->setFormat(app::progress_bar::barTextFormat);
	this->setTextVisible(app::progress_bar::progressTextVisible);
	this->setTextDirection(app::progress_bar::progressTextDirection);

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

	// range
	this->setMinimum(app::progress_bar::Bar::getMinimumValue());
	this->setMaximum(app::progress_bar::Bar::getMaximumValue());

	// Hide the bar at the start
	this->setVisible(false);
}

void app::progress_bar::Bar::setMaximum(const int value) {
	QProgressBar::setMaximum(value);
}

int app::progress_bar::Bar::getMaximumValue() {
	return 100;
}

void app::progress_bar::Bar::setMinimum(const int value) {
	QProgressBar::setMinimum(value);
}

int app::progress_bar::Bar::getMinimumValue() {
	return 0;
}

app::progress_bar::Bar::~Bar() {
	LOG_INFO(app::logger::info_level_e::ZERO, progressBarOverall,  "Progress bar destructor");
}

void app::progress_bar::Bar::startLoading() {
	this->setValue(this->minimum());
}

void app::progress_bar::Bar::setValue(const int & value) {
	this->setVisible(true);
	QProgressBar::setValue(value);

	// When tabs are refreshed, loadFinished is not send therefore endLoading slot is not called
	// Forcing call endLoading
	if (value == this->maximum()) {
		this->endLoading(true);
	}
}

void app::progress_bar::Bar::endLoading(const bool & success) {

	EXCEPTION_ACTION_COND((!success), throw,  "Operation didn't complete succesfully");

	// Hide progress bar after operation completes
	this->setVisible(false);
}

QSize app::progress_bar::Bar::minimumSizeHint() {
	return this->sizeHint();
}

QSize app::progress_bar::Bar::sizeHint() {
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
