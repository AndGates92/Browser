/**
 * @copyright
 * @file open_tab.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Open tab functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "utility/qt/include/qt_operator.h"
#include "tests/include/open_tab.h"
#include "base/tester/include/suite.h"

LOGGING_CONTEXT(openTabOverall, openTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openTabTest, openTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace open_tab {

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
				static const std::string jsonFileName("tab_commands.json");

				/**
				 * @brief Full path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonFileFullPath(jsonFilePath + jsonFileName);

			}

		}

	}

}

tester::test::OpenTab::OpenTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Open tab", tester::test::open_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, openTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::OpenTab::~OpenTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, openTabOverall,  "Test " << this->getName() << " destructor");
}

void tester::test::OpenTab::testBody() {
	LOG_INFO(app::logger::info_level_e::ZERO, openTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string website("website.com");
	LOG_INFO(app::logger::info_level_e::ZERO, openTabTest, "Open new tab with website " << website);
	this->openNewTab(website);

	const std::string closeCommandName("close tab");
	this->executeCommand(closeCommandName, std::string());

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	WAIT_FOR_CONDITION((windowCore->getTabCount() == 0), tester::shared::error_type_e::TABS, "Closed tab with URL " + website + " - actual number of tabs " + std::to_string(windowCore->getTabCount()), 5000);
}
