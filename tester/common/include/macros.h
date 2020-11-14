#ifndef TEST_MACROS_H
#define TEST_MACROS_H
/**
 * @copyright
 * @file macros.h
 * @author Andrea Gianarda
 * @date 29th of September 2020
 * @brief Test Macros file
*/

/** @defgroup TesterSharedGroup Tester Shared Doxygen Group
 *  Tester shared enums, macros, functions and classes
 *  @{
 */

/**
 * @brief ASSERT(CONDITION, TYPE, MESSAGE)
 *
 * \param CONDITION : condition to execute action on exception
 * \param TYPE      : error type
 * \param MESSAGE   : error message
 *
 * Verify that the condition is true, add to failure list otherwise
 */
#define ASSERT(CONDITION, TYPE, MESSAGE)\
	if (!CONDITION) { \
		this->addAssertionFailure(__LINE__, __FILE__, #CONDITION, TYPE, MESSAGE); \
	}

/**
 * @brief WAIT_FOR_CONDITION(CONDITION, TYPE, MESSAGE, TIMEOUT)
 *
 * \param CONDITION : condition to execute action on exception
 * \param TYPE      : error type
 * \param MESSAGE   : error message
 * \param TIMEOUT   : timeout in milliseconds
 *
 * Wait for the condition to become true and add it to failure list if it is still false
 */
#define WAIT_FOR_CONDITION(CONDITION, TYPE, MESSAGE, TIMEOUT)\
	this->waitForCondition([&] () { \
			return CONDITION; \
		}, std::chrono::milliseconds(TIMEOUT)); \
	ASSERT(CONDITION, TYPE, MESSAGE)

/** @} */ // End of TesterSharedGroup group

#endif // TEST_MACROS_H
