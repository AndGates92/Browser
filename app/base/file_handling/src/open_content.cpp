/**
 * @copyright
 * @file open_content.cpp
 * @author Andrea Gianarda
 * @date 14th June 2020
 * @brief Open content functions
 */

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/global_enums.h"
#include "utility/stl/include/cpp_operator.h"
#include "base/file_handling/include/open_content.h"
#include "common/include/exception_macros.h"

// Categories
LOGGING_CONTEXT(openContentOverall, openContent.overall, TYPE_LEVEL, INFO_VERBOSITY)

open_content::OpenContent::OpenContent(QWidget *widgetParent) : file_handling_widgets::FileHandlingWidgets(widgetParent) {

	LOG_INFO(logger::info_level_e::ZERO, openContentOverall,  "Creating OpenContent class");

	this->pathToOpen->setPlaceholderText("<URL or file to open>");

	this->applyAction->setText("Open");
	this->applyAction->setStatusTip("Open URL or file");
	this->applyAction->setShortcut(key_sequence::KeySequence(Qt::Key_O));

}

open_content::OpenContent::~OpenContent() {
	LOG_INFO(logger::info_level_e::ZERO, openContentOverall,  "Destructor of OpenContent class");
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
				LOG_INFO(logger::info_level_e::ZERO, openContentOverall,  "Opening " << path);
				this->openItem(path);
				LOG_INFO(logger::info_level_e::ZERO, openContentOverall,  "Close " << path);
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

CONST_GETTER(open_content::OpenContent::getTypedPath, QString, this->pathToOpen->text())
