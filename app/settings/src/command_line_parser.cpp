/**
 * @copyright
 * @file command_line_parser.cpp
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Command line parser functions
 */

#include "common/include/global_enums.h"
#include "utility/stl/include/stl_helper.h"
#include "utility/qt/include/qt_operator.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/exception_macros.h"
#include "settings/include/command_line_parser.h"

LOGGING_CONTEXT(commandLineParserOverall, commandLineParser.overall, TYPE_LEVEL, INFO_VERBOSITY)

command_line::CommandLineParser::CommandLineParser(int & argc, char** argv, const std::string & jsonFile) : json::JsonAction<command_line::CommandLineArgument>(QString::fromStdString(jsonFile)), argc(argc), argv(argv), decodedArguments(command_line::argument_map_t()) {
	EXCEPTION_ACTION_COND((jsonFile.empty() == true), throw, "JSON file name cannot be empty");
	EXCEPTION_ACTION_COND(((this->argc == 0) && (this->argv != nullptr)), throw, "The list of arguments (argv) must be null if the number of arguments (argc) is " << this->argc << ". Argv is set to " << this->argv << " instead.");
	EXCEPTION_ACTION_COND(((this->argc != 0) && (this->argv == nullptr)), throw, "The number of arguments (argc) must be 0 if the list of arguments (argv) is null. Number of arguments is set to " << this->argc);
	EXCEPTION_ACTION_COND((this->argc < 0), throw, "Number of arguments (argc) must be greater or equal than 0. Argc is set to " << this->argc);
	LOG_INFO(logger::info_level_e::ZERO, commandLineParserOverall,  "Creating command line parser\n" << *this);

	this->populateDefaultDecodedArguments();
	this->populateActionData();
	if ((this->argc != 0) && (this->argv != nullptr)) {
		this->extractArguments();
	}
}

command_line::CommandLineParser::~CommandLineParser() {
	LOG_INFO(logger::info_level_e::ZERO, commandLineParserOverall,  "Command line parser destructor");
}

void command_line::CommandLineParser::addArguments(const command_line::argument_map_t & arguments, const bool enableOverride) {
	this->decodedArguments.merge(const_cast<command_line::argument_map_t &>(arguments));
	const int remainingArguments = static_cast<int>(arguments.size());
	if (enableOverride == true) {
		std::for_each(arguments.cbegin(), arguments.cend(), [&] (const auto & element) {
			this->overrideArgumentValue(element.first, element.second);
		});
	} else {
		EXCEPTION_ACTION_COND((remainingArguments != 0), throw, "Expected override flag is set to " << std::boolalpha << enableOverride << " however there are " << remainingArguments << " elements after merging in the map passed as argument to function " << __func__);
	}
}


void command_line::CommandLineParser::addArgument(const std::string & key, const std::string & value) {
	const auto & currentValue = this->decodedArguments.find(key);
	EXCEPTION_ACTION_COND((currentValue != this->decodedArguments.cend()), throw, "Unable to add key " << key << " because it was found in the command line argument map with value " << currentValue->second);
	LOG_INFO(logger::info_level_e::ZERO, commandLineParserOverall,  "Adding key " << key << " set to " << value);
	this->decodedArguments.insert({key, value});
}

void command_line::CommandLineParser::overrideArgumentValue(const std::string & key, const std::string & value) {
	const auto & currentValue = this->decodedArguments.find(key);
	EXCEPTION_ACTION_COND((currentValue == this->decodedArguments.cend()), throw, "Unable to find key " << key << " in command line argument map");
	LOG_INFO(logger::info_level_e::ZERO, commandLineParserOverall,  "Changing value of key " << key << " from " << currentValue->second << " to " << value);
	// Use insert_or_assign instead of operator[]
	this->decodedArguments.insert_or_assign(key, value);
}

CONST_GETTER(command_line::CommandLineParser::getDecodedArguments, command_line::argument_map_t &, this->decodedArguments)
CONST_GETTER(command_line::CommandLineParser::getArgc, int &, this->argc)

char ** command_line::CommandLineParser::getArgv() {
	return this->argv;
}

const std::string command_line::CommandLineParser::print() const {
	std::string commandLineInfo;

	commandLineInfo = commandLineInfo + "Command line:\n";
	commandLineInfo = commandLineInfo + "Number of arguments " + std::to_string(this->argc) + "\n";
	for (int i = 0; i < argc; i++) {
		commandLineInfo = commandLineInfo + "\targument " + std::to_string(i) + ": " + this->argv[i] + "\n";
	}

	return commandLineInfo;
}

void command_line::CommandLineParser::initialize(int & argc, char** argv) {
	if ((this->argc == 0) && (this->argv == nullptr)) {
		this->argc = argc;
		this->argv = argv;
		this->extractArguments();
	}
}

void command_line::CommandLineParser::extractArguments() {
	// Start counter at 1 because the first argument is the name of the program
	int counter = 1;

	EXCEPTION_ACTION_COND(((this->argc == 0) || (this->argv == nullptr)), throw, "Cannot call " << __func__ << " when argc is " << this->argc << " and argv is " << this->argv << ". argc must be greater than 0 and argv must be not null");

	while (counter < this->argc) {
		const std::string option(this->argv[counter]);

		const std::string searchString("-");
		const std::string replacingString("");
		const std::string prunedOption(stl_helper::findAndReplaceString(option, searchString, replacingString));

		const std::unique_ptr<command_line::CommandLineArgument> & shortCmdMatch = this->findDataWithFieldValue("ShortCmd", &prunedOption);
		const std::unique_ptr<command_line::CommandLineArgument> & longCmdMatch = this->findDataWithFieldValue("LongCmd", &prunedOption);

		EXCEPTION_ACTION_COND(((shortCmdMatch == this->getInvalidData()) && (longCmdMatch == this->getInvalidData())), throw, "Unrecognized option " << option << ". No match found for short or long command");
		EXCEPTION_ACTION_COND(((shortCmdMatch != this->getInvalidData()) && (longCmdMatch != this->getInvalidData())), throw, "Option " << option << " matches a short or long command");

		const std::unique_ptr<command_line::CommandLineArgument> & match = (shortCmdMatch == nullptr) ? longCmdMatch : shortCmdMatch;

		const int & numberOfArguments = match->getNumberOfArguments();
		const std::string & longCmd = match->getLongCmd();

		std::string value = std::string();
		if (numberOfArguments == 0) {
			value = std::to_string(1);
		} else {

			EXCEPTION_ACTION_COND(((counter + numberOfArguments) >= this->argc), throw, "Argument " << option << " expects " << numberOfArguments << " argument(s) (range within the command line from " << counter << " to " << (counter + numberOfArguments) << " but the number of provided arguments is " << this->argc);
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

void command_line::CommandLineParser::addItemToActionData(std::unique_ptr<command_line::CommandLineArgument> & data, const std::string & key, const std::string & item) {

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

void command_line::CommandLineParser::populateDefaultDecodedArguments() {

	const std::map<std::string, std::string> defaultArgumentValueMap = qt_types_to_stl::qMapOfqStringToStdMapofStdStrings(this->commands.findKeyAllValues("DefaultValue"));

	for (const auto & item : defaultArgumentValueMap) {
		this->decodedArguments[item.first] = item.second;
		
	}
}
