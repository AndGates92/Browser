#ifndef COMMAND_SUITE_H
#define COMMAND_SUITE_H
/**
 * @copyright
 * @file command_suite.h
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Command suite header file
 */

#include <memory>

#include "common/include/constructor_macros.h"
#include "utility/log/include/printable_object.h"
#include "base/tester/include/suite.h"

/** @defgroup SuiteGroup Suite Doxygen Group
 *  Suite functions and classes
 *  @{
 */

namespace tester {

	namespace suite {

		/**
		 * @brief CommandSuite class
		 *
		 */
		class CommandSuite : public tester::base::Suite {

			public:
				/**
				 * @brief Function: explicit CommandSuite(const std::shared_ptr<tester::base::Factory> & testFactory, const tester::base::Suite::tests_container_t & testList = tester::base::Suite::tests_container_t())
				 *
				 * \param testFactory: test factory
				 * \param testList: initial collection of tests
				 *
				 * Command suite constructor
				 */
				explicit CommandSuite(const std::shared_ptr<tester::base::Factory> & testFactory, const tester::base::Suite::tests_container_t & testList = tester::base::Suite::tests_container_t());

				/**
				 * @brief Function: virtual ~CommandSuite()
				 *
				 * Command suite destructor
				 */
				virtual ~CommandSuite();

				/**
				 * @brief Function: virtual void populate() override
				 *
				 * This function populates the suite
				 */
				virtual void populate() override;

			protected:

			private:
				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class CommandSuite
				 *
				 */
				DISABLE_COPY_MOVE(CommandSuite)

		};

	}

}
/** @} */ // End of SuiteGroup group

#endif // COMMAND_SUITE_H
