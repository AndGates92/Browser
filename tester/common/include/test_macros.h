#ifndef TEST_MACROS_H
#define TEST_MACROS_H
/**
 * @copyright
 * @file test_macros.h
 * @author Andrea Gianarda
 * @date 29th of September 2020
 * @brief Test Macros file
*/

/** @defgroup TestMacrosGroup Test Macros Doxygen Group
 *  Test Macros
 *  @{
 */

/**
 * @brief ASSERT(CONDITION, TYPE, MESSAGE)
 *
 * \param CONDITION : condition to execute action on exception
 * \param TYPE      : error type
 * \param MESSAGE   : error message
 *
 * Verify that the condition is true, add to failure ist otherwise
 */
#define ASSERT(CONDITION, TYPE, MESSAGE)\
	if (!CONDITION) { \
		this->addAssertionFailure(__LINE__, __FILE__, #CONDITION, TYPE, MESSAGE); \
	}


/** @} */ // End of TestMacrosGroup group

#endif // TEST_MACROS_H
