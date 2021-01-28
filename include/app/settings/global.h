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
#include "app/settings/command_line_parser.h"

#include "app/settings/types.h"
#include "app/utility/cpp/singleton.h"

/** @defgroup SettingsGroup Browser Settings Group
 *  Browser settings functions and classes
 *  @{
 */
namespace app {

	namespace settings {

		/**
		 * @brief Global class
		 *
		 */
		class Global : public app::utility::Singleton<app::settings::Global>, public app::command_line::Parser {

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
				 * @brief Function: void printHelp() const
				 *
				 * This function prints the help of the browser
				 */
				void printHelp() const;

				/**
				 * @brief Function: void appendActionData(const std::list<std::string> & jsonFiles)
				 *
				 * \param jsonFiles: list of JSON file names
				 *
				 * This function append to the action data map with the content from the json files
				 */
				void appendActionData(const std::list<std::string> & jsonFiles);

				/**
				 * @brief Function: void appendActionData(const std::string & filename)
				 *
				 * \param filename: JSON file name to append
				 *
				 * This function append to the action data map with the content of a JSON file
				 */
				void appendActionData(const std::string & filename);

				/**
				 * @brief Function: void clear()
				 *
				 * This function clears content of the settings 
				 */
				void clear();

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
