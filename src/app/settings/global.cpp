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
#include "app/settings/command_line_parser.h"

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
				EXCEPTION_ACTION_COND(((counter + numberOfArguments) >= argc), throw, "Argument " << option << " expects 1 argument (range within the command line from " << counter << " to " << (counter + numberOfArguments) << " but the number of provided arguments is " << argc);
				counter++;
				logFilePathFromArgument = argv[counter];
				break;
			}
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

app::settings::Global::Global(int argc, char** argv) : parser(new app::command_line::Parser(argc, argv, app::settings::global::jsonFullPath)) {
	LOG_INFO(app::logger::info_level_e::ZERO, browserSettingsOverall,  "Creating browser settings with argc set to " << argc << " and argv set to " << argv);
	if (app::settings::Global::getLogFilePath().empty() == true) {
		app::settings::Global::setLogPath(argc, argv);
	}
	this->initialize();
}

app::settings::Global::~Global() {
	LOG_INFO(app::logger::info_level_e::ZERO, browserSettingsOverall,  "Browser settings destructor");
}

void app::settings::Global::initialize(int & argc, char** argv) {
	if ((this->parser->getArgc() == 0) && (this->parser->getArgv() == nullptr)) {
		this->parser->initialize(argc, argv);
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

void app::settings::Global::addArguments(const app::command_line::argument_map_t & arguments, const bool enableOverride) {
	this->parser->addArguments(arguments, enableOverride);
}

void app::settings::Global::addArgument(const std::string & key, const std::string & value) {
	this->parser->addArgument(key, value);
}

void app::settings::Global::overrideArgumentValue(const std::string & key, const std::string & value) {
	this->parser->overrideArgumentValue(key, value);
}

const std::string app::settings::Global::print() const {
	const app::command_line::argument_map_t & settingsMap = this->getSettingsMap();

	std::string settingsInfo = "Browser settings:\n";
	for (const auto & setting : settingsMap) {
		settingsInfo = settingsInfo + "- " + setting.first + ": " + setting.second;
	}

	return settingsInfo;
}

CONST_GETTER(app::settings::Global::getSettingsMap, app::command_line::argument_map_t &, this->parser->getDecodedArguments())
