#ifndef MAIN_WINDOW_SHARED_TYPES_H
#define MAIN_WINDOW_SHARED_TYPES_H
/**
 * @copyright
 * @file main_window_shared_types.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Shared Types file
*/

#include <qt5/QtCore/QtDebug>

/** @defgroup MainWindowSharedTypesGroup Main Window Shared Types Doxygen Group
 *  Main Window Shared Types
 *  @{
 */
namespace main_window_shared_types {

	/**
	 * @brief list of objects to execute actions on 
	 *
	 */
	typedef enum class object_type_list {
		CURSOR,              /**< cursor */
		TAB,                 /**< tab */
		UNKNOWN              /**< unknown object */
	} object_type_e;

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window::MainWindow::object_type_e & object)
	 *
	 * \param os: output stream
	 * \param object: object type the action is applied on
	 *
	 * Overload << operator to print they object type the action is execute on
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::object_type_e & object);

	/**
	 * @brief states
	 *
	 */
	typedef enum class state_list {
		IDLE,             /**< Idle state - no user input */
		COMMAND,          /**< Typing command */
		OPEN_TAB,         /**< Open new tab */
		CLOSE_TAB,        /**< Close tab */
		REFRESH_TAB,      /**< Refresh tab */
		MOVE_LEFT,        /**< Move to tab to the left */
		MOVE_RIGHT,       /**< Move to tab to the right */
		TAB_MOVE,         /**< Move tab */
		SEARCH            /**< Search on same tab */
	} state_e;

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & state)
	 *
	 * \param os: output stream
	 * \param state: state to print
	 *
	 * Overload << operator to print state
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & state);

	/**
	 * @brief move info
	 *
	 */
	typedef enum class move_value_list {
		IDLE,             /**< Idle state - no user input */
		LEFT,             /**< Left movement */
		RIGHT,            /**< Right movement */
		ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
	} move_value_e;

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::move_value_e & value_type)
	 *
	 * \param os: output stream
	 * \param value_type: move type
	 *
	 * Overload << operator to print the move type
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::move_value_e & value_type);

	/**
	 * @brief text action 
	 *
	 */
	typedef enum class text_action_list {
		SET,              /**< Set text */
		APPEND,           /**< Append text */
		CLEAR             /**< Clear text */
	} text_action_e;

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & action)
	 *
	 * \param os: output stream
	 * \param action: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & action);

}

/** @} */ // End of MainWindowSharedTypesGroup group

#endif // MAIN_WINDOW_SHARED_TYPES_H
