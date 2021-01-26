/**
 * @copyright
 * @file open_tab.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Open tab functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/windows/main_window/window/core.h"
#include "app/shared/enums.h"
#include "app/shared/qt_functions.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "tester/tests/open_tab.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_wrapper.h"
#include "tester/utility/test.h"

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

tester::test::OpenTab::OpenTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts, const tester::shared::text_type_e type) : tester::base::CommandTest(testSuite, "", tester::test::open_tab::jsonFileFullPath, useShortcuts), searchType(type) {

	std::string enumToString = app::shared::qEnumToQString(type, true).toStdString();
	std::transform(enumToString.begin(), enumToString.end(), enumToString.begin(), [] (unsigned char c) {
		return std::tolower(c);
	});
	std::string testName("Open tab with " + enumToString + " search using " + (useShortcuts ? "shortcuts" : "full commands"));
	this->setName(testName);
	
	LOG_INFO(app::logger::info_level_e::ZERO, openTabOverall, "Creating test " << this->getName() << " in suite " << this->getSuite()->getName() << " with search text type " << type);
}

tester::test::OpenTab::~OpenTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, openTabOverall, "Test " << this->getName() << " destructor");
}

void tester::test::OpenTab::testBody() {
	LOG_INFO(app::logger::info_level_e::ZERO, openTabTest, "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	std::string search = std::string();
	for (const auto & character : search) {
		switch (this->searchType) {
			case tester::shared::text_type_e::ALPHANUMERICAL:
				search = "mysearch";
				break;
			case tester::shared::text_type_e::COMPLEX:
				search = "my search. - Do you like punctuation characters? if (true) { return EXIT_SUCCESS; }";
				break;
			case tester::shared::text_type_e::URL:
				search = "my.search";
				break;
			default:
				ASSERT(false, tester::shared::error_type_e::TEST, std::string("No checks performed on character ") + character + " of the text to search " + search + " for search type " + this->searchType);
				break;
		}
	}

	tester::utility::checkText(search, this->searchType);
	LOG_INFO(app::logger::info_level_e::ZERO, openTabTest, "Open new tab with website " << search);
	this->openNewTab(search);

	const std::string closeCommandName("close tab");
	this->executeCommand(closeCommandName, std::string());
	tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	WAIT_FOR_CONDITION((windowCore->getTabCount() == 0), tester::shared::error_type_e::TABS, "Closed tab with URL " + search + " - actual number of tabs " + std::to_string(windowCore->getTabCount()), 5000);
}
