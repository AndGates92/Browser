#ifndef BASE_TEST_H
#define BASE_TEST_H
/**
 * @copyright
 * @file test.h
 * @author Andrea Gianarda
 * @date 24th August 2020
 * @brief Base test header file
 */

#include <memory>
#include <map>

#include <QtTest/QTest>

#include "tester/shared/enums.h"
#include "tester/shared/macros.h"
#include "app/shared/constructor_macros.h"
#include "app/utility/log/printable_object.h"
#include "tester/shared/base_element_creation.h"

/** @defgroup TesterBaseGroup Tester Base Doxygen Group
 *  Tester Base functions and classes
 *  @{
 */

namespace app {
	namespace main_window {
		namespace window {
			class MainWindow;
		}
	}
}

namespace tester {

	namespace main_window_wrapper {
		class MainWindowWrapper;
	}

	namespace utility {
		class TestRunner;
	}

	namespace shared {
		class ErrorData;
	}

	namespace base {

		class Factory;
		class Suite;

		/**
		 * @brief BaseTest class
		 *
		 */
		class Test : public std::enable_shared_from_this<tester::base::Test>, public app::printable_object::PrintableObject, public tester::shared::BaseElementCreation {
			friend tester::base::Suite;
			friend tester::utility::TestRunner;

			public:

				/**
				 * @brief type of test error container
				 *
				 */
				typedef std::multimap<tester::shared::error_type_e, tester::shared::ErrorData> test_error_container_t;

				/**
				 * @brief Function: bool operator==(const Test & otherTest) const
				 *
				 * \param otherTest: base test to compare
				 *
				 * \return value of the comparison
				 *
				 * Base Test overloading of operator ==
				 */
				bool operator== (const Test & otherTest) const;

				/**
				 * @brief Function: bool weakEqualByName(const std::string & testName) const
				 *
				 * \param testName: string to find in the test name
				 *
				 * \return true if the name of the test contains the string provided as argument without case sensitivity
				 *
				 * This function returns the name of the test contains the string provided as argument
				 */
				bool weakEqualByName(const std::string & testName) const;

				/**
				 * @brief Function: static void sendKeyClickToFocus(const Qt::Key key)
				 *
				 * \return key: key to send to the focus
				 *
				 * This function sends a key click to the current focus
				 */
				static void sendKeyClickToFocus(const Qt::Key key);

				/**
				 * @brief Function: static void sendKeyClicksToFocus(const std::string & text)
				 *
				 * \return text: key to send to the focus
				 *
				 * This function sends the text as key clicks to the current focus
				 */
				static void sendKeyClicksToFocus(const std::string & text);

				/*
				 * @brief Function: static void sendKeyEventToFocus(const QTest::KeyAction & keyAction, const char character)
				 *
				 * \return keyAction: key action to send to the focus
				 * \return character: character to send to the focus
				 *
				 * This function sends a key action to the current focus
				 */
				static void sendKeyEventToFocus(const QTest::KeyAction & keyAction, const char character);

				/*
				 * @brief Function: static void sendKeyEventsToFocus(const QTest::KeyAction & keyAction, const std::string & text)
				 *
				 * \return keyAction: key action to send to the focus
				 * \return text: string to send to the focus
				 *
				 * This function sends a string as single characters to the current focus
				 */
				static void sendKeyEventsToFocus(const QTest::KeyAction & keyAction, const std::string & text);

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
				 * @brief Function: const std::shared_ptr<tester::base::Factory> & getFactory() const
				 *
				 * \return factory the test belongs to
				 *
				 * This function returns the factory the test belongs to
				 */
				const std::shared_ptr<tester::base::Factory> & getFactory() const;

				/**
				 * @brief Function: const std::shared_ptr<tester::base::Suite> getSuite() const
				 *
				 * \return suite the test belongs to
				 *
				 * This function returns the test suite the test belongs to
				 */
				const std::shared_ptr<tester::base::Suite> getSuite() const;

				/**
				 * @brief Function: const std::string & getName() const
				 *
				 * \return name of the test
				 *
				 * This function returns the name of the test
				 */
				const std::string & getName() const;

				/**
				 * @brief Function: const tester::shared::test_state_e & getState() const
				 *
				 * \return state of the test
				 *
				 * This function returns the state of the test
				 */
				const tester::shared::test_state_e & getState() const;

				/**
				 * @brief Function: const tester::shared::test_status_e & getStatus() const
				 *
				 * \return status of the test
				 *
				 * This function returns the status of the test
				 */
				const tester::shared::test_status_e & getStatus() const;

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
				 * @brief Function: const std::unique_ptr<app::main_window::window::MainWindow> & getWindow() const
				 *
				 * \return browser window
				 *
				 * This function returns the window used for the test
				 */
				const std::unique_ptr<app::main_window::window::MainWindow> & getWindow() const;

			protected:

				/**
				 * @brief browser window wrapper
				 *
				 */
				std::unique_ptr<tester::main_window_wrapper::MainWindowWrapper> windowWrapper;

				/**
				 * @brief Function: explicit Test(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName)
				 *
				 * \param testSuite: suite the test belongs to
				 * \param testName: name of the test
				 *
				 * Base test constructor
				 */
				explicit Test(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName);

				/**
				 * @brief Function: explicit Test(const std::shared_ptr<tester::base::Factory> & factory, const std::string & suiteName, const std::string & testName)
				 *
				 * \param testFactory: test factory
				 * \param suiteName: name of the suite the test belongs to
				 * \param testName: name of the test
				 *
				 * Base test constructor
				 */
				explicit Test(const std::shared_ptr<tester::base::Factory> & factory, const std::string & suiteName, const std::string & testName);

				/**
				 * @brief Function: virtual ~Test()
				 *
				 * Base test destructor
				 */
				virtual ~Test();

				/**
				 * @brief Function: void setName(const std::string & testName)
				 *
				 * \param testName: name of the test
				 *
				 * This function sets the name of the test
				 */
				void setName(const std::string & testName);

				/**
				 * @brief Function: void addExpectedError(const test_error_container_t & errors)
				 *
				 * \param errors: expected errors
				 *
				 * This function adds items to the expected error multi map
				 */
				void addExpectedError(const test_error_container_t & errors);

				/**
				 * @brief Function: void addExpectedError(const tester::shared::error_type_e & type, const tester::shared::ErrorData & data)
				 *
				 * \param type: type of expected error
				 * \param data: data of the expected error
				 *
				 * This function adds an item to the expected error multi map
				 */
				void addExpectedError(const tester::shared::error_type_e & type, const tester::shared::ErrorData & data);

				/**
				 * @brief Function: void addTestError(const tester::shared::error_type_e & type, const tester::shared::ErrorData & data)
				 *
				 * \param type: type of expected error
				 * \param data: data of the expected error
				 *
				 * This function adds an item to the expected error multi map
				 */
				void addError(test_error_container_t & errors, const tester::shared::error_type_e & type, const tester::shared::ErrorData & data);

				/**
				 * @brief Function: void addAssertionFailure(const int & line, const std::string & filename, const std::string & condition, const tester::shared::error_type_e & type, const std::string & errorMessage);
				 *
				 * \param line: line number of the error
				 * \param filename: filename where the error occurred
				 * \param condition: condition that failed
				 * \param type: type of the error
				 * \param errorMessage: message of the error
				 *
				 * This function adds an item to the expected error multi map
				 */
				void addAssertionFailure(const int & line, const std::string & filename, const std::string & condition, const tester::shared::error_type_e & type, const std::string & errorMessage);

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
				 * @brief Function: bool waitForCondition(const std::function<bool(void)> & conditionFunction, const std::chrono::milliseconds & timeout) const
				 *
				 * \param conditionFunction: function that the method is waiting to become true
				 * \param timeout: timeout of the wait for the function to become true
				 *
				 * \return value returned by the function when exiting the method
				 *
				 * This function wait for a condition to become true before the timeout
				 */
				bool waitForCondition(const std::function<bool(void)> & conditionFunction, const std::chrono::milliseconds & timeout) const;

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
				std::weak_ptr<tester::base::Suite> suite;

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
				tester::shared::test_state_e state;

				/**
				 * @brief status of the test
				 *
				 */
				tester::shared::test_status_e status;

				/**
				 * @brief Function: void test()
				 *
				 * This function contains the test to run
				 */
				void test();

				/**
				 * @brief Function: virtual bool setup() final
				 *
				 * \return whether setup was successful
				 *
				 * This function contains the setup of the test
				 */
				virtual bool setup() final;

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
				 * @brief Function: bool searchError(const test_error_container_t & container, const tester::shared::error_type_e & type, const tester::shared::ErrorData & data, const bool & fullMatch) const
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
				bool searchError(const test_error_container_t & container, const tester::shared::error_type_e & type, const tester::shared::ErrorData & data, const bool & fullMatch) const;

				/**
				 * @brief Function: void setState(const tester::shared::test_state_e & value)
				 *
				 * \param value: state of the test
				 *
				 * This function sets the state of the test
				 */
				void setState(const tester::shared::test_state_e & value);

				/**
				 * @brief Function: void checkCreation() const
				 *
				 * This function checks that the creation of the test is successful
				 */
				void checkCreation() const;

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class Test
				 *
				 */
				DISABLE_COPY_MOVE(Test)

		};

		/**
		 * @brief TestPtrCompare struct
		 *
		 */
		struct TestPtrCompare {
			// Struct sets the default access to public
			/**
			 * @brief Function: bool operator() (const std::shared_ptr<tester::base::Test> & rhs, const std::shared_ptr<tester::base::Test> & lhs) const
			 *
			 * \param rhs: base test to compare
			 * \param lhs: base test to compare
			 *
			 * \return: true if the two tests are the same, false otherwise
			 *
			 * This function compares two shared pointers of object tester::base::Test
			 */
			bool operator() (const std::shared_ptr<tester::base::Test> & rhs, const std::shared_ptr<tester::base::Test> & lhs) const;
		};

	}

}
/** @} */ // End of TesterBaseGroup group

#endif // BASE_TEST_H
