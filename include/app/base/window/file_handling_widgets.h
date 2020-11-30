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

// Qt libraries
#include <QtCore/QDir>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QAction>
#include <QtWidgets/QFileSystemModel>
#include <QtWidgets/QTreeView>

#include "app/widgets/commands/action.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/shared/constructor_macros.h"
#include "app/base/window/action_interface.h"

/** @defgroup WindowGroup Window Doxygen Group
 *  Window functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace window {

			/**
			 * @brief FileHandlingWidgets class
			 *
			 */
			class FileHandlingWidgets : public app::base::window::ActionInterface {

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
					std::shared_ptr<QLineEdit> pathToOpen;

					/**
					 * @brief open action
					 *
					 */
					std::unique_ptr<app::action::Action> applyAction;

					/**
					 * @brief browse action
					 *
					 */
					std::unique_ptr<app::action::Action> browseAction;

					/**
					 * @brief cancel action
					 *
					 */
					std::unique_ptr<app::action::Action> cancelAction;

					/**
					 * @brief insert action
					 *
					 */
					std::unique_ptr<app::action::Action> typeAction;

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
					 * @brief Function: virtual void browse()
					 *
					 * This function is the slot of the browse action
					 */
					virtual void browse() = 0;

					/**
					 * @brief Function: virtual void pathChanged(const QString & path)
					 *
					 * \param path: path of the file
					 *
					 * This function is the slot triggered whenever the path of the file changes on the QLineEdit
					 */
					virtual void pathChanged(const QString & path) = 0;

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

	}

}
/** @} */ // End of WindowGroup group

#endif // FILE_HANDLING_WIDGETS_H
