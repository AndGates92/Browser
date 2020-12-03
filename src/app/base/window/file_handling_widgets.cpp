/**
 * @copyright
 * @file file_handling_widgets.cpp
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief File handling widgets functions
 */

#include <string>

// Qt libraries
#include <QtCore/QObject>

#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/shared/exception.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/base/window/file_handling_widgets.h"
#include "app/windows/secondary_windows/shared/utility.h"

// Categories
LOGGING_CONTEXT(fileHandlingWidgetsOverall, fileHandlingWidgets.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::window::FileHandlingWidgets::FileHandlingWidgets(QWidget *widgetParent) :
	pathToOpen(Q_NULLPTR),
	applyAction(Q_NULLPTR),
	browseAction(Q_NULLPTR),
	cancelAction(Q_NULLPTR),
	typeAction(Q_NULLPTR),
	fileModel(Q_NULLPTR),
	fileView(Q_NULLPTR)
{

	LOG_INFO(app::logger::info_level_e::ZERO, fileHandlingWidgetsOverall,  "Creating FileHandlingWidgets class");

	this->applyAction = std::move(app::secondary_window::createAction(widgetParent, std::string(), std::string(), app::key_sequence::KeySequence(Qt::Key_unknown)));
	this->browseAction = std::move(app::secondary_window::createAction(widgetParent, "Browse", "Browse files", app::key_sequence::KeySequence(Qt::Key_B)));
	this->cancelAction = std::move(app::secondary_window::createAction(widgetParent, "Cancel", "Cancel operation", app::key_sequence::KeySequence(Qt::Key_Escape)));
	this->typeAction = std::move(app::secondary_window::createAction(widgetParent, "Insert", "Insert", app::key_sequence::KeySequence(Qt::Key_I)));

	this->pathToOpen = app::secondary_window::createLineEdit(widgetParent, std::string(), this->typeAction);

//	const QStringList filters({"text/html", "application/octet-stream"});
	const QStringList filters({"*.html", "All (*.*)"});
	this->fileModel.reset(Q_NULLPTR);
	this->fileView = std::move(app::secondary_window::createFileView(this->fileModel, widgetParent, filters, QDir::currentPath()));

}

app::base::window::FileHandlingWidgets::~FileHandlingWidgets() {
	LOG_INFO(app::logger::info_level_e::ZERO, fileHandlingWidgetsOverall,  "Destructor of FileHandlingWidgets class");
}

const QString app::base::window::FileHandlingWidgets::getPathFromModelIndex(const std::unique_ptr<QFileSystemModel> & model, const QModelIndex & index) {
	QString path = QString();

	if (index == QModelIndex()) {
		path = model->rootPath();
	} else {
		path = model->filePath(index);
	}

	return path;
}

void app::base::window::FileHandlingWidgets::fileViewClickAction(const QModelIndex & index) {
	const QString path(this->getPathFromModelIndex(this->fileModel, index));

	LOG_INFO(app::logger::info_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected " << path);

	const QFileInfo pathInfo(path);

	LOG_INFO(app::logger::info_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected following path " << path << " (absolute path: " << pathInfo.absoluteFilePath() << ") type: directory -> " << pathInfo.isDir() << " file -> " << pathInfo.isFile());

	// Print path
	this->pathToOpen->setText(pathInfo.absoluteFilePath());
}

void app::base::window::FileHandlingWidgets::fileViewDoubleClickAction(const QModelIndex & index) {
	const QString path(this->getPathFromModelIndex(this->fileModel, index));

	const QFileInfo pathInfo(path);

	LOG_INFO(app::logger::info_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected following path " << path << " (absolute path: " << pathInfo.absoluteFilePath() << ") type: directory -> " << pathInfo.isDir() << " file -> " << pathInfo.isFile());

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

void app::base::window::FileHandlingWidgets::directoryLoadedAction(const QString & path) {
	LOG_INFO(app::logger::info_level_e::ZERO, fileHandlingWidgetsOverall,  "Finished loading " << path);
	// Sort column 0 (i.e. names) in ascending order
	this->fileModel->sort(0, Qt::AscendingOrder);
}

void app::base::window::FileHandlingWidgets::addActionsToWidget(QWidget * widget) {
	// Add actions in order to trigger them using shortcuts
	widget->addAction(this->applyAction.get());
	widget->addAction(this->browseAction.get());
	widget->addAction(this->cancelAction.get());
	widget->addAction(this->typeAction.get());
}
