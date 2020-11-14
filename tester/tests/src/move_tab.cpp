/**
 * @copyright
 * @file move_tab.cpp
 * @author Andrea Gianarda
 * @date 13th October 2020
 * @brief Move tab functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "utility/qt/include/qt_operator.h"
#include "tests/include/move_tab.h"
#include "base/tester/include/suite.h"

LOGGING_CONTEXT(moveTabOverall, moveTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(moveTabTest, moveTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace move_tab {

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

tester::test::MoveTab::MoveTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Move tab", tester::test::move_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, moveTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::MoveTab::~MoveTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, moveTabOverall,  "Test " << this->getName() << " destructor");
}

void tester::test::MoveTab::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, moveTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	const std::string https(app::shared::https.toStdString());
	const std::string www(app::shared::www.toStdString());

	// Create 2 tabs
	const std::string website0("website0.com");
	LOG_INFO(app::logger::info_level_e::ZERO, moveTabTest, "Open new tab with website " << website0);
	this->openNewTab(website0);
	const std::string url0 = https + www + website0;

	const std::string website1("website1.com");
	LOG_INFO(app::logger::info_level_e::ZERO, moveTabTest, "Open new tab with website " << website1);
	this->openNewTab(website1);
	const std::string url1 = https + www + website1;

	const int initialTabIndex = windowCore->getCurrentTabIndex();
	const int expectedInitialTabIndex = 1;
	const int expectedNumberOfTabs = expectedInitialTabIndex + 1;
	ASSERT((initialTabIndex == expectedInitialTabIndex), tester::shared::error_type_e::TABS, "Current tab index is " + std::to_string(initialTabIndex) + " whereas the expected tab index is " + std::to_string(expectedInitialTabIndex) + " because " + std::to_string(expectedNumberOfTabs) + " tabs have been opened with websites " + url0 + " and " + url1);

	const int initialNumberOfTabs = windowCore->getTabCount();
	ASSERT((initialNumberOfTabs == expectedNumberOfTabs), tester::shared::error_type_e::TABS, "Actual number of tabs " + std::to_string(initialNumberOfTabs) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs));

	// Move current tab index 1 to index 0
	const std::string moveCommandName("move tab");
	const int expectedTargetTab = 0;
	this->executeCommand(moveCommandName, std::to_string(expectedTargetTab));
	const int tabIndexAfterMove = windowCore->getCurrentTabIndex();
	ASSERT((tabIndexAfterMove == expectedTargetTab), tester::shared::error_type_e::TABS, "Current tab index is " + std::to_string(tabIndexAfterMove) + " whereas the expected tab index is " + std::to_string(expectedTargetTab) + " because tab at index number " + std::to_string(expectedInitialTabIndex) + " with website " + website1 + " has been moved to tab index " + std::to_string(expectedTargetTab));
	const int numberOfTabsAfterMove = windowCore->getTabCount();
	ASSERT((numberOfTabsAfterMove == expectedNumberOfTabs), tester::shared::error_type_e::TABS, "Actual number of tabs " + std::to_string(numberOfTabsAfterMove) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs));

	const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
	ASSERT((url1.compare(textInLabel) == 0), tester::shared::error_type_e::STATUSBAR, "Source of the content in tab index " + std::to_string(tabIndexAfterMove) + " " + textInLabel + " doesn't match the expected source " + url1);
}
