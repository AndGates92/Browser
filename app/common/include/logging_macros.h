#ifndef LOGGING_MACROS_H
#define LOGGING_MACROS_H
/**
 * @copyright
 * @file logging_macros.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Logging Macros file
*/

#include "global_types.h"

/** @defgroup LoggingMacrosGroup Logging Macros Doxygen Group
 *  Logging Macros
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
 * @brief QDEBUG_PRINT(CATEGORY, ...)
 *
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to debugMsg
 *
 * Print a debug message to the log file
 */
#define QDEBUG_PRINT(CATEGORY, ...)\
	QDebug debugMsg(qDebug(CATEGORY)); \
	debugMsg.noquote(); \
	debugMsg.nospace(); \
	debugMsg << __VA_ARGS__; \

/**
 * @brief QINFO_PRINT(VERBOSITY, CATEGORY, ...)
 *
 * \param VERBOSITY : verbosity level
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define QINFO_PRINT(VERBOSITY, CATEGORY, ...)\
	if (VERBOSITY <= static_cast<global_types::qinfo_level_e>(QINFO_VERBOSITY)) { \
		QDebug infoMsg(qInfo(CATEGORY)); \
		infoMsg.noquote(); \
		infoMsg.nospace(); \
		infoMsg << __VA_ARGS__; \
	}

/**
 * @brief QWARNING_PRINT(CATEGORY, ...)
 *
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to warningMsg
 *
 * Print a warning message to the log file
 */
#define QWARNING_PRINT(CATEGORY, ...)\
	QDebug warningMsg(qWarning(CATEGORY)); \
	warningMsg.noquote(); \
	warningMsg.nospace(); \
	warningMsg << __VA_ARGS__; \

/**
 * @brief QCRITICAL_PRINT(CONDITION, CATEGORY, ...)
 *
 * \param CONDITION : condition to print the message
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a critical message to the log file is the condition is true
 */
#define QCRITICAL_PRINT(CONDITION, CATEGORY, ...)\
	if (CONDITION) { \
		QDebug criticalMsg(qCritical(CATEGORY)); \
		criticalMsg.noquote(); \
		criticalMsg.nospace(); \
		criticalMsg << __VA_ARGS__; \
	}

/**
 * @brief QFATAL_PRINT(MSG)
 *
 * \param MSG  : text to print
 *
 * Print a fatal message to the log file
 */
#define QFATAL_PRINT(MSG) \
	qFatal(MSG);

/** @} */ // End of LoggingMacrosGroup group

#endif // LOGGING_MACROS_H