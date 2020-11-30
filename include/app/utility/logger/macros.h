#ifndef LOGGER_MACROS_H
#define LOGGER_MACROS_H
/**
 * @copyright
 * @file macros.h
 * @author Andrea Gianarda
 * @date 08th of November 2020
 * @brief Logger Macros file
*/

#include "app/shared/utility_macros.h"
#include "app/shared/enums.h"
#include "app/utility/logger/logger.h"

/** @defgroup Logger Logging Macros Doxygen Group
 *  Logger Macros
 *  @{
 */

/**
 * @brief Default info verbosity level
 *
 */
#if !defined(INFO_VERBOSITY)
	#define INFO_VERBOSITY MEDIUM
#endif // INFO_VERBOSITY

/**
 * @brief Default message type level
 *
 */
#if !defined(TYPE_LEVEL)
	#define TYPE_LEVEL INFO
#endif // TYPE_LEVEL

/**
 * @brief EXPORT_CONTEXT(CONTEXT)
 *
 * \param CONTEXT      : name of the function declaring the context
 *
 * Export context
 */
#define EXPORT_CONTEXT(CONTEXT) \
	extern const app::logger::Context & CONTEXT();

/**
 * @brief LOGGING_CONTEXT(CONTEXT, NAME, MINIMUM_TYPE, MINIMUM_INFO)
 *
 * \param CONTEXT      : name of the function declaring the context
 * \param NAME         : name of the context
 * \param MINIMUM_TYPE : minimum type printed by the context
 * \param MINIMUM_INFO : minimum verbosity for info messages
 *
 * Declare context
 */
#define LOGGING_CONTEXT(CONTEXT, NAME, MINIMUM_TYPE, MINIMUM_INFO) \
	const app::logger::Context & CONTEXT() { \
		static const app::logger::Context context(STRINGIFY(NAME), app::logger::msg_type_e::MINIMUM_TYPE, app::logger::info_level_e::INFO_VERBOSITY); \
		return context; \
	}

/**
 * @brief LOG_INFO(VERBOSITY, CONTEXT, ...)
 *
 * \param VERBOSITY : verbosity level
 * \param CONTEXTY  : context of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define LOG_INFO(VERBOSITY, CONTEXT, ...)\
	{ \
		app::logger::Logger infoLogger(app::logger::msg_type_e::INFO, __FILE__, __LINE__, __func__, VERBOSITY); \
		infoLogger.initializeLogging(CONTEXT); \
		infoLogger << __VA_ARGS__; \
	}

/**
 * @brief LOG_WARNING(CONTEXT, ...)
 *
 * \param CONTEXTY  : context of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a message to the warning file
 */
#define LOG_WARNING(CONTEXT, ...)\
	{ \
		app::logger::Logger warningLogger(app::logger::msg_type_e::WARNING, __FILE__, __LINE__, __func__); \
		warningLogger.initializeLogging(CONTEXT); \
		warningLogger << __VA_ARGS__; \
	}

/**
 * @brief LOG_ERROR(CONTEXT, ...)
 *
 * \param CONTEXTY  : context of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a message to the error file
 */
#define LOG_ERROR(CONTEXT, ...)\
	{ \
		app::logger::Logger errorLogger(app::logger::msg_type_e::ERROR, __FILE__, __LINE__, __func__); \
		errorLogger.initializeLogging(CONTEXT); \
		errorLogger << __VA_ARGS__; \
	}

/**
 * @brief LOG_FATAL(CONTEXT, ...)
 *
 * \param CONTEXTY  : context of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a message to the fatal file
 */
#define LOG_FATAL(CONTEXT, ...)\
	{ \
		app::logger::Logger fatalLogger(app::logger::msg_type_e::FATAL, __FILE__, __LINE__, __func__); \
		fatalLogger.initializeLogging(CONTEXT); \
		fatalLogger << __VA_ARGS__; \
	}

/** @} */ // End of LoggerMacrosGroup group

#endif // LOGGER_MACROS_H
