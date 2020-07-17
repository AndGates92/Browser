#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H
/**
 * @copyright
 * @file global_enums.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Global Types file
*/

#include "type_print_macros.h"

/** @defgroup GlobalTypesGroup Global Types Doxygen Group
 *  Global Types
 *  @{
 */
namespace global_enums {

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
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(qinfo_level_list, global_enums::qinfo_level_e)

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
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(sign_list, global_enums::sign_e)

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
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(offset_type_list, global_enums::offset_type_e)

}

/** @} */ // End of GlobalTypesGroup group

#endif // GLOBAL_TYPES_H
