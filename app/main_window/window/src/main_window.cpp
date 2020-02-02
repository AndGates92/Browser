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
#include <qt5/QtWidgets/QGridLayout>
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
#include "tab_widget.h"
#include "command_menu.h"
#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(main_window_core::MainWindowCore * core, QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), mainWindowCore(core) {

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
	this->mainWindowCore->mainWidget = new QWidget(this);
	this->mainWindowCore->mainWidget->setAttribute(Qt::WA_DeleteOnClose);
	// Disable widget resizing
	this->mainWindowCore->mainWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->mainWindowCore->mainWidget->setFocusPolicy(Qt::StrongFocus);

	this->mainWindowCore->mainWidget->setStyleSheet(
		"QWidget {"
			"background: brown; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);
	this->setCentralWidget(this->mainWindowCore->mainWidget);
}

QLabel * main_window::MainWindow::newWindowLabel() {
	QLabel * label = new QLabel("", this);
	label->setAttribute(Qt::WA_DeleteOnClose);
	label->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	label->setFixedHeight(main_window::labelHeight);
	label->setTextFormat(Qt::PlainText);
	// Disable widget resizing
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	label->setStyleSheet(
		"QLabel {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border-right: 1px solid black; "
			"border-left: 1px solid black; "
		"}"
	);

	return label;
}

void main_window::MainWindow::fillMainWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Fill main window");

	// Customize MainWidget
	// Tabs
	this->createTabs();

	// Menu bar
	this->createTopMenuBar();

	// user input
	this->mainWindowCore->userInputText = this->newWindowLabel();
	this->mainWindowCore->userInputText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
	this->mainWindowCore->userInputText->setFocus(Qt::OtherFocusReason);

	// website URL
	this->mainWindowCore->websiteText = this->newWindowLabel();
	this->mainWindowCore->websiteText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// info
	this->mainWindowCore->infoText = this->newWindowLabel();
	this->mainWindowCore->infoText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// command menu
	this->mainWindowCore->cmdMenu = new command_menu::CommandMenu(this);
	this->mainWindowCore->cmdMenu->setVisible(false);
}

void main_window::MainWindow::createTabs() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create tabs");

	this->mainWindowCore->tabs = new tab_widget::TabWidget(this->mainWindowCore->mainWidget);
	// Disable widget resizing
	this->mainWindowCore->tabs->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	this->mainWindowCore->tabs->setStyleSheet(
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

	this->mainWindowCore->topMenuBar = new main_window_menu_bar::MainWindowMenuBar(this);

	// set menu bar of the main window
	this->setMenuBar(this->mainWindowCore->topMenuBar);
}


void main_window::MainWindow::mainWindowLayout() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Define layout");

	// Layout
	// -------------------------------------------------
	// |                     <tabs>                    |
	// |                    <content>                  |
	// | <user text> |      <website>     |   <info>   |
	// -------------------------------------------------

	QGridLayout * layout = new QGridLayout(this->mainWindowCore->mainWidget);

	// tabs
	int tabsRowSpan = 20;
	int tabsColumnSpan = 10;
	int tabsFromRow = 0;
	int tabsFromColumn = 0;
	layout->addWidget(this->mainWindowCore->tabs, tabsFromRow, tabsFromColumn, tabsRowSpan, tabsColumnSpan);

	// user input text
	int userTextRowSpan = 1;
	int userTextColumnSpan = 3;
	int userTextFromRow = tabsRowSpan;
	int userTextFromColumn = 0;
	layout->addWidget(this->mainWindowCore->userInputText, userTextFromRow, userTextFromColumn, userTextRowSpan, userTextColumnSpan);

	// website URL
	int websiteRowSpan = 1;
	int websiteColumnSpan = 5;
	int websiteFromRow = tabsRowSpan;
	int websiteFromColumn = userTextFromColumn + userTextColumnSpan;
	layout->addWidget(this->mainWindowCore->websiteText, websiteFromRow, websiteFromColumn, websiteRowSpan, websiteColumnSpan);

	// info
	int infoRowSpan = 1;
	int infoColumnSpan = 2;
	int infoFromRow = tabsRowSpan;
	int infoFromColumn = websiteFromColumn + websiteColumnSpan;
	layout->addWidget(this->mainWindowCore->infoText, infoFromRow, infoFromColumn, infoRowSpan, infoColumnSpan);

	// command menu
	int cmdMenuRowSpan = 3;
	int cmdMenuColumnSpan = tabsColumnSpan;
	int cmdMenuFromRow = tabsRowSpan - cmdMenuRowSpan;
	int cmdMenuFromColumn = 0;
	layout->addWidget(this->mainWindowCore->cmdMenu, cmdMenuFromRow, cmdMenuFromColumn, cmdMenuRowSpan, cmdMenuColumnSpan);


	layout->setHorizontalSpacing(main_window::horizontalWidgetSpacing);
	layout->setVerticalSpacing(main_window::verticalWidgetSpacing);
	layout->setContentsMargins(main_window::leftMargin, main_window::topMargin, main_window::rightMargin, main_window::bottomMargin);

	this->mainWindowCore->mainWidget->setLayout(layout);
}

void main_window::MainWindow::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Connect signals");

	// When the file has been read, then show it on the screen
	connect(this->mainWindowCore->topMenuBar->getFileMenu(), &file_menu::FileMenu::updateCenterWindowSignal, this, &main_window::MainWindow::setCenterWindow);

	// Close window
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window::MainWindow::closeWindow);

}

void main_window::MainWindow::createCtrl() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create controller");

	// main window control class
	this->ctrl = new main_window_ctrl::MainWindowCtrl(this->mainWindowCore, this);
}




void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->mainWindowCore->tabs->currentWidget());
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

	this->mainWindowCore->mainWidget->repaint();
}

void main_window::MainWindow::keyReleaseEvent(QKeyEvent * event) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	QMainWindow::keyReleaseEvent(event);

	this->ctrl->keyReleaseEvent(event);

	this->mainWindowCore->mainWidget->repaint();
}
