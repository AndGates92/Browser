#ifndef APP_ENUMS_H
#define APP_ENUMS_H
/**
 * @copyright
 * @file enums.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Global Enums file
*/

#include "app/shared/type_print_macros.h"

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */
namespace app {

	namespace shared {

		Q_NAMESPACE

		/**
		 * @brief Verbosity levels
		 *
		 */
		typedef enum class qinfo_level_list {
			ZERO,   /**< Always printed */
			LOW,    /**< Low level pf printing */
			MEDIUM, /**< Medium level of printing */
			HIGH    /**< High level of printing */
		} qinfo_level_e;

		/**
		 * @brief Overload operators to ease print of the qinfo level
		 *
		 */
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(qinfo_level_list, app::shared::qinfo_level_e)

		/**
		 * @brief signs
		 *
		 */
		typedef enum class sign_list {
			MINUS =  -1,   /**< Minus sign */
			NOSIGN =  0,   /**< No sign */
			PLUS =    1,   /**< Plus sign */
		} sign_e;

		/**
		 * @brief Overload operators to ease print of the sign
		 *
		 */
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(sign_list, app::shared::sign_e)

		/**
		 * @brief move info
		 *
		 */
		typedef enum class offset_type_list {
			IDLE,             /**< Idle state - no user input */
			UP,               /**< Upward movement */
			DOWN,             /**< Downward movement */
			LEFT,             /**< Left movement */
			RIGHT,            /**< Right movement */
			ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
		} offset_type_e;

		/**
		 * @brief Overload operators to ease print of the movement type
		 *
		 */
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(offset_type_list, app::shared::offset_type_e)

		/**
		 * @brief element position in a list
		 *
		 */
		typedef enum class element_position_list {
			UNKNOWN,          /**< Unknown */
			BEGINNING,        /**< Beginning */
			MIDDLE,           /**< Middle */
			END               /**< End */
		} element_position_e;

		/**
		 * @brief Overload operators to ease print of the element position in a list
		 *
		 */
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(element_position_list, app::shared::element_position_e)

	}

}

/** @} */ // End of SharedGroup group

#endif // APP_ENUMS_H
