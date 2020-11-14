#ifndef TEST_ENUMS_H
#define TEST_ENUMS_H
/**
 * @copyright
 * @file test_enums.h
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Test Enums file
*/

#include "common/include/type_print_macros.h"

/** @defgroup TestEnumsGroup Test Enums Doxygen Group
 *  Test Enums
 *  @{
 */
namespace test_enums {

	Q_NAMESPACE

	/**
	 * @brief Error types
	 *
	 */
	typedef enum class error_type_list {
		UNKNOWN,   /**< Unknown error type */
		EXCEPTION, /**< Exception thrown */
		COMMAND,   /**< Command error */
		STATUSBAR, /**< Statusbar error */
		WINDOW,    /**< Window errors */
		TABS,      /**< Tab errors */
		POPUP      /**< Popup errors */
	} error_type_e;

	/**
	 * @brief Overload operators to ease print of the error types
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(error_type_list, test_enums::error_type_e)

	/**
	 * @brief Test state
	 *
	 */
	typedef enum class test_state_list {
		INSTATIATED,  /**< Test has been instatiated but it has not been created yet */
		CREATED,      /**< Test has been created and added to the factory */
		SETTING_UP,   /**< Setting up the test */
		RUNNING,   /**< Test is running */
		WRAPPING_UP,  /**< Wrapping up the test */
		FINISHED      /**< Test has finished */
	} test_state_e;

	/**
	 * @brief Overload operators to ease print of the state of the test
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(test_state_list, test_enums::test_state_e)

	/**
	 * @brief Test status
	 *
	 */
	typedef enum class test_status_list {
		NOT_RUN,  /**< Test has not been run yet */
		PASS,     /**< Test passes */
		FAIL      /**< Test fails */
	} test_status_e;

	/**
	 * @brief Overload operators to ease print of the status of the test
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(test_status_list, test_enums::test_status_e)

}

/** @} */ // End of TestEnumsGroup group

#endif // TEST_ENUMS_H
