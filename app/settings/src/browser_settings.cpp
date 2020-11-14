/**
 * @copyright
 * @file browser_settings.cpp
 * @author Andrea Gianarda
 * @date 28th October 2020
 * @brief Browser settings functions
 */

#include "common/include/global_enums.h"
#include "common/include/exception_macros.h"
#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"
#include "settings/include/browser_settings.h"
#include "settings/include/command_line_parser.h"

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
std::string browser_settings::BrowserSettings::logFilePath = std::string();


namespace browser_settings {

	namespace {
		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string settingsJsonPath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		static const std::string settingsJsonName("browser_arguments.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string settingsJsonFullPath(settingsJsonPath + settingsJsonName);
	}

}

void browser_settings::BrowserSettings::setLogPath(int & argc, char** argv) {
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

const std::string & browser_settings::BrowserSettings::getLogFilePath() {
	return logFilePath;
}

browser_settings::BrowserSettings::BrowserSettings() : browser_settings::BrowserSettings(0, nullptr) {

}

browser_settings::BrowserSettings::BrowserSettings(int argc, char** argv) : parser(new command_line_parser::CommandLineParser(argc, argv, browser_settings::settingsJsonFullPath)) {
	LOG_INFO(logger::info_level_e::ZERO, browserSettingsOverall,  "Creating browser settings with argc set to " << argc << " and argv set to " << argv);
	if (browser_settings::BrowserSettings::getLogFilePath().empty() == true) {
		browser_settings::BrowserSettings::setLogPath(argc, argv);
	}
	this->initialize();
}

browser_settings::BrowserSettings::~BrowserSettings() {
	LOG_INFO(logger::info_level_e::ZERO, browserSettingsOverall,  "Browser settings destructor");
}

void browser_settings::BrowserSettings::initialize(int & argc, char** argv) {
	if ((this->parser->getArgc() == 0) && (this->parser->getArgv() == nullptr)) {
		this->parser->initialize(argc, argv);
		if (browser_settings::BrowserSettings::getLogFilePath().empty() == true) {
			browser_settings::BrowserSettings::setLogPath(argc, argv);
		}
		this->initialize();
	}
}

void browser_settings::BrowserSettings::initialize() {
	if (browser_settings::BrowserSettings::getLogFilePath().empty() == false) {
		this->overrideArgumentValue("Log", browser_settings::BrowserSettings::getLogFilePath());
	}
}

void browser_settings::BrowserSettings::addArguments(const command_line::argument_map_t & arguments, const bool enableOverride) {
	this->parser->addArguments(arguments, enableOverride);
}

void browser_settings::BrowserSettings::addArgument(const std::string & key, const std::string & value) {
	this->parser->addArgument(key, value);
}

void browser_settings::BrowserSettings::overrideArgumentValue(const std::string & key, const std::string & value) {
	this->parser->overrideArgumentValue(key, value);
}

const std::string browser_settings::BrowserSettings::print() const {
	const command_line::argument_map_t & settingsMap = this->getSettingsMap();

	std::string settingsInfo = "Browser settings:\n";
	for (const auto & setting : settingsMap) {
		settingsInfo = settingsInfo + "- " + setting.first + ": " + setting.second;
	}

	return settingsInfo;
}

CONST_GETTER(browser_settings::BrowserSettings::getSettingsMap, command_line::argument_map_t &, this->parser->getDecodedArguments())
