/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QShortcut>
#include <qt5/QtWidgets/QTabBar>
#include <qt5/QtWebEngineWidgets/QWebEngineView>
#include <qt5/QtCore/QUrl>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "main_window_menu_bar.h"
#include "main_window_status_bar.h"
#include "tab_widget.h"
#include "command_menu.h"
#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(main_window_core::MainWindowCore * core, QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), main_window_base::MainWindowBase(core) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Main window constructor");

	this->setFocusPolicy(Qt::StrongFocus);
	this->setFocus(Qt::ActiveWindowFocusReason);
	this->setEnabled(true);

	// main widget
	this->createMainWidget();

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

	setWindowTitle(tr("Browser"));

	this->setStyleSheet(
		"QMainWindow {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);

	this->setAttribute(Qt::WA_DeleteOnClose);

	QSize winSize(320,400);
	this->resize(winSize);

	// Update info label
	this->ctrl->updateInfo();
}

main_window::MainWindow::~MainWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Main window destructor");

	delete this->ctrl;
}

void main_window::MainWindow::createMainWidget() {
	this->windowCore->mainWidget = new QWidget(this);
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
	this->createTabs();

	// Menu bar
	this->createTopMenuBar();

	// Status bar
	this->createBottomStatusBar();

	// command menu
	this->windowCore->cmdMenu = new command_menu::CommandMenu(this);
	this->windowCore->cmdMenu->setVisible(false);
}

void main_window::MainWindow::createTabs() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create tabs");

	this->windowCore->tabs = new tab_widget::TabWidget(this->windowCore->mainWidget);
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

void main_window::MainWindow::createTopMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create top menu bar");

	this->windowCore->topMenuBar = new main_window_menu_bar::MainWindowMenuBar(this);

	// set menu bar of the main window
	this->setMenuBar(this->windowCore->topMenuBar);
}

void main_window::MainWindow::createBottomStatusBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create top menu bar");

	this->windowCore->bottomStatusBar = new main_window_status_bar::MainWindowStatusBar(this);
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

	// When the file has been read, then show it on the screen
	connect(this->windowCore->topMenuBar->getFileMenu(), &file_menu::FileMenu::updateCenterWindowSignal, this, &main_window::MainWindow::setCenterWindow);

	// Close window
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window::MainWindow::closeWindow);

}

void main_window::MainWindow::createCtrl() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create controller");

	// main window control class
	this->ctrl = new main_window_ctrl::MainWindowCtrl(this->windowCore, this);
}




void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->windowCore->tabs->currentWidget());
	currentWidget->setText(str);
	currentWidget->repaint();
}

void main_window::MainWindow::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Close main window");
	bool success = this->close();
	Q_ASSERT_X(success, "main window close", "Main window close request was not handled properly");
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
