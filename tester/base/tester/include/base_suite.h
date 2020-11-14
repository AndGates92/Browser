#ifndef BASE_SUITE_H
#define BASE_SUITE_H
/**
 * @copyright
 * @file base_suite.h
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Base suite header file
 */

#include <memory>
#include <set>

#include "common/include/constructor_macros.h"
#include "utility/log/include/printable_object.h"
#include "base/tester/include/base_test.h"
#include "common/include/base_element_creation.h"

/** @defgroup BaseSuiteGroup Base Suite Group
 *  Base suite functions and classes
 *  @{
 */

namespace base_factory {
	class BaseFactory;
}

namespace base_test {
	class BaseTest;
	struct TestPtrCompare;
}

namespace base_suite {

	/**
	 * @brief BaseSuite class
	 *
	 */
	class BaseSuite : public std::enable_shared_from_this<base_suite::BaseSuite>, public printable_object::PrintableObject, public base_element_creation::BaseElementCreation {

		public:

			/**
			 * @brief type of test error container
			 *
			 */
			typedef std::set<std::shared_ptr<base_test::BaseTest>, base_test::TestPtrCompare> tests_container_t;

			/**
			 * @brief Function: explicit BaseSuite(const std::shared_ptr<base_factory::BaseFactory> & testFactory, const std::string & suiteName, const tests_container_t & testList = tests_container_t())
			 *
			 * \param testFactory: test factory
			 * \param suiteName: name of the suite
			 * \param testList: initial collection of tests
			 *
			 * Base suite constructor
			 */
			explicit BaseSuite(const std::shared_ptr<base_factory::BaseFactory> & testFactory, const std::string & suiteName, const tests_container_t & testList = tests_container_t());

			/**
			 * @brief Function: virtual ~BaseSuite()
			 *
			 * Base suite destructor
			 */
			virtual ~BaseSuite();

			/**
			 * @brief Function: virtual void postProcessCreation() override
			 *
			 * This function run tasks that follows suite creation
			 */
			virtual void postProcessCreation() override;

			/**
			 * @brief Function: const std::string & getName() const
			 *
			 * \return name of the suite
			 *
			 * This function returns the name of the suite
			 */
			const std::string & getName() const;

			/**
			 * @brief Function: const std::shared_ptr<base_factory::BaseFactory> getFactory() const
			 *
			 * \return factory the suite belongs to
			 *
			 * This function returns the factory the suite belongs to
			 */
			const std::shared_ptr<base_factory::BaseFactory> getFactory() const;

			/**
			 * @brief Function: const tests_container_t & getTests() const
			 *
			 * \return tests in the suite
			 *
			 * This function returns the tests in the suite
			 */
			const tests_container_t & getTests() const;

			/**
			 * @brief Function: void addTest(const std::shared_ptr<base_test::BaseTest> & test)
			 *
			 * \param test: test to add
			 *
			 * This function adds tests to this suite
			 */
			void addTest(const std::shared_ptr<base_test::BaseTest> & test);

			/**
			 * @brief Function: virtual void populate()
			 *
			 * This function populates the suite
			 */
			virtual void populate();

			/**
			 * @brief Function: std::shared_ptr<base_test::BaseTest> findTest(const std::string & testName) const
			 *
			 * \param testName: name of the test to find
			 *
			 * \return the test
			 *
			 * This function finds a test with a given name
			 */
			std::shared_ptr<base_test::BaseTest> findTest(const std::string & testName) const;

			/**
			 * @brief Function: bool operator== (const BaseSuite & otherSuite) const
			 *
			 * \param otherSuite: base test to compare
			 *
			 * \return value of the comparison
			 *
			 * Base Suite overloading of operator ==
			 */
			bool operator== (const BaseSuite & otherSuite) const;

		protected:
			/**
			 * @brief Function: const std::string print() const override
			 *
			 * \return tests suite converted to std::string
			 *
			 * This functions prints test suite info to std::string
			 */
			const std::string print() const override;

		private:

			/**
			 * @brief test factory
			 *
			 */
			std::weak_ptr<base_factory::BaseFactory> factory;

			/**
			 * @brief name of the test
			 *
			 */
			std::string name;

			/**
			 * @brief test suites
			 *
			 */
			tests_container_t tests;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class BaseSuite
			 *
			 */
			DISABLE_COPY_MOVE(BaseSuite)

	};

	/**
	 * @brief SuitePtrCompare struct
	 *
	 */
	struct SuitePtrCompare {
		// Struct sets the default access to public
		/**
		 * @brief Function: bool operator() (const std::shared_ptr<base_suite::BaseSuite> & rhs, const std::shared_ptr<base_suite::BaseSuite> & lhs) const
		 *
		 * \param rhs: test suite to compare
		 * \param lhs: test suite to compare
		 *
		 * \return: true if the two tests are the same, false otherwise
		 *
		 * This function compares two shared pointers of object base_suite::BaseSuite
		 */
		bool operator() (const std::shared_ptr<base_suite::BaseSuite> & rhs, const std::shared_ptr<base_suite::BaseSuite> & lhs) const;
	};

}
/** @} */ // End of BaseSuiteGroup group

#endif // TEST_SUITE_H
