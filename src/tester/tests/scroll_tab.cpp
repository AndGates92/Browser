/**
 * @copyright
 * @file scroll_tab.cpp
 * @author Andrea Gianarda
 * @date 15th October 2020
 * @brief Scroll tab functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/shared/enums.h"
#include "app/shared/constants.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/window/core.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/windows/main_window/tabs/tab.h"
#include "tester/base/suite.h"
#include "tester/tests/scroll_tab.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(scrollTabOverall, scrollTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(scrollTabTest, scrollTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace scroll_tab {

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

tester::test::ScrollTab::ScrollTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Scroll tab", tester::test::scroll_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, scrollTabOverall, "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::ScrollTab::~ScrollTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, scrollTabOverall, "Test " << this->getName() << " destructor");
}

void tester::test::ScrollTab::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, scrollTabTest, "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	const std::string search("test");
	LOG_INFO(app::logger::info_level_e::ZERO, scrollTabTest, "Open new tab searching " << search);
	this->openNewTab(search);
	const std::string url = app::main_window::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though it should have website " + url + " open.");

	if (currentTab != nullptr) {
		const int initialScrollPercentage = 0;
		const int minScrollPercentage = 0;
		const int maxScrollPercentage = 100;
		const int & verticalInitialScrollPercentage = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalInitialScrollPercentage == initialScrollPercentage), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalInitialScrollPercentage) + " whereas it is expected to be " + std::to_string(initialScrollPercentage) + " because a tab was just opened.");

		const int initialVScroll = windowCore->bottomStatusBar->getVScroll();
		ASSERT((verticalInitialScrollPercentage == initialVScroll), tester::shared::error_type_e::STATUSBAR, "Current value of vertical scrolling in the status bar is " + std::to_string(initialVScroll) + " whereas the position of the scrollbar is " + std::to_string(verticalInitialScrollPercentage));

		// Test scroll up on a newly opened page
		// No change should be triggered as page scrolling is already at the top
		const std::string scrollUpCommandName("scroll up");
		this->executeCommand(scrollUpCommandName, std::string());

		const int & verticalScrollPercentageAfterScrollUp = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollPercentageAfterScrollUp == verticalInitialScrollPercentage), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollPercentageAfterScrollUp) + " whereas it is expected to be " + std::to_string(verticalInitialScrollPercentage) + " because command " + scrollUpCommandName + " has been executed just after the tab was opened hence the scroll position shouldn't have changed.");

		const int vScrollAfterScrollUp = windowCore->bottomStatusBar->getVScroll();
		ASSERT((vScrollAfterScrollUp == initialVScroll), tester::shared::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollAfterScrollUp) + " whereas its position should have not changed and stayed " + std::to_string(initialVScroll) + " because command " + scrollUpCommandName + " has been executed just after the tab was opened hence the scroll position shouldn't have changed.");

		// Test scroll down followed by scroll up
		// No change should be triggered as the two actions cancel each other
		const std::string scrollDownCommandName("scroll down");
		this->executeCommand(scrollDownCommandName, std::string());

		WAIT_FOR_CONDITION((currentTab->getVerticalScrollPercentage() > verticalScrollPercentageAfterScrollUp), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(currentTab->getVerticalScrollPercentage()) + " whereas it is expected to be greater than " + std::to_string(verticalScrollPercentageAfterScrollUp) + " because command " + scrollDownCommandName + " has been executed.", 5000);

		const int & verticalScrollPercentageAfterScrollDown = currentTab->getVerticalScrollPercentage();
		const int vScrollAfterScrollDown = windowCore->bottomStatusBar->getVScroll();
		ASSERT((vScrollAfterScrollDown == verticalScrollPercentageAfterScrollDown), tester::shared::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollAfterScrollDown) + " and its position should match the value of the tab scroll manager " + std::to_string(verticalScrollPercentageAfterScrollDown) + " after command " + scrollDownCommandName + " has been executed.");

		this->executeCommand(scrollUpCommandName, std::string());

		WAIT_FOR_CONDITION((currentTab->getVerticalScrollPercentage() == verticalScrollPercentageAfterScrollUp), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(currentTab->getVerticalScrollPercentage()) + " whereas it is expected to be " + std::to_string(verticalScrollPercentageAfterScrollUp) + " because command " + scrollUpCommandName + " has been executed after command " + scrollDownCommandName + " hence the scrollbar should return to the initial position.", 5000);

		const int & verticalScrollPercentageAfterSecondScrollUp = currentTab->getVerticalScrollPercentage();
		const int vScrollAfterSecondScrollUp = windowCore->bottomStatusBar->getVScroll();
		ASSERT((vScrollAfterSecondScrollUp == verticalScrollPercentageAfterSecondScrollUp), tester::shared::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollAfterSecondScrollUp) + " whereas its position should have not changed and stayed " + std::to_string(verticalScrollPercentageAfterSecondScrollUp) + " because command " + scrollUpCommandName + " has been executed after command " + scrollDownCommandName + " hence the scrollbar should return to the initial position.");

		// Scroll to the bottom of the page
		// Both scroll value and status bar should be synchronized
		int previousVerticalScrollDownPercentage = verticalScrollPercentageAfterSecondScrollUp;
		while (windowCore->bottomStatusBar->getVScroll() < maxScrollPercentage) {
			this->executeCommand(scrollDownCommandName, std::string());

//			const int & currentVerticalScrollDownPercentage = currentTab->getVerticalScrollPercentage();
			WAIT_FOR_CONDITION((currentTab->getVerticalScrollPercentage() > previousVerticalScrollDownPercentage), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(currentTab->getVerticalScrollPercentage()) + " whereas it is expected to be greater than " + std::to_string(previousVerticalScrollDownPercentage) + " because command " + scrollDownCommandName + " has been executed.", 5000);

			const int & currentVerticalScrollDownPercentage = currentTab->getVerticalScrollPercentage();
			const int vScrollStatusBar = windowCore->bottomStatusBar->getVScroll();
			ASSERT((vScrollStatusBar == currentVerticalScrollDownPercentage), tester::shared::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollStatusBar) + " and its position should match the value of the tab scroll manager " + std::to_string(currentVerticalScrollDownPercentage) + " after command " + scrollDownCommandName + " has been executed.");

			previousVerticalScrollDownPercentage = currentVerticalScrollDownPercentage;
		}

		const int & verticalScrollDownPercentageBottom = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollDownPercentageBottom == maxScrollPercentage), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollDownPercentageBottom) + " but it should have reached the bottom of the page hence its value should be " + std::to_string(maxScrollPercentage));

		// Scroll to the bottom of the page
		// Both scroll value and status bar should be synchronized
		int previousVerticalScrollUpPercentage = currentTab->getVerticalScrollPercentage();
		while (windowCore->bottomStatusBar->getVScroll() > minScrollPercentage) {
			this->executeCommand(scrollUpCommandName, std::string());

			WAIT_FOR_CONDITION((currentTab->getVerticalScrollPercentage() < previousVerticalScrollUpPercentage), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(currentTab->getVerticalScrollPercentage()) + " whereas it is expected to be smaller than " + std::to_string(previousVerticalScrollUpPercentage) + " because command " + scrollUpCommandName + " has been executed.", 5000);

			const int & currentVerticalScrollUpPercentage = currentTab->getVerticalScrollPercentage();
			const int vScrollStatusBar = windowCore->bottomStatusBar->getVScroll();
			ASSERT((vScrollStatusBar == currentVerticalScrollUpPercentage), tester::shared::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollStatusBar) + " and its position should match the value of the tab scroll manager " + std::to_string(currentVerticalScrollUpPercentage) + " after command " + scrollUpCommandName + " has been executed.");

			previousVerticalScrollUpPercentage = currentVerticalScrollUpPercentage;
		}

		const int & verticalScrollUpPercentageTop = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollUpPercentageTop == minScrollPercentage), tester::shared::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollUpPercentageTop) + " but it should have reached the top of the page hence its value should be " + std::to_string(minScrollPercentage));

	}

}
