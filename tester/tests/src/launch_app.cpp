/**
 * @copyright
 * @file launch_app.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Launch app functions
 */

#include <QtTest/QTest>

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "utility/qt/include/qt_operator.h"
#include "utility/stl/include/stl_helper.h"
#include "tests/include/launch_app.h"
#include "base/tester/include/base_suite.h"

LOGGING_CONTEXT(launchAppOverall, launchApp.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(launchAppTest, launchApp.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace launch_app {

	namespace {

		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string jsonFilePath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		static const std::string jsonFileName("global_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string jsonFileFullPath(jsonFilePath + jsonFileName);

	}

}

launch_app::LaunchApp::LaunchApp(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Launch app and exit", launch_app::jsonFileFullPath, useShortcuts) {
	LOG_INFO(logger::info_level_e::ZERO, launchAppOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

launch_app::LaunchApp::~LaunchApp() {
	LOG_INFO(logger::info_level_e::ZERO, launchAppOverall,  "Test " << this->getName() << " destructor");
}

void launch_app::LaunchApp::testBody() {

	LOG_INFO(logger::info_level_e::ZERO, launchAppTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string quitCommandName("quit browser");
	this->executeCommand(quitCommandName, std::string());

	const std::unique_ptr<main_window_json_data::MainWindowJsonData> & quitCommandData = this->findDataWithFieldValue("Name", &quitCommandName);
	ASSERT((quitCommandData != nullptr), test_enums::error_type_e::COMMAND, "Unable to find data with Name " + quitCommandName + " in " + this->getSourceFileName().toStdString());

	const std::string * const quitCommandLongCmdPtr(static_cast<const std::string *>(quitCommandData->getValueFromMemberName("LongCmd")));
	const std::string quitCommandLongCmd(*quitCommandLongCmdPtr);

	WAIT_FOR_CONDITION((this->getWindow()->isHidden() == true), test_enums::error_type_e::WINDOW, "Window is still active even though command " + quitCommandLongCmd + " was executed.", 5000);
}
