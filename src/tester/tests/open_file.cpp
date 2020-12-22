/**
 * @copyright
 * @file open_file.cpp
 * @author Andrea Gianarda
 * @date 12th October 2020
 * @brief Open file functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include <sstream>
#include <string>

#include "app/windows/main_window/window/core.h"
#include "app/windows/main_window/popup/popup_container.h"
#include "app/windows/main_window/popup/open_popup.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/cpp/cpp_operator.h"
#include "tester/tests/open_file.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(openFileOverall, openFile.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openFileTest, openFile.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace open_file {

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

tester::test::OpenFile::OpenFile(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts) : tester::base::CommandTest(testSuite, "Open file", tester::test::open_file::jsonFileFullPath, useShortcuts) {
	LOG_INFO(app::logger::info_level_e::ZERO, openFileOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::OpenFile::~OpenFile() {
	LOG_INFO(app::logger::info_level_e::ZERO, openFileOverall,  "Test " << this->getName() << " destructor");
}

void tester::test::OpenFile::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, openFileTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	const std::string openCommandName("open file");
	this->executeCommand(openCommandName, std::string());

	const std::shared_ptr<app::main_window::popup::PopupContainer> & popupContainer = this->windowWrapper->getPopupContainer();
	ASSERT((popupContainer != nullptr), tester::shared::error_type_e::POPUP, "Popup container pointer is null");
	std::shared_ptr<app::main_window::popup::OpenPopup> openFilePopup = popupContainer->getOpenFilePopup();
	ASSERT((openFilePopup != nullptr), tester::shared::error_type_e::POPUP, "Open file popup pointer is null");
	std::stringstream openFilePopupAddress;
	openFilePopupAddress << openFilePopup.get();
	std::shared_ptr<app::base::popup::PopupBase> currentPopupWidget = popupContainer->getCurrentWidget();
	ASSERT((currentPopupWidget != nullptr), tester::shared::error_type_e::POPUP, "Current popup widget pointer is null");
	std::stringstream currentPopupWidgetAddress;
	currentPopupWidgetAddress << currentPopupWidget.get();
	ASSERT((openFilePopup == currentPopupWidget), tester::shared::error_type_e::POPUP, "Open file popup pointer address " + openFilePopupAddress.str() + " doesn't match current popup widget " + currentPopupWidgetAddress.str());

	if (openFilePopup != nullptr) {
		WAIT_FOR_CONDITION((openFilePopup->isVisible() == true), tester::shared::error_type_e::POPUP, "Open file popup is not visible even though command " + openCommandName + " was executed.", 5000);

		ASSERT((windowCore->getTabCount() == 0), tester::shared::error_type_e::TABS, "No tab opened but actual number of tabs is " + std::to_string(windowCore->getTabCount()));

		// Try to type text while not in insert mode
		const std::string dummyText("aaaaaa");
		tester::test::OpenFile::sendKeyClicksToFocus(dummyText);
		const std::string initialFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((initialFilePath.empty() == true), tester::shared::error_type_e::POPUP, "Typed filepath is expected to be empty because the open file popup is not in insert mode instead it has the following text " + initialFilePath);

		// Enable insert mode
		tester::test::OpenFile::sendKeyEventToFocus(QTest::KeyAction::Click, 'i');

		// Open file
		const std::string filename("Makefile");
		tester::test::OpenFile::sendKeyClicksToFocus(filename);
		const std::string typedFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((typedFilePath.compare(filename) == 0), tester::shared::error_type_e::POPUP, "Typed filepath " + typedFilePath + " doesn't match expected filepath " + filename);

		// Open file
		if (this->commandSentThroughShortcuts() == true) {
			// Remove focus from QLineEdit
			tester::test::OpenFile::sendKeyClickToFocus(Qt::Key_Escape);
			tester::test::OpenFile::sendKeyEventToFocus(QTest::KeyAction::Click, 'o');
		} else {
			// Press enter while focus is still on the QLineEdit opens the file
			tester::test::OpenFile::sendKeyClickToFocus(Qt::Key_Enter);
		}

		ASSERT((windowCore->getTabCount() == 1), tester::shared::error_type_e::TABS, "Opened file " + filename + " in tab - actual number of tabs " + std::to_string(windowCore->getTabCount()));
		ASSERT((openFilePopup->isVisible() == false), tester::shared::error_type_e::POPUP, "Open file popup is visible even though file " + filename + " was opened.");

		const std::string textInStatusBar = windowCore->bottomStatusBar->getContentPathText().toStdString();
		const bool foundFilename = (textInStatusBar.find(filename) != std::string::npos);
		const std::string filetype("file:");
		const bool foundFiletype = (textInStatusBar.find(filetype) != std::string::npos);

		ASSERT((foundFilename == true), tester::shared::error_type_e::STATUSBAR, "Text in statusbar " + textInStatusBar + " is missing the filename " + filename);
		ASSERT((foundFiletype == true), tester::shared::error_type_e::STATUSBAR, "Text in statusbar " + textInStatusBar + " is missing the filetype " + filetype);
	}

}
