/**
 * @copyright
 * @file command_line_parser.cpp
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Command line parser functions
 */

#include "global_enums.h"
#include "stl_helper.h"
#include "qt_operator.h"
#include "macros.h"
#include "function_macros.h"
#include "exception_macros.h"
#include "command_line_parser.h"

LOGGING_CONTEXT(commandLineParserOverall, commandLineParser.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace command_line_parser {

	namespace {
		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string testerJsonPath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		static const std::string testerJsonName("tester_arguments.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string testerJsonFullPath(testerJsonPath + testerJsonName);
	}

}

command_line_parser::CommandLineParser::CommandLineParser(int & argc, char** argv) : json_action::JsonAction<command_line_argument::CommandLineArgument>(QString::fromStdString(command_line_parser::testerJsonFullPath)), argc(argc), argv(argv), decodedArguments(command_line_parser::CommandLineParser::argument_map_t()) {
	LOG_INFO(logger::info_level_e::ZERO, commandLineParserOverall,  "Creating command line parser\n" << *this);

	this->populateDefaultDecodedArguments();
	this->populateActionData();

	this->extractArguments();

}

command_line_parser::CommandLineParser::~CommandLineParser() {
	LOG_INFO(logger::info_level_e::ZERO, commandLineParserOverall,  "Command line parser destructor");
}

CONST_GETTER(command_line_parser::CommandLineParser::getDecodedArguments, command_line_parser::CommandLineParser::argument_map_t &, this->decodedArguments)
CONST_GETTER(command_line_parser::CommandLineParser::getArgc, int &, this->argc)

char ** command_line_parser::CommandLineParser::getArgv() {
	return this->argv;
}

const std::string command_line_parser::CommandLineParser::print() const {
	std::string commandLineInfo;

	commandLineInfo = commandLineInfo + "Command line:\n";
	commandLineInfo = commandLineInfo + "Number of arguments " + std::to_string(this->argc) + "\n";
	for (int i = 0; i < argc; i++) {
		commandLineInfo = commandLineInfo + "\targument " + std::to_string(i) + ": " + this->argv[i] + "\n";
	}

	return commandLineInfo;
}

void command_line_parser::CommandLineParser::extractArguments() {
	// Start counter at 1 because the first argument is the name of the program
	int counter = 1;
	while (counter < this->argc) {
		const std::string option(this->argv[counter]);

		const std::string searchString("-");
		const std::string replacingString("");
		const std::string prunedOption(stl_helper::findAndReplaceString(option, searchString, replacingString));

		const std::unique_ptr<command_line_argument::CommandLineArgument> & shortCmdMatch = this->findDataWithFieldValue("ShortCmd", &prunedOption);
		const std::unique_ptr<command_line_argument::CommandLineArgument> & longCmdMatch = this->findDataWithFieldValue("LongCmd", &prunedOption);

		EXCEPTION_ACTION_COND(((shortCmdMatch == this->getInvalidData()) && (longCmdMatch == this->getInvalidData())), throw, "Unrecognized option " << option << ". No match found for short or long command");
		EXCEPTION_ACTION_COND(((shortCmdMatch != this->getInvalidData()) && (longCmdMatch != this->getInvalidData())), throw, "Option " << option << " matches a short or long command");

		const std::unique_ptr<command_line_argument::CommandLineArgument> & match = (shortCmdMatch == nullptr) ? longCmdMatch : shortCmdMatch;

		const int & numberOfArguments = match->getNumberOfArguments();
		const std::string & longCmd = match->getLongCmd();

		std::string value = std::string();
		if (numberOfArguments == 0) {
			value = std::to_string(1);
		} else {

			EXCEPTION_ACTION_COND(((counter + numberOfArguments) >= this->argc), throw, "Argument " << option << " expects " << numberOfArguments << " arguments (range within the command line from " << counter << " to " << (counter + numberOfArguments) << " but the number of provided arguments is " << this->argc);
			for (int arg = 0; arg < numberOfArguments; arg++) {
				counter++;
				std::string value(this->argv[counter]);
				if (arg != (numberOfArguments - 1)) {
					value = value + " ";
				}
			}
		}

		this->decodedArguments[longCmd] = value;
		counter++;
	}
}

void command_line_parser::CommandLineParser::addItemToActionData(std::unique_ptr<command_line_argument::CommandLineArgument> & data, const std::string & key, const std::string & item) {

	void * valuePtr = nullptr;
	int numberArguments = 0;

	if (key.compare("NumberArguments") == 0) {
		double noArgumentsDouble = std::stod(item);
		numberArguments = static_cast<int>(noArgumentsDouble);
		valuePtr = &numberArguments;
	} else {
		valuePtr = &const_cast<std::string &>(item);
	}

	data->setValueFromMemberName(key, valuePtr);
}

void command_line_parser::CommandLineParser::populateDefaultDecodedArguments() {

	const std::map<std::string, std::string> defaultArgumentValueMap = qt_types_to_stl::qMapOfqStringToStdMapofStdStrings(this->commands.findKeyAllValues("DefaultValue"));

	for (const auto & item : defaultArgumentValueMap) {
		this->decodedArguments[item.first] = item.second;
		
	}
}
