#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H
/**
 * @copyright
 * @file test.h
 * @author Andrea Gianarda
 * @date 12th January 2021
 * @brief Test utilities header file
 */

#include <string>

#include "tester/shared/enums.h"

/** @defgroup UtilityGroup Utility Doxygen Group
 *  Utility functions and classes
 *  @{
 */
namespace tester {

	namespace utility {

		/**
		 * @brief Function: void checkText(const std::string & text, const tester::shared::text_type_e type)
		 *
		 * \param text: text to check
		 * \param type: expected type of the text
		 *
		 * This function checks that the text matches the expected type
		 */
		void checkText(const std::string & text, const tester::shared::text_type_e type);

	}

}
/** @} */ // End of UtilityGroup group

#endif // TEST_UTILITY_H
