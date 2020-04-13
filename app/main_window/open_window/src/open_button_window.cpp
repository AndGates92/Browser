/**
 * @copyright
 * @file open_button_window.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Open Button Window functions
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
#include "global_functions.h"
#include "open_button_window.h"
#include "exception_macros.h"


// Categories
Q_LOGGING_CATEGORY(openButtonWindowOverall, "openButtonWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowLayout, "openButtonWindow.layout", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowOpen, "openButtonWindow.open_button", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowCancel, "openButtonWindow.cancel_button", MSG_TYPE_LEVEL)

open_button_window::OpenButtonWindow::OpenButtonWindow(QWidget * parent, Qt::WindowFlags flags) : QDialog(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Creating open button window");

	// Set modal because other windows should not be active
	this->setModal(true);

	this->setFocusPolicy(Qt::StrongFocus);

	// Create widgets to put in the window
	this->fillWindow();

	// define window layout
	this->windowLayout();

	// Connect signals and slots
	this->connectSignals();

}

open_button_window::OpenButtonWindow::~OpenButtonWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Destructor of OpenButtonWindow class");
	delete this->text;
	delete this->openButton;
	delete this->browseButton;
	delete this->cancelButton;
}

void open_button_window::OpenButtonWindow::open() {
	const QString filename(text->displayText());

	// Do not try to open and read file if the name is empty
	if (!filename.isEmpty()) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Opening " << filename);
		emit this->fileRead(filename, nullptr);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Close " << filename);
	}

	// Close window when Open is clicked
	this->close();
}

void open_button_window::OpenButtonWindow::browse() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Browsing files");
	QFileDialog * fileBrowser = new QFileDialog(this, Qt::Popup);
	fileBrowser->setOption(QFileDialog::DontResolveSymlinks, true);
	fileBrowser->setViewMode(QFileDialog::Detail);
	// Returns QString::null if user presses Cancel
	QString filename = fileBrowser->getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("Web Pages (*.html);;All (*.*)"));
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Selected " << filename);
	if (filename != QString::null) {
		// Do not update text if user presses cancel
		this->text->setText(filename);
	}
}

void open_button_window::OpenButtonWindow::cancel() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowCancel,  "Deleting dialog as Cancel button has been clicked");
	this->close();
}

void open_button_window::OpenButtonWindow::windowLayout() {
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
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Text: start coordinates: row " << textFromRow << " and column " << textFromColumn << " width " << textColumnSpan << " height " << textRowSpan);
	int browseButtonRowSpan = textRowSpan;
	int browseButtonColumnSpan = 1;
	int browseButtonFromRow = textFromRow;
	int browseButtonFromColumn = textFromColumn + textColumnSpan;
	layout->addWidget(this->browseButton, browseButtonFromRow, browseButtonFromColumn, browseButtonRowSpan, browseButtonColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Browse button: start coordinates: row " << browseButtonFromRow << " and column " << browseButtonFromColumn << " width " << browseButtonColumnSpan << " height " << browseButtonRowSpan);
	int openButtonRowSpan = 1;
	int openButtonColumnSpan = 1;
	int openButtonFromRow = textFromRow + textRowSpan;
	int openButtonFromColumn = 0;
	layout->addWidget(this->openButton, openButtonFromRow, openButtonFromColumn, openButtonRowSpan, openButtonColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Open button: start coordinates: row " << openButtonFromRow << " and column " << openButtonFromColumn << " width " << openButtonColumnSpan << " height " << openButtonRowSpan);
	int cancelButtonRowSpan = openButtonRowSpan;
	int cancelButtonColumnSpan = 2;
	int cancelButtonFromRow = openButtonFromRow;
	int cancelButtonFromColumn = textFromColumn + textColumnSpan;
	layout->addWidget(this->cancelButton, cancelButtonFromRow, cancelButtonFromColumn, cancelButtonRowSpan, cancelButtonColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Cancel button: start coordinates: row " << cancelButtonFromRow << " and column " << cancelButtonFromColumn << " width " << cancelButtonColumnSpan << " height " << cancelButtonRowSpan);

	this->setLayout(layout);
}

void open_button_window::OpenButtonWindow::fillWindow() {
	this->text = new QLineEdit(this);
	this->text->setPlaceholderText(tr("<URL or file to open>"));

	this->openButton = new QPushButton("Open", this);
	this->browseButton = new QPushButton("Browse", this);
	this->cancelButton = new QPushButton("Cancel", this);
}

void open_button_window::OpenButtonWindow::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Connect signals");

	connect(this->openButton, &QPushButton::pressed, this, &open_button_window::OpenButtonWindow::open);
	connect(this->browseButton, &QPushButton::pressed, this, &open_button_window::OpenButtonWindow::browse);
	connect(this->cancelButton, &QPushButton::released, this, &open_button_window::OpenButtonWindow::cancel);
}
