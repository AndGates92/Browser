/**
 * @copyright
 * @file find_tab.cpp
 * @author Andrea Gianarda
 * @date 25th October 2020
 * @brief Find tab test functions
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
#include "find_tab.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(findTabOverall, "findTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(findTabTest, "findTab.test", MSG_TYPE_LEVEL)

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

find_tab::FindTab::FindTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Find tab", find_tab::jsonFileFullPath, useShortcuts) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findTabOverall,  "Creating test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

}

find_tab::FindTab::~FindTab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findTabOverall,  "Test " << QString::fromStdString(this->getName()) << " destructor");
}

std::vector<std::string> find_tab::FindTab::extractDataFromSearchResult(const std::regex & numberRegex, const int & expectedNumberOfMatches) {
	auto sregexIteratorEnd = std::sregex_iterator();

	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();
	const std::string searchTextInLabelAfterUp = windowCore->bottomStatusBar->getSearchResultText().toStdString();
	auto itemMatch = std::sregex_iterator(searchTextInLabelAfterUp.cbegin(), searchTextInLabelAfterUp.cend(), numberRegex);
	const long int numberOfMatches = std::distance(itemMatch, sregexIteratorEnd);
	ASSERT((numberOfMatches == expectedNumberOfMatches), test_enums::error_type_e::STATUSBAR,  + "Found " + std::to_string(numberOfMatches) + " numbers in the text in search label of the status bar " + searchTextInLabelAfterUp + " whereas only " + std::to_string(expectedNumberOfMatches) + " were expected");

	std::vector<std::string> result;
	for (std::sregex_iterator & resultIt = itemMatch; resultIt != sregexIteratorEnd; resultIt++ ) {
		const std::smatch & match = *resultIt;
		const std::string & matchStr = match.str();
		result.push_back(matchStr);
	}

	return result;
}

int find_tab::FindTab::computeNextMatchNumber(const std::string & command, const std::vector<int> & initialMatchPosition) {
	const int & currentMatch = initialMatchPosition[0];
	const int & totalNumberOfMatches = initialMatchPosition[1];

	ASSERT(((command.compare(find_tab::findDownCommandName) == 0) && (command.compare(find_tab::findCommandName) == 0) && (command.compare(find_tab::findDownCommandName) == 0)), test_enums::error_type_e::COMMAND, "Command " + command + " is not in the list of allowed commands: " + find_tab::findCommandName + ", " + find_tab::findUpCommandName + " and " + find_tab::findDownCommandName);

	int nextMatch = -1;
	if (command.compare(find_tab::findUpCommandName) == 0) {
	       if (currentMatch == 0) {
			nextMatch = totalNumberOfMatches - 1;
		} else {
			nextMatch = currentMatch - 1;
		}
	} else if ((command.compare(find_tab::findCommandName) == 0) && (command.compare(find_tab::findDownCommandName) == 0)) {
	       if (currentMatch == (totalNumberOfMatches - 1)) {
			nextMatch = 0;
		} else {
			nextMatch = currentMatch + 1;
		}
	}

	return nextMatch;
}

int find_tab::FindTab::checkVScrolling(const int & initialVScroll, const int & initialMatchPosition, const int & finalMatchPosition) {
	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();
	const int currentVScroll = windowCore->bottomStatusBar->getVScroll();

	if (initialMatchPosition < finalMatchPosition) {
		// Find downwards or find upward with wrapping
		ASSERT((initialVScroll <= currentVScroll), test_enums::error_type_e::STATUSBAR, "When searching text downward or upward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be smaller than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
	} else if (initialMatchPosition > finalMatchPosition) {
		ASSERT((initialVScroll >= currentVScroll), test_enums::error_type_e::STATUSBAR, "When searching text upward or downward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be larger than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
	} else {
		ASSERT((initialVScroll == currentVScroll), test_enums::error_type_e::STATUSBAR, "When making no search as the match position remains unchnaged, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be the same as the current vertical scrolling " + std::to_string(currentVScroll));
	}

	return currentVScroll;
}

int find_tab::FindTab::checkVScrolling(const int & initialVScroll, const std::string & command, const bool wrapping) {
	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();
	const int currentVScroll = windowCore->bottomStatusBar->getVScroll();

	ASSERT(((command.compare(find_tab::findDownCommandName) == 0) && (command.compare(find_tab::findCommandName) == 0) && (command.compare(find_tab::findDownCommandName) == 0)), test_enums::error_type_e::COMMAND, "Command " + command + " is not in the list of allowed commands: " + find_tab::findCommandName + ", " + find_tab::findUpCommandName + " and " + find_tab::findDownCommandName);

	if (command.compare(find_tab::findUpCommandName) == 0) {
		if (wrapping == true) {
			ASSERT((initialVScroll <= currentVScroll), test_enums::error_type_e::STATUSBAR, "When searching text upward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be smaller than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		} else {
			ASSERT((initialVScroll >= currentVScroll), test_enums::error_type_e::STATUSBAR, "When searching text upward, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be larger than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		}
	} else if ((command.compare(find_tab::findCommandName) == 0) && (command.compare(find_tab::findDownCommandName) == 0)) {
		if (wrapping == true) {
			ASSERT((initialVScroll >= currentVScroll), test_enums::error_type_e::STATUSBAR, "When searching text downward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be larger than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		} else {
			ASSERT((initialVScroll <= currentVScroll), test_enums::error_type_e::STATUSBAR, "When searching text upward with wrapping around the page, the initial vertical scrolling " + std::to_string(initialVScroll) + " is expected to be smaller than or equal to the current vertical scrolling " + std::to_string(currentVScroll));
		}
	}

	return currentVScroll;
}

std::vector<int> find_tab::FindTab::checkMatchPosition(const std::string & command, const std::regex & textRegex, const int & expectedNumberOfMatches, const std::vector<int> & initialMatchPosition) {
	const std::vector<std::string> matchVectorStr = find_tab::FindTab::extractDataFromSearchResult(textRegex, expectedNumberOfMatches);
	std::vector<int> matchVector;
	std::transform(matchVectorStr.cbegin(), matchVectorStr.cend(), back_inserter(matchVector), [] (const std::string & str) {
		return std::atoi(str.c_str());
	});
	const int & totalNumberOfMatches = initialMatchPosition[1];
	ASSERT((totalNumberOfMatches > 0), test_enums::error_type_e::STATUSBAR, "Total number of matches is " + std::to_string(totalNumberOfMatches) + " and it should be greater than 0");
	const int expectedMatchNumber = this->computeNextMatchNumber(command, initialMatchPosition);
	ASSERT((matchVector[0] == expectedMatchNumber), test_enums::error_type_e::STATUSBAR, "The current match number " + std::to_string(matchVector[0]) + " doesn't match the expected match number " + std::to_string(expectedMatchNumber));
	ASSERT((matchVector[1] == totalNumberOfMatches), test_enums::error_type_e::STATUSBAR, "Total number of matches changed. Current value is " + std::to_string(matchVector[1]) + " previous value is " + std::to_string(totalNumberOfMatches));
	return matchVector;
}

void find_tab::FindTab::testBody() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findTabTest,  "Starting test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	const std::string https(global_constants::https.toStdString());
	const std::string www(global_constants::www.toStdString());

	// Create 1 tabs
	const std::string search("test");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findTabTest, "Open new tab searching " << search);
	this->openNewTab(search);
	const std::string authorityUrl0 = www + main_window_constants::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();
	const std::string url0 = https + authorityUrl0;

	const std::shared_ptr<main_window_tab::MainWindowTab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), test_enums::error_type_e::TABS, "Current tab pointer is null event though it should have loaded website " + url0);
	if (currentTab != nullptr) {

		const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::regex numberRegex("[0-9]+");
		const int expectedNumberOfMatches = 2;
#endif // QT_VERSION

		// Do initial search to start value of vertical scrolling and mach position
		// Search instances of the search in the opened webpage
		const std::string findCommandName("find");
		QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findTabTest, "Find " << search << " in tab");
		this->executeCommand(findCommandName, search);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		// Get the total number of matches and initial match number
		const std::vector<std::string> matchVectorInitial = find_tab::FindTab::extractDataFromSearchResult(numberRegex, expectedNumberOfMatches);
		std::vector<int> initialMatchPosition({std::atoi(matchVectorInitial[0]), std::atoi(matchVectorInitial[1]});
#endif // QT_VERSION
		const int initialVScroll = windowCore->bottomStatusBar->getVScroll();

		// Finding upward means that the current item found is the one at the bottom of the webpage
		this->executeCommand(find_tab::findUpCommandName, std::string());

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::vector<int> bottomPageMatchPosition = this->checkMatchPosition(find_tab::findUpCommandName, numberRegex, expectedNumberOfMatches, initialMatchPosition);
		this->checkVScrolling(initialVScroll, initialMatchPosition[0], bottomPageMatchPosition[0]);
#endif // QT_VERSION

		const int vScrollBottomPageMatch = this->checkVScrolling(initialVScroll, find_tab::findUpCommandName, true);

		// Finding downward means that the current item found is the one at the top of the webpage
		this->executeCommand(find_tab::findDownCommandName, std::string());

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::vector<int> topPageMatchPosition = this->checkMatchPosition(find_tab::findDownCommandName, numberRegex, expectedNumberOfMatches, bottomPageMatchPosition);
		ASSERT((topPageMatchPosition[0] == initialMatchPosition[0]), test_enums::error_type_e::STATUSBAR, "Match position after one search upwards and one downward " + std::to_string(topPageMatchPosition[0]) + " must be the same as the initial one " + std::to_string(initialMatchPosition[0]));
		this->checkVScrolling(vScrollBottomPageMatch, bottomPageMatchPosition[0], topPageMatchPosition[0]);
#endif // QT_VERSION
		const int vScrollTopPageMatch = this->checkVScrolling(vScrollBottomPageMatch, find_tab::findDownCommandName, true);

		ASSERT((vScrollTopPageMatch == initialVScroll), test_enums::error_type_e::STATUSBAR, "Vertical scrolling after one search upwards and one downward " + std::to_string(vScrollTopPageMatch) + " must be the same as the initial one " + std::to_string(initialVScroll));

		// Finding downward means that the current item found is the second item from the top of the webpage
		this->executeCommand(find_tab::findDownCommandName, std::string());

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::vector<int> matchVectorAfterFindingDownward = this->checkMatchPosition(find_tab::findDownCommandName, numberRegex, expectedNumberOfMatches, topPageMatchPosition);
		this->checkVScrolling(vScrollTopPageMatch, topPageMatchPosition[0], matchVectorAfterFindingDownward[0]);
#endif // QT_VERSION
		const int vScrollAfterFindingDownward = this->checkVScrolling(vScrollTopPageMatch, find_tab::findDownCommandName, false);

		// Finding upward means that the current item found is the one at the top of the webpage
		this->executeCommand(find_tab::findUpCommandName, std::string());

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
		const std::vector<int> matchVectorAfterFindingUpward = this->checkMatchPosition(find_tab::findUpCommandName, numberRegex, expectedNumberOfMatches, matchVectorAfterFindingDownward);
		ASSERT((std::to_string(matchVectorAfterFindingUpward[0]) == matchVectorAfterFindingDownward[0]), test_enums::error_type_e::STATUSBAR, "Match position after one search upwards and one downward " + std::to_string(matchVectorAfterFindingUpward[0]) + " must be the same as the one before the second round of find down - find up " + std::to_string(matchVectorAfterFindingDownward[0]));
		this->checkVScrolling(initialVScroll, matchVectorAfterFindingDownward[0], matchVectorAfterFindingUpward[0]);
#endif // QT_VERSION

		const int vScrollAfterFindingUpward = this->checkVScrolling(vScrollAfterFindingDownward, find_tab::findUpCommandName, false);

		ASSERT((vScrollAfterFindingUpward == vScrollTopPageMatch), test_enums::error_type_e::STATUSBAR, "Vertical scrolling after one search upwards and one downward " + std::to_string(vScrollAfterFindingUpward) + " must be the same as the one before the second round of find down - find up " + std::to_string(vScrollTopPageMatch));

	}
}
