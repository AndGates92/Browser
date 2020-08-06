/**
 * @copyright
 * @file main_window_status_bar.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtWidgets/QHBoxLayout>

#include "main_window_status_bar.h"
#include "function_macros.h"
#include "logging_macros.h"
#include "global_enums.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowStatusBarOverall, "mainWindowStatusBar.overall", MSG_TYPE_LEVEL)

namespace main_window_status_bar {

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

	}

}

main_window_status_bar::MainWindowStatusBar::MainWindowStatusBar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), userInput(Q_NULLPTR), contentPath(Q_NULLPTR), scroll(Q_NULLPTR), info(Q_NULLPTR), loadBar(Q_NULLPTR) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar constructor");

	this->userInput = std::move(this->newWindowLabel());
	this->contentPath = std::move(this->newWindowLabel());
	this->scroll= std::move(this->newWindowLabel());
	this->info = std::move(this->newWindowLabel());
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

	// loadBar
	this->loadBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// Populate statusbar
	this->fillStatusBar();
}

main_window_status_bar::MainWindowStatusBar::~MainWindowStatusBar() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar destructor");

}

std::unique_ptr<elided_label::ElidedLabel> main_window_status_bar::MainWindowStatusBar::newWindowLabel() {
	std::unique_ptr<elided_label::ElidedLabel> newLabel = std::make_unique<elided_label::ElidedLabel>(this, this->windowFlags(), QString(), main_window_status_bar::textOrigin, Qt::ElideRight);
	newLabel->setAttribute(Qt::WA_DeleteOnClose);
	newLabel->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	newLabel->setFixedHeight(main_window_status_bar::textHeight);
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

std::unique_ptr<progress_bar::ProgressBar> main_window_status_bar::MainWindowStatusBar::newProgressBar() {
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

void main_window_status_bar::MainWindowStatusBar::fillStatusBar() {

	// Layout
	// ------------------------------------------------------------------
	// | <user text> |      <content>     |   <info>   | <progress bar> |
	// ------------------------------------------------------------------

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

	layout->setSpacing(main_window_status_bar::horizontalWidgetSpacing);
	layout->setContentsMargins(main_window_status_bar::leftMargin, main_window_status_bar::topMargin, main_window_status_bar::rightMargin, main_window_status_bar::bottomMargin);

	this->setLayout(layout);
}

QSize main_window_status_bar::MainWindowStatusBar::minimumSizeHint() const {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + main_window_status_bar::topMargin + main_window_status_bar::bottomMargin;

	return QSize(width,height);
}

bool main_window_status_bar::MainWindowStatusBar::isValidScrollValue(const int & value) const {
	return  ((value >= main_window_status_bar::minScrollValue) && (value <= main_window_status_bar::maxScrollValue));
}

void main_window_status_bar::MainWindowStatusBar::setVScroll(const int & vScroll) {
	QString vScrollText = QString();
	// Keep 3 characters for all scroll positions
	if (this->isValidScrollValue(vScroll) == true) {
		if (vScroll == main_window_status_bar::minScrollValue) {
			vScrollText.append("top");
		} else if (vScroll == main_window_status_bar::maxScrollValue) {
			vScrollText.append("bot");
		} else {
			vScrollText.append(QString("%1").arg(vScroll, 2, 10, QChar('0')));
			vScrollText.append("%");
		}
	}

	this->scroll->setText(vScrollText);
}

void main_window_status_bar::MainWindowStatusBar::setProgressValue(const int & value) {
	this->loadBar->setValue(value);
}

void main_window_status_bar::MainWindowStatusBar::setInfoText(const QString & text) {
	this->info->setText(text);
}

void main_window_status_bar::MainWindowStatusBar::setUserInputText(const QString & text) {
	this->userInput->setText(text);
}

void main_window_status_bar::MainWindowStatusBar::setContentPathText(const QString & text) {
	this->contentPath->setText(text);
}
