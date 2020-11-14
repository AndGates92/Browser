#ifndef EXCEPTION_MACROS_H
#define EXCEPTION_MACROS_H
/**
 * @copyright
 * @file exception_macros.h
 * @author Andrea Gianarda
 * @date 16th of February 2020
 * @brief Exception Macros file
*/

#include "common/include/global_macros.h"
#include "utility/exception/include/browser_exception.h"
#include "common/include/logging_functions.h"

/** @defgroup ExceptionMacrosGroup Exception Macros Doxygen Group
 *  Exception Macros
 *  @{
 */

/**
 * @brief EXCEPTION_ACTION_COND(CONDITION, ACTION, ...)
 *
 * \param CONDITION : condition to execute action on exception
 * \param ACTION    : action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception if CONDITION Is true
 */
#define EXCEPTION_ACTION_COND(CONDITION, ACTION, ...)\
	if (CONDITION) { \
		EXCEPTION_ACTION_INTERNAL(ACTION, STRINGIFY(CONDITION), __VA_ARGS__); \
	}

/**
 * @brief EXCEPTION_ACTION(ACTION, ...)
 *
 * \param ACTION    : action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception with an empty condition
 */
#define EXCEPTION_ACTION(ACTION, ...)\
	EXCEPTION_ACTION_INTERNAL(ACTION, "", __VA_ARGS__);

/**
 * @brief EXCEPTION_ACTION_INTERNAL(ACTION, ...)
 *
 * \param ACTION    : action on exception
 * \param CONDITION : condition to execute action on exception
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Execute action on an exception
 */
#define EXCEPTION_ACTION_INTERNAL(ACTION, CONDITION, ...)\
	std::stringstream msgStream; \
	msgStream << __VA_ARGS__; \
	ACTION browser_exception::BrowserException(logging_functions::getDateTime().toStdString(), __LINE__, __FILE__, CONDITION, msgStream.str());

/** @} */ // End of ExceptionMacrosGroup group

#endif // EXCEPTION_MACROS_H
