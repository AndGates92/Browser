/**
 * @copyright
 * @file search_tab.cpp
 * @author Andrea Gianarda
 * @date 15th January 2021
 * @brief Search tab test functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/shared/constants.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/windows/main_window/window/core.h"
#include "tester/base/suite.h"
#include "tester/tests/search_tab.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(searchTabOverall, searchTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(searchTabTest, searchTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace search_tab {

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

tester::test::SearchTab::SearchTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Search tab", tester::test::search_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, searchTabOverall, "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::SearchTab::~SearchTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, searchTabOverall, "Test " << this->getName() << " destructor");
}

void tester::test::SearchTab::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, searchTabTest, "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string https(app::shared::https.toStdString());
	const std::string www(app::shared::www.toStdString());

	// Create 1 tabs and make 2 searches
	const std::string search0("test0");
	LOG_INFO(app::logger::info_level_e::ZERO, searchTabTest, "Open new tab searching " << search0);
	this->openNewTab(search0);
	const std::string authorityUrl0 = www + app::main_window::defaultSearchEngine.arg(QString::fromStdString(search0)).toStdString();
	const std::string url0 = https + authorityUrl0;

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though it should have loaded website " + url0);
	if (currentTab != nullptr) {

		const std::string searchCommandName("search tab");
		const std::string search1("test1");
		LOG_INFO(app::logger::info_level_e::ZERO, searchTabTest, "Search in tab " << search1);
		this->makeSearchInTab(searchCommandName, search1);

		const std::string editSearchCommandName("edit search tab");
		this->executeCommand(editSearchCommandName);
		const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
		const std::string initTextInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
		const app::main_window::state_e & currentState = windowCore->getMainWindowState();
		const std::string commandToText(this->commandNameToShownText(editSearchCommandName, (currentState == app::main_window::state_e::COMMAND)));
		std::string expectedText = std::string();
		expectedText.append(commandToText);
		expectedText.append(" ");
		expectedText.append(search1);
		ASSERT((initTextInLabel.compare(expectedText) == 0), tester::shared::error_type_e::STATUSBAR, "Expected text in the statusbar " + expectedText + " doesn't match current text in the statusbar " + initTextInLabel);

		const std::string search2(" the browser");
		expectedText.append(search2);
		QTest::KeyAction keyAction = QTest::KeyAction::Click;
		tester::base::CommandTest::sendKeyEventsToFocus(keyAction, search2);
		const std::string editedTextInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
		ASSERT((editedTextInLabel.compare(expectedText) == 0), tester::shared::error_type_e::STATUSBAR, "Expected text in the statusbar " + expectedText + " doesn't match current text in the statusbar " + editedTextInLabel);

		tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);

		const std::string fullSearch(search1 + search2);
		std::string expectedAuthority = app::main_window::defaultSearchEngine.arg(QString::fromStdString(fullSearch)).toStdString();
		const std::string pageSource = windowCore->bottomStatusBar->getContentPathText().toStdString();
		ASSERT((expectedAuthority.compare(pageSource) == 0), tester::shared::error_type_e::STATUSBAR, "Expected text in the statusbar " + expectedAuthority + " doesn't match current text in the statusbar " + pageSource);

	}
}
