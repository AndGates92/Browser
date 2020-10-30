#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H
/**
 * @copyright
 * @file command_line_parser.h
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Command line parser header file
 */

#include <string>
#include <list>
#include <map>

#include "constructor_macros.h"
#include "printable_object.h"
#include "command_line_argument.h"
#include "json_action.h"

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
			 * @brief action data type
			 *
			 */
			typedef std::map<std::string, std::string> argument_map_t;

			/**
			 * @brief Function: explicit CommandLineParser(int & argc, char** argv)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 *
			 * Command Line Parser constructor
			 */
			explicit CommandLineParser(int & argc, char** argv);

			/**
			 * @brief Function: virtual ~CommandLineParser()
			 *
			 * Command Line Parser destructor
			 */
			virtual ~CommandLineParser();

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
			 * @brief Function: const argument_map_t & getDecodedArguments() const
			 *
			 * \return decoded arguments
			 *
			 * This function returns the decoded arguments
			 */
			const argument_map_t & getDecodedArguments() const;

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
			argument_map_t decodedArguments;

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
