/**
 * @copyright
 * @file find_tab.cpp
 * @author Andrea Gianarda
 * @date 25th October 2020
 * @brief Find tab test functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/shared/enums.h"
#include "app/shared/constants.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/window/core.h"
#include "app/windows/main_window/statusbar/status_bar.h"
#include "app/windows/main_window/tabs/tab.h"
#include "tester/tests/find_tab.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_tester_wrapper.h"

LOGGING_CONTEXT(findTabOverall, findTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(findTabTest, findTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace find_tab {

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

				/**
				 * @brief Find command name
				 *
				 */
				static const std::string findCommandName("find");

				/**
				 * @brief Find upward command name
				 *
				 */
				static const std::string findUpCommandName("find upward");

				/**
				 * @brief Find downward command name
				 *
				 */
				static const std::string findDownCommandName("find downward");
			}

		}

	}

}

tester::test::FindTab::FindTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Find tab", tester::test::find_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, findTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::FindTab::~FindTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, findTabOverall,  "Test " << this->getName() << " destructor");
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
std::vector<std::string> tester::test::FindTab::extractDataFromSearchResult(const std::regex & numberRegex, const int & expectedNumberOfMatches) {
	auto sregexIteratorEnd = std::sregex_iterator();

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const std::string searchTextInLabelAfterUp = windowCore->bottomStatusBar->getSearchResultText().toStdString();
	auto itemMatch = std::sregex_iterator(searchTextInLabelAfterUp.cbegin(), searchTextInLabelAfterUp.cend(), numberRegex);
	const long int numberOfMatches = std::distance(itemMatch, sregexIteratorEnd);
	ASSERT((numberOfMatches == expectedNumberOfMatches), tester::shared::error_type_e::STATUSBAR,  "Found " + std::to_string(numberOfMatches) + " numbers in the text in search label of the status bar " + searchTextInLabelAfterUp + " whereas only " + std::to_string(expectedNumberOfMatches) + " were expected");

	std::vector<std::string> result;
	for (std::sregex_iterator & resultIt = itemMatch; resultIt != sregexIteratorEnd; resultIt++ ) {
		const std::smatch & match = *resultIt;
		const std::string & matchStr = match.str();
		result.push_back(matchStr);
	}

	return result;
}
#endif // QT_VERSION

int tester::test::FindTab::computeNextMatchNumber(const std::string & command, const std::vector<int> & initialMatchPosition) {
	const std::vector<int>::size_type initialMatchPositionSize = initialMatchPosition.size();
	ASSERT((initialMatchPositionSize >= 2), tester::shared::error_type_e::STATUSBAR, "Initial match position vector must have at least 2 elements to be able to perform checks. It has " + std::to_string(initialMatchPositionSize) + " instead.");
	int nextMatch = -1;
	if (initialMatchPositionSize >= 2) {
		const int & currentMatch = initialMatchPosition[0];
		const int & totalNumberOfMatches = initialMatchPosition[1];

		ASSERT(((command.compare(tester::test::find_tab::findDownCommandName) == 0) || (command.compare(tester::test::find_tab::findCommandName) == 0) || (command.compare(tester::test::find_tab::findUpCommandName) == 0)), tester::shared::error_type_e::COMMAND, "Command " + command + " is not in the list of allowed commands: " + tester::test::find_tab::findCommandName + ", " + tester::test::find_tab::findUpCommandName + " and " + tester::test::find_tab::findDownCommandName);

		if (command.compare(tester::test::find_tab::findUpCommandName) == 0) {
		       if (currentMatch == 1) {
				nextMatch = totalNumberOfMatches;
			} else {
				nextMatch = currentMatch - 1;
			}
		} else if ((command.compare(tester::test::find_tab::findCommandName) == 0) || (command.compare(tester::test::find_tab::findDownCommandName) == 0)) {
		       if (currentMatch == totalNumberOfMatches) {
				nextMatch = 1;
			} else {
				nextMatch = currentMatch + 1;
			}
		}
	}

	return nextMatch;
}

int tester::test::FindTab::checkVScrolling(const int & initialVScroll, const int & initialMatchPosition, const int & finalMatchPosition) {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const int currentVScroll = windowCore->bottomStatusBar->getVScroll();

	if (initialMatchPosition < finalMatchPosition) {
		// Find downwards or find upward with wrapping
		ASSERT((initialVScroll <= currentVScroll), tester::shared::error_type_e::TABS, "When searching text downward or upward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " (with matching position " + std::to_string(initialMatchPosition) + ") is expected to be smaller than or equal to the current vertical scrolling " + std::to_string(currentVScroll) + " (with matching position " + std::to_string(finalMatchPosition) + ")");
	} else if (initialMatchPosition > finalMatchPosition) {
		ASSERT((initialVScroll >= currentVScroll), tester::shared::error_type_e::TABS, "When searching text upward or downward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " (with matching position " + std::to_string(initialMatchPosition) + ") is expected to be larger than or equal to the current vertical scrolling " + std::to_string(currentVScroll) + " (with matching position " + std::to_string(finalMatchPosition) + ")");
	} else {
		ASSERT((initialVScroll == currentVScroll), tester::shared::error_type_e::TABS, "When making no search as the match position remains unchnaged, the initial vertical scrolling " + std::to_string(initialVScroll) + " (with matching position " + std::to_string(initialMatchPosition) + ") is expected to be the same as the current vertical scrolling " + std::to_string(currentVScroll) + " (with matching position " + std::to_string(finalMatchPosition) + ")");
	}

	return currentVScroll;
}

int tester::test::FindTab::checkVScrolling(const int & initialVScroll, const std::string & command, const bool wrapping) {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const int currentVScroll = windowCore->bottomStatusBar->getVScroll();

	ASSERT(((command.compare(tester::test::find_tab::findDownCommandName) == 0) || (command.compare(tester::test::find_tab::findCommandName) == 0) || (command.compare(tester::test::find_tab::findUpCommandName) == 0)), tester::shared::error_type_e::COMMAND, "Command " + command + " is not in the list of allowed commands: " + tester::test::find_tab::findCommandName + ", " + tester::test::find_tab::findUpCommandName + " and " + tester::test::find_tab::findDownCommandName);

	if (command.compare(tester::test::find_tab::findUpCommandName) == 0) {
		if (wrapping == true) {
			ASSERT((initialVScroll <= currentVScroll), tester::shared::error_type_e::STATUSBAR, "When searching text upward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be smaller than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		} else {
			ASSERT((initialVScroll >= currentVScroll), tester::shared::error_type_e::STATUSBAR, "When searching text upward, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be larger than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		}
	} else if ((command.compare(tester::test::find_tab::findCommandName) == 0) && (command.compare(tester::test::find_tab::findDownCommandName) == 0)) {
		if (wrapping == true) {
			ASSERT((initialVScroll >= currentVScroll), tester::shared::error_type_e::STATUSBAR, "When searching text downward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be larger than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		} else {
			ASSERT((initialVScroll <= currentVScroll), tester::shared::error_type_e::STATUSBAR, "When searching text upward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be smaller than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		}
	}

	return currentVScroll;
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
std::vector<int> tester::test::FindTab::searchDataToNumbers(const std::regex & textRegex, const int & expectedNumberOfMatches) {
	const std::vector<std::string> matchVectorStr = this->extractDataFromSearchResult(textRegex, expectedNumberOfMatches);
	std::vector<int> matchVector;
	std::transform(matchVectorStr.cbegin(), matchVectorStr.cend(), back_inserter(matchVector), [] (const std::string & str) {
		return std::atoi(str.c_str());
	});
	return matchVector;
}
#endif // QT_VERSION

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
std::vector<int> tester::test::FindTab::checkMatchPosition(const std::string & command, const std::regex & textRegex, const int & expectedNumberOfMatches, const std::vector<int> & initialMatchPosition) {
	const std::vector<int> matchVector = this->searchDataToNumbers(textRegex, expectedNumberOfMatches);
	const std::vector<int>::size_type initialMatchPositionSize = initialMatchPosition.size();
	ASSERT((initialMatchPositionSize >= 2), tester::shared::error_type_e::STATUSBAR, "Initial match position vector must have at least 2 elements to be able to perform checks. It has " + std::to_string(initialMatchPositionSize) + " instead.");
	if (initialMatchPositionSize >= 2) {
		const int & totalNumberOfMatches = initialMatchPosition[1];
		ASSERT((totalNumberOfMatches > 0), tester::shared::error_type_e::STATUSBAR, "Total number of matches is " + std::to_string(totalNumberOfMatches) + " and it should be greater than 0");

		const int expectedMatchNumber = this->computeNextMatchNumber(command, initialMatchPosition);
		ASSERT((expectedMatchNumber >= 0), tester::shared::error_type_e::STATUSBAR, "Invalid expected match number " + std::to_string(expectedMatchNumber) + ". It is expected to be equal or greater than 0");
		const std::vector<int>::size_type matchVectorSize = matchVector.size();
		ASSERT((matchVectorSize >= 2), tester::shared::error_type_e::STATUSBAR, "Current match position vector must have at least 2 elements to be able to perform checks. It has " + std::to_string(matchVectorSize) + " instead.");
		if (matchVectorSize >= 2) {
			ASSERT((matchVector[0] == expectedMatchNumber), tester::shared::error_type_e::STATUSBAR, "The current match number " + std::to_string(matchVector[0]) + " after " + command + " has been executed doesn't match the expected match number " + std::to_string(expectedMatchNumber));
			ASSERT((matchVector[1] == totalNumberOfMatches), tester::shared::error_type_e::STATUSBAR, "Total number of matches changed. Current value is " + std::to_string(matchVector[1]) + " previous value is " + std::to_string(totalNumberOfMatches));
		}
	}
	return matchVector;
}
#endif // QT_VERSION

void tester::test::FindTab::findInTab(const std::string & command, const std::regex & numberRegex, const int & expectedNumberOfMatches, int & currentVScroll, std::vector<int> & currentMatchPosition, const bool wrapping) {
	// Finding upward means that the current item found is the one at the bottom of the webpage
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const std::string initialSearchResult = windowCore->bottomStatusBar->getSearchResultText().toStdString();
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	const std::vector<int> initialMatchPosition = this->searchDataToNumbers(numberRegex, expectedNumberOfMatches);
#endif // QT_VERSION
	const int initialVScroll = windowCore->bottomStatusBar->getVScroll();
	this->executeCommand(command, std::string());

	WAIT_FOR_CONDITION((initialVScroll != windowCore->bottomStatusBar->getVScroll()), tester::shared::error_type_e::TABS, "Initial vertical scroll " + std::to_string(initialVScroll) + " is the same as the current vertical scrolling " + std::to_string(windowCore->bottomStatusBar->getVScroll()), 5000);

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	WAIT_FOR_CONDITION((initialSearchResult.compare(windowCore->bottomStatusBar->getSearchResultText().toStdString()) != 0), tester::shared::error_type_e::TABS, "Current search result " + windowCore->bottomStatusBar->getSearchResultText().toStdString() + " is still the same as the initial one " + initialSearchResult, 5000);

	currentMatchPosition = this->checkMatchPosition(command, numberRegex, expectedNumberOfMatches, initialMatchPosition);
	const std::vector<int>::size_type currentMatchPositionSize = currentMatchPosition.size();
	const std::vector<int>::size_type initialMatchPositionSize = initialMatchPosition.size();
	if ((initialMatchPositionSize >= 1) && (currentMatchPositionSize >= 1)) {
		this->checkVScrolling(initialVScroll, initialMatchPosition[0], currentMatchPosition[0]);
	}
#endif // QT_VERSION

	currentVScroll = this->checkVScrolling(initialVScroll, command, wrapping);
}


void tester::test::FindTab::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, findTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string https(app::shared::https.toStdString());
	const std::string www(app::shared::www.toStdString());

	// Create 1 tabs
	const std::string search("eleifend quam");
	const std::string fileName("tester_files/text");
	this->openFile(fileName);

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though it should have loaded website " + fileName);
	if (currentTab != nullptr) {

		const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::regex numberRegex("[0-9]+");
		const int expectedNumberOfMatches = 2;
#endif // QT_VERSION

		// Do initial search to start value of vertical scrolling and mach position
		// Search instances of the search in the opened webpage
		LOG_INFO(app::logger::info_level_e::ZERO, findTabTest, "Find " << search << " in tab");
		const std::string initialSearchResult = windowCore->bottomStatusBar->getSearchResultText().toStdString();
		const int defaultVScroll = windowCore->bottomStatusBar->getVScroll();
		this->executeCommand(tester::test::find_tab::findCommandName, search);

		WAIT_FOR_CONDITION((defaultVScroll != windowCore->bottomStatusBar->getVScroll()), tester::shared::error_type_e::TABS, "Initial vertical scroll " + std::to_string(defaultVScroll) + " is the same as the current vertical scrolling " + std::to_string(windowCore->bottomStatusBar->getVScroll()), 5000);

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		WAIT_FOR_CONDITION((initialSearchResult.compare(windowCore->bottomStatusBar->getSearchResultText().toStdString()) != 0), tester::shared::error_type_e::TABS, "Current search result " + windowCore->bottomStatusBar->getSearchResultText().toStdString() + " is still the same as the initial one " + initialSearchResult, 10000);
		// Get the total number of matches and initial match number
		const std::vector<int> initialMatchPosition = this->searchDataToNumbers(numberRegex, expectedNumberOfMatches);
		const std::vector<int>::size_type matchVectorInitialSize = initialMatchPosition.size();
		if (matchVectorInitialSize > 2) {
			LOG_WARNING(findTabTest,  "Size of the search result data is " << matchVectorInitialSize << ", nonetheless only the first 2 element are relevant for the subsequent checks");
		}
#endif // QT_VERSION

		const int initialVScroll = windowCore->bottomStatusBar->getVScroll();

		// Finding upward means that the current item found is the one at the bottom of the webpage
		std::vector<int> bottomPageMatchPosition({-1, -1});
		int vScrollBottomPageMatch = -1;
		this->findInTab(tester::test::find_tab::findUpCommandName, numberRegex, expectedNumberOfMatches, vScrollBottomPageMatch, bottomPageMatchPosition, true);

		// Finding downward means that the current item found is the one at the top of the webpage
		std::vector<int> topPageMatchPosition({-1, -1});
		int vScrollTopPageMatch = -1;
		this->findInTab(tester::test::find_tab::findDownCommandName, numberRegex, expectedNumberOfMatches, vScrollTopPageMatch, topPageMatchPosition, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::vector<int>::size_type topPageMatchPositionSize = topPageMatchPosition.size();
		if ((matchVectorInitialSize >= 1) && (topPageMatchPositionSize >= 1)) {
			ASSERT((topPageMatchPosition[0] == initialMatchPosition[0]), tester::shared::error_type_e::STATUSBAR, "Match position after one search upwards and one downward " + std::to_string(topPageMatchPosition[0]) + " must be the same as the initial one " + std::to_string(initialMatchPosition[0]));
		}
#endif // QT_VERSION

		ASSERT((vScrollTopPageMatch == initialVScroll), tester::shared::error_type_e::STATUSBAR, "Vertical scrolling after one search upwards and one downward " + std::to_string(vScrollTopPageMatch) + " must be the same as the initial one " + std::to_string(initialVScroll));

		// Finding downward means that the current item found is the second item from the top of the webpage
		std::vector<int> matchVectorAfterFindingDownward({-1, -1});
		int vScrollAfterFindingDownward = -1;
		this->findInTab(tester::test::find_tab::findDownCommandName, numberRegex, expectedNumberOfMatches, vScrollAfterFindingDownward, matchVectorAfterFindingDownward, false);

		// Finding upward means that the current item found is the one at the top of the webpage
		std::vector<int> matchVectorAfterFindingUpward({-1, -1});
		int vScrollAfterFindingUpward = -1;
		this->findInTab(tester::test::find_tab::findUpCommandName, numberRegex, expectedNumberOfMatches, vScrollAfterFindingUpward, matchVectorAfterFindingUpward, false);

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::vector<int>::size_type findUpwardMatchPositionSize = matchVectorAfterFindingUpward.size();
		if ((topPageMatchPositionSize >= 1) && (findUpwardMatchPositionSize >= 1)) {
			ASSERT((matchVectorAfterFindingUpward[0] == topPageMatchPosition[0]), tester::shared::error_type_e::STATUSBAR, "Match position after one search upwards and one downward " + std::to_string(matchVectorAfterFindingUpward[0]) + " must be the same as the one before the second round of find down - find up " + std::to_string(topPageMatchPosition[0]));
		}
#endif // QT_VERSION

		ASSERT((vScrollAfterFindingUpward == vScrollTopPageMatch), tester::shared::error_type_e::STATUSBAR, "Vertical scrolling after one search upwards and one downward " + std::to_string(vScrollAfterFindingUpward) + " must be the same as the one before the second round of find down - find up " + std::to_string(vScrollTopPageMatch));

		const std::string closeCommandName("close tab");
		this->executeCommand(closeCommandName, std::string());
		tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);

	}
}
