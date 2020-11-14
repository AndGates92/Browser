#ifndef BASE_SUITE_H
#define BASE_SUITE_H
/**
 * @copyright
 * @file suite.h
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Base suite header file
 */

#include <memory>
#include <set>

#include "common/include/constructor_macros.h"
#include "utility/log/include/printable_object.h"
#include "base/tester/include/test.h"
#include "common/include/base_element_creation.h"

/** @defgroup TesterBaseGroup Tester Base Doxygen Group
 *  Tester Base functions and classes
 *  @{
 */

namespace tester {

	namespace base {

		class Factory;

		class Test;
		struct TestPtrCompare;

		/**
		 * @brief BaseSuite class
		 *
		 */
		class Suite : public std::enable_shared_from_this<tester::base::Suite>, public app::printable_object::PrintableObject, public tester::shared::BaseElementCreation {

			public:

				/**
				 * @brief type of test error container
				 *
				 */
				typedef std::set<std::shared_ptr<tester::base::Test>, tester::base::TestPtrCompare> tests_container_t;

				/**
				 * @brief Function: explicit Suite(const std::shared_ptr<tester::base::Factory> & testFactory, const std::string & suiteName, const tests_container_t & testList = tests_container_t())
				 *
				 * \param testFactory: test factory
				 * \param suiteName: name of the suite
				 * \param testList: initial collection of tests
				 *
				 * Base suite constructor
				 */
				explicit Suite(const std::shared_ptr<tester::base::Factory> & testFactory, const std::string & suiteName, const tests_container_t & testList = tests_container_t());

				/**
				 * @brief Function: virtual ~Suite()
				 *
				 * Base suite destructor
				 */
				virtual ~Suite();

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
				 * @brief Function: const std::shared_ptr<tester::base::Factory> getFactory() const
				 *
				 * \return factory the suite belongs to
				 *
				 * This function returns the factory the suite belongs to
				 */
				const std::shared_ptr<tester::base::Factory> getFactory() const;

				/**
				 * @brief Function: const tests_container_t & getTests() const
				 *
				 * \return tests in the suite
				 *
				 * This function returns the tests in the suite
				 */
				const tests_container_t & getTests() const;

				/**
				 * @brief Function: void addTest(const std::shared_ptr<tester::base::Test> & test)
				 *
				 * \param test: test to add
				 *
				 * This function adds tests to this suite
				 */
				void addTest(const std::shared_ptr<tester::base::Test> & test);

				/**
				 * @brief Function: virtual void populate()
				 *
				 * This function populates the suite
				 */
				virtual void populate();

				/**
				 * @brief Function: std::shared_ptr<tester::base::Test> findTest(const std::string & testName) const
				 *
				 * \param testName: name of the test to find
				 *
				 * \return the test
				 *
				 * This function finds a test with a given name
				 */
				std::shared_ptr<tester::base::Test> findTest(const std::string & testName) const;

				/**
				 * @brief Function: bool operator== (const Suite & otherSuite) const
				 *
				 * \param otherSuite: base test to compare
				 *
				 * \return value of the comparison
				 *
				 * Base Suite overloading of operator ==
				 */
				bool operator== (const Suite & otherSuite) const;

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
				std::weak_ptr<tester::base::Factory> factory;

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
				 * @brief Disable move and copy constructors and operator= overloading for class Suite
				 *
				 */
				DISABLE_COPY_MOVE(Suite)

		};

		/**
		 * @brief SuitePtrCompare struct
		 *
		 */
		struct SuitePtrCompare {
			// Struct sets the default access to public
			/**
			 * @brief Function: bool operator() (const std::shared_ptr<tester::base::Suite> & rhs, const std::shared_ptr<tester::base::Suite> & lhs) const
			 *
			 * \param rhs: test suite to compare
			 * \param lhs: test suite to compare
			 *
			 * \return: true if the two tests are the same, false otherwise
			 *
			 * This function compares two shared pointers of object tester::base::Suite
			 */
			bool operator() (const std::shared_ptr<tester::base::Suite> & rhs, const std::shared_ptr<tester::base::Suite> & lhs) const;
		};

	}

}
/** @} */ // End of TesterBaseGroup group

#endif // TEST_SUITE_H
