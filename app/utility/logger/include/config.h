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
#include "singleton.h"

/** @defgroup LoggerGroup Logger Doxygen Group
 *  Logger functions and classes
 *  @{
 */

namespace logger {

	class Config : public singleton::Singleton<logger::Config> {

		public:
			/**
			 * @brief Function: static const logger::info_level_e & getDefaultVerbosity() const
			 *
			 * \return the default verbosity of info messages
			 *
			 * This function returns the default verbosity of info messages
			 */
			const logger::info_level_e & getDefaultVerbosity() const;

			/**
			 * @brief Function: static const logger::msg_type_e & getDefaultType() const
			 *
			 * \return the default type of message
			 *
			 * This function returns the default message type
			 */
			const logger::msg_type_e & getDefaultType() const;

			/**
			 * @brief Function: static const std::string & getDefaultContextName() const
			 *
			 * \return the default context name
			 *
			 * This function returns the default context name
			 */
			const std::string & getDefaultContextName() const;

			/**
			 * @brief Function: static const std::string & getDefaultOutputFile() const
			 *
			 * \return the default output file
			 *
			 * This function returns the default output file
			 */
			const std::string & getDefaultOutputFile() const;

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
			logger::msg_type_e defaultType;

			/**
			 * @brief default verbosity
			 *
			 */
			logger::info_level_e defaultVerbosity;

			/**
			 * @brief default context name
			 *
			 */
			std::string defaultContextName;

			/**
			 * @brief default output file
			 *
			 */
			std::string defaultOutputFile;

	};

}
/** @} */ // End of LoggerGroup group

#endif // LOGGER_CONFIG_H
