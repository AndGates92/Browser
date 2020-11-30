#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H
/**
 * @copyright
 * @file exception.h
 * @author Andrea Gianarda
 * @date 16th of February 2020
 * @brief Exception Macros file
*/

#include "app/shared/utility_macros.h"
#include "app/utility/exception/exception.h"
#include "app/shared/logging.h"

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
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
	ACTION app::exception::Exception(app::shared::getDateTime().toStdString(), __LINE__, __FILE__, CONDITION, msgStream.str());

/** @} */ // End of SharedGroup group

#endif // APP_EXCEPTION_H
