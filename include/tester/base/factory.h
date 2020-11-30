#ifndef BASE_FACTORY_H
#define BASE_FACTORY_H
/**
 * @copyright
 * @file factory.h
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Base factory header file
 */

#include <memory>
#include <set>

#include "app/shared/constructor_macros.h"
#include "app/utility/log/printable_object.h"
#include "tester/base/suite.h"
#include "tester/shared/base_element_creation.h"

/** @defgroup TesterBaseGroup Tester Base Doxygen Group
 *  Tester Base functions and classes
 *  @{
 */

namespace tester {

	namespace base {

		class Test;

		/**
		 * @brief BaseFactory class
		 *
		 */
		class Factory : public std::enable_shared_from_this<tester::base::Factory>, public app::printable_object::PrintableObject, public tester::shared::BaseElementCreation {

			public:

				/**
				 * @brief type of test error container
				 *
				 */
				typedef std::set<std::shared_ptr<tester::base::Suite>, tester::base::SuitePtrCompare> suite_container_t;

				/**
				 * @brief Function: explicit Factory(int & argc, char** argv, const suite_container_t & testSuites = suite_container_t())
				 *
				 * \param argc: number of arguments
				 * \param argv: value of arguments
				 * \param testSuites: initial collection of test suites
				 *
				 * Base factory constructor
				 */
				explicit Factory(int & argc, char** argv, const suite_container_t & testSuites = suite_container_t());

				/**
				 * @brief Function: virtual ~Factory()
				 *
				 * Base factory destructor
				 */
				virtual ~Factory();

				/**
				 * @brief Function: void addTest(const std::string & suiteName, const std::shared_ptr<tester::base::Test> & test)
				 *
				 * \param suiteName: name of the suite the test belongs to
				 * \param test: test to add
				 *
				 * This function adds tests to a suite. It the suite doesn't exists, it will be created
				 */
				void addTest(const std::string & suiteName, const std::shared_ptr<tester::base::Test> & test);

				/**
				 * @brief Function: void addTest(const std::shared_ptr<tester::base::Suite> & suite, const std::shared_ptr<tester::base::Test> & test)
				 *
				 * \param suite: suite the test belongs to
				 * \param test: test to add
				 *
				 * This function adds tests to a suite. It the suite doesn't exists, it will be created
				 */
				void addTest(const std::shared_ptr<tester::base::Suite> & suite, const std::shared_ptr<tester::base::Test> & test);

				/**
				 * @brief Function: void addSuite(const std::shared_ptr<tester::base::Suite> & suite)
				 *
				 * \param suite: suite to add to the factory
				 *
				 * This function adds a suite to the factory
				 */
				void addSuite(const std::shared_ptr<tester::base::Suite> & suite);

				/**
				 * @brief Function: std::shared_ptr<tester::base::Suite> findOrCreateSuite(const std::string & suiteName)
				 *
				 * \param suiteName: name of the suite to find
				 *
				 * \return the suite
				 *
				 * This function finds a suite with a given name. If it is not found, it will be created
				 */
				std::shared_ptr<tester::base::Suite> findOrCreateSuite(const std::string & suiteName);

				/**
				 * @brief Function: std::shared_ptr<tester::base::Suite> findSuite(const std::string & suiteName) const
				 *
				 * \param suiteName: name of the suite to find
				 *
				 * \return the suite
				 *
				 * This function finds a suite with a given name
				 */
				std::shared_ptr<tester::base::Suite> findSuite(const std::string & suiteName) const;

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
				 * @brief Function: std::shared_ptr<tester::base::Suite> createSuite(const std::string & suiteName)
				 *
				 * \param suiteName: name of the suite
				 *
				 * \return the suite created
				 *
				 * This function creates a new suite to the factory
				 */
				std::shared_ptr<tester::base::Suite> createSuite(const std::string & suiteName);

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
				 * @brief Disable move and copy constructors and operator= overloading for class Factory
				 *
				 */
				DISABLE_COPY_MOVE(Factory)

		};

	}

}
/** @} */ // End of TesterBaseGroup group

#endif // BASE_FACTORY_H
