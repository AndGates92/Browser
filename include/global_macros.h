#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H
/**
 * @copyright
 * @file global_macros.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Global Macros file
*/

#include "global_types.h"

/** @defgroup GlobalMacrosGroup Global Macros Doxygen Group
 *  Global Macros
 *  @{
 */

/**
 * @brief Default message type level
 *
 */
#if !defined(MSG_TYPE_LEVEL)
	#define MSG_TYPE_LEVEL QtInfoMsg
#endif

/**
 * @brief Default qinfo verbosity level
 *
 */
#if !defined(QINFO_VERBOSITY)
	#define QINFO_VERBOSITY global_types::qinfo_level_e::MEDIUM
#endif

/**
 * @brief QINFO_PRINT(VERBOSITY, CATEGORY, ...)
 *
 * \param VERBOSITY : verbosity level
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to log_info
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define QINFO_PRINT(VERBOSITY, CATEGORY, ...)\
	if (VERBOSITY <= static_cast<global_types::qinfo_level_e>(QINFO_VERBOSITY)) { \
		qInfo(CATEGORY) << __VA_ARGS__; \
	}

/** @} */ // End of GlobalMacrosGroup group

#endif // GLOBAL_MACROS_H
