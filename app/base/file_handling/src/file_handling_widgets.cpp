/**
 * @copyright
 * @file file_handling_widgets.cpp
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief File handling widgets functions
 */

#include <string>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QObject>

#include "logging_macros.h"
#include "global_enums.h"
#include "file_handling_widgets.h"
#include "secondary_window_utility.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(fileHandlingWidgetsOverall, "fileHandlingWidgets.overall", MSG_TYPE_LEVEL)

file_handling_widgets::FileHandlingWidgets::FileHandlingWidgets(QWidget *widgetParent) :
	pathToOpen(Q_NULLPTR),
	applyAction(Q_NULLPTR),
	browseAction(Q_NULLPTR),
	cancelAction(Q_NULLPTR),
	typeAction(Q_NULLPTR),
	fileModel(Q_NULLPTR),
	fileView(Q_NULLPTR)
{

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Creating FileHandlingWidgets class");

	this->applyAction = std::move(secondary_window_utility::createAction(widgetParent, std::string(), std::string(), key_sequence::KeySequence(Qt::Key_unknown)));
	this->browseAction = std::move(secondary_window_utility::createAction(widgetParent, "Browse", "Browse files", key_sequence::KeySequence(Qt::Key_B)));
	this->cancelAction = std::move(secondary_window_utility::createAction(widgetParent, "Cancel", "Cancel operation", key_sequence::KeySequence(Qt::Key_Escape)));
	this->typeAction = std::move(secondary_window_utility::createAction(widgetParent, "Insert", "Insert", key_sequence::KeySequence(Qt::Key_I)));

	this->pathToOpen = secondary_window_utility::createLineEdit(widgetParent, std::string(), this->typeAction);

//	const QStringList filters({"text/html", "application/octet-stream"});
	const QStringList filters({"*.html", "All (*.*)"});
	this->fileModel.reset(Q_NULLPTR);
	this->fileView = std::move(secondary_window_utility::createFileView(this->fileModel, widgetParent, filters, QDir::currentPath()));

}

file_handling_widgets::FileHandlingWidgets::~FileHandlingWidgets() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Destructor of FileHandlingWidgets class");
}

const QString file_handling_widgets::FileHandlingWidgets::getPathFromModelIndex(const std::unique_ptr<QFileSystemModel> & model, const QModelIndex & index) {
	QString path = QString();

	if (index == QModelIndex()) {
		path = model->rootPath();
	} else {
		path = model->filePath(index);
	}

	return path;
}

void file_handling_widgets::FileHandlingWidgets::fileViewClickAction(const QModelIndex & index) {
	const QString path(this->getPathFromModelIndex(this->fileModel, index));

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected " << path);

	const QFileInfo pathInfo(path);

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected following path " << path << " (absolute path: " << pathInfo.absoluteFilePath() << ") type: directory -> " << pathInfo.isDir() << " file -> " << pathInfo.isFile());

	// Print path
	this->pathToOpen->setText(pathInfo.absoluteFilePath());
}

void file_handling_widgets::FileHandlingWidgets::fileViewDoubleClickAction(const QModelIndex & index) {
	const QString path(this->getPathFromModelIndex(this->fileModel, index));

	const QFileInfo pathInfo(path);

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected following path " << path << " (absolute path: " << pathInfo.absoluteFilePath() << ") type: directory -> " << pathInfo.isDir() << " file -> " << pathInfo.isFile());

	if (pathInfo.isDir() == true) {
		this->fileModel->setRootPath(pathInfo.absoluteFilePath());
		// Need to use absolute path here as links in the path need to be resolved
		// For example, double click on .. should lead to moving up once
		this->fileView->setRootIndex(this->fileModel->index(pathInfo.absoluteFilePath()));
		// Reset current index as a new directory is entered
		this->fileView->setCurrentIndex(QModelIndex());
	} else if (pathInfo.isFile() == true) {
		this->doubleClickOnFile(pathInfo);
	}
}

void file_handling_widgets::FileHandlingWidgets::directoryLoadedAction(const QString & path) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Finished loading " << path);
	// Sort column 0 (i.e. names) in ascending order
	this->fileModel->sort(0, Qt::AscendingOrder);
}

void file_handling_widgets::FileHandlingWidgets::addActionsToWidget(QWidget * widget) {
	// Add actions in order to trigger them using shortcuts
	widget->addAction(this->applyAction.get());
	widget->addAction(this->browseAction.get());
	widget->addAction(this->cancelAction.get());
	widget->addAction(this->typeAction.get());
}