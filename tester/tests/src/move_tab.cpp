/**
 * @copyright
 * @file move_tab.cpp
 * @author Andrea Gianarda
 * @date 13th October 2020
 * @brief Move tab functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "global_enums.h"
#include "logging_macros.h"
#include "qt_operator.h"
#include "stl_helper.h"
#include "move_tab.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(moveTabOverall, "moveTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(moveTabTest, "moveTab.test", MSG_TYPE_LEVEL)

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

move_tab::MoveTab::MoveTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Move tab", move_tab::jsonFileFullPath, useShortcuts) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, moveTabOverall,  "Creating test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

}

move_tab::MoveTab::~MoveTab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, moveTabOverall,  "Test " << QString::fromStdString(this->getName()) << " destructor");
}

void move_tab::MoveTab::testBody() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, moveTabTest,  "Starting test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();

	const std::string https(global_constants::https.toStdString());
	const std::string www(global_constants::www.toStdString());

	// Create 2 tabs
	const std::string website0("website0.com");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, moveTabTest, "Open new tab with website " << website0);
	this->openNewTab(website0);
	const std::string url0 = https + www + website0;

	const std::string website1("website1.com");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, moveTabTest, "Open new tab with website " << website1);
	this->openNewTab(website1);
	const std::string url1 = https + www + website1;

	const int initialTabIndex = windowCore->getCurrentTabIndex();
	const int expectedInitialTabIndex = 1;
	const int expectedNumberOfTabs = expectedInitialTabIndex + 1;
	ASSERT((initialTabIndex == expectedInitialTabIndex), test_enums::error_type_e::TABS, "Current tab index is " + std::to_string(initialTabIndex) + " whereas the expected tab index is " + std::to_string(expectedInitialTabIndex) + " because " + std::to_string(expectedNumberOfTabs) + " tabs have been opened with websites " + url0 + " and " + url1);

	const int initialNumberOfTabs = windowCore->getTabCount();
	ASSERT((initialNumberOfTabs == expectedNumberOfTabs), test_enums::error_type_e::TABS, "Actual number of tabs " + std::to_string(initialNumberOfTabs) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs));

	// Move current tab index 1 to index 0
	const std::string moveCommandName("move tab");
	const int expectedTargetTab = 0;
	this->executeCommand(moveCommandName, std::to_string(expectedTargetTab));
	const int tabIndexAfterMove = windowCore->getCurrentTabIndex();
	ASSERT((tabIndexAfterMove == expectedTargetTab), test_enums::error_type_e::TABS, "Current tab index is " + std::to_string(tabIndexAfterMove) + " whereas the expected tab index is " + std::to_string(expectedTargetTab) + " because tab at index number " + std::to_string(expectedInitialTabIndex) + " with website " + website1 + " has been moved to tab index " + std::to_string(expectedTargetTab));
	const int numberOfTabsAfterMove = windowCore->getTabCount();
	ASSERT((numberOfTabsAfterMove == expectedNumberOfTabs), test_enums::error_type_e::TABS, "Actual number of tabs " + std::to_string(numberOfTabsAfterMove) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs));

	const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
	ASSERT((url1.compare(textInLabel) == 0), test_enums::error_type_e::STATUSBAR, "Source of the content in tab index " + std::to_string(tabIndexAfterMove) + " " + textInLabel + " doesn't match the expected source " + url1);
}
