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

#include "type_print_macros.h"

/** @defgroup MainWindowSharedTypesGroup Main Window Shared Types Doxygen Group
 *  Main Window Shared Types
 *  @{
 */
namespace main_window_shared_types {

	Q_NAMESPACE

	/**
	 * @brief postprocessing action after state change
	 *
	 */
	typedef enum class state_postprocessing_list {
		NONE,             /**< No post processing ot state transition */
		POSTPROCESS,      /**< Run postprocessing */
		ACTION            /**< Execute action */
	} state_postprocessing_e;

	/**
	 * @brief Overload operators to ease print of the state of the main window controller
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(state_postprocessing_list, main_window_shared_types::state_postprocessing_e)


	/**
	 * @brief states
	 *
	 */
	typedef enum class state_list {
		IDLE,             /**< Idle state - no user input */
		TOGGLE_MENUBAR,   /**< Toggle menu bar */
		QUIT,             /**< Exit browser */
		COMMAND,          /**< Typing command */
		OPEN_TAB,         /**< Open new tab */
		CLOSE_TAB,        /**< Close tab */
		REFRESH_TAB,      /**< Refresh tab */
		MOVE_LEFT,        /**< Move to tab to the left */
		MOVE_RIGHT,       /**< Move to tab to the right */
		MOVE_TAB,         /**< Move tab */
		SEARCH,           /**< Search on same tab */
		FIND,             /**< Find string in the tab */
	} state_e;

	/**
	 * @brief Overload operators to ease print of the state of the main window controller
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(state_list, main_window_shared_types::state_e)

	/**
	 * @brief move info
	 *
	 */
	typedef enum class offset_type_list {
		IDLE,             /**< Idle state - no user input */
		LEFT,             /**< Left movement */
		RIGHT,            /**< Right movement */
		ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
	} offset_type_e;

	/**
	 * @brief Overload operators to ease print of the movement type
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(offset_type_list, main_window_shared_types::offset_type_e)

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
	 * @brief Overload operators to ease print of the action applied on the text in the status bar
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(text_action_list, main_window_shared_types::text_action_e)

	/**
	 * @brief text action
	 *
	 */
	typedef enum class page_type_list {
		WEB_CONTENT,       /**< Tab type is a web engine */
		TEXT,            /**< Tab type is QLabel */
		UNKNOWN           /**< Tab type is unknown */
	} page_type_e;

	/**
	 * @brief Overload operators to ease print of the type of the tab
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(page_type_list, main_window_shared_types::page_type_e)

}

/** @} */ // End of MainWindowSharedTypesGroup group

#endif // MAIN_WINDOW_SHARED_TYPES_H
