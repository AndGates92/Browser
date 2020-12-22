/**
 * @copyright
 * @file open_content.cpp
 * @author Andrea Gianarda
 * @date 14th June 2020
 * @brief Open content functions
 */

#include "app/base/window/open_content.h"
#include "app/shared/setters_getters.h"
#include "app/shared/enums.h"
#include "app/shared/exception.h"
#include "app/utility/logger/macros.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/widgets/commands/action.h"
#include "app/widgets/commands/key_sequence.h"

// Categories
LOGGING_CONTEXT(openContentOverall, openContent.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::window::OpenContent::OpenContent(QWidget *widgetParent) : app::base::window::FileHandlingWidgets(widgetParent) {

	LOG_INFO(app::logger::info_level_e::ZERO, openContentOverall,  "Creating OpenContent class");

	this->pathToOpen->setPlaceholderText("<URL or file to open>");

	this->applyAction->setText("Open");
	this->applyAction->setStatusTip("Open URL or file");
	this->applyAction->setShortcut(app::commands::KeySequence(Qt::Key_O));

}

app::base::window::OpenContent::~OpenContent() {
	LOG_INFO(app::logger::info_level_e::ZERO, openContentOverall,  "Destructor of OpenContent class");
}

void app::base::window::OpenContent::openPath() {
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
				LOG_INFO(app::logger::info_level_e::ZERO, openContentOverall,  "Opening " << path);
				this->openItem(path);
				LOG_INFO(app::logger::info_level_e::ZERO, openContentOverall,  "Close " << path);
			}
			// Close window when Open is clicked and a file has been opened
			this->close();
		}
	}

}

void app::base::window::OpenContent::doubleClickOnFile(const QFileInfo & pathInfo) {
	this->pathToOpen->setText(pathInfo.absoluteFilePath());
	this->openPath();
}

CONST_GETTER(app::base::window::OpenContent::getTypedPath, QString, this->pathToOpen->text())

bool app::base::window::OpenContent::isTypedPathValid() const {
	const QFileInfo pathInfo(this->getTypedPath());
	return pathInfo.exists();
}

bool app::base::window::OpenContent::isTypedPathAFile() const {
	const QFileInfo pathInfo(this->getTypedPath());
	return this->isTypedPathValid() && pathInfo.isFile();
}

bool app::base::window::OpenContent::isTypedPathADirectory() const {
	const QFileInfo pathInfo(this->getTypedPath());
	return this->isTypedPathValid() && pathInfo.isDir();
}
