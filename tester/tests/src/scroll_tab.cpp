/**
 * @copyright
 * @file scroll_tab.cpp
 * @author Andrea Gianarda
 * @date 15th October 2020
 * @brief Scroll tab functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "global_enums.h"
#include "logging_macros.h"
#include "qt_operator.h"
#include "stl_helper.h"
#include "main_window_constants.h"
#include "scroll_tab.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(scrollTabOverall, "scrollTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(scrollTabTest, "scrollTab.test", MSG_TYPE_LEVEL)

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

scroll_tab::ScrollTab::ScrollTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Scroll tab", scroll_tab::jsonFileFullPath, useShortcuts) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, scrollTabOverall,  "Creating test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

}

scroll_tab::ScrollTab::~ScrollTab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, scrollTabOverall,  "Test " << QString::fromStdString(this->getName()) << " destructor");
}

void scroll_tab::ScrollTab::testBody() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, scrollTabTest,  "Starting test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();

	const std::string https(global_constants::https.toStdString());
	const std::string www(global_constants::www.toStdString());

	const std::string search("test");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, scrollTabTest, "Open new tab searching " << search);
	this->openNewTab(search);
	const std::string url = https + www + main_window_constants::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();

	const std::shared_ptr<main_window_tab::MainWindowTab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), test_enums::error_type_e::TABS, "Current tab pointer is null event though it should have website " + url + " open.");

	if (currentTab != nullptr) {
		const int initialScrollPercentage = 0;
		const int minScrollPercentage = 0;
		const int maxScrollPercentage = 100;
		const int & verticalInitialScrollPercentage = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalInitialScrollPercentage == initialScrollPercentage), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalInitialScrollPercentage) + " whereas it is expected to be " + std::to_string(initialScrollPercentage) + " because a tab was just opened.");

		const int initialVScroll = windowCore->bottomStatusBar->getVScroll();
		ASSERT((verticalInitialScrollPercentage == initialVScroll), test_enums::error_type_e::STATUSBAR, "Current value of vertical scrolling in the status bar is " + std::to_string(initialVScroll) + " whereas the position of the scrollbar is " + std::to_string(verticalInitialScrollPercentage));

		// Test scroll up on a newly opened page
		// No change should be triggered as page scrolling is already at the top
		const std::string scrollUpCommandName("scroll up");
		this->executeCommand(scrollUpCommandName, std::string());

		const int & verticalScrollPercentageAfterScrollUp = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollPercentageAfterScrollUp == verticalInitialScrollPercentage), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollPercentageAfterScrollUp) + " whereas it is expected to be " + std::to_string(verticalInitialScrollPercentage) + " because command " + scrollUpCommandName + " has been executed just after the tab was opened hence the scroll position shouldn't have changed.");

		const int vScrollAfterScrollUp = windowCore->bottomStatusBar->getVScroll();
		ASSERT((vScrollAfterScrollUp == initialVScroll), test_enums::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollAfterScrollUp) + " whereas its position should have not changed and stayed " + std::to_string(initialVScroll) + " because command " + scrollUpCommandName + " has been executed just after the tab was opened hence the scroll position shouldn't have changed.");

		// Test scroll down followed by scroll up
		// No change should be triggered as the two actions cancel each other
		const std::string scrollDownCommandName("scroll down");
		this->executeCommand(scrollDownCommandName, std::string());

		const int & verticalScrollPercentageAfterScrollDown = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollPercentageAfterScrollDown > verticalScrollPercentageAfterScrollUp), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollPercentageAfterScrollDown) + " whereas it is expected to be greater than " + std::to_string(verticalScrollPercentageAfterScrollUp) + " because command " + scrollDownCommandName + " has been executed.");

		const int vScrollAfterScrollDown = windowCore->bottomStatusBar->getVScroll();
		ASSERT((vScrollAfterScrollDown == verticalScrollPercentageAfterScrollDown), test_enums::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollAfterScrollDown) + " and its position should match the value of the tab scroll manager " + std::to_string(verticalScrollPercentageAfterScrollDown) + " after command " + scrollDownCommandName + " has been executed.");

		this->executeCommand(scrollUpCommandName, std::string());

		const int & verticalScrollPercentageAfterSecondScrollUp = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollPercentageAfterSecondScrollUp == verticalScrollPercentageAfterScrollUp), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollPercentageAfterSecondScrollUp) + " whereas it is expected to be " + std::to_string(verticalScrollPercentageAfterScrollUp) + " because command " + scrollUpCommandName + " has been executed after command " + scrollDownCommandName + " hence the scrollbar should return to the initial position.");

		const int vScrollAfterSecondScrollUp = windowCore->bottomStatusBar->getVScroll();
		ASSERT((vScrollAfterSecondScrollUp == verticalScrollPercentageAfterSecondScrollUp), test_enums::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollAfterSecondScrollUp) + " whereas its position should have not changed and stayed " + std::to_string(verticalScrollPercentageAfterSecondScrollUp) + " because command " + scrollUpCommandName + " has been executed after command " + scrollDownCommandName + " hence the scrollbar should return to the initial position.");

		// Scroll to the bottom of the page
		// Both scroll value and status bar should be synchronized
		int previousVerticalScrollDownPercentage = verticalScrollPercentageAfterSecondScrollUp;
		while (windowCore->bottomStatusBar->getVScroll() < maxScrollPercentage) {
			this->executeCommand(scrollDownCommandName, std::string());

			const int & currentVerticalScrollDownPercentage = currentTab->getVerticalScrollPercentage();
			ASSERT((currentVerticalScrollDownPercentage > previousVerticalScrollDownPercentage), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(currentVerticalScrollDownPercentage) + " whereas it is expected to be greater than " + std::to_string(previousVerticalScrollDownPercentage) + " because command " + scrollDownCommandName + " has been executed.");

			const int vScrollStatusBar = windowCore->bottomStatusBar->getVScroll();
			ASSERT((vScrollStatusBar == currentVerticalScrollDownPercentage), test_enums::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollStatusBar) + " and its position should match the value of the tab scroll manager " + std::to_string(currentVerticalScrollDownPercentage) + " after command " + scrollDownCommandName + " has been executed.");

			previousVerticalScrollDownPercentage = currentVerticalScrollDownPercentage;
		}

		const int & verticalScrollDownPercentageBottom = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollDownPercentageBottom == maxScrollPercentage), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollDownPercentageBottom) + " but it should have reached the bottom of the page hence its value should be " + std::to_string(maxScrollPercentage));

		// Scroll to the bottom of the page
		// Both scroll value and status bar should be synchronized
		int previousVerticalScrollUpPercentage = verticalScrollPercentageAfterSecondScrollUp;
		while (windowCore->bottomStatusBar->getVScroll() > minScrollPercentage) {
			this->executeCommand(scrollUpCommandName, std::string());

			const int & currentVerticalScrollUpPercentage = currentTab->getVerticalScrollPercentage();
			ASSERT((currentVerticalScrollUpPercentage > previousVerticalScrollUpPercentage), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(currentVerticalScrollUpPercentage) + " whereas it is expected to be greater than " + std::to_string(previousVerticalScrollUpPercentage) + " because command " + scrollUpCommandName + " has been executed.");

			const int vScrollStatusBar = windowCore->bottomStatusBar->getVScroll();
			ASSERT((vScrollStatusBar == currentVerticalScrollUpPercentage), test_enums::error_type_e::STATUSBAR, "Current value of the vertical scrolling in the status bar is " + std::to_string(vScrollStatusBar) + " and its position should match the value of the tab scroll manager " + std::to_string(currentVerticalScrollUpPercentage) + " after command " + scrollUpCommandName + " has been executed.");

			previousVerticalScrollUpPercentage = currentVerticalScrollUpPercentage;
		}

		const int & verticalScrollUpPercentageTop = currentTab->getVerticalScrollPercentage();
		ASSERT((verticalScrollUpPercentageTop == minScrollPercentage), test_enums::error_type_e::TABS, "Current position of the vertical scrollbar is " + std::to_string(verticalScrollUpPercentageTop) + " but it should have reached the top of the page hence its value should be " + std::to_string(minScrollPercentage));


	}

}
