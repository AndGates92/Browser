#ifndef BROWSER_EXCEPTION_H
#define BROWSER_EXCEPTION_H
/**
 * @copyright
 * @file exception.h
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

#include <sstream>
#include <exception>

/** @defgroup ExceptionGroup Browser Exception Doxygen Group
 *  Browser Exception functions and classes
 *  @{
 */

namespace app {

	namespace exception {

		/**
		 * @brief Function: void printException(std::string message)
		 *
		 * \param message: message of the exception
		 *
		 * Print message on stderr
		 */
		void printException(std::string message);

		/**
		 * @brief Exception class
		 *
		 */
		class Exception final : public std::exception {

			public:

				/**
				 * @brief Function: explicit Exception(const std::string exceptionTimestamp, const int & exceptionLine, const std::string & exceptionFile, const std::string & exceptionCondition, const std::string & exceptionMsg)
				 *
				 * \param exceptionTimestamp: timestamp when the exception was created
				 * \param exceptionLine: line where the exception was triggered
				 * \param exceptionFile: file in which the exception was triggered
				 * \param exceptionCondition: condition that triggered the exception
				 * \param exceptionMsg: message of the exception
				 *
				 * Browser exception constructor
				 */
				explicit Exception(const std::string exceptionTimestamp, const int & exceptionLine, const std::string & exceptionFile, const std::string & exceptionCondition, const std::string & exceptionMsg);

				/**
				 * @brief Function: virtual ~Exception()
				 *
				 * Browser exception destructor
				 */
				virtual ~Exception();

				/**
				 * @brief Function: void raise() const
				 *
				 * Raise exception
				 */
				void raise() const;

				/**
				 * @brief Function: app::exception::Exception * clone() const
				 *
				 * \return a deep copy of the exception
				 *
				 * Clone exception
				 */
				app::exception::Exception * clone() const;

				/**
				 * @brief Function: virtual const char * what() const noexcept override
				 *
				 * \return print the exception message
				 *
				 * Print message
				 */
				virtual const char * what() const noexcept override;

				/**
				 * @brief Function: std::string print() const
				 *
				 * \return print the exception message
				 *
				 * Print message
				 */
				std::string print() const;

				/**
				 * @brief Function: const std::string & getTimestamp() const
				 *
				 * \return exception timestamp
				 *
				 * This function returns the timestamp when the exception was triggered
				 */
				const std::string & getTimestamp() const;

				/**
				 * @brief Function: const int & getLine() const
				 *
				 * \return the line where the exception occurred
				 *
				 * This function returns the line where the exception occurred
				 */
				const int & getLine() const;

				/**
				 * @brief Function: const std::string & getFilename() const
				 *
				 * \return file where the exception was triggered
				 *
				 * This function returns the filename where the exception occurred
				 */
				const std::string & getFilename() const;

				/**
				 * @brief Function: const std::string & getCondition() const
				 *
				 * \return condition triggering the exception
				 *
				 * This function returns the condition that triggered the exception
				 */
				const std::string & getCondition() const;

				/**
				 * @brief Function: const std::string & getMessage() const
				 *
				 * \return exception message
				 *
				 * This function returns the exception message
				 */
				const std::string & getMessage() const;

			private:
				/**
				 * @brief timestamp of the exception
				 *
				 */
				std::string timestamp;

				/**
				 * @brief line of the exception
				 *
				 */
				int line;

				/**
				 * @brief filename where the exception triggered
				 *
				 */
				std::string filename;

				/**
				 * @brief condition that caused the exception
				 *
				 */
				std::string condition;

				/**
				 * @brief message of the exception
				 *
				 */
				std::string message;

		};

	}

}
/** @} */ // End of ExceptionGroup group

#endif // BROWSER_EXCEPTION_H
