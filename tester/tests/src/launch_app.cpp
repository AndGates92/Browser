/**
 * @copyright
 * @file launch_app.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Launch app functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include <QtTest/QTest>

#include "global_enums.h"
#include "logging_macros.h"
#include "launch_app.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(launchAppOverall, "launchApp.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(launchAppTest, "launchApp.test", MSG_TYPE_LEVEL)

launch_app::LaunchApp::LaunchApp(const std::shared_ptr<base_suite::BaseSuite> & testSuite) : base_test::BaseTest(testSuite, "Launch app and exit") {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppOverall,  "Creating test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

}

launch_app::LaunchApp::~LaunchApp() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppOverall,  "Test " << QString::fromStdString(this->getName()) << " destructor");
}

void launch_app::LaunchApp::testBody() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppTest,  "Starting test " << QString::fromStdString(this->getName()) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	ASSERT((this->window->getWindow()->isHidden() == false), test_enums::error_type_e::SHORTCUT, "Window is not active at te start of the test");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, launchAppTest,  "Press Q");

	const std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> & windowCtrl =  this->window->getWindow()->getCtrl();
	QTest::keyClicks(windowCtrl.get(), ":quit");
	QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);

	ASSERT((this->window->getWindow()->isHidden() == true), test_enums::error_type_e::SHORTCUT, "Window is still active even though key Q was pressed");
}
