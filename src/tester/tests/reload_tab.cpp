/**
 * @copyright
 * @file reload_tab.cpp
 * @author Andrea Gianarda
 * @date 27th October 2020
 * @brief Reload tab test functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/windows/main_window/shared/constants.h"
#include "tester/tests/reload_tab.h"
#include "tester/base/suite.h"

LOGGING_CONTEXT(reloadTabOverall, reloadTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(reloadTabTest, reloadTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

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

	}

}

tester::test::ReloadTab::ReloadTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Reload tab", tester::test::reload_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, reloadTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::ReloadTab::~ReloadTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, reloadTabOverall,  "Test " << this->getName() << " destructor");
}

void tester::test::ReloadTab::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, reloadTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string https(app::shared::https.toStdString());
	const std::string www(app::shared::www.toStdString());

	// Create 1 tabs
	const std::string search("test");
	LOG_INFO(app::logger::info_level_e::ZERO, reloadTabTest, "Open new tab searching " << search);
	this->openNewTab(search);
	const std::string authorityUrl0 = www + app::main_window::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();
	const std::string url0 = https + authorityUrl0;

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though it should have loaded website " + url0);
	if (currentTab != nullptr) {

		const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
		const std::string initialUrl = windowCore->bottomStatusBar->getUserInputText().toStdString();

		const std::string refreshCommandName("refresh tab");
		this->executeCommand(refreshCommandName, std::string());

		// Wait for page being refreshed
		WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getLoadBarVisibility() == true), tester::shared::error_type_e::STATUSBAR, "Load bar never became visible following command " + refreshCommandName, 1000);
		const int maximumProgressValue = app::progress_bar::ProgressBar::getMaximumValue();
		WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getProgressValue() == maximumProgressValue), tester::shared::error_type_e::STATUSBAR, "Load bar is expected to reach " + std::to_string(maximumProgressValue) + " instead it reached " + std::to_string(windowCore->bottomStatusBar->getProgressValue()) + " after executing command " + refreshCommandName, 1000);
		WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getLoadBarVisibility() == false), tester::shared::error_type_e::STATUSBAR, "Load bar is expected to be hiddeni after command " + refreshCommandName + " is executed", 1000);

		const int currentTabIndex = windowCore->getCurrentTabIndex();
		const int expectedInitialTabIndex = 0;
		const int expectedNumberOfTabs = expectedInitialTabIndex + 1;
		ASSERT((currentTabIndex == expectedInitialTabIndex), tester::shared::error_type_e::TABS, "Current tab index is " + std::to_string(currentTabIndex) + " whereas the expected tab index is " + std::to_string(expectedInitialTabIndex) + " because " + std::to_string(expectedNumberOfTabs) + " tabs have been opened with website " + url0);

		const int currentNumberOfTabs = windowCore->getTabCount();
		ASSERT((currentNumberOfTabs == expectedNumberOfTabs), tester::shared::error_type_e::TABS, "Actual number of tabs " + std::to_string(currentNumberOfTabs) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs));

		const std::string urlAfterRefresh = windowCore->bottomStatusBar->getUserInputText().toStdString();
		ASSERT((initialUrl.compare(urlAfterRefresh) == 0), tester::shared::error_type_e::STATUSBAR, "Source of the content in tab index " + std::to_string(currentTabIndex) + " " + urlAfterRefresh + " doesn't match the expected source " + initialUrl);

	}
}
