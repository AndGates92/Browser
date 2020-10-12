#ifndef BASE_TEST_H
#define BASE_TEST_H
/**
 * @copyright
 * @file base_test.h
 * @author Andrea Gianarda
 * @date 24th August 2020
 * @brief Base test header file
 */
// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>
#include <QtWidgets/QApplication>

#include <memory>
#include <map>

#include "test_enums.h"
#include "test_macros.h"
#include "constructor_macros.h"
#include "error_data.h"
#include "printable_object.h"
#include "base_element_creation.h"
#include "main_window_wrapper.h"

/** @defgroup BaseTestGroup Base Test Group
 *  Base test functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(baseTestOverall)
Q_DECLARE_LOGGING_CATEGORY(baseTestTest)
Q_DECLARE_LOGGING_CATEGORY(baseTestApp)

namespace base_factory {
	class BaseFactory;
}

namespace base_suite {
	class BaseSuite;
}

namespace test_runner {
	class TestRunner;
}

namespace base_test {

	/**
	 * @brief BaseTest class
	 *
	 */
	class BaseTest : public std::enable_shared_from_this<base_test::BaseTest>, public printable_object::PrintableObject, public base_element_creation::BaseElementCreation {
		friend base_suite::BaseSuite;
		friend test_runner::TestRunner;

		public:

			/**
			 * @brief type of test error container
			 *
			 */
			typedef std::multimap<test_enums::error_type_e, error_data::ErrorData> test_error_container_t;

			/**
			 * @brief Function: virtual void postProcessCreation() override
			 *
			 * This function run tasks that follows test creation
			 */
			virtual void postProcessCreation() override;

			/**
			 * @brief Function: virtual void run() final
			 *
			 * This function runs the test
			 */
			virtual void run() final;

			/**
			 * @brief Function: bool operator==(const BaseTest & otherTest) const
			 *
			 * \param otherTest: base test to compare
			 *
			 * \return value of the comparison
			 *
			 * Base Test overloading of operator ==
			 */
			bool operator== (const BaseTest & otherTest) const;

			/**
			 * @brief Function: const std::shared_ptr<base_factory::BaseFactory> & getFactory() const
			 *
			 * \return factory the test belongs to
			 *
			 * This function returns the factory the test belongs to
			 */
			const std::shared_ptr<base_factory::BaseFactory> & getFactory() const;

			/**
			 * @brief Function: const std::shared_ptr<base_suite::BaseSuite> getSuite() const
			 *
			 * \return suite the test belongs to
			 *
			 * This function returns the test suite the test belongs to
			 */
			const std::shared_ptr<base_suite::BaseSuite> getSuite() const;

			/**
			 * @brief Function: const std::string & getName() const
			 *
			 * \return name of the test
			 *
			 * This function returns the name of the test
			 */
			const std::string & getName() const;

			/**
			 * @brief Function: const test_enums::test_state_e & getState() const
			 *
			 * \return state of the test
			 *
			 * This function returns the state of the test
			 */
			const test_enums::test_state_e & getState() const;

			/**
			 * @brief Function: const test_enums::test_status_e & getStatus() const
			 *
			 * \return status of the test
			 *
			 * This function returns the status of the test
			 */
			const test_enums::test_status_e & getStatus() const;

			/**
			 * @brief Function: const test_error_container_t & getErrorMap() const
			 *
			 * \return map of errors of the test
			 *
			 * This function returns the map of errors of the test
			 */
			const test_error_container_t & getErrorMap() const;

			/**
			 * @brief Function: const test_error_container_t & getExpectedErrors() const
			 *
			 * \return map of expected errors of the test
			 *
			 * This function returns the map of expected errors of the test
			 */
			const test_error_container_t & getExpectedErrors() const;

			/**
			 * @brief Function: const std::unique_ptr<main_window_wrapper::MainWindowWrapper> & getWindow() const
			 *
			 * \return browser window
			 *
			 * This function returns the window used for the test
			 */
			const std::unique_ptr<main_window_wrapper::MainWindowWrapper> & getWindow() const;


		protected:

			/**
			 * @brief browser window
			 *
			 */
			std::unique_ptr<main_window_wrapper::MainWindowWrapper> window;

			/**
			 * @brief Function: explicit BaseTest(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const std::string & testName)
			 *
			 * \param testSuite: suite the test belongs to
			 * \param testName: name of the test
			 *
			 * Base test constructor
			 */
			explicit BaseTest(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const std::string & testName);

			/**
			 * @brief Function: explicit BaseTest(const std::shared_ptr<base_factory::BaseFactory> & factory, const std::string & suiteName, const std::string & testName)
			 *
			 * \param testFactory: test factory
			 * \param suiteName: name of the suite the test belongs to
			 * \param testName: name of the test
			 *
			 * Base test constructor
			 */
			explicit BaseTest(const std::shared_ptr<base_factory::BaseFactory> & factory, const std::string & suiteName, const std::string & testName);

			/**
			 * @brief Function: virtual ~BaseTest()
			 *
			 * Base test destructor
			 */
			virtual ~BaseTest();

			/**
			 * @brief Function: void addExpectedError(const test_error_container_t & errors)
			 *
			 * \param errors: expected errors
			 *
			 * This function adds items to the expected error multi map
			 */
			void addExpectedError(const test_error_container_t & errors);

			/**
			 * @brief Function: void addExpectedError(const test_enums::error_type_e & type, const error_data::ErrorData & data)
			 *
			 * \param type: type of expected error
			 * \param data: data of the expected error
			 *
			 * This function adds an item to the expected error multi map
			 */
			void addExpectedError(const test_enums::error_type_e & type, const error_data::ErrorData & data);

			/**
			 * @brief Function: void addTestError(const test_enums::error_type_e & type, const error_data::ErrorData & data)
			 *
			 * \param type: type of expected error
			 * \param data: data of the expected error
			 *
			 * This function adds an item to the expected error multi map
			 */
			void addError(test_error_container_t & errors, const test_enums::error_type_e & type, const error_data::ErrorData & data);

			/**
			 * @brief Function: void addAssertionFailure(const int & line, const std::string & filename, const std::string & condition, const test_enums::error_type_e & type, const std::string & errorMessage);
			 *
			 * \param line: line number of the error
			 * \param filename: filename where the error occurred
			 * \param condition: condition that failed
			 * \param type: type of the error
			 * \param errorMessage: message of the error
			 *
			 * This function adds an item to the expected error multi map
			 */
			void addAssertionFailure(const int & line, const std::string & filename, const std::string & condition, const test_enums::error_type_e & type, const std::string & errorMessage);

			/**
			 * @brief Function: void addExceptionThrown(const int & line, const std::string & filename, const std::string & condition, const std::string & errorMessage);
			 *
			 * \param line: line number of the error
			 * \param filename: filename where the error occurred
			 * \param condition: condition that failed
			 * \param errorMessage: message of the error
			 *
			 * This function adds an item to the expected error multi map of type exception and call the wrap-up function if the window is visible
			 */
			void addExceptionThrown(const int & line, const std::string & filename, const std::string & condition, const std::string & errorMessage);

			/**
			 * @brief Function: const std::string print() const override
			 *
			 * \return base test converted to std::string
			 *
			 * This functions prints base test info to std::string
			 */
			const std::string print() const override;

			/**
			 * @brief Function: virtual void testBody()
			 *
			 * This function contains the body of the test
			 */
			virtual void testBody() = 0;

		private:
			/**
			 * @brief Suite the test belongs to
			 *
			 */
			std::weak_ptr<base_suite::BaseSuite> suite;

			/**
			 * @brief name of the test
			 *
			 */
			std::string name;

			/**
			 * @brief map of errors
			 *
			 */
			test_error_container_t errorMap;

			/**
			 * @brief map of expected errors
			 *
			 */
			test_error_container_t expectedErrors;

			/**
			 * @brief state of the test
			 *
			 */
			test_enums::test_state_e state;

			/**
			 * @brief status of the test
			 *
			 */
			test_enums::test_status_e status;

			/**
			 * @brief Function: void test()
			 *
			 * This function contains the test to run
			 */
			void test();

			/**
			 * @brief Function: virtual void setup() final
			 *
			 * This function contains the setup of the test
			 */
			virtual void setup() final;

			/**
			 * @brief Function: virtual void wrapup() final
			 *
			 * This function contains the wrap up of the test
			 */
			virtual void wrapup() final;

			/**
			 * @brief Function: bool errorMatch() const
			 *
			 * \return whether the expected errors are the same as the actual errors
			 *
			 * This function compares the expected and the actual error map
			 */
			bool errorMatch() const;

			/**
			 * @brief Function: bool searchError(const test_error_container_t & container, const test_enums::error_type_e & type, const error_data::ErrorData & data, const bool & fullMatch) const
			 *
			 * \param container: container to search error for
			 * \param type: type of expected error
			 * \param data: data of the expected error
			 * \param fullMatch: compare data with full match
			 *
			 * \return whether the error has been found
			 *
			 * This function searches an error type and data in the container
			 */
			bool searchError(const test_error_container_t & container, const test_enums::error_type_e & type, const error_data::ErrorData & data, const bool & fullMatch) const;

			/**
			 * @brief Function: void setState(const test_enums::test_state_e & value)
			 *
			 * \param value: state of the test
			 *
			 * This function sets the state of the test
			 */
			void setState(const test_enums::test_state_e & value);

			/**
			 * @brief Function: void checkCreation() const
			 *
			 * This function checks that the creation of the test is successful
			 */
			void checkCreation() const;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class BaseTest
			 *
			 */
			DISABLE_COPY_MOVE(BaseTest)

	};

	/**
	 * @brief TestPtrCompare struct
	 *
	 */
	struct TestPtrCompare {
		// Struct sets the default access to public
		/**
		 * @brief Function: bool operator() (const std::shared_ptr<base_test::BaseTest> & rhs, const std::shared_ptr<base_test::BaseTest> & lhs) const
		 *
		 * \param rhs: base test to compare
		 * \param lhs: base test to compare
		 *
		 * \return: true if the two tests are the same, false otherwise
		 *
		 * This function compares two shared pointers of object base_test::BaseTest
		 */
		bool operator() (const std::shared_ptr<base_test::BaseTest> & rhs, const std::shared_ptr<base_test::BaseTest> & lhs) const;
	};

}
/** @} */ // End of BaseTestGroup group

#endif // BASE_TEST_H
