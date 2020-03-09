/**
 * @copyright
 * @file main_window_status_bar.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QHBoxLayout>

#include "main_window_status_bar.h"
#include "global_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowStatusBarOverall, "mainWindowStatusBar.overall", MSG_TYPE_LEVEL)

main_window_status_bar::MainWindowStatusBar::MainWindowStatusBar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar constructor");

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	this->setStyleSheet(
		"QWidget {"
			"background-color: black; "
		"}"
	);

	// user input
	this->userInputText = this->newWindowLabel();
	this->userInputText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
	this->userInputText->setFocus(Qt::OtherFocusReason);

	// path to the content
	this->contentPathText = this->newWindowLabel();
	this->contentPathText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// info
	this->infoText = this->newWindowLabel();
	this->infoText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// info
	this->loadBar = this->newProgressBar();

	// Populate statusbar
	this->fillStatusBar();
}

main_window_status_bar::MainWindowStatusBar::~MainWindowStatusBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar destructor");

	delete this->userInputText;
	delete this->contentPathText;
	delete this->infoText;
	delete this->loadBar;
}

elided_label::ElidedLabel * main_window_status_bar::MainWindowStatusBar::newWindowLabel() {
	elided_label::ElidedLabel * newLabel = new elided_label::ElidedLabel(QString::null, main_window_status_bar::textOrigin, this, this->windowFlags(), Qt::ElideRight);
	newLabel->setAttribute(Qt::WA_DeleteOnClose);
	newLabel->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	newLabel->setFixedHeight(main_window_status_bar::textHeight);
	newLabel->setTextFormat(Qt::PlainText);
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

progress_bar::ProgressBar * main_window_status_bar::MainWindowStatusBar::newProgressBar() {
	progress_bar::ProgressBar * bar = new progress_bar::ProgressBar(this);

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

	QHBoxLayout * layout = new QHBoxLayout();

	// user input text
	layout->addWidget(this->userInputText);

	// path to the content
	layout->addWidget(this->contentPathText);

	// info
	layout->addWidget(this->infoText);

	// load bar
	layout->addWidget(this->loadBar);

	layout->setSpacing(main_window_status_bar::horizontalWidgetSpacing);
	layout->setContentsMargins(main_window_status_bar::leftMargin, main_window_status_bar::topMargin, main_window_status_bar::rightMargin, main_window_status_bar::bottomMargin);

	this->setLayout(layout);
}

elided_label::ElidedLabel * main_window_status_bar::MainWindowStatusBar::getUserInputText() {
	return this->userInputText;
}

elided_label::ElidedLabel * main_window_status_bar::MainWindowStatusBar::getContentPathText() {
	return this->contentPathText;
}

elided_label::ElidedLabel * main_window_status_bar::MainWindowStatusBar::getInfoText() {
	return this->infoText;
}

progress_bar::ProgressBar * main_window_status_bar::MainWindowStatusBar::getLoadBar() {
	return this->loadBar;
}

QSize main_window_status_bar::MainWindowStatusBar::minimumSizeHint() {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + main_window_status_bar::topMargin + main_window_status_bar::bottomMargin;

	return QSize(width,height);
}
