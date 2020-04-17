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
#include "logging_functions.h"

/** @defgroup ExceptionMacrosGroup Exception Macros Doxygen Group
 *  Exception Macros
 *  @{
 */

/**
 * @brief QEXCEPTION_ACTION_COND(CONDITION, ACTION, ...)
 *
 * \param CONDITION : condition to execute action on exception
 * \param ACTION    : action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception if CONDITION Is true
 */
#define QEXCEPTION_ACTION_COND(CONDITION, ACTION, ...)\
	if (CONDITION) { \
		QEXCEPTION_ACTION(ACTION, __VA_ARGS__); \
	}

/**
 * @brief QEXCEPTION_ACTION(ACTION, ...)
 *
 * \param ACTION    : action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception
 */
#define QEXCEPTION_ACTION(ACTION, ...)\
	QString str(QString::null); \
	QTextStream(&str) << "[" << logging_functions::getDateTime() << "] Exception caught on file " << __FILE__ << " at line " << __LINE__ << ": " << __VA_ARGS__; \
	ACTION browser_exception::BrowserException(str);

/** @} */ // End of ExceptionMacrosGroup group

#endif // EXCEPTION_MACROS_H
