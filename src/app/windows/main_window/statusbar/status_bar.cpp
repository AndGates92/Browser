/**
 * @copyright
 * @file status_bar.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <QtWidgets/QHBoxLayout>

#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/windows/main_window/statusbar/status_bar.h"

// Categories
LOGGING_CONTEXT(mainWindowStatusBarOverall, mainWindowStatusBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace status_bar {

			namespace {

				/**
				 * @brief default origin of text in status bar widget
				 *
				 */
				static const QPoint textOrigin(0,0);

				/**
				 * @brief bottom information text height
				 *
				 */
				static constexpr int textHeight = 20;

				/**
				 * @brief horizontal spacing between widgets
				 *
				 */
				static constexpr int horizontalWidgetSpacing = 0;

				/**
				 * @brief left margin between widget and window
				 *
				 */
				static constexpr int leftMargin = 0;

				/**
				 * @brief right margin between widget and window
				 *
				 */
				static constexpr int rightMargin = 0;

				/**
				 * @brief top margin between widget and window
				 *
				 */
				static constexpr int topMargin = 0;

				/**
				 * @brief bottom margin between widget and window
				 *
				 */
				static constexpr int bottomMargin = 0;

				/**
				 * @brief minimum value of scrolling
				 *
				 */
				static constexpr int minScrollValue = 0;

				/**
				 * @brief maximum value of scrolling
				 *
				 */
				static constexpr int maxScrollValue = 100;

				/**
				 * @brief string to print when cursor is at the top of the page
				 *
				 */
				static const QString topScroll = "top";

				/**
				 * @brief string to print when cursor is at the bottom of the page
				 *
				 */
				static const QString bottomScroll = "bot";

			}

		}

	}

}

app::main_window::status_bar::StatusBar::StatusBar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), userInput(Q_NULLPTR), contentPath(Q_NULLPTR), scroll(Q_NULLPTR), info(Q_NULLPTR), searchResult(Q_NULLPTR), loadBar(Q_NULLPTR) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar constructor");

	this->userInput = std::move(this->newWindowLabel());
	this->contentPath = std::move(this->newWindowLabel());
	this->scroll= std::move(this->newWindowLabel());
	this->info = std::move(this->newWindowLabel());
	this->searchResult = std::move(this->newWindowLabel());
	this->loadBar = std::move(this->newProgressBar());

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	this->setStyleSheet(
		"QWidget {"
			"background-color: black;"
		"}"
	);

	// user input
	this->userInput->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	// path to the content
	this->contentPath->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->contentPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// info
	this->info->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->info->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// scroll
	this->scroll->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->scroll->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// search result
	this->showSearchResult(false);
	this->searchResult->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->searchResult->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// loadBar
	this->loadBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// Populate statusbar
	this->fillStatusBar();
}

app::main_window::status_bar::StatusBar::~StatusBar() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar destructor");

}

std::unique_ptr<app::elided_label::ElidedLabel> app::main_window::status_bar::StatusBar::newWindowLabel() {
	std::unique_ptr<app::elided_label::ElidedLabel> newLabel = std::make_unique<app::elided_label::ElidedLabel>(this, this->windowFlags(), QString(), app::main_window::status_bar::textOrigin, Qt::ElideRight);
	newLabel->setAttribute(Qt::WA_DeleteOnClose);
	newLabel->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	newLabel->setFixedHeight(app::main_window::status_bar::textHeight);
	newLabel->setTextFormat(Qt::PlainText);
	// Align at the bottom of the widget - this override the default of vertically centered
	newLabel->setAlignment(Qt::AlignBottom);
	// Set style sheet from the parent object because it can be customized based on the parent object properties
	newLabel->setStyleSheet(
		"QLabel {"
			// Backgorund color to be inherited from the parent one
			"background: inherit; "
			// Text color
			// Set to white as status bar backgorund color is black
			"color: white; "
			"text-align: center; "
			"border-right: 1px solid inherit; "
			"border-left: 1px solid inherit; "
			// Inherit font
			"font: inherit; "
		"}"
	);

	return newLabel;
}

std::unique_ptr<app::progress_bar::ProgressBar> app::main_window::status_bar::StatusBar::newProgressBar() {
	std::unique_ptr<app::progress_bar::ProgressBar> bar = std::make_unique<app::progress_bar::ProgressBar>(this);

	// Set style sheet from the parent object because it can be customized based on the parent object properties
	bar->setStyleSheet(
		"QProgressBar {"
			// Backgorund color to be inherited from the parent one
			"background-color: inherit; "
			"text-align: center; "
			// Text color
			// Set to black as progress bar backgorund color is white
			"color: black; "
			// How rounded borders are. No rounding in this case
			"border-radius: 0px; "
			"border-right: 1px solid inherit; "
			"border-left: 1px solid inherit; "
			// Inherit font
			"font: inherit; "
		"}"
		"QProgressBar::chunk {"
			// Set to white as status bar backgorund color is black
			"background-color: white; "
			"margin-left: 2px; "
			"margin-right: 2px; "
			"margin-top: 4px; "
			"margin-bottom: 4px; "
		"}"
	);

	return bar;
}

void app::main_window::status_bar::StatusBar::fillStatusBar() {

	// Layout
	// ------------------------------------------------------------------------------------
	// | <user text> |      <content>     |   <info>   | <progress bar> | <search result> |
	// ------------------------------------------------------------------------------------

	QHBoxLayout * layout = new QHBoxLayout(this);

	// user input text
	layout->addWidget(this->userInput.get());

	// path to the content
	layout->addWidget(this->contentPath.get());

	// scroll
	layout->addWidget(this->scroll.get());

	// info
	layout->addWidget(this->info.get());

	// load bar
	layout->addWidget(this->loadBar.get());

	// search result
	layout->addWidget(this->searchResult.get());

	layout->setSpacing(app::main_window::status_bar::horizontalWidgetSpacing);
	layout->setContentsMargins(app::main_window::status_bar::leftMargin, app::main_window::status_bar::topMargin, app::main_window::status_bar::rightMargin, app::main_window::status_bar::bottomMargin);

	this->setLayout(layout);
}

QSize app::main_window::status_bar::StatusBar::minimumSizeHint() const {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + app::main_window::status_bar::topMargin + app::main_window::status_bar::bottomMargin;

	return QSize(width,height);
}

bool app::main_window::status_bar::StatusBar::isValidScrollValue(const int & value) const {
	return  ((value >= app::main_window::status_bar::minScrollValue) && (value <= app::main_window::status_bar::maxScrollValue));
}

void app::main_window::status_bar::StatusBar::setVScroll(const int & vScroll) {
	QString vScrollText = QString();
	// Keep 3 characters for all scroll positions
	if (this->isValidScrollValue(vScroll) == true) {
		if ((vScroll == app::main_window::status_bar::minScrollValue) && (app::main_window::status_bar::topScroll.isEmpty() == false)) {
			vScrollText.append(app::main_window::status_bar::topScroll);
		} else if ((vScroll == app::main_window::status_bar::maxScrollValue) && (app::main_window::status_bar::bottomScroll.isEmpty() == false)) {
			vScrollText.append(app::main_window::status_bar::bottomScroll);
		} else {
			// arg(value, field width, base, fill character)
			vScrollText.append(QString("%1").arg(vScroll, 2, 10, QChar('0')));
			vScrollText.append("%");
		}
	}

	this->scroll->setText(vScrollText);
}

int app::main_window::status_bar::StatusBar::getVScroll() const {
	QString vScrollText(this->scroll->text());
	int topCompare = QString::compare(vScrollText, app::main_window::status_bar::topScroll);
	int bottomCompare = QString::compare(vScrollText, app::main_window::status_bar::bottomScroll);

	int value = 0;

	if (topCompare == 0) {
		value = app::main_window::status_bar::minScrollValue;
	} else if (bottomCompare == 0) {
		value = app::main_window::status_bar::maxScrollValue;
	} else {
		vScrollText.resize(vScrollText.size() - 1);
		bool success = false;
		value = vScrollText.toInt(&success, 10);
		EXCEPTION_ACTION_COND((success == false), throw, "Conversion of " << vScrollText << " to integer failed");
	}

	return value;
}

void app::main_window::status_bar::StatusBar::setProgressValue(const int & value) {
	this->loadBar->setValue(value);
}
BASE_GETTER(app::main_window::status_bar::StatusBar::getProgressValue, int, this->loadBar->value())
BASE_GETTER(app::main_window::status_bar::StatusBar::getLoadBarVisibility, bool, this->loadBar->isVisible())

void app::main_window::status_bar::StatusBar::setInfoText(const QString & text) {
	this->info->setText(text);
}
CONST_GETTER(app::main_window::status_bar::StatusBar::getInfoText, QString, this->info->text())

void app::main_window::status_bar::StatusBar::setUserInputText(const QString & text) {
	this->userInput->setText(text);
}
CONST_GETTER(app::main_window::status_bar::StatusBar::getUserInputText, QString, this->userInput->text())

void app::main_window::status_bar::StatusBar::setContentPathText(const QString & text) {
	this->contentPath->setText(text);
}
CONST_GETTER(app::main_window::status_bar::StatusBar::getContentPathText, QString, this->contentPath->text())

void app::main_window::status_bar::StatusBar::setSearchResultText(const QString & text) {
	this->searchResult->setText(text);
}
CONST_GETTER(app::main_window::status_bar::StatusBar::getSearchResultText, QString, this->searchResult->text())

void app::main_window::status_bar::StatusBar::showSearchResult(const bool & showWidget) {
	const bool isTextEmpty = this->searchResult->text().isEmpty();
	if ((showWidget == true) && (isTextEmpty == false)) {
		this->searchResult->show();
	} else {
		this->searchResult->hide();
	}
}
