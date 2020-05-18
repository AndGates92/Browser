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

main_window_status_bar::MainWindowStatusBar::MainWindowStatusBar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), userInput(this->newWindowLabel()), contentPath(this->newWindowLabel()), scroll(this->newWindowLabel()), info(this->newWindowLabel()), loadBar(this->newProgressBar()) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar constructor");

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
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowStatusBarOverall,  "Main window status bar destructor");

	if (this->userInput != Q_NULLPTR) {
		delete this->userInput;
	}
	if (this->contentPath != Q_NULLPTR) {
		delete this->contentPath;
	}
	if (this->scroll != Q_NULLPTR) {
		delete this->scroll;
	}
	if (this->info != Q_NULLPTR) {
		delete this->info;
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
	layout->addWidget(this->userInput);

	// path to the content
	layout->addWidget(this->contentPath);

	// scroll
	layout->addWidget(this->scroll);

	// info
	layout->addWidget(this->info);

	// load bar
	layout->addWidget(this->loadBar);

	layout->setSpacing(main_window_status_bar::horizontalWidgetSpacing);
	layout->setContentsMargins(main_window_status_bar::leftMargin, main_window_status_bar::topMargin, main_window_status_bar::rightMargin, main_window_status_bar::bottomMargin);

	this->setLayout(layout);
}

PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getUserInput, elided_label::ElidedLabel, this->userInput)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getContentPath, elided_label::ElidedLabel, this->contentPath)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getScroll, elided_label::ElidedLabel, this->scroll)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getInfo, elided_label::ElidedLabel, this->info)
PTR_GETTER(main_window_status_bar::MainWindowStatusBar::getLoadBar, progress_bar::ProgressBar, this->loadBar)

QSize main_window_status_bar::MainWindowStatusBar::minimumSizeHint() const {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + main_window_status_bar::topMargin + main_window_status_bar::bottomMargin;

	return QSize(width,height);
}

void main_window_status_bar::MainWindowStatusBar::setVScroll(const int & vScroll) {
	QString vScrollText(QString::null);
	// Keep 3 characters for all scroll positions
	if (vScroll == 0) {
		vScrollText.append("top");
	} else if (vScroll == 100) {
		vScrollText.append("bot");
	} else {
		vScrollText.append(QString("%1").arg(vScroll, 2, 10, QChar('0')));
		vScrollText.append("%");
	}

	this->scroll->setText(vScrollText);
}
