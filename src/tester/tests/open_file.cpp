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

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "tester/tests/open_file.h"
#include "tester/base/suite.h"

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

	const std::unique_ptr<app::main_window::window::CtrlWrapper> & windowCtrl =  this->windowWrapper->getWindowCtrl();
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
		ASSERT((openFilePopup->isVisible() == true), tester::shared::error_type_e::POPUP, "Open file popup is not visible even though command " + openCommandName + " was executed.");

		ASSERT((windowCore->getTabCount() == 0), tester::shared::error_type_e::TABS, "No tab opened but actual number of tabs is " + std::to_string(windowCore->getTabCount()));

		// Try to type text while not in insert mode
		const std::string dummyText("aaaaaa");
		QTest::keyClicks(openFilePopup.get(), QString::fromStdString(dummyText));
		QApplication::processEvents(QEventLoop::AllEvents);
		const std::string initialFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((initialFilePath.empty() == true), tester::shared::error_type_e::POPUP, "Typed filepath is expected to be empty because the open file popup is not in insert mode instead it has the following text " + initialFilePath);

		// Enable insert mode
		QTest::keyEvent(QTest::KeyAction::Click, openFilePopup.get(), 'i');
		QApplication::processEvents(QEventLoop::AllEvents);

		// Open file
		const std::string filename("Makefile");
		QTest::keyClicks(openFilePopup.get(), QString::fromStdString(filename));
		QApplication::processEvents(QEventLoop::AllEvents);
		const std::string typedFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((typedFilePath.compare(filename) == 0), tester::shared::error_type_e::POPUP, "Typed filepath " + typedFilePath + " doesn't match expected filepath " + filename);

		if (this->commandSentThroughShortcuts() == true) {
			QTest::keyClick(windowCtrl.get(), Qt::Key_Escape);
			QTest::keyEvent(QTest::KeyAction::Click, openFilePopup.get(), 'o');
		} else {
			QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);
		}
		QApplication::processEvents(QEventLoop::AllEvents);

		ASSERT((windowCore->getTabCount() == 1), tester::shared::error_type_e::TABS, "Opened file " + filename + " in tab - actual number of tabs " + std::to_string(windowCore->getTabCount()));
		ASSERT((openFilePopup->isVisible() == false), tester::shared::error_type_e::POPUP, "Open file popup is visible even though file " + filename + " was opened.");

		const std::string textInStatusBar = windowCore->bottomStatusBar->getUserInputText().toStdString();
		const bool foundFilename = (textInStatusBar.find(filename) != std::string::npos);
		const std::string filetype("file:");
		const bool foundFiletype = (textInStatusBar.find(filetype) != std::string::npos);

		ASSERT((foundFilename == true), tester::shared::error_type_e::STATUSBAR, "Text in statusbar " + textInStatusBar + " is missing the filename " + filename);
		ASSERT((foundFiletype == true), tester::shared::error_type_e::STATUSBAR, "Text in statusbar " + textInStatusBar + " is missing the filetype " + filetype);
	}

}
