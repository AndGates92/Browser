#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H
/**
 * @copyright
 * @file global.h
 * @author Andrea Gianarda
 * @date 28th October 2020
 * @brief Browser settings header file
 */

#include "app/shared/constructor_macros.h"
#include "app/utility/log/printable_object.h"

#include "app/settings/types.h"
#include "app/utility/stl/singleton.h"

/** @defgroup SettingsGroup Browser Settings Group
 *  Browser settings functions and classes
 *  @{
 */
namespace app {

	namespace command_line {
		class Parser;
	}

	namespace settings {

		/**
		 * @brief Global class
		 *
		 */
		class Global : public app::utility::Singleton<app::settings::Global>, public app::printable_object::PrintableObject {

			public:
				/**
				 * @brief Function: void setLogPath(int & argc, char** argv)
				 *
				 * \param argc: number of arguments
				 * \param argv: value of arguments
				 *
				 * This function initializes the value of the log path
				 * It is necessary to treat log file as a special case because the logger needs this value to default the output file
				 */
				static void setLogPath(int & argc, char** argv);

				/**
				 * @brief Function: static const std::string & getLogFilePath()
				 *
				 * \return the path towards the logfile set in the settings
				 *
				 * This functions returns the path towards the default logfile
				 */
				static const std::string & getLogFilePath();

				/**
				 * @brief Function: explicit Global()
				 *
				 * Browser Settings constructor
				 */
				explicit Global();

				/**
				 * @brief Function: virtual ~Global()
				 *
				 * Browser Settings destructor
				 */
				virtual ~Global();

				/**
				 * @brief Function: void initialize(int & argc, char** argv)
				 *
				 * \param argc: number of arguments
				 * \param argv: value of arguments
				 *
				 * This function initializes settings of the browser
				 */
				void initialize(int & argc, char** argv);

				/**
				 * @brief Function: const std::string print() const override
				 *
				 * \return settings informations to std::string
				 *
				 * This functions prints settings informations to std::string
				 */
				const std::string print() const override;

				/**
				 * @brief Function: const app::command_line::argument_map_t & getSettingsMap() const
				 *
				 * \return a map of settings
				 *
				 * This function returns a map of settings
				 */
				const app::command_line::argument_map_t & getSettingsMap() const;

				/**
				 * @brief Function: void addArguments(const app::command_line::argument_map_t & arguments, const bool enableOverride = false)
				 *
				 * \param arguments: arguments to add or override
				 * \param enableOverride: if the decoded argument map already contains some keys, they will be overridden
				 *
				 * This function merges the map of arguments provided as argument with the map locally stored.
				 */
				void addArguments(const app::command_line::argument_map_t & arguments, const bool enableOverride = false);

				/**
				 * @brief Function: void addArgument(const std::string & key, const std::string & value)
				 *
				 * \param key: key to add
				 * \param value: new value of key provided as argument
				 *
				 * This function adds a key and its value to the argument map.
				 * It will throw an exception if the key is already in the map before adding it.
				 */
				void addArgument(const std::string & key, const std::string & value);

				/**
				 * @brief Function: void overrideArgumentValue(const std::string & key, const std::string & value)
				 *
				 * \param key: key whose value has to be changed
				 * \param value: new value of key provided as argument
				 *
				 * This function changes the value of an argument.
				 * It will throw an exception if the key is not found.
				 */
				void overrideArgumentValue(const std::string & key, const std::string & value);

			protected:

			private:

				/**
				 * @brief path toward logfile
				 *
				 */
				static std::string logFilePath;

				/**
				 * @brief Function: explicit Global(int argc, char** argv)
				 *
				 * \param argc: number of arguments
				 * \param argv: value of arguments
				 *
				 * Browser Settings constructor
				 */
				explicit Global(int argc, char** argv);

				/**
				 * @brief command line parser
				 *
				 */
				std::unique_ptr<app::command_line::Parser> parser;

				/**
				 * @brief Function: void initialize()
				 *
				 * This function initializes settings of the browser
				 */
				void initialize();

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class Global
				 *
				 */
				DISABLE_COPY_MOVE(Global)

		};

	}

}
/** @} */ // End of SettingsGroup group

#endif // GLOBAL_SETTINGS_H
