/**
 * @copyright
 * @file command_line_parser.cpp
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Command line parser functions
 */

#include "app/shared/enums.h"
#include "app/utility/cpp/stl_helper.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/shared/exception.h"
#include "app/settings/command_line_parser.h"

LOGGING_CONTEXT(commandLineParserOverall, commandLineParser.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::command_line::Parser::Parser(int & argc, char** argv) : app::base::json::Action<app::command_line::Argument>(), argc(argc), argv(argv), decodedArguments(app::command_line::argument_map_t()) {

	EXCEPTION_ACTION_COND(((this->argc == 0) && (this->argv != nullptr)), throw, "The list of arguments (argv) must be null if the number of arguments (argc) is " << this->argc << ". Argv is set to " << this->argv << " instead.");
	EXCEPTION_ACTION_COND(((this->argc != 0) && (this->argv == nullptr)), throw, "The number of arguments (argc) must be 0 if the list of arguments (argv) is null. Number of arguments is set to " << this->argc);
	EXCEPTION_ACTION_COND((this->argc < 0), throw, "Number of arguments (argc) must be greater or equal than 0. Argc is set to " << this->argc);
	LOG_INFO(app::logger::info_level_e::ZERO, commandLineParserOverall, "Creating command line parser\n" << *this);

}

app::command_line::Parser::Parser(int & argc, char** argv, const std::string & jsonFile) : app::command_line::Parser::Parser(argc, argv) {

	this->appendActionData(jsonFile);
}

app::command_line::Parser::Parser(int & argc, char** argv, const std::list<std::string> & jsonFiles) : app::command_line::Parser::Parser(argc, argv) {

	this->appendActionData(jsonFiles);
}

app::command_line::Parser::~Parser() {
	LOG_INFO(app::logger::info_level_e::ZERO, commandLineParserOverall, "Command line parser destructor");
}

void app::command_line::Parser::addArguments(const app::command_line::argument_map_t & arguments, const bool enableOverride) {
	this->decodedArguments.merge(const_cast<app::command_line::argument_map_t &>(arguments));
	const int remainingArguments = static_cast<int>(arguments.size());
	if (enableOverride == true) {
		std::for_each(arguments.cbegin(), arguments.cend(), [&] (const auto & element) {
			this->overrideArgumentValue(element.first, element.second);
		});
	} else {
		EXCEPTION_ACTION_COND((remainingArguments != 0), throw, "Expected override flag is set to " << std::boolalpha << enableOverride << " however there are " << remainingArguments << " elements after merging in the map passed as argument to function " << __func__);
	}
}


void app::command_line::Parser::addArgument(const std::string & key, const std::string & value) {
	const auto & currentValue = this->decodedArguments.find(key);
	EXCEPTION_ACTION_COND((currentValue != this->decodedArguments.cend()), throw, "Unable to add key " << key << " because it was found in the command line argument map with value " << currentValue->second);
	LOG_INFO(app::logger::info_level_e::ZERO, commandLineParserOverall, "Adding key " << key << " set to " << value);
	this->decodedArguments.insert({key, value});
}

void app::command_line::Parser::overrideArgumentValue(const std::string & key, const std::string & value) {
	const auto & currentValue = this->decodedArguments.find(key);
	EXCEPTION_ACTION_COND((currentValue == this->decodedArguments.cend()), throw, "Unable to find key " << key << " in command line argument map");
	LOG_INFO(app::logger::info_level_e::ZERO, commandLineParserOverall, "Changing value of key " << key << " from " << currentValue->second << " to " << value);
	// Use insert_or_assign instead of operator[]
	this->decodedArguments.insert_or_assign(key, value);
}

CONST_GETTER(app::command_line::Parser::getDecodedArguments, app::command_line::argument_map_t &, this->decodedArguments)
CONST_GETTER(app::command_line::Parser::getArgc, int &, this->argc)

char ** app::command_line::Parser::getArgv() const {
	return this->argv;
}

const std::string app::command_line::Parser::print() const {
	std::string commandLineInfo;

	commandLineInfo = commandLineInfo + "Command line:\n";
	commandLineInfo = commandLineInfo + "Number of arguments " + std::to_string(this->argc) + "\n";
	for (int i = 0; i < argc; i++) {
		commandLineInfo = commandLineInfo + "\targument " + std::to_string(i) + ": " + this->argv[i] + "\n";
	}

	return commandLineInfo;
}

void app::command_line::Parser::initialize(int & argc, char** argv) {
	if ((this->argc == 0) && (this->argv == nullptr)) {
		this->argc = argc;
		this->argv = argv;
		this->extractArguments();
	}
}

void app::command_line::Parser::extractArguments() {
	// Start counter at 1 because the first argument is the name of the program
	int counter = 1;

	EXCEPTION_ACTION_COND(((this->argc == 0) || (this->argv == nullptr)), throw, "Cannot call " << __func__ << " when argc is " << this->argc << " and argv is " << this->argv << ". argc must be greater than 0 and argv must be not null");

	while (counter < this->argc) {
		const std::string option(this->argv[counter]);

		const std::string searchString("-");
		const std::string replacingString("");
		const std::string prunedOption(app::utility::findAndReplaceString(option, searchString, replacingString));

		const std::unique_ptr<app::command_line::Argument> & shortCmdMatch = this->findDataWithFieldValue("ShortCmd", &prunedOption);
		const std::unique_ptr<app::command_line::Argument> & longCmdMatch = this->findDataWithFieldValue("LongCmd", &prunedOption);

		// An option cannot match a short and long command at the same time
		EXCEPTION_ACTION_COND(((shortCmdMatch != this->getInvalidData()) && (longCmdMatch != this->getInvalidData())), throw, "Option " << option << " matches a short or long command");

		// An option may be unrecognized because it is dealt in another JSON file
		if ((shortCmdMatch == this->getInvalidData()) && (longCmdMatch == this->getInvalidData())) {
			std::string jsonFilePrint = std::string();
			const std::list<std::string> & actionFiles = this->getActionJsonFiles();
			if (actionFiles.empty() == true) {
				jsonFilePrint.append("because no action JSON file was provided");
			} else {
				jsonFilePrint.append(" in JSON file");
				if (actionFiles.size() > 1) {
					// Append s to make plural as the file list has more than 1 element
					jsonFilePrint.append("s");
				}
				jsonFilePrint.append(": ");

				for (const auto & filename : actionFiles) {
					if (filename.compare(actionFiles.front()) != 0) {
						jsonFilePrint.append(", ");
					}
					jsonFilePrint.append(filename);
				}
			}
			LOG_WARNING(commandLineParserOverall, "Unrecognized option " << option << ". No match found for short or long command listed " << jsonFilePrint);
		} else {

			const std::unique_ptr<app::command_line::Argument> & match = (shortCmdMatch == nullptr) ? longCmdMatch : shortCmdMatch;

			const auto & numberOfArguments = match->getNumberOfArguments();
			const auto & cmdName = match->getName();
			LOG_INFO(app::logger::info_level_e::ZERO, commandLineParserOverall, "Found setting " << cmdName << " matching option " << option << " which expected " << numberOfArguments << " arguments");

			std::string value = std::string();
			if (numberOfArguments == 0) {
				value = std::to_string(1);
			} else {

				EXCEPTION_ACTION_COND(((counter + numberOfArguments) >= this->argc), throw, "Argument " << option << " expects " << numberOfArguments << " argument(s) (range within the command line from " << counter << " to " << (counter + numberOfArguments) << " but the number of provided arguments is " << this->argc);
				for (int argNo = 0; argNo < numberOfArguments; argNo++) {

					counter++;

					std::string arg(this->argv[counter]);

					const auto & validValues = match->getValidValues();
					if (validValues.empty() == false) {
						const auto valueMatch = std::find(validValues.cbegin(), validValues.cend(), arg);
						EXCEPTION_ACTION_COND((valueMatch == validValues.cend()), throw, "Unable to find value " << arg << " for argument " << cmdName << " in list of valid values");
					}

					LOG_INFO(app::logger::info_level_e::ZERO, commandLineParserOverall, "Argument " << argNo << " of settings " << cmdName << " is " << arg);

					value = value + arg;
					if (argNo != (numberOfArguments - 1)) {
						value = value + " ";
					}
				}
			}

			this->decodedArguments[cmdName] = value;

		}

		counter++;
	}
}

void app::command_line::Parser::addItemToActionData(std::unique_ptr<app::command_line::Argument> & data, const std::string & key, const std::string & item) {

	void * valuePtr = nullptr;
	int numberArguments = 0;
	std::list<std::string> validValues;

	if (key.compare("NumberArguments") == 0) {
		double noArgumentsDouble = std::stod(item);
		numberArguments = static_cast<int>(noArgumentsDouble);
		valuePtr = &numberArguments;
	} else if (key.compare("ValidValues") == 0) {
		const std::string delimiter(",");
		validValues = app::utility::splitStringByDelimiter<std::list>(item, delimiter);
		valuePtr = &validValues;
	} else {
		valuePtr = &const_cast<std::string &>(item);
	}

	data->setValueFromMemberName(key, valuePtr);
}

void app::command_line::Parser::populateDefaultDecodedArguments() {
	for (const auto & item : this->actionData) {
		const auto & argument = item.second;
		const std::string & defaultValue = argument->getDefaultValue();
		const std::string & name = argument->getName();
		this->decodedArguments[name] = defaultValue;
	}
}

void app::command_line::Parser::appendActionData(const std::list<std::string> & jsonFiles) {
	app::base::json::Action<app::command_line::Argument>::appendActionData(jsonFiles);
	this->populateDefaultDecodedArguments();
	if ((this->argc != 0) && (this->argv != nullptr)) {
		this->extractArguments();
	}
}

void app::command_line::Parser::appendActionData(const std::string & filename) {
	app::base::json::Action<app::command_line::Argument>::appendActionData(filename);
	// assign default values to the command line arguments
	this->populateDefaultDecodedArguments();
	if ((this->argc != 0) && (this->argv != nullptr)) {
		// Change value of command line argument map based on inputs from the user (argc and argv)
		this->extractArguments();
	}
}

void app::command_line::Parser::clear() {
	app::base::json::Action<app::command_line::Argument>::clear();
	this->decodedArguments.clear();
}
