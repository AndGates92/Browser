/**
 * @copyright
 * @file open_button_window.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Open Button Window functions
 */

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QDir>
#include <qt5/QtCore/QFile>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QFileDialog>

#include "global_macros.h"
#include "global_types.h"
#include "open_button_window.h"


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

}

open_button_window::OpenButtonWindow::~OpenButtonWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Destructor");
	delete label;
	delete text;
	delete openButton;
	delete cancelButton;
}

void open_button_window::OpenButtonWindow::open() {
	QString filename(text->displayText());

	// Do not try to open and read file if the name is empty
	if (!filename.isEmpty()) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Opening " << filename);

		QFile userFile(filename);
		bool fileOpenRet = userFile.open(QIODevice::ReadOnly | QIODevice::Text);
		if (!fileOpenRet) {
			qCritical(openButtonWindowOpen) << "Unable to open file " << filename;
			exit(EXIT_FAILURE);
		}

		QString fileContent("");
		while(!userFile.atEnd()) {
			char fileLine[open_button_window::userFileSize];
			qint64 bytesRead = userFile.readLine(fileLine, sizeof(fileLine));
			if (bytesRead == -1) {
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Nothing was read from file " << filename);
			} else if (bytesRead == 0) {
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Nothing was read from file " << filename << " however no error was returned");
			} else {
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Line read: " << fileLine);
			}
			fileContent.append(fileLine);
		}

		emit this->fileRead(fileContent);

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Close " << filename);
		userFile.close();
	}

	// Close window when Open is clicked
	this->close();
}

void open_button_window::OpenButtonWindow::browse() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Browsing files");
	QFileDialog * fileBrowser = new QFileDialog(this, Qt::Popup);
	fileBrowser->setOption(QFileDialog::DontResolveSymlinks, true);
	fileBrowser->setViewMode(QFileDialog::Detail);
	QString filename = fileBrowser->getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("Web Pages (*.html);;All (*.*)"));
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Selected " << filename);
	this->text->setText(filename);
}

void open_button_window::OpenButtonWindow::cancel() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowCancel,  "Deleting dialog as Cancel button has been clicked");
	this->close();
}

void open_button_window::OpenButtonWindow::windowLayout() {
	// Layout
	// -------------------------------------------------
	// |  <label>  |     <text to open>    | <browse>  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------
	QGridLayout * layout = new QGridLayout(this);
	int labelRowSpan = 1;
	int labelColumnSpan = 1;
	int labelFromRow = 0;
	int labelFromColumn = 0;
	layout->addWidget(this->label, labelFromRow, labelFromColumn, labelRowSpan, labelColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Label: start coordinates: row " << labelFromRow << " and column " << labelFromColumn << " width " << labelColumnSpan << " height " << labelRowSpan);
	int textRowSpan = labelRowSpan;
	int textColumnSpan = 3;
	int textFromRow = labelFromRow;
	int textFromColumn = labelFromColumn + labelColumnSpan;
	layout->addWidget(this->text, textFromRow, textFromColumn, textRowSpan, textColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Text: start coordinates: row " << textFromRow << " and column " << textFromColumn << " width " << textColumnSpan << " height " << textRowSpan);
	int browseButtonRowSpan = labelRowSpan;
	int browseButtonColumnSpan = 1;
	int browseButtonFromRow = labelFromRow;
	int browseButtonFromColumn = textFromColumn + textColumnSpan;
	layout->addWidget(this->browseButton, browseButtonFromRow, browseButtonFromColumn, browseButtonRowSpan, browseButtonColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Open button: start coordinates: row " << browseButtonFromRow << " and column " << browseButtonFromColumn << " width " << browseButtonColumnSpan << " height " << browseButtonRowSpan);
	int openButtonRowSpan = 1;
	int openButtonColumnSpan = 1;
	int openButtonFromRow = labelFromRow + labelRowSpan;
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
	this->label = new QLabel(tr("Open -> "), this);
	this->label->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	this->label->setAlignment(Qt::AlignCenter);

	this->text = new QLineEdit(this);
	this->text->setPlaceholderText(tr("<URL or file to open>"));

	this->openButton = new QPushButton("Open", this);
	connect(this->openButton, &QPushButton::pressed, this, &open_button_window::OpenButtonWindow::open);
	this->browseButton = new QPushButton("Browse", this);
	connect(this->browseButton, &QPushButton::pressed, this, &open_button_window::OpenButtonWindow::browse);
	this->cancelButton = new QPushButton("Cancel", this);
	connect(this->cancelButton, &QPushButton::released, this, &open_button_window::OpenButtonWindow::cancel);
}
