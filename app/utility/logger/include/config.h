#ifndef LOGGER_CONFIG_H
#define LOGGER_CONFIG_H
/**
 * @copyright
 * @file config.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Logger configuration header file
*/

#include <string>
#include <memory>

#include "enums.h"

/** @defgroup LoggerGroup Logger Doxygen Group
 *  Logger functions and classes
 *  @{
 */

namespace logger {

	class Config {

		public:
			/**
			 * @brief Function: static const logger::info_level_e & getDefaultVerbosity()
			 *
			 * \return the default verbosity of info messages
			 *
			 * This function returns the default verbosity of info messages
			 */
			static const logger::info_level_e & getDefaultVerbosity();

			/**
			 * @brief Function: static const logger::msg_type_e & getDefaultType()
			 *
			 * \return the default type of message
			 *
			 * This function returns the default message type
			 */
			static const logger::msg_type_e & getDefaultType();

			/**
			 * @brief Function: static const std::string & getDefaultContextName()
			 *
			 * \return the default context name
			 *
			 * This function returns the default context name
			 */
			static const std::string & getDefaultContextName();

			/**
			 * @brief Function: static const std::string & getDefaultOutputFile()
			 *
			 * \return the default output file
			 *
			 * This function returns the default output file
			 */
			static const std::string & getDefaultOutputFile();

			/**
			 * @brief Function: explicit Config()
			 *
			 * Logger config constructor
			 */
			explicit Config();

			/**
			 * @brief Function: virtual ~Config()
			 *
			 * Logger config destructor
			 */
			virtual ~Config();

		protected:

		private:
			/**
			 * @brief default type of prints
			 *
			 */
			static logger::msg_type_e defaultType;

			/**
			 * @brief default verbosity
			 *
			 */
			static logger::info_level_e defaultVerbosity;

			/**
			 * @brief default context name
			 *
			 */
			static std::string defaultContextName;

			/**
			 * @brief default output file
			 *
			 */
			static std::string defaultOutputFile;

	};

}
/** @} */ // End of LoggerGroup group

#endif // LOGGER_CONFIG_H
