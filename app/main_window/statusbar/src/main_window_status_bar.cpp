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
#include "function_macros.h"
#include "logging_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowStatusBarOverall, "mainWindowStatusBar.overall", MSG_TYPE_LEVEL)

main_window_status_bar::MainWindowStatusBar::MainWindowStatusBar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), userInputText(this->newWindowLabel()), contentPathText(this->newWindowLabel()), scroll(this->newWindowLabel()), infoText(this->newWindowLabel()), loadBar(this->newProgressBar()) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar constructor");

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	this->setStyleSheet(
		"QWidget {"
			"background-color: black; "
		"}"
	);

	// user input
	this->userInputText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	// path to the content
	this->contentPathText->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->contentPathText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// info
	this->infoText->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->infoText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// scroll
	this->scroll->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// loadBar
	this->loadBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// Populate statusbar
	this->fillStatusBar();
}

main_window_status_bar::MainWindowStatusBar::~MainWindowStatusBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar destructor");

	if (this->userInputText != Q_NULLPTR) {
		delete this->userInputText;
	}
	if (this->contentPathText != Q_NULLPTR) {
		delete this->contentPathText;
	}
	if (this->scroll != Q_NULLPTR) {
		delete this->scroll;
	}
	if (this->infoText != Q_NULLPTR) {
		delete this->infoText;
	}
	if (this->loadBar != Q_NULLPTR) {
		delete this->loadBar;
	}
}

elided_label::ElidedLabel * main_window_status_bar::MainWindowStatusBar::newWindowLabel() {
	elided_label::ElidedLabel * newLabel = new elided_label::ElidedLabel(this, this->windowFlags(), QString::null, main_window_status_bar::textOrigin, Qt::ElideRight);
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

	QHBoxLayout * layout = new QHBoxLayout(this);

	// user input text
	layout->addWidget(this->userInputText);

	// path to the content
	layout->addWidget(this->contentPathText);

	// scroll
	layout->addWidget(this->scroll);

	// info
	layout->addWidget(this->infoText);

	// load bar
	layout->addWidget(this->loadBar);

	layout->setSpacing(main_window_status_bar::horizontalWidgetSpacing);
	layout->setContentsMargins(main_window_status_bar::leftMargin, main_window_status_bar::topMargin, main_window_status_bar::rightMargin, main_window_status_bar::bottomMargin);

	this->setLayout(layout);
}

PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getUserInputText, elided_label::ElidedLabel, this->userInputText)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getContentPathText, elided_label::ElidedLabel, this->contentPathText)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getScroll, elided_label::ElidedLabel, this->scroll)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getInfoText, elided_label::ElidedLabel, this->infoText)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getLoadBar, progress_bar::ProgressBar, this->loadBar)

QSize main_window_status_bar::MainWindowStatusBar::minimumSizeHint() const {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + main_window_status_bar::topMargin + main_window_status_bar::bottomMargin;

	return QSize(width,height);
}

void main_window_status_bar::MainWindowStatusBar::setVScroll(const int & vScroll) {

	QString vScrollText(QString::null);
	vScrollText.setNum(vScroll, 10);
	vScrollText.append("%");

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "DADA vScroll " << vScroll << " string " << vScrollText);

	this->scroll->setText(vScrollText);

}
