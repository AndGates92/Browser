#ifndef EXCEPTION_MACROS_H
#define EXCEPTION_MACROS_H
/**
 * @copyright
 * @file exception_macros.h
 * @author Andrea Gianarda
 * @date 16th of February 2020
 * @brief Exception Macros file
*/

#include "browser_exception.h"

/** @defgroup ExceptionMacrosGroup Exception Macros Doxygen Group
 *  Exception Macros
 *  @{
 */

/**
 * @brief QEXCEPTION_THROW_COND(CONDITION, ...)
 *
 * \param CONDITION : condition to throw the exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Throw an exception if CONDITION Is true
 */
#define QEXCEPTION_THROW_COND(CONDITION, ...)\
	if (CONDITION) { \
		QEXCEPTION_THROW(...); \
	}

/**
 * @brief QEXCEPTION_THROW(...)
 *
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Throw an exception
 */
#define QEXCEPTION_THROW(...)\
	QString str(QString::null); \
	str + __VA_ARGS__; \
	throw browser_exception::BrowserException(str);

/** @} */ // End of ExceptionMacrosGroup group

#endif // EXCEPTION_MACROS_H
