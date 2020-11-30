#ifndef TAB_SHARED_TYPES_H
#define TAB_SHARED_TYPES_H
/**
 * @copyright
 * @file tab_shared_types.h
 * @author Andrea Gianarda
 * @date 11th of April 2020
 * @brief Tab Shared Types file
*/

#include "app/shared/type_print_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			Q_NAMESPACE

			/**
			 * @brief states
			 *
			 */
			typedef enum class load_status_list {
				IDLE,             /**< Idle state - no user input */
				LOADING,          /**< Typing command */
				FINISHED,         /**< Open new tab */
				ERROR,            /**< Close tab */
			} load_status_e;

			/**
			 * @brief Overload operators to ease print of the status of loading of a tab
			 *
			 */
			OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(load_status_list, app::base::tab::load_status_e)

			/**
			 * @brief direction info
			 *
			 */
			typedef enum class direction_list {
				IDLE,             /**< Idle state - no user input */
				UP,               /**< Upward movement */
				DOWN,             /**< Downward movement */
				LEFT,             /**< Left movement */
				RIGHT             /**< Right movement */
			} direction_e;

			/**
			 * @brief Overload operators to ease print of the direction of movement of a tab component
			 *
			 */
			OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(direction_list, app::base::tab::direction_e)

			/**
			 * @brief direction info
			 *
			 */
			typedef enum class stepping_list {
				IDLE,             /**< Idle state - no user input */
				NEXT,             /**< Next position */
				PREVIOUS,         /**< Previous position */
				ITEM              /**< User specified item */
			} stepping_e;

			/**
			 * @brief Overload operators to ease print of the stepping in a list
			 *
			 */
			OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(stepping_list, app::base::tab::stepping_e)

		}

	}

}

/** @} */ // End of TabGroup group

#endif // TAB_SHARED_TYPES_H
