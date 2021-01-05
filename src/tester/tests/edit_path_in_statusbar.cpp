/**
 * @copyright
 * @file edit_path_in_statusbar.cpp
 * @author Andrea Gianarda
 * @date 16th January 2021
 * @brief Edit path in statusbar functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include "app/widgets/elided_label/elided_label.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/windows/main_window/window/core.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/cpp/cpp_operator.h"
#include "tester/tests/edit_path_in_statusbar.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(editPathInStatusbarOverall, editPathInStatusbar.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editPathInStatusbarTest, editPathInStatusbar.test, TYPE_LEVEL, INFO_VERBOSITY)

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

tester::test::EditPathInStatusbar::EditPathInStatusbar(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Edit path in statusbar", tester::test::open_tab_through_statusbar::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, editPathInStatusbarOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::EditPathInStatusbar::~EditPathInStatusbar() {
	LOG_INFO(app::logger::info_level_e::ZERO, editPathInStatusbarOverall,  "Test " << this->getName() << " destructor");
}

void tester::test::EditPathInStatusbar::testBody() {
	LOG_INFO(app::logger::info_level_e::ZERO, editPathInStatusbarTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	// Open tab
	const std::string filepath("tester_files/text");
	LOG_INFO(app::logger::info_level_e::ZERO, editPathInStatusbarTest, "Open new tab with file at " << filepath);
	this->openNewTab(filepath);

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
	const std::unique_ptr<app::main_window::statusbar::Bar> & statusbar = windowCore->bottomStatusBar;
	const std::unique_ptr<app::elided_label::ElidedLabel> & pageSourceText = statusbar->getContentPath();
	ASSERT((pageSourceText != nullptr), tester::shared::error_type_e::STATUSBAR, "Unable to find page source text widget in the status bar");
	if (pageSourceText != nullptr) {
		ASSERT((pageSourceText->text().isEmpty() == false), tester::shared::error_type_e::STATUSBAR, "Command text is expected not to be empty");
		ASSERT((pageSourceText->text().contains(QString::fromStdString(filepath)) == true), tester::shared::error_type_e::STATUSBAR, "Text in page source text \"" + pageSourceText->text().toStdString() + "\" doesn't contains the path to file \"" + filepath + "\"");
		const QPoint & pageSourceLabelPosition = pageSourceText->pos();
		const QRect & pageSourceLabelGeometry = pageSourceText->geometry();
		const QPoint mousePressPosition(pageSourceLabelPosition.x() + pageSourceLabelGeometry.width()/2, pageSourceLabelPosition.y() + pageSourceLabelGeometry.height()/2);
		const Qt::MouseButton mouseButton = Qt::LeftButton;
		LOG_INFO(app::logger::info_level_e::ZERO, editPathInStatusbarTest,  "Mouse button " << mouseButton << " has pressed at x:" << mousePressPosition.x() << " y:" << mousePressPosition.y());
		QTest::mousePress(statusbar.get(), mouseButton, Qt::NoModifier, mousePressPosition);

		const char searchChar = '/';
		std::size_t slashPos = filepath.find(searchChar);
		// Substract one not to delete the search character
		const std::size_t noCharToDelete = filepath.size() - slashPos - 1;
		for (std::size_t cnt = 0; cnt < noCharToDelete; cnt++) {
			tester::base::Test::sendKeyClickToFocus(Qt::Key_Backspace);
		}
		// Complete search
		const std::string filenameToOpen("assembly");
		tester::base::Test::sendKeyClicksToFocus(filenameToOpen);
		std::string editedPath(filepath, 0, (slashPos+1));
		editedPath.append(filenameToOpen);
		ASSERT((pageSourceText->text().contains(QString::fromStdString(editedPath)) == true), tester::shared::error_type_e::STATUSBAR, "Text in page source label \"" + pageSourceText->text().toStdString() + "\" doesn't contains string with edits \"" + editedPath + "\"");
		tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);

		this->waitForTabOpened();
		const int expectedNumberOfTabAfterEditingPath = 1;
		this->checkCurrentTab(editedPath, expectedNumberOfTabAfterEditingPath);

		// This should open a second tab
		tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);

		this->waitForTabOpened();
		const int expectedNumberOfTabAfterEditingCommand = 2;
		this->checkCurrentTab(search, expectedNumberOfTabAfterEditingCommand);
	}
}
