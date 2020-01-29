#ifndef MAIN_WINDOW_CTRL_BASE_H
#define MAIN_WINDOW_CTRL_BASE_H
/**
 * @copyright
 * @file main_window_ctrl_base.h
 * @author Andrea Gianarda
 * @date 29th of January 2019
 * @brief Main Window Control base class header file
*/

#include <qt5/QtCore/QLoggingCategory>

#include "main_window_shared_types.h"
#include "json_parser.h"

/** @defgroup MainWindowCtrlBaseGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlBaseOverall)

namespace main_window_ctrl_base {

	/**
	 * @brief MainWindowCtrlBase class
	 *
	 */
	class MainWindowCtrlBase : public QObject {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlBase(QWidget * parent = QString::null, int tabIndex = 0, int tabCount = 0, QString jsonFileName = QString::null)
			 *
			 * \param parent: parent window
			 * \param tabIndex: current tab index
			 * \param tabCount: number of opened tabs
			 * \param jsonFileName: JSON filename
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrlBase(QWidget * parent = Q_NULLPTR, int tabIndex = 0, int tabCount = 0, QString jsonFileName = QString::null);

		protected:

			/**
			 * @brief Function: void createShortcuts()
			 *
			 * This function creates shortcuts for the items on the window
			 */
			virtual void createShortcuts() = 0;

			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots within main window controller
			 */
			virtual void connectSignals() = 0;

			/**
			 * @brief parent widget
			 *
			 */
			QWidget * parent;

			/**
			 * @brief current tab index
			 *
			 */
			int currentTabIndex;

			/**
			 * @brief number of opened tabs
			 *
			 */
			int tabCount;

			/**
			 * @brief state of the main window
			 *
			 */
			main_window_shared_types::state_e mainWindowState;

			/**
			 * @brief tab commands and information
			 *
			 */
			json_parser::JsonParser commands;




	};

}
/** @} */ // End of MainWindowCtrlBaseGroup group

#endif // MAIN_WINDOW_CTRL_BASE_H
