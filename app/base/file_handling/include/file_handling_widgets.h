#ifndef FILE_HANDLING_WIDGETS_H
#define FILE_HANDLING_WIDGETS_H
/**
 * @copyright
 * @file file_handling_widgets.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief File Handling Widgets header file
*/

#include <string>
#include <memory>

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QDir>
#include <qt5/QtWidgets/QLineEdit>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QFileSystemModel>
#include <qt5/QtWidgets/QTreeView>

#include "action.h"
#include "key_sequence.h"
#include "constructor_macros.h"

/** @defgroup FileHandlingWidgetsGroup File Handling Widgets Doxygen Group
 *  File Handling Widgets functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(fileHandlingWidgetsOverall)

namespace file_handling_widgets {

	/**
	 * @brief FileHandlingWidgets class
	 *
	 */
	class FileHandlingWidgets {

		public:

		protected:
			/**
			 * @brief Function: explicit FileHandlingWidgets(QWidget *widgetParent)
			 *
			 * \param widgetParent: parent of widgets
			 *
			 * File handling widgets constructor
			 */
			explicit FileHandlingWidgets(QWidget *widgetParent);

			/**
			 * @brief Function: virtual ~FileHandlingWidgets()
			 *
			 * File handling widgets destructor
			 */
			virtual ~FileHandlingWidgets();

			/**
			 * @brief user typed text
			 *
			 */
			std::unique_ptr<QLineEdit> pathToOpen;

			/**
			 * @brief open action
			 *
			 */
			std::shared_ptr<action::Action> applyAction;

			/**
			 * @brief browse action
			 *
			 */
			std::shared_ptr<action::Action> browseAction;

			/**
			 * @brief cancel action
			 *
			 */
			std::shared_ptr<action::Action> cancelAction;

			/**
			 * @brief insert action
			 *
			 */
			std::shared_ptr<action::Action> typeAction;

			/**
			 * @brief file browser
			 *
			 */
			std::unique_ptr<QFileSystemModel> fileModel;

			/**
			 * @brief file browser
			 *
			 */
			std::unique_ptr<QTreeView> fileView;

			/**
			 * @brief Function: void fileViewClickAction(const QModelIndex & index)
			 *
			 * \param index: chosen index in the model of the fileview
			 *
			 * This function execute actions following a click in the model item
			 */
			void fileViewClickAction(const QModelIndex & index);

			/**
			 * @brief Function: void fileViewDoubleClickAction(const QModelIndex & index)
			 *
			 * \param index: chosen index in the model of the fileview
			 *
			 * This function execute actions following a click in the model item
			 */
			void fileViewDoubleClickAction(const QModelIndex & index);

			/**
			 * @brief Function: void directoryLoadedAction(const QString & path)
			 *
			 * \param path: path that was loaded in the file system model
			 *
			 * This function execute actions after a path was loaded
			 */
			void directoryLoadedAction(const QString & path);

			/**
			 * @brief Function: void addActionsToWidget(QWidget * widget)
			 *
			 * \param widget: widget ot add actions to
			 *
			 * This function adds all the file handling actions to the widget provided as argument
			 */
			void addActionsToWidget(QWidget * widget);

			/**
			 * @brief Function: virtual void apply()
			 *
			 * This function is the slot of the apply action
			 */
			virtual void apply() = 0;

			/**
			 * @brief Function: virtual void browse()
			 *
			 * This function is the slot of the browse action 
			 */
			virtual void browse() = 0;

			/**
			 * @brief Function: virtual void cancel()
			 *
			 * This function is the slot of the cancel action
			 */
			virtual void cancel() = 0;

			/**
			 * @brief Function: virtual void insert()
			 *
			 * This function is the slot of the insert action
			 */
			virtual void insert() = 0;

			/**
			 * @brief Function: virtual void doubleClickOnFile(const QFileInfo & pathInfo) = 0
			 *
			 * \param pathInfo: path to the file
			 *
			 * This function execute actions when the user double clicks on a file
			 */
			virtual void doubleClickOnFile(const QFileInfo & pathInfo) = 0;

		private:
			/**
			 * @brief Function: std::unique_ptr<action::Action> createAction(QObject * parent, const std::string & text, const std::string & tip, const key_sequence::KeySequence & shortcut)
			 *
			 * \param parent: parent object
			 * \param text: descriptive text of the action
			 * \param tip: action status tip
			 * \param shortcut: shortcut linked to the action
			 *
			 * This function creates a new action
			 */
			std::unique_ptr<action::Action> createAction(QObject * parent, const std::string & text, const std::string & tip, const key_sequence::KeySequence & shortcut);

			/**
			 * @brief Function: std::unique_ptr<QLineEdit> createLineEdit(QWidget * parent, const std::string & text)
			 *
			 * \param parent: parent widget
			 * \param text: text to show on the line edit
			 *
			 * This function creates a new QLineEdit
			 */
			std::unique_ptr<QLineEdit> createLineEdit(QWidget * parent, const std::string & text);

			/**
			 * @brief Function: std::unique_ptr<QFileSystemModel> createFileModel(QWidget * parent, const QStringList & filters, const QDir & directory)
			 *
			 * \param parent: parent widget
			 * \param filters: file dialog filters
			 * \param directory: current dialog directory
			 *
			 * This function creates a new QFileSystemModel
			 */
			std::unique_ptr<QFileSystemModel> createFileModel(QWidget * parent, const QStringList & filters, const QDir & directory);

			/**
			 * @brief Function: std::unique_ptr<QTreeView> createFileView(std::unique_ptr<QFileSystemModel> & model, QWidget *parent, const QStringList & filters, const QDir & directory)
			 *
			 * \param model: model of the fileview
			 * \param parent: parent widget
			 * \param filters: file dialog filters
			 * \param directory: current dialog directory
			 *
			 * This function creates a new QTreeView to display the content of the model. If the pointer to the model is null, this method will construct one based on the informations provided
			 */
			std::unique_ptr<QTreeView> createFileView(std::unique_ptr<QFileSystemModel> & model, QWidget *parent, const QStringList & filters = QStringList(), const QDir & directory = QDir::currentPath());

			/**
			 * @brief Function: const QString getPathFromModelIndex(const std::unique_ptr<QFileSystemModel> & model, const QModelIndex & index)
			 *
			 * \param model: model of the file system
			 * \param index: index in the model
			 *
			 * \return path in the index
			 *
			 * This function returns the file path matching the provided index in the file system model given as argument
			 */
			const QString getPathFromModelIndex(const std::unique_ptr<QFileSystemModel> & model, const QModelIndex & index);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class FileHandlingWidgets
			 *
			 */
			DISABLE_COPY_MOVE(FileHandlingWidgets)

	};

}
/** @} */ // End of FileHandlingWidgetsGroup group

#endif // FILE_HANDLING_WIDGETS_H
