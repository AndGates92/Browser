#ifndef TEST_FACTORY_H
#define TEST_FACTORY_H
/**
 * @copyright
 * @file test_factory.h
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Test factory header file
 */

#include "app/shared/constructor_macros.h"
#include "tester/base/factory.h"

/** @defgroup FactoryGroup Factory Doxygen Group
 *  Factory functions and classes
 *  @{
 */

namespace tester {

	namespace factory {

		/**
		 * @brief TestFactory class
		 *
		 */
		class TestFactory : public tester::base::Factory {

			public:
				/**
				 * @brief Function: explicit TestFactory(int & argc, char** argv, const tester::base::Factory::suite_container_t & testSuites = tester::base::Factory::suite_container_t())
				 *
				 * \param argc: number of arguments
				 * \param argv: value of arguments
				 * \param testSuites: initial collection of test suites
				 *
				 * Test factory constructor
				 */
				explicit TestFactory(int & argc, char** argv, const tester::base::Factory::suite_container_t & testSuites = tester::base::Factory::suite_container_t());

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

}
/** @} */ // End of FactoryGroup group

#endif // TEST_FACTORY_H
