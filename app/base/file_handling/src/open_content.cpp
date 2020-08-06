/**
 * @copyright
 * @file open_content.cpp
 * @author Andrea Gianarda
 * @date 14th June 2020
 * @brief Open content functions
 */

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "logging_macros.h"
#include "global_enums.h"
#include "open_content.h"
#include "exception_macros.h"


// Categories
Q_LOGGING_CATEGORY(openContentOverall, "openContent.overall", MSG_TYPE_LEVEL)

open_content::OpenContent::OpenContent(QWidget *widgetParent) : file_handling_widgets::FileHandlingWidgets(widgetParent) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openContentOverall,  "Creating OpenContent class");

	this->pathToOpen->setPlaceholderText("<URL or file to open>");

	this->applyAction->setText("Open");
	this->applyAction->setStatusTip("Open URL or file");
	this->applyAction->setShortcut(key_sequence::KeySequence(Qt::Key_O));

}

open_content::OpenContent::~OpenContent() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openContentOverall,  "Destructor of OpenContent class");
}

void open_content::OpenContent::openPath() {
	const QString pathText(this->pathToOpen->displayText());
	const QFileInfo pathInfo(pathText);
	const QString path(pathInfo.absoluteFilePath());

	// Ignore open command if file is inexisting
	if (pathInfo.exists() == true) {
		if (pathInfo.isDir() == true) {
			// Path is an existing directory
			this->fileView->setRootIndex(this->fileModel->index(path));
			// Reset current index as a new directory is entered
			this->fileView->setCurrentIndex(QModelIndex());
		} else if (pathInfo.isFile() == true) {
			// Path is an existing file
			// Do not try to open and read file if the name is empty
			if (!path.isEmpty()) {
				QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openContentOverall,  "Opening " << path);
				this->openItem(path);
				QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openContentOverall,  "Close " << path);
			}
			// Close window when Open is clicked and a file has been opened
			this->close();
		}
	}

}

void open_content::OpenContent::doubleClickOnFile(const QFileInfo & pathInfo) {
	this->pathToOpen->setText(pathInfo.absoluteFilePath());
	this->openPath();
}
