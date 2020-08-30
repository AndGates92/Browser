#ifndef ERROR_DATA_H
#define ERROR_DATA_H
/**
 * @copyright
 * @file error_data.h
 * @author Andrea Gianarda
 * @date 29th August 2020
 * @brief Error Data header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <memory>
#include <string>

#include "printable_object.h"

/** @defgroup ErrorDataGroup Error Data Doxygen Group
 *  Error Data functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(errorDataOverall)

namespace base_test {
	class BaseTest;
}

namespace error_data {

	/**
	 * @brief search data changed
	 *
	 */
	class ErrorData : public printable_object::PrintableObject {
		public:
			/**
			 * @brief Function: explicit ErrorData(const std::weak_ptr<base_test::BaseTest> & errorTest, const std::string & errorFilename, const int & errorLineNumber, const std::string & errorCondition, const std::string & errorMessage)
			 *
			 * \param errorTest: test the error occurred
			 * \param errorLineNumber: line number of the error
			 * \param errorFilename: filename where the error occurred
			 * \param errorCondition: condition that failed
			 * \param errorMessage: message of the error
			 *
			 * Error data constructor
			 */
			explicit ErrorData(const std::weak_ptr<base_test::BaseTest> & errorTest, const std::string & errorFilename, const int & errorLineNumber, const std::string & errorCondition, const std::string & errorMessage);

			/**
			 * @brief Function: virtual ~ErrorData()
			 *
			 * Error data destructor
			 */
			virtual ~ErrorData();

			// Move and copy constructor
			/**
			 * @brief Function: ErrorData(const error_data::ErrorData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Error data copy constructor
			 */
			ErrorData(const error_data::ErrorData & rhs);

			/**
			 * @brief Function: explicit ErrorData(error_data::ErrorData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Error data move constructor
			 */
			explicit ErrorData(error_data::ErrorData && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: ErrorData & operator=(const error_data::ErrorData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Error data copy assignment operator
			 */
			ErrorData & operator=(const error_data::ErrorData & rhs);

			/**
			 * @brief Function: ErrorData & operator=(error_data::ErrorData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Error data move assignment operator
			 */
			ErrorData & operator=(error_data::ErrorData && rhs);

			/**
			 * @brief Function: bool operator==(const ErrorData & otherData) const
			 *
			 * \param otherData: error data to compare
			 *
			 * \return value of the comparison
			 *
			 * Error Data overloading of operator ==
			 */
			bool operator==(const ErrorData & otherData) const;

			/**
			 * @brief Function: bool partialEqual(const ErrorData & otherData) const
			 *
			 * \param otherData: error data to compare
			 *
			 * \return value of the comparison
			 *
			 * This function compares two error data without taking into account the line
			 */
			bool partialEqual(const ErrorData & otherData) const;

		protected:

			/**
			 * @brief Function: const int & getLine() const
			 *
			 * \return the line where the error occurred
			 *
			 * This function returns the line where the error occurred
			 */
			const int & getLine() const;

			/**
			 * @brief Function: const std::string & getFilename() const
			 *
			 * \return file where the error was triggered
			 *
			 * This function returns the filename where the error occurred 
			 */
			const std::string & getFilename() const;

			/**
			 * @brief Function: const std::string & getCondition() const
			 *
			 * \return condition triggering the error
			 *
			 * This function returns the condition that triggered the error
			 */
			const std::string & getCondition() const;

			/**
			 * @brief Function: const std::string & getMessage() const
			 *
			 * \return error message
			 *
			 * This function returns the error message
			 */
			const std::string & getMessage() const;

			/**
			 * @brief Function: const std::shared_ptr<base_test::BaseTest> getTest() const
			 *
			 * \return shared pointer to the test
			 *
			 * This function returns a share dpointer to the test where the error occurred
			 */
			const std::shared_ptr<base_test::BaseTest> getTest() const;

			/**
			 * @brief Function: virtual const std::string print() const override
			 *
			 * \return error data to print converted to std::string
			 *
			 * This functions prints error data to std::string
			 */
			virtual const std::string print() const override;

		private:
			/**
			 * @brief test where the error was occurred
			 *
			 */
			std::weak_ptr<base_test::BaseTest> test;

			/**
			 * @brief line of the error
			 *
			 */
			int lineNumber;

			/**
			 * @brief filename where the error occurred
			 *
			 */
			std::string filename;

			/**
			 * @brief condition that caused the error
			 *
			 */
			std::string condition;

			/**
			 * @brief error message
			 *
			 */
			std::string message;
	};

}
/** @} */ // End of ErrorDataGroup group

#endif // ERROR_DATA_H
