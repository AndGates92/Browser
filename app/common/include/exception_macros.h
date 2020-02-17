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
		QEXCEPTION_ACTION(ACTION, ...); \
	}

/**
 * @brief QEXCEPTION_ACTION(...)
 *
 * \param ACTION    : action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception
 */
#define QEXCEPTION_ACTION(ACTION, ...)\
	QString str(QString::null); \
	str + __VA_ARGS__; \
	ACTION browser_exception::BrowserException(str);

/** @} */ // End of ExceptionMacrosGroup group

#endif // EXCEPTION_MACROS_H
