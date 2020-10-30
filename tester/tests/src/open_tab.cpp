/**
 * @copyright
 * @file open_tab.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Open tab functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "global_enums.h"
#include "macros.h"
#include "qt_operator.h"
#include "stl_helper.h"
#include "open_tab.h"
#include "base_suite.h"

LOGGING_CONTEXT(openTabOverall, openTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openTabTest, openTab.test, TYPE_LEVEL, INFO_VERBOSITY)

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

open_tab::OpenTab::OpenTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Open tab", open_tab::jsonFileFullPath, useShortcuts) {
	LOG_INFO(logger::info_level_e::ZERO, openTabOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

open_tab::OpenTab::~OpenTab() {
	LOG_INFO(logger::info_level_e::ZERO, openTabOverall,  "Test " << this->getName() << " destructor");
}

void open_tab::OpenTab::testBody() {
	LOG_INFO(logger::info_level_e::ZERO, openTabTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string website("website.com");
	LOG_INFO(logger::info_level_e::ZERO, openTabTest, "Open new tab with website " << website);
	this->openNewTab(website);

	const std::string closeCommandName("close tab");
	this->executeCommand(closeCommandName, std::string());

	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();
	WAIT_FOR_CONDITION((windowCore->getTabCount() == 0), test_enums::error_type_e::TABS, "Closed tab with URL " + website + " - actual number of tabs " + std::to_string(windowCore->getTabCount()), 5000);
}
