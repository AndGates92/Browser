/**
 * @copyright
 * @file command_suite.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Command suite functions
 */

#include "macros.h"
#include "command_suite.h"
#include "launch_app.h"
#include "open_tab.h"
#include "move_tab.h"
#include "find_tab.h"
#include "reload_tab.h"
#include "scroll_tab.h"
#include "history_tab.h"
#include "open_file.h"

LOGGING_CONTEXT(commandSuiteOverall, commandSuite.overall, TYPE_LEVEL, INFO_VERBOSITY)

command_suite::CommandSuite::CommandSuite(const std::shared_ptr<base_factory::BaseFactory> & testFactory, const base_suite::BaseSuite::tests_container_t & testList) : base_suite::BaseSuite(testFactory, "Command suite", testList) {

}

command_suite::CommandSuite::~CommandSuite() {

	LOG_INFO(logger::info_level_e::ZERO, commandSuiteOverall,  "Command suite destructor");

}

void command_suite::CommandSuite::populate() {
	for (const bool & shortcut : { false, true } ) {
		launch_app::LaunchApp::create<launch_app::LaunchApp>(this->shared_from_this(), shortcut);
		open_tab::OpenTab::create<open_tab::OpenTab>(this->shared_from_this(), shortcut);
		find_tab::FindTab::create<find_tab::FindTab>(this->shared_from_this(), shortcut);
		move_tab::MoveTab::create<move_tab::MoveTab>(this->shared_from_this(), shortcut);
		reload_tab::ReloadTab::create<reload_tab::ReloadTab>(this->shared_from_this(), shortcut);
		scroll_tab::ScrollTab::create<scroll_tab::ScrollTab>(this->shared_from_this(), shortcut);
		history_tab::HistoryTab::create<history_tab::HistoryTab>(this->shared_from_this(), shortcut);
		open_file::OpenFile::create<open_file::OpenFile>(this->shared_from_this(), shortcut);
	}
}
