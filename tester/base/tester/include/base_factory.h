#ifndef BASE_FACTORY_H
#define BASE_FACTORY_H
/**
 * @copyright
 * @file base_factory.h
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Base factory header file
 */

#include <memory>
#include <set>

#include "constructor_macros.h"
#include "printable_object.h"
#include "base_suite.h"
#include "base_element_creation.h"

/** @defgroup BaseFactoryGroup Base Factory Group
 *  Base factory functions and classes
 *  @{
 */

namespace base_test {
	class BaseTest;
}

namespace base_factory {

	/**
	 * @brief BaseFactory class
	 *
	 */
	class BaseFactory : public std::enable_shared_from_this<base_factory::BaseFactory>, public printable_object::PrintableObject, public base_element_creation::BaseElementCreation {

		public:

			/**
			 * @brief type of test error container
			 *
			 */
			typedef std::set<std::shared_ptr<base_suite::BaseSuite>, base_suite::SuitePtrCompare> suite_container_t;

			/**
			 * @brief Function: explicit BaseFactory(int & argc, char** argv, const suite_container_t & testSuites = suite_container_t())
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 * \param testSuites: initial collection of test suites
			 *
			 * Base factory constructor
			 */
			explicit BaseFactory(int & argc, char** argv, const suite_container_t & testSuites = suite_container_t());

			/**
			 * @brief Function: virtual ~BaseFactory()
			 *
			 * Base factory destructor
			 */
			virtual ~BaseFactory();

			/**
			 * @brief Function: void addTest(const std::string & suiteName, const std::shared_ptr<base_test::BaseTest> & test)
			 *
			 * \param suiteName: name of the suite the test belongs to
			 * \param test: test to add
			 *
			 * This function adds tests to a suite. It the suite doesn't exists, it will be created
			 */
			void addTest(const std::string & suiteName, const std::shared_ptr<base_test::BaseTest> & test);

			/**
			 * @brief Function: void addTest(const std::shared_ptr<base_suite::BaseSuite> & suite, const std::shared_ptr<base_test::BaseTest> & test)
			 *
			 * \param suite: suite the test belongs to
			 * \param test: test to add
			 *
			 * This function adds tests to a suite. It the suite doesn't exists, it will be created
			 */
			void addTest(const std::shared_ptr<base_suite::BaseSuite> & suite, const std::shared_ptr<base_test::BaseTest> & test);

			/**
			 * @brief Function: void addSuite(const std::shared_ptr<base_suite::BaseSuite> & suite)
			 *
			 * \param suite: suite to add to the factory
			 *
			 * This function adds a suite to the factory
			 */
			void addSuite(const std::shared_ptr<base_suite::BaseSuite> & suite);

			/**
			 * @brief Function: std::shared_ptr<base_suite::BaseSuite> findOrCreateSuite(const std::string & suiteName)
			 *
			 * \param suiteName: name of the suite to find
			 *
			 * \return the suite
			 *
			 * This function finds a suite with a given name. If it is not found, it will be created
			 */
			std::shared_ptr<base_suite::BaseSuite> findOrCreateSuite(const std::string & suiteName);

			/**
			 * @brief Function: std::shared_ptr<base_suite::BaseSuite> findSuite(const std::string & suiteName) const
			 *
			 * \param suiteName: name of the suite to find
			 *
			 * \return the suite
			 *
			 * This function finds a suite with a given name
			 */
			std::shared_ptr<base_suite::BaseSuite> findSuite(const std::string & suiteName) const;

			/**
			 * @brief Function: const suite_container_t & getSuites() const
			 *
			 * \return a container with all test suites
			 *
			 * This function returns the test suites
			 */
			const suite_container_t & getSuites() const;

			/**
			 * @brief Function: virtual void postProcessCreation() override
			 *
			 * This function run tasks that follows factory creation
			 */
			virtual void postProcessCreation() override;

			/**
			 * @brief Function: virtual void populate()
			 *
			 * This function populates the suite
			 */
			virtual void populate();

			/**
			 * @brief Function: int & getArgc()
			 *
			 * \return the number of arguments provided in the command line
			 *
			 * This function returns the number of argument provided in the command line that launched the application
			 */
			int & getArgc();

			/**
			 * @brief Function: char ** getArgv()
			 *
			 * \return the command line
			 *
			 * This function returns the command line that launched the application
			 */
			char ** getArgv();

		protected:
			/**
			 * @brief Function: std::shared_ptr<base_suite::BaseSuite> createSuite(const std::string & suiteName)
			 *
			 * \param suiteName: name of the suite
			 *
			 * \return the suite created
			 *
			 * This function creates a new suite to the factory
			 */
			std::shared_ptr<base_suite::BaseSuite> createSuite(const std::string & suiteName);

			/**
			 * @brief Function: const std::string print() const override
			 *
			 * \return base factory converted to std::string
			 *
			 * This functions prints base factory info to std::string
			 */
			const std::string print() const override;

		private:

			/**
			 * @brief number of arguments provided in the command line to launch the application
			 *
			 */
			int argc;

			/**
			 * @brief command line used to launch the application
			 *
			 */
			char** argv;

			/**
			 * @brief test suites
			 *
			 */
			suite_container_t suites;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class BaseFactory
			 *
			 */
			DISABLE_COPY_MOVE(BaseFactory)

	};

}
/** @} */ // End of BaseFactoryGroup group

#endif // BASE_FACTORY_H
