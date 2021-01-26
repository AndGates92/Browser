/**
 * @copyright
 * @file launch_app.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Launch app functions
 */

#include <QtTest/QTest>

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/windows/main_window/window/main_window.h"
#include "app/windows/main_window/json/data.h"
#include "tester/tests/launch_app.h"
#include "tester/base/suite.h"

LOGGING_CONTEXT(launchAppOverall, launchApp.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(launchAppTest, launchApp.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

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

	}

}

tester::test::LaunchApp::LaunchApp(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Launch app and exit", tester::test::launch_app::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, launchAppOverall, "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::LaunchApp::~LaunchApp() {
	LOG_INFO(app::logger::info_level_e::ZERO, launchAppOverall, "Test " << this->getName() << " destructor");
}

void tester::test::LaunchApp::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, launchAppTest, "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string quitCommandName("quit browser");
	this->executeCommand(quitCommandName, std::string());

	const std::unique_ptr<app::main_window::json::Data> & quitCommandData = this->findDataWithFieldValue("Name", &quitCommandName);
	ASSERT((quitCommandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + quitCommandName + " in " + this->getActionJsonFilesAsString());

	const std::string * const quitCommandLongCmdPtr(static_cast<const std::string *>(quitCommandData->getValueFromMemberName("LongCmd")));
	const std::string quitCommandLongCmd(*quitCommandLongCmdPtr);

	WAIT_FOR_CONDITION((this->getWindow()->isHidden() == true), tester::shared::error_type_e::WINDOW, "Window is still active even though command " + quitCommandLongCmd + " was executed.", 5000);
}
