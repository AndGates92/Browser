/**
 * @copyright
 * @file open_tab.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Open tab functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "global_enums.h"
#include "logging_macros.h"
#include "qt_operator.h"
#include "stl_helper.h"
#include "open_tab.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(openTabOverall, "openTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openTabTest, "openTab.test", MSG_TYPE_LEVEL)

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

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openTabOverall,  "Creating test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

}

open_tab::OpenTab::~OpenTab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openTabOverall,  "Test " << QString::fromStdString(this->getName()) << " destructor");
}

void open_tab::OpenTab::testBody() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openTabTest,  "Starting test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();

	const std::string website("website.com");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openTabTest, "Open new tab with website " << website);
	this->openNewTab(website);

	const std::string closeCommandName("close tab");
	this->executeCommand(closeCommandName, std::string());

	WAIT_FOR_CONDITION((windowCore->getTabCount() == 0), test_enums::error_type_e::TABS, "Closed tab with URL " + website + " - actual number of tabs " + std::to_string(windowCore->getTabCount()), 5000);
}
