#ifndef BROWSER_EXCEPTION_H
#define BROWSER_EXCEPTION_H
/**
 * @copyright
 * @file browser_exception.h
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QException>

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
	class BrowserException : public QException {

		public:

			/**
			 * @brief Function: explicit BrowserException(const QString & msg)
			 *
			 * \param msg: message of the exception
			 *
			 * Browser exception constructor
			 */
			explicit BrowserException(const QString & msg);

			/**
			 * @brief Function: ~BrowserException()
			 *
			 * Browser exception destructor
			 */
			~BrowserException();

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

		private:
			QString message;

	};

}
/** @} */ // End of BrowserExceptionGroup group

#endif // BROWSER_EXCEPTION_H
