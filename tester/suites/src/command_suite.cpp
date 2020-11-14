/**
 * @copyright
 * @file command_suite.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Command suite functions
 */

#include "utility/logger/include/macros.h"
#include "suites/include/command_suite.h"
#include "tests/include/launch_app.h"
#include "tests/include/open_tab.h"
#include "tests/include/move_tab.h"
#include "tests/include/find_tab.h"
#include "tests/include/reload_tab.h"
#include "tests/include/scroll_tab.h"
#include "tests/include/history_tab.h"
#include "tests/include/open_file.h"

LOGGING_CONTEXT(commandSuiteOverall, commandSuite.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::suite::CommandSuite::CommandSuite(const std::shared_ptr<tester::base::Factory> & testFactory, const tester::base::Suite::tests_container_t & testList) : tester::base::Suite(testFactory, "Command suite", testList) {

}

tester::suite::CommandSuite::~CommandSuite() {

	LOG_INFO(app::logger::info_level_e::ZERO, commandSuiteOverall,  "Command suite destructor");

}

void tester::suite::CommandSuite::populate() {
	for (const bool & shortcut : { false, true } ) {
		tester::test::LaunchApp::create<tester::test::LaunchApp>(this->shared_from_this(), shortcut);
		tester::test::OpenTab::create<tester::test::OpenTab>(this->shared_from_this(), shortcut);
		tester::test::FindTab::create<tester::test::FindTab>(this->shared_from_this(), shortcut);
		tester::test::MoveTab::create<tester::test::MoveTab>(this->shared_from_this(), shortcut);
		tester::test::ReloadTab::create<tester::test::ReloadTab>(this->shared_from_this(), shortcut);
		tester::test::ScrollTab::create<tester::test::ScrollTab>(this->shared_from_this(), shortcut);
		tester::test::HistoryTab::create<tester::test::HistoryTab>(this->shared_from_this(), shortcut);
		tester::test::OpenFile::create<tester::test::OpenFile>(this->shared_from_this(), shortcut);
	}
}
