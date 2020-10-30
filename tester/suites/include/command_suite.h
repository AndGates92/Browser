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

#include "constructor_macros.h"
#include "printable_object.h"
#include "base_suite.h"

/** @defgroup CommandSuiteGroup Command suite Group
 *  Command suite functions and classes
 *  @{
 */

namespace command_suite {

	/**
	 * @brief CommandSuite class
	 *
	 */
	class CommandSuite : public base_suite::BaseSuite {

		public:
			/**
			 * @brief Function: explicit CommandSuite(const std::shared_ptr<base_factory::BaseFactory> & testFactory, const base_suite::BaseSuite::tests_container_t & testList = base_suite::BaseSuite::tests_container_t())
			 *
			 * \param testFactory: test factory
			 * \param testList: initial collection of tests
			 *
			 * Command suite constructor
			 */
			explicit CommandSuite(const std::shared_ptr<base_factory::BaseFactory> & testFactory, const base_suite::BaseSuite::tests_container_t & testList = base_suite::BaseSuite::tests_container_t());

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
/** @} */ // End of CommandSuiteGroup group

#endif // COMMAND_SUITE_H
