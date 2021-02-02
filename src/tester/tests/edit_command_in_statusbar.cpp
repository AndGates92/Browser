/**
 * @copyright
 * @file edit_command_in_statusbar.cpp
 * @author Andrea Gianarda
 * @date 08th January 2021
 * @brief Edit command in statusbar functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/widgets/text/line_edit.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/windows/main_window/window/core.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/cpp/cpp_operator.h"
#include "tester/tests/edit_command_in_statusbar.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(editCommandInStatusbarOverall, editCommandInStatusbar.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editCommandInStatusbarTest, editCommandInStatusbar.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace open_tab_through_statusbar {

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

tester::test::EditCommandInStatusbar::EditCommandInStatusbar(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Edit command in statusbar", tester::test::open_tab_through_statusbar::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, editCommandInStatusbarOverall, "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::EditCommandInStatusbar::~EditCommandInStatusbar() {
	LOG_INFO(app::logger::info_level_e::ZERO, editCommandInStatusbarOverall, "Test " << this->getName() << " destructor");
}

void tester::test::EditCommandInStatusbar::testBody() {
	LOG_INFO(app::logger::info_level_e::ZERO, editCommandInStatusbarTest, "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	// Open tab
	const std::string website("website.com");
	LOG_INFO(app::logger::info_level_e::ZERO, editCommandInStatusbarTest, "Open new tab with website " << website);
	this->openNewTab(website);

	// Start opening a second tab but do not execute the command
	const std::string openCommandName("open new tab");
	const std::string search("testing");
	this->executeCommand(openCommandName, search, false);

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const app::main_window::state_e & currentState = windowCore->getMainWindowState();
	const app::main_window::state_e expectedState = app::main_window::state_e::OPEN_TAB;
	ASSERT((currentState == expectedState), tester::shared::error_type_e::WINDOW, "Expected window state " + expectedState + " doesn't match current window state " + currentState);

	// Emulate click on the command in the status bar
	const int expectedNumberOfTabAfterStartTypingCommand = 1;
	ASSERT((windowCore->getTabCount() == expectedNumberOfTabAfterStartTypingCommand), tester::shared::error_type_e::TABS, "Number of tab mismatch after start typing command " + openCommandName + " by editing status bar command - actual number of tabs " + std::to_string(windowCore->getTabCount()) + " expected number of tabs is " + std::to_string(expectedNumberOfTabAfterStartTypingCommand));
	const auto & statusbar = windowCore->bottomStatusBar;
	const auto & commandText = statusbar->getUserInput();
	ASSERT((commandText != nullptr), tester::shared::error_type_e::STATUSBAR, "Unable to find command text widget in the status bar");
	if (commandText != nullptr) {
		ASSERT((commandText->text().isEmpty() == false), tester::shared::error_type_e::STATUSBAR, "Command text is expected not to be empty");
		ASSERT((commandText->text().contains(QString::fromStdString(search)) == true), tester::shared::error_type_e::STATUSBAR, "Text in command text \"" + commandText->text().toStdString() + "\" doesn't contains search string \"" + search + "\"");
		const QPoint & commandLabelPosition = commandText->pos();
		const QRect & commandLabelGeometry = commandText->geometry();
		const QPoint mousePressPosition(commandLabelPosition.x() + commandLabelGeometry.width()/2, commandLabelPosition.y() + commandLabelGeometry.height()/2);
		const Qt::MouseButton mouseButton = Qt::LeftButton;
		LOG_INFO(app::logger::info_level_e::ZERO, editCommandInStatusbarTest, "Mouse button " << mouseButton << " has pressed at x:" << mousePressPosition.x() << " y:" << mousePressPosition.y());
		QTest::mousePress(statusbar.get(), mouseButton, Qt::NoModifier, mousePressPosition);

		// Complete search
		const std::string endSearch(" my browser");
		tester::base::Test::sendKeyClicksToFocus(endSearch);
		const std::string fullSearch(search + endSearch);
		ASSERT((commandText->text().contains(QString::fromStdString(fullSearch)) == true), tester::shared::error_type_e::STATUSBAR, "Text in command text \"" + commandText->text().toStdString() + "\" doesn't contains search string \"" + fullSearch + "\"");
		const app::main_window::state_e & currentStateAfterEndingTypingCommand = windowCore->getMainWindowState();
		ASSERT((currentStateAfterEndingTypingCommand == expectedState), tester::shared::error_type_e::WINDOW, "Expected window state " + expectedState + " doesn't match current window state " + currentStateAfterEndingTypingCommand);

		tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);

		this->waitForTabOpened();
		const int expectedNumberOfTabAfterEditingStatusbar = 2;
		this->checkCurrentTab(fullSearch, expectedNumberOfTabAfterEditingStatusbar);
	}
}
