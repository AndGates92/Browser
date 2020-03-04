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
	this->loadBar = new progress_bar::ProgressBar(this);

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
	// Disable widget resizing
	newLabel->setStyleSheet(
		"QLabel {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border-right: 1px solid black; "
			"border-left: 1px solid black; "
		"}"
	);

	return newLabel;
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
