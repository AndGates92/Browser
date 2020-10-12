#ifndef BROWSER_EXCEPTION_H
#define BROWSER_EXCEPTION_H
/**
 * @copyright
 * @file browser_exception.h
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

#include <QtCore/QLoggingCategory>
#include <QtCore/QException>

/** @defgroup BrowserExceptionGroup Browser Exception Doxygen Group
 *  Browser Exception functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(browserExceptionOverall)
Q_DECLARE_LOGGING_CATEGORY(browserExceptionPrint)

namespace browser_exception {

	/**
	 * @brief Function: void printException(QString message)
	 *
	 * \param message: message of the exception
	 *
	 * Print message on stderr
	 */
	void printException(QString message);

	/**
	 * @brief BrowserException class
	 *
	 */
	class BrowserException final : public QException {

		public:

			/**
			 * @brief Function: explicit BrowserException(const QString exceptionTimestamp, const int & exceptionLine, const QString & exceptionFile, const QString & exceptionCondition, const QString & exceptionMsg)
			 *
			 * \param exceptionTimestamp: timestamp when the exception was created
			 * \param exceptionLine: line where the exception was triggered
			 * \param exceptionFile: file in which the exception was triggered
			 * \param exceptionCondition: condition that triggered the exception
			 * \param exceptionMsg: message of the exception
			 *
			 * Browser exception constructor
			 */
			explicit BrowserException(const QString exceptionTimestamp, const int & exceptionLine, const QString & exceptionFile, const QString & exceptionCondition, const QString & exceptionMsg);

			/**
			 * @brief Function: virtual ~BrowserException()
			 *
			 * Browser exception destructor
			 */
			virtual ~BrowserException();

			/**
			 * @brief Function: void raise() const override
			 *
			 * Raise exception
			 */
			void raise() const override;

			/**
			 * @brief Function: browser_exception::BrowserException * clone() const override
			 *
			 * \return a deep copy of the exception
			 *
			 * Clone exception
			 */
			browser_exception::BrowserException * clone() const override;

			/**
			 * @brief Function: QString print() const
			 *
			 * Print message
			 */
			QString print() const;

			/**
			 * @brief Function: const QString & getTimestamp() const
			 *
			 * \return exception timestamp
			 *
			 * This function returns the timestamp when the exception was triggered
			 */
			const QString & getTimestamp() const;

			/**
			 * @brief Function: const int & getLine() const
			 *
			 * \return the line where the exception occurred
			 *
			 * This function returns the line where the exception occurred
			 */
			const int & getLine() const;

			/**
			 * @brief Function: const QString & getFilename() const
			 *
			 * \return file where the exception was triggered
			 *
			 * This function returns the filename where the exception occurred
			 */
			const QString & getFilename() const;

			/**
			 * @brief Function: const QString & getCondition() const
			 *
			 * \return condition triggering the exception
			 *
			 * This function returns the condition that triggered the exception
			 */
			const QString & getCondition() const;

			/**
			 * @brief Function: const QString & getMessage() const
			 *
			 * \return exception message
			 *
			 * This function returns the exception message
			 */
			const QString & getMessage() const;

		private:
			/**
			 * @brief timestamp of the exception
			 *
			 */
			QString timestamp;

			/**
			 * @brief line of the exception
			 *
			 */
			int line;

			/**
			 * @brief filename where the exception triggered
			 *
			 */
			QString filename;

			/**
			 * @brief condition that caused the exception
			 *
			 */
			QString condition;

			/**
			 * @brief message of the exception
			 *
			 */
			QString message;

	};

}
/** @} */ // End of BrowserExceptionGroup group

#endif // BROWSER_EXCEPTION_H
