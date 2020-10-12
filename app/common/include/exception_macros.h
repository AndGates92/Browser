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
		QEXCEPTION_ACTION_INTERNAL(ACTION, #CONDITION, __VA_ARGS__); \
	}

/**
 * @brief QEXCEPTION_ACTION(ACTION, ...)
 *
 * \param ACTION    : action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception with an empty condition
 */
#define QEXCEPTION_ACTION(ACTION, ...)\
	QEXCEPTION_ACTION_INTERNAL(ACTION, "", __VA_ARGS__);

/**
 * @brief QEXCEPTION_ACTION_INTERNAL(ACTION, ...)
 *
 * \param ACTION    : action on exception
 * \param CONDITION : condition to execute action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception
 */
#define QEXCEPTION_ACTION_INTERNAL(ACTION, CONDITION, ...)\
	QString msg = QString(); \
	QTextStream(&msg) << __VA_ARGS__; \
	ACTION browser_exception::BrowserException(logging_functions::getDateTime(), __LINE__, __FILE__, CONDITION, msg);

/** @} */ // End of ExceptionMacrosGroup group

#endif // EXCEPTION_MACROS_H
