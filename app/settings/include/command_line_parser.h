#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H
/**
 * @copyright
 * @file command_line_parser.h
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Command line parser header file
 */

#include <list>

#include "common/include/constructor_macros.h"
#include "utility/log/include/printable_object.h"
#include "settings/include/command_line_argument.h"
#include "settings/include/types.h"
#include "base/json/include/json_action.h"

/** @defgroup CommandLineParserGroup Command Line Parser Group
 *  Command line parser functions and classes
 *  @{
 */

namespace command_line_parser {

	/**
	 * @brief CommandLineParser class
	 *
	 */
	class CommandLineParser : public json_action::JsonAction<command_line_argument::CommandLineArgument>, public printable_object::PrintableObject {

		public:
			/**
			 * @brief Function: explicit CommandLineParser(int & argc, char** argv, const std::string & jsonFile)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 * \param jsonFile: JSON filename
			 *
			 * Command Line Parser constructor
			 */
			explicit CommandLineParser(int & argc, char** argv, const std::string & jsonFile);

			/**
			 * @brief Function: virtual ~CommandLineParser()
			 *
			 * Command Line Parser destructor
			 */
			virtual ~CommandLineParser();

			/**
			 * @brief Function: void initialize(int & argc, char** argv)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 *
			 * This function initializes the command line parser if no already done in the constructor
			 */
			void initialize(int & argc, char** argv);

			/**
			 * @brief Function: const int & getArgc() const
			 *
			 * \return the number of arguments provided in the command line
			 *
			 * This function returns the number of argument provided in the command line that launched the application
			 */
			const int & getArgc() const;

			/**
			 * @brief Function: char ** getArgv()
			 *
			 * \return the command line
			 *
			 * This function returns the command line that launched the application
			 */
			char ** getArgv();

			/**
			 * @brief Function: void addArguments(const command_line::argument_map_t & arguments, const bool enableOverride = false)
			 *
			 * \param arguments: arguments to add or override
			 * \param enableOverride: if the decoded argument map already contains some keys, they will be overridden
			 *
			 * This function merges the map of arguments provided as argument with the map locally stored.
			 */
			void addArguments(const command_line::argument_map_t & arguments, const bool enableOverride = false);

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

			/**
			 * @brief Function: const command_line::argument_map_t & getDecodedArguments() const
			 *
			 * \return decoded arguments
			 *
			 * This function returns the decoded arguments
			 */
			const command_line::argument_map_t & getDecodedArguments() const;

			/**
			 * @brief Function: const std::string print() const override
			 *
			 * \return command line to std::string
			 *
			 * This functions prints command line parsed informations to std::string
			 */
			const std::string print() const override;

			/**
			 * @brief Function: virtual void addItemToActionData(std::unique_ptr<command_line_argument::CommandLineArgument> & data, const std::string & key, const std::string & item) override
			 *
			 * \param data: data to be updated
			 * \param key: key the tiem belongs to
			 * \param item: item to add
			 *
			 * This functions adds an item linked to the key to the data provided as input
			 */
			virtual void addItemToActionData(std::unique_ptr<command_line_argument::CommandLineArgument> & data, const std::string & key, const std::string & item) override;

		protected:

		private:
			/**
			 * @brief number of arguments provided in the command line to launch the application
			 *
			 */
			int argc;

			/**
			 * @brief command line used to launch the application
			 *
			 */
			char** argv;

			/**
			 * @brief decoded command line arguments
			 *
			 */
			command_line::argument_map_t decodedArguments;

			/**
			 * @brief Function: void extractArguments()
			 *
			 * This functions parses the array of char pointer argv and extract informations to store in the map decodedArguments
			 */
			void extractArguments();

			/**
			 * @brief Function: void populateDefaultDecodedArguments()
			 *
			 * This functions fills the decoded argument map with default values
			 */
			void populateDefaultDecodedArguments();

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class CommandLineParser
			 *
			 */
			DISABLE_COPY_MOVE(CommandLineParser)

	};

}
/** @} */ // End of CommandLineParserGroup group

#endif // COMMAND_LINE_PARSER_H
