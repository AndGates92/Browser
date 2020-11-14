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

#include "utility/logger/include/enums.h"
#include "utility/stl/include/singleton.h"

/** @defgroup LoggerGroup Logger Doxygen Group
 *  Logger functions and classes
 *  @{
 */

namespace app {

	namespace logger {

		class Config : public app::utility::Singleton<app::logger::Config> {

			public:
				/**
				 * @brief Function: static const app::logger::info_level_e & getDefaultVerbosity() const
				 *
				 * \return the default verbosity of info messages
				 *
				 * This function returns the default verbosity of info messages
				 */
				const app::logger::info_level_e & getDefaultVerbosity() const;

				/**
				 * @brief Function: static const app::logger::msg_type_e & getDefaultType() const
				 *
				 * \return the default type of message
				 *
				 * This function returns the default message type
				 */
				const app::logger::msg_type_e & getDefaultType() const;

				/**
				 * @brief Function: static const std::string & getDefaultContextName() const
				 *
				 * \return the default context name
				 *
				 * This function returns the default context name
				 */
				const std::string & getDefaultContextName() const;

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
				app::logger::msg_type_e defaultType;

				/**
				 * @brief default verbosity
				 *
				 */
				app::logger::info_level_e defaultVerbosity;

				/**
				 * @brief default context name
				 *
				 */
				std::string defaultContextName;

		};

	}

}
/** @} */ // End of LoggerGroup group

#endif // LOGGER_CONFIG_H
