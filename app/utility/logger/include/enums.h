#ifndef LOGGER_ENUMS_H
#define LOGGER_ENUMS_H
/**
 * @copyright
 * @file enums.h
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Logger enumeration file
*/

#include "type_print_macros.h"

/** @defgroup LoggerGroup Logger Doxygen Group
 *  Logger
 *  @{
 */
namespace logger {

	Q_NAMESPACE

	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class info_level_list {
		ZERO,   /**< Always printed */
		LOW,    /**< Low level pf printing */
		MEDIUM, /**< Medium level of printing */
		HIGH    /**< High level of printing */
	} info_level_e;

	/**
	 * @brief Overload operators to ease print of the info level
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(info_level_list, logger::info_level_e)

	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class msg_type_list {
		DEBUG,   /**< Debug information */
		INFO,    /**< Information */
		WARNING, /**< Warning message */
		ERROR,   /**< Error message */
		FATAL    /**< Fatal message */
	} msg_type_e;

	/**
	 * @brief Overload operators to ease print of the qinfo level
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(msg_type_list, logger::msg_type_e)

	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class state_list {
		CONSTRUCTED,     /**< constructed */
		INITIALIZED,     /**< context data are copied */
		WRITING_HEADER,  /**< header is about to be written */
		LOGGING_MESSAGE, /**< logging message */
		LOGGING_ENDED,   /**< logging is ended */
		TERMINATING      /**< terminating logger */
	} state_e;

	/**
	 * @brief Overload operators to ease print of the qinfo level
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(state_list, logger::state_e)


}

/** @} */ // End of LoggerGroup group

#endif // LOGGER_ENUMS_H
