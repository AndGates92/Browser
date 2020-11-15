/**
 * @copyright
 * @file status_bar.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <QtWidgets/QHBoxLayout>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "windows/main_window/statusbar/include/status_bar.h"

// Categories
LOGGING_CONTEXT(mainWindowStatusBarOverall, mainWindowStatusBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace main_window {

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

main_window::StatusBar::StatusBar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), userInput(Q_NULLPTR), contentPath(Q_NULLPTR), scroll(Q_NULLPTR), info(Q_NULLPTR), searchResult(Q_NULLPTR), loadBar(Q_NULLPTR) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar constructor");

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

main_window::StatusBar::~StatusBar() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar destructor");

}

std::unique_ptr<elided_label::ElidedLabel> main_window::StatusBar::newWindowLabel() {
	std::unique_ptr<elided_label::ElidedLabel> newLabel = std::make_unique<elided_label::ElidedLabel>(this, this->windowFlags(), QString(), main_window::textOrigin, Qt::ElideRight);
	newLabel->setAttribute(Qt::WA_DeleteOnClose);
	newLabel->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	newLabel->setFixedHeight(main_window::textHeight);
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

std::unique_ptr<progress_bar::ProgressBar> main_window::StatusBar::newProgressBar() {
	std::unique_ptr<progress_bar::ProgressBar> bar = std::make_unique<progress_bar::ProgressBar>(this);

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

void main_window::StatusBar::fillStatusBar() {

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

	layout->setSpacing(main_window::horizontalWidgetSpacing);
	layout->setContentsMargins(main_window::leftMargin, main_window::topMargin, main_window::rightMargin, main_window::bottomMargin);

	this->setLayout(layout);
}

QSize main_window::StatusBar::minimumSizeHint() const {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + main_window::topMargin + main_window::bottomMargin;

	return QSize(width,height);
}

bool main_window::StatusBar::isValidScrollValue(const int & value) const {
	return  ((value >= main_window::minScrollValue) && (value <= main_window::maxScrollValue));
}

void main_window::StatusBar::setVScroll(const int & vScroll) {
	QString vScrollText = QString();
	// Keep 3 characters for all scroll positions
	if (this->isValidScrollValue(vScroll) == true) {
		if ((vScroll == main_window::minScrollValue) && (main_window::topScroll.isEmpty() == false)) {
			vScrollText.append(main_window::topScroll);
		} else if ((vScroll == main_window::maxScrollValue) && (main_window::bottomScroll.isEmpty() == false)) {
			vScrollText.append(main_window::bottomScroll);
		} else {
			// arg(value, field width, base, fill character)
			vScrollText.append(QString("%1").arg(vScroll, 2, 10, QChar('0')));
			vScrollText.append("%");
		}
	}

	this->scroll->setText(vScrollText);
}

int main_window::StatusBar::getVScroll() const {
	QString vScrollText(this->scroll->text());
	int topCompare = QString::compare(vScrollText, main_window::topScroll);
	int bottomCompare = QString::compare(vScrollText, main_window::bottomScroll);

	int value = 0;

	if (topCompare == 0) {
		value = main_window::minScrollValue;
	} else if (bottomCompare == 0) {
		value = main_window::maxScrollValue;
	} else {
		vScrollText.resize(vScrollText.size() - 1);
		bool success = false;
		value = vScrollText.toInt(&success, 10);
		EXCEPTION_ACTION_COND((success == false), throw, "Conversion of " << vScrollText << " to integer failed");
	}

	return value;
}

void main_window::StatusBar::setProgressValue(const int & value) {
	this->loadBar->setValue(value);
}
BASE_GETTER(main_window::StatusBar::getProgressValue, int, this->loadBar->value())
BASE_GETTER(main_window::StatusBar::getLoadBarVisibility, bool, this->loadBar->isVisible())

void main_window::StatusBar::setInfoText(const QString & text) {
	this->info->setText(text);
}
CONST_GETTER(main_window::StatusBar::getInfoText, QString, this->info->text())

void main_window::StatusBar::setUserInputText(const QString & text) {
	this->userInput->setText(text);
}
CONST_GETTER(main_window::StatusBar::getUserInputText, QString, this->userInput->text())

void main_window::StatusBar::setContentPathText(const QString & text) {
	this->contentPath->setText(text);
}
CONST_GETTER(main_window::StatusBar::getContentPathText, QString, this->contentPath->text())

void main_window::StatusBar::setSearchResultText(const QString & text) {
	this->searchResult->setText(text);
}
CONST_GETTER(main_window::StatusBar::getSearchResultText, QString, this->searchResult->text())

void main_window::StatusBar::showSearchResult(const bool & showWidget) {
	const bool isTextEmpty = this->searchResult->text().isEmpty();
	if ((showWidget == true) && (isTextEmpty == false)) {
		this->searchResult->show();
	} else {
		this->searchResult->hide();
	}
}
