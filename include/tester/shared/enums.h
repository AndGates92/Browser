#ifndef TEST_ENUMS_H
#define TEST_ENUMS_H
/**
 * @copyright
 * @file enums.h
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Test Enums file
*/

#include "app/shared/type_print_macros.h"

/** @defgroup TesterSharedGroup Tester Shared Doxygen Group
 *  Tester shared enums, macros, functions and classes
 *  @{
 */
namespace tester {

	namespace shared {

		Q_NAMESPACE

		/**
		 * @brief Error types
		 *
		 */
		typedef enum class error_type_list {
			UNKNOWN,   /**< Unknown error */
			TEST,      /**< Test error */
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
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(error_type_list, tester::shared::error_type_e)

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
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(test_state_list, tester::shared::test_state_e)

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
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(test_status_list, tester::shared::test_status_e)

		/**
		 * @brief Text type
		 *
		 */
		typedef enum class text_type_list {
			URL,                /**< Text is an URL */
			ALPHANUMERICAL,     /**< Text has only alphanumerical characters */
			COMPLEX             /**< Text has also punctuation and spaces */
		} text_type_e;

		/**
		 * @brief Overload operators to ease print of the status of the test
		 *
		 */
		OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(text_type_list, tester::shared::text_type_e)

	}

}
/** @} */ // End of TesterSharedGroup group

#endif // TEST_ENUMS_H
