/**
 * @copyright
 * @file open_prompt.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Open Prompt functions
 */

#include <string>

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QDir>
#include <qt5/QtCore/QFile>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QFileDialog>

#include "logging_macros.h"
#include "global_types.h"
#include "open_prompt.h"
#include "exception_macros.h"


// Categories
Q_LOGGING_CATEGORY(openPromptOverall, "openPrompt.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openPromptLayout, "openPrompt.layout", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openPromptOpen, "openPrompt.open_button", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openPromptCancel, "openPrompt.cancel_button", MSG_TYPE_LEVEL)

open_prompt::OpenPrompt::OpenPrompt(QWidget * parent, Qt::WindowFlags flags) : main_window_prompt_menu::MainWindowPromptMenu(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openPromptOverall,  "Creating open prompt");

	// Create widgets to put in the window
	this->fillPrompt();

	// define window layout
	this->promptLayout();

	// Connect signals and slots
	this->connectSignals();

}

open_prompt::OpenPrompt::~OpenPrompt() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openPromptOverall,  "Destructor of open prompt class");
	if (this->text != Q_NULLPTR) {
		delete this->text;
	}
}

void open_prompt::OpenPrompt::promptLayout() {
	// Layout
	// -------------------------------------------------
	// |           <text to open>          | <browse>  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------
	QGridLayout * layout = new QGridLayout(this);
	int textRowSpan = 1;
	int textColumnSpan = 4;
	int textFromRow = 0;
	int textFromColumn = 0;
	layout->addWidget(this->text, textFromRow, textFromColumn, textRowSpan, textColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openPromptLayout,  "Text: start coordinates: row " << textFromRow << " and column " << textFromColumn << " width " << textColumnSpan << " height " << textRowSpan);
	this->setLayout(layout);
}

void open_prompt::OpenPrompt::fillPrompt() {
	this->text = new QLineEdit(this);
	this->text->setPlaceholderText(tr("<URL or file to open>"));

}

void open_prompt::OpenPrompt::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openPromptOverall,  "Connect signals");

}
