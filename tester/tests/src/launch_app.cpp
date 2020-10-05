/**
 * @copyright
 * @file launch_app.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Launch app functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include <QtTest/QTest>

#include "global_enums.h"
#include "logging_macros.h"
#include "qt_operator.h"
#include "stl_helper.h"
#include "launch_app.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(launchAppOverall, "launchApp.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(launchAppTest, "launchApp.test", MSG_TYPE_LEVEL)

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

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppOverall,  "Creating test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

}

launch_app::LaunchApp::~LaunchApp() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppOverall,  "Test " << QString::fromStdString(this->getName()) << " destructor");
}

void launch_app::LaunchApp::testBody() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppTest,  "Starting test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	const std::string quitCommandName("quit browser");
	this->executeCommand(quitCommandName, std::string());

	const std::unique_ptr<main_window_json_data::MainWindowJsonData> & quitCommandData = this->findDataWithFieldValue("Name", &quitCommandName);
	ASSERT((quitCommandData != nullptr), test_enums::error_type_e::COMMAND, "Unable to find data with Name " + quitCommandName + " in " + this->getSourceFileName().toStdString());

	const std::string * const quitCommandLongCmdPtr(static_cast<const std::string *>(quitCommandData->getValueFromMemberName("LongCmd")));
	const std::string quitCommandLongCmd(*quitCommandLongCmdPtr);

	WAIT_FOR_CONDITION((this->getWindow()->isHidden() == true), test_enums::error_type_e::WINDOW, "Window is still active even though command " + quitCommandLongCmd + " was executed.", 5000);
}
