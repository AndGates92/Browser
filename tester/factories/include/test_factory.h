#ifndef TEST_FACTORY_H
#define TEST_FACTORY_H
/**
 * @copyright
 * @file test_factory.h
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Test factory header file
 */

#include "constructor_macros.h"
#include "base_factory.h"

/** @defgroup TestFactoryGroup Test Factory Group
 *  Test factory functions and classes
 *  @{
 */

namespace test_factory {

	/**
	 * @brief TestFactory class
	 *
	 */
	class TestFactory : public base_factory::BaseFactory {

		public:
			/**
			 * @brief Function: explicit TestFactory(int & argc, char** argv, const base_factory::BaseFactory::suite_container_t & testSuites = base_factory::BaseFactory::suite_container_t())
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 * \param testSuites: initial collection of test suites
			 *
			 * Test factory constructor
			 */
			explicit TestFactory(int & argc, char** argv, const base_factory::BaseFactory::suite_container_t & testSuites = base_factory::BaseFactory::suite_container_t());

			/**
			 * @brief Function: virtual ~TestFactory()
			 *
			 * Test factory destructor
			 */
			virtual ~TestFactory();

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
			 * @brief Disable move and copy constructors and operator= overloading for class TestFactory
			 *
			 */
			DISABLE_COPY_MOVE(TestFactory)

	};

}
/** @} */ // End of TestFactoryGroup group

#endif // TEST_FACTORY_H
