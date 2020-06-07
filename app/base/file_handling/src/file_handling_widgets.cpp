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
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "logging_macros.h"
#include "global_types.h"
#include "file_handling_widgets.h"
#include "exception_macros.h"

namespace file_handling_widgets {

	namespace {

		/**
		 * @brief margin above the text inside the line edit
		 *
		 */
		static constexpr int topLineEditMargin = 2;

		/**
		 * @brief margin underneat the text inside the line edit
		 *
		 */
		static constexpr int bottomLineEditMargin = 2;

	}

}


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

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Creating FileHandlingWidgets class");

	this->pathToOpen = this->createLineEdit(widgetParent, std::string());

	this->applyAction = this->createAction(widgetParent, std::string(), std::string(), key_sequence::KeySequence(Qt::Key_unknown));
	this->browseAction = this->createAction(widgetParent, "Browse", "Browse files", key_sequence::KeySequence(Qt::Key_B));
	this->cancelAction = this->createAction(widgetParent, "Cancel", "Cancel operation", key_sequence::KeySequence(Qt::Key_Escape));
	this->typeAction = this->createAction(widgetParent, "Insert", "Insert", key_sequence::KeySequence(Qt::Key_I));


//	const QStringList filters({"text/html", "application/octet-stream"});
	const QStringList filters({"*.html", "All (*.*)"});
	this->fileModel = Q_NULLPTR;
	this->fileView = this->createFileView(&(this->fileModel), widgetParent, filters, QDir::currentPath());

}

file_handling_widgets::FileHandlingWidgets::~FileHandlingWidgets() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Destructor of FileHandlingWidgets class");
	if (this->pathToOpen != Q_NULLPTR) {
		delete this->pathToOpen;
	}
	if (this->applyAction != Q_NULLPTR) {
		delete this->applyAction;
	}
	if (this->browseAction != Q_NULLPTR) {
		delete this->browseAction;
	}
	if (this->cancelAction != Q_NULLPTR) {
		delete this->cancelAction;
	}
	if (this->typeAction != Q_NULLPTR) {
		delete this->typeAction;
	}
	if (this->fileModel != Q_NULLPTR) {
		delete this->fileModel;
	}
	if (this->fileView != Q_NULLPTR) {
		delete this->fileView;
	}
}

QFileSystemModel * file_handling_widgets::FileHandlingWidgets::createFileModel(QWidget *parent, const QStringList & filters, const QDir & directory) {

	QFileSystemModel * model = new QFileSystemModel(parent);
	#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	model->setOption(QFileSystemModel::DontResolveSymlinks, true);
	#endif
	model->setFilter(QDir::AllDirs | QDir::Hidden | QDir::AllEntries);

	model->setNameFilterDisables(true);
	model->setNameFilters(filters);

	model->setRootPath(directory.path());

	return model;
}

QTreeView * file_handling_widgets::FileHandlingWidgets::createFileView(QFileSystemModel ** model, QWidget *parent, const QStringList & filters, const QDir & directory) {

	if ((*model) == Q_NULLPTR) {
		*model = this->createFileModel(parent, filters, directory);
	}

	QTreeView * tree = new QTreeView(parent);
	tree->setModel(*model);
	tree->setRootIndex((*model)->index(directory.path()));
	tree->setExpandsOnDoubleClick(false);
	tree->setItemsExpandable(false);

	return tree;

}

action::Action * file_handling_widgets::FileHandlingWidgets::createAction(QObject * parent, const std::string & text, const std::string & tip, const key_sequence::KeySequence & shortcut) {

	QString actionText = QString::null;
	if (text.empty() == false) {
		actionText = QAction::tr(text.c_str());
	}

	action::Action * newAction = new action::Action(parent, actionText);
	if (tip.empty() == false) {
		newAction->setStatusTip(QAction::tr(tip.c_str()));
	}
	newAction->setShortcut(shortcut);

	return newAction;
}

QLineEdit * file_handling_widgets::FileHandlingWidgets::createLineEdit(QWidget * parent, const std::string & text) {
	QLineEdit * lineEdit = new QLineEdit(parent);
	if (text.empty() == false) {
		lineEdit->setPlaceholderText(QLineEdit::tr(text.c_str()));
	}
	lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	lineEdit->setFixedHeight(lineEdit->fontMetrics().height() + file_handling_widgets::topLineEditMargin + file_handling_widgets::bottomLineEditMargin);

	return lineEdit;
}


const QString file_handling_widgets::FileHandlingWidgets::getPathFromModelIndex(const QFileSystemModel * model, const QModelIndex & index) {
	QString path = QString::null;

	if (index == QModelIndex()) {
		path = model->rootPath();
	} else {
		path = model->filePath(index);
	}

	return path;
}

void file_handling_widgets::FileHandlingWidgets::fileViewClickAction(const QModelIndex & index) {
	const QString path(this->getPathFromModelIndex(this->fileModel, index));

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected " << path);

	const QFileInfo pathInfo(path);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected following path " << path << " (absolute path: " << pathInfo.absoluteFilePath() << ") type: directory -> " << pathInfo.isDir() << " file -> " << pathInfo.isFile());

	// Print path
	this->pathToOpen->setText(pathInfo.absoluteFilePath());
}

void file_handling_widgets::FileHandlingWidgets::fileViewDoubleClickAction(const QModelIndex & index) {
	const QString path(this->getPathFromModelIndex(this->fileModel, index));

	const QFileInfo pathInfo(path);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Selected following path " << path << " (absolute path: " << pathInfo.absoluteFilePath() << ") type: directory -> " << pathInfo.isDir() << " file -> " << pathInfo.isFile());

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
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileHandlingWidgetsOverall,  "Finished loading " << path);
	// Sort column 0 (i.e. names) in ascending order
	this->fileModel->sort(0, Qt::AscendingOrder);
}

void file_handling_widgets::FileHandlingWidgets::addActionsToWidget(QWidget * widget) {
	// Add actions in order to trigger them using shortcuts
	widget->addAction(this->applyAction);
	widget->addAction(this->browseAction);
	widget->addAction(this->cancelAction);
	widget->addAction(this->typeAction);
}
