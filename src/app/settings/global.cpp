/**
 * @copyright
 * @file global.cpp
 * @author Andrea Gianarda
 * @date 28th October 2020
 * @brief Browser settings functions
 */

#include "app/shared/enums.h"
#include "app/shared/exception.h"
#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/settings/global.h"

LOGGING_CONTEXT(browserSettingsOverall, browserSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

/**
 * @brief log filename
 *
 */
#if !defined(LOGFILE)
	#define LOGFILE browser.log
#endif

/**
 * @brief global browser settings
 *
 */
std::string app::settings::Global::logFilePath = std::string();

namespace app {

	namespace settings {

		namespace global {

			namespace {
				/**
				 * @brief Path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonPath("json/");

				/**
				 * @brief Filename storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonName("browser_arguments.json");

				/**
				 * @brief Full path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonFullPath(jsonPath + jsonName);
			}

		}

	}

}

void app::settings::Global::setLogPath(int & argc, char** argv) {
	if (argv != nullptr) {
		const std::string logFilePathLongCmd("--log");
		const std::string logFilePathShortCmd("-l");
		std::string logFilePathFromArgument = std::string();
		const std::string logFilePathFromMakefile(STRINGIFY(LOGFILE));
		const std::string defaultLogFilePath("stdout");

		// Start counter at 1 because the first argument is the name of the program
		int counter = 1;

		while (counter < argc) {
			const int & numberOfArguments = 1;
			const std::string option(argv[counter]);

			if ((option.compare(logFilePathLongCmd) == 0) || (option.compare(logFilePathShortCmd) == 0)) {
				EXCEPTION_ACTION_COND(((counter + numberOfArguments) >= argc), throw, "Argument " << option << " expects " << numberOfArguments << " argument(s) (range within the command line from " << counter << " to " << (counter + numberOfArguments) << " but the number of provided arguments is " << argc);
				counter++;
				logFilePathFromArgument = argv[counter];
				break;
			}
			counter++;
		}

		if (logFilePathFromArgument.empty() == false) {
			logFilePath = logFilePathFromArgument;
		} else if (logFilePathFromMakefile.empty() == false) {
			logFilePath = logFilePathFromMakefile;
		} else {
			logFilePath = defaultLogFilePath;
		}
	}
}

const std::string & app::settings::Global::getLogFilePath() {
	return logFilePath;
}

app::settings::Global::Global() : app::settings::Global(0, nullptr) {

}

app::settings::Global::Global(int argc, char** argv) : app::command_line::Parser(argc, argv, app::settings::global::jsonFullPath) {
	LOG_INFO(app::logger::info_level_e::ZERO, browserSettingsOverall, "Creating browser settings with argc set to " << argc << " and argv set to " << argv);
	if (app::settings::Global::getLogFilePath().empty() == true) {
		app::settings::Global::setLogPath(argc, argv);
	}
	this->initialize();
}

app::settings::Global::~Global() {
	LOG_INFO(app::logger::info_level_e::ZERO, browserSettingsOverall, "Browser settings destructor");
}

void app::settings::Global::initialize(int & argc, char** argv) {
	if ((this->getArgc() == 0) && (this->getArgv() == nullptr)) {
		app::command_line::Parser::initialize(argc, argv);
		if (app::settings::Global::getLogFilePath().empty() == true) {
			app::settings::Global::setLogPath(argc, argv);
		}
		this->initialize();
	}
}

void app::settings::Global::initialize() {
	if (app::settings::Global::getLogFilePath().empty() == false) {
		this->overrideArgumentValue("Log", app::settings::Global::getLogFilePath());
	}

}

const std::string app::settings::Global::print() const {
	const app::command_line::argument_map_t & settingsMap = this->getSettingsMap();

	std::string settingsInfo = "Browser settings:\n";
	for (const auto & setting : settingsMap) {
		settingsInfo = settingsInfo + "- " + setting.first + ": " + setting.second;
	}

	return settingsInfo;
}

void app::settings::Global::printHelp() const {
	const std::string helpLogfile("stdout");
	LOG_INFO_TO_FILE(app::logger::info_level_e::ZERO, browserSettingsOverall, helpLogfile, "Help for program " << this->getArgv()[0] << ":");
	for (const auto & item : this->actionData) {
		const auto & argument = item.second;
		const std::string & shortCmd = argument->getShortCmd();
		const std::string & longCmd = argument->getLongCmd();
		const std::string & defaultValue = argument->getDefaultValue();
		const std::string & help = argument->getHelp();
		std::string argumentHelp;
		// Append short command
		if (shortCmd.empty() == false) {
			argumentHelp.append("-" + shortCmd);
			// If long command is also defined, then print pipe
			if (longCmd.empty() == false) {
				argumentHelp.append("|");
			}
		}

		// Print long command
		if (longCmd.empty() == false) {
			argumentHelp.append("--" + longCmd);
		}

		argumentHelp.append(":\n  ");
		argumentHelp.append(help);
		if (defaultValue.empty() == false) {
			argumentHelp.append("\n  Default value: ");
			argumentHelp.append(defaultValue);
		}

		LOG_INFO_TO_FILE(app::logger::info_level_e::ZERO, browserSettingsOverall, helpLogfile, "- " + argumentHelp);
	}
}

CONST_GETTER(app::settings::Global::getSettingsMap, app::command_line::argument_map_t &, this->getDecodedArguments())

void app::settings::Global::appendActionData(const std::list<std::string> & jsonFiles) {
	app::command_line::Parser::appendActionData(jsonFiles);
}

void app::settings::Global::appendActionData(const std::string & filename) {
	app::command_line::Parser::appendActionData(filename);
}

void app::settings::Global::clear() {
	app::command_line::Parser::clear();
}
