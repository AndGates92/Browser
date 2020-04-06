/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QTabBar>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "main_window_menu_bar.h"
#include "main_window_status_bar.h"
#include "main_window_tab_widget.h"
#include "command_menu.h"
#include "logging_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), main_window_base::MainWindowBase(QSharedPointer<main_window_core::MainWindowCore>(new main_window_core::MainWindowCore(this))) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Main window constructor");

	this->setFocusPolicy(Qt::StrongFocus);
	this->setFocus(Qt::ActiveWindowFocusReason);
	this->setEnabled(true);

	// main widget
	this->customizeMainWidget();

	// main window body
	this->fillMainWindow();

	// Control
	this->createCtrl();

	// Connect signals and slots
	this->connectSignals();

	// main window layout
	this->mainWindowLayout();

	QString msg(tr("status bar message"));
	this->statusBar()->showMessage(msg);
	this->statusBar()->hide();

	this->setWindowTitle(tr("Browser"));

	this->setStyleSheet(
		"QMainWindow {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);

	this->setAttribute(Qt::WA_DeleteOnClose);

	const QSize winSize(320,400);
	this->resize(winSize);

	// Update info label - as no tabs in the window, then updateInfo must be explicitely called
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	this->ctrl->updateInfo(tabIndex);
}

main_window::MainWindow::~MainWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Main window destructor");

	delete this->ctrl;
}

void main_window::MainWindow::customizeMainWidget() {
	this->windowCore->mainWidget->setAttribute(Qt::WA_DeleteOnClose);
	// Disable widget resizing
	this->windowCore->mainWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->windowCore->mainWidget->setFocusPolicy(Qt::StrongFocus);

	this->windowCore->mainWidget->setStyleSheet(
		"QWidget {"
			"background: brown; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);
	this->setCentralWidget(this->windowCore->mainWidget);
}

void main_window::MainWindow::fillMainWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Fill main window");

	// Customize MainWidget
	// Tabs
	this->customizeTabs();

	// Menu bar
	this->customizeTopMenuBar();

	// Status bar
	this->customizeBottomStatusBar();

	// command menu
	this->windowCore->cmdMenu->setVisible(false);
}

void main_window::MainWindow::customizeTabs() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Customize tabs");

	// Disable widget resizing
	this->windowCore->tabs->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	this->windowCore->tabs->setStyleSheet(
		"QTabBar::tab {"
			"background: gray; "
			"color: white; "
			"text-align: center; "
		"}"
		"QTabBar::tab::selected {"
			"background: black; "
		"}"
	);

}

void main_window::MainWindow::customizeTopMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Customize top menu bar");

	// set menu bar of the main window
	this->setMenuBar(this->windowCore->topMenuBar);
}

void main_window::MainWindow::customizeBottomStatusBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Customize top menu bar");

}

void main_window::MainWindow::mainWindowLayout() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Define layout");

	// Layout
	// -------------------------------------------------
	// |                     <tabs>                    |
	// |                    <content>                  |
	// |                   <statusbar>                 |
	// -------------------------------------------------

	QVBoxLayout * layout = new QVBoxLayout(this->windowCore->mainWidget);

	// tabs
	layout->addWidget(this->windowCore->tabs);

	// command menu
	layout->addWidget(this->windowCore->cmdMenu);

	// status bar
	layout->addWidget(this->windowCore->bottomStatusBar);

	layout->setSpacing(main_window::verticalWidgetSpacing);
	layout->setContentsMargins(main_window::leftMargin, main_window::topMargin, main_window::rightMargin, main_window::bottomMargin);

	this->windowCore->mainWidget->setLayout(layout);
}

void main_window::MainWindow::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Connect signals");

	// Close window
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window::MainWindow::closeWindow);

}

void main_window::MainWindow::createCtrl() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create controller");

	// main window control class
	this->ctrl = new main_window_ctrl::MainWindowCtrl(this->windowCore, this);
}

void main_window::MainWindow::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Close main window");
	const bool success = this->close();
	Q_ASSERT_X(success, "main window close success check", "Main window close request was not handled properly");
}

void main_window::MainWindow::keyPressEvent(QKeyEvent * event) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	QMainWindow::keyPressEvent(event);

	this->ctrl->keyPressEvent(event);

	this->windowCore->mainWidget->repaint();
}

void main_window::MainWindow::keyReleaseEvent(QKeyEvent * event) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	QMainWindow::keyReleaseEvent(event);

	this->ctrl->keyReleaseEvent(event);

	this->windowCore->mainWidget->repaint();
}
