/**
 * @copyright
 * @file history_tab.cpp
 * @author Andrea Gianarda
 * @date 23th October 2020
 * @brief History tab test functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/windows/main_window/shared/constants.h"
#include "tester/tests/history_tab.h"
#include "tester/base/suite.h"

LOGGING_CONTEXT(historyTabOverall, historyTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(historyTabTest, historyTab.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace history_tab {

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

tester::test::HistoryTab::HistoryTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "History tab", tester::test::history_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, historyTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::HistoryTab::~HistoryTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, historyTabOverall,  "Test " << this->getName() << " destructor");
}

void tester::test::HistoryTab::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, historyTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string https(app::shared::https.toStdString());
	const std::string www(app::shared::www.toStdString());

	// Create 1 tabs and make 2 searches
	const std::string search0("test0");
	LOG_INFO(app::logger::info_level_e::ZERO, historyTabTest, "Open new tab searching " << search0);
	this->openNewTab(search0);
	const std::string authorityUrl0 = www + app::main_window::defaultSearchEngine.arg(QString::fromStdString(search0)).toStdString();
	const std::string url0 = https + authorityUrl0;

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though it should have loaded website " + url0);
	if (currentTab != nullptr) {

		const std::string searchCommandName("search tab");
		const std::string search1("test1");
		LOG_INFO(app::logger::info_level_e::ZERO, historyTabTest, "Search in tab " << search1);
		this->makeSearchInTab(searchCommandName, search1);
		const std::string authorityUrl1 = www + app::main_window::defaultSearchEngine.arg(QString::fromStdString(search1)).toStdString();
		const std::string url1 = https + authorityUrl1;

		const std::string historyPrevCommandName("history previous");
		this->executeCommand(historyPrevCommandName, std::string());

		const QUrl & tabUrlAfterHistoryBack = currentTab->getPage()->url();
	
		WAIT_FOR_CONDITION((authorityUrl0.compare(tabUrlAfterHistoryBack.authority().toStdString()) == 0), tester::shared::error_type_e::TABS, "Current URL authority " + tabUrlAfterHistoryBack.authority().toStdString() + " doesn't match expected authority " + authorityUrl0, 5000);

		const std::string historyNextCommandName("history next");
		this->executeCommand(historyNextCommandName, std::string());

		const QUrl & tabUrlAfterHistoryForward = currentTab->getPage()->url();
	
		WAIT_FOR_CONDITION((authorityUrl1.compare(tabUrlAfterHistoryForward.authority().toStdString()) == 0), tester::shared::error_type_e::TABS, "Current URL authority " + tabUrlAfterHistoryForward.authority().toStdString() + " doesn't match expected authority " + authorityUrl1, 5000);

	}
}
