/**
 * @copyright
 * @file reload_tab.cpp
 * @author Andrea Gianarda
 * @date 27th October 2020
 * @brief Reload tab test functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "utility/qt/include/qt_operator.h"
#include "utility/stl/include/stl_helper.h"
#include "windows/main_window/common/include/main_window_constants.h"
#include "tests/include/reload_tab.h"
#include "base/tester/include/base_suite.h"

LOGGING_CONTEXT(reloadTabOverall, reloadTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(reloadTabTest, reloadTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace reload_tab {

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

reload_tab::ReloadTab::ReloadTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Reload tab", reload_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(logger::info_level_e::ZERO, reloadTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

reload_tab::ReloadTab::~ReloadTab() {
	LOG_INFO(logger::info_level_e::ZERO, reloadTabOverall,  "Test " << this->getName() << " destructor");
}

void reload_tab::ReloadTab::testBody() {

	LOG_INFO(logger::info_level_e::ZERO, reloadTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string https(global_constants::https.toStdString());
	const std::string www(global_constants::www.toStdString());

	// Create 1 tabs
	const std::string search("test");
	LOG_INFO(logger::info_level_e::ZERO, reloadTabTest, "Open new tab searching " << search);
	this->openNewTab(search);
	const std::string authorityUrl0 = www + main_window_constants::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();
	const std::string url0 = https + authorityUrl0;

	const std::shared_ptr<main_window_tab::MainWindowTab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), test_enums::error_type_e::TABS, "Current tab pointer is null event though it should have loaded website " + url0);
	if (currentTab != nullptr) {

		const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();
		const std::string initialUrl = windowCore->bottomStatusBar->getUserInputText().toStdString();

		const std::string refreshCommandName("refresh tab");
		this->executeCommand(refreshCommandName, std::string());

		// Wait for page being refreshed
		WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getLoadBarVisibility() == true), test_enums::error_type_e::STATUSBAR, "Load bar never became visible following command " + refreshCommandName, 1000);
		const int maximumProgressValue = progress_bar::ProgressBar::getMaximumValue();
		WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getProgressValue() == maximumProgressValue), test_enums::error_type_e::STATUSBAR, "Load bar is expected to reach " + std::to_string(maximumProgressValue) + " instead it reached " + std::to_string(windowCore->bottomStatusBar->getProgressValue()) + " after executing command " + refreshCommandName, 1000);
		WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getLoadBarVisibility() == false), test_enums::error_type_e::STATUSBAR, "Load bar is expected to be hiddeni after command " + refreshCommandName + " is executed", 1000);

		const int currentTabIndex = windowCore->getCurrentTabIndex();
		const int expectedInitialTabIndex = 0;
		const int expectedNumberOfTabs = expectedInitialTabIndex + 1;
		ASSERT((currentTabIndex == expectedInitialTabIndex), test_enums::error_type_e::TABS, "Current tab index is " + std::to_string(currentTabIndex) + " whereas the expected tab index is " + std::to_string(expectedInitialTabIndex) + " because " + std::to_string(expectedNumberOfTabs) + " tabs have been opened with website " + url0);

		const int currentNumberOfTabs = windowCore->getTabCount();
		ASSERT((currentNumberOfTabs == expectedNumberOfTabs), test_enums::error_type_e::TABS, "Actual number of tabs " + std::to_string(currentNumberOfTabs) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs));

		const std::string urlAfterRefresh = windowCore->bottomStatusBar->getUserInputText().toStdString();
		ASSERT((initialUrl.compare(urlAfterRefresh) == 0), test_enums::error_type_e::STATUSBAR, "Source of the content in tab index " + std::to_string(currentTabIndex) + " " + urlAfterRefresh + " doesn't match the expected source " + initialUrl);

	}
}
