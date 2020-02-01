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
	this->setEnabled(true);

	// main widget
	this->createMainWidget();

	// main window body
	this->fillMainWindow();

	// Control
	this->createCtrl();

	// Menu bar
	this->fillMenuBar();

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
	this->createTabs();

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

	// info
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

void main_window::MainWindow::fillMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create menus");
	this->mainWindowCore->fileMenu = new file_menu::FileMenu(this, this->menuBar(), "File", Qt::Key_F);
	this->mainWindowCore->editMenu = new edit_menu::EditMenu(this, this->menuBar(), "Edit", Qt::Key_E);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Connect signals");

	// When the file has been read, then show it on the screen
	connect(this->mainWindowCore->fileMenu, &file_menu::FileMenu::updateCenterWindowSignal, this, &main_window::MainWindow::setCenterWindow);

	// open tab action
	connect(this->mainWindowCore->fileMenu->openTabAction, &QAction::triggered, this->ctrl, &main_window_ctrl::MainWindowCtrl::openNewTab);

	// Close tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeTabSignal, this, &main_window::MainWindow::closeTab);

	// Move tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::moveCursorSignal, this, &main_window::MainWindow::moveCursor);
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::moveTabSignal, this, &main_window::MainWindow::moveTab);

	// Refresh URL tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::refreshUrlSignal, this, &main_window::MainWindow::refreshUrl);

	// Close window
	connect(this->mainWindowCore->fileMenu->exitAction, &QAction::triggered, this, &main_window::MainWindow::closeWindow);
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window::MainWindow::closeWindow);

	// show/hide menu bar
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::toggleShowMenubarSignal, this, &main_window::MainWindow::toggleShowMenubar);

	// Update info bar
	connect(this->mainWindowCore->tabs, &QTabWidget::currentChanged, this, &main_window::MainWindow::updateInfoSlot);
	connect(this->mainWindowCore->tabs, &QTabWidget::tabCloseRequested, this, &main_window::MainWindow::updateInfoSlot);

}

void main_window::MainWindow::createCtrl() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Create controller");

	// main window control class
	this->ctrl = new main_window_ctrl::MainWindowCtrl(this->mainWindowCore, this);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// Function connected to both currentChanged and tabCloseRequested signals
// In the case of currentChanged signal, index is the current tab
// In the case of tabCloseRequested signal, index is the closed tab
void main_window::MainWindow::updateInfoSlot(int index) {
	this->ctrl->updateInfo();
}
#pragma GCC diagnostic pop



void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->mainWindowCore->tabs->currentWidget());
	currentWidget->setText(str);
	currentWidget->repaint();
}

void main_window::MainWindow::moveCursor(int tabIndex) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move cursor to tab " << tabIndex);
	this->mainWindowCore->tabs->setCurrentIndex(tabIndex);
}

void main_window::MainWindow::moveTab(int tabIndex) {
	int tabIndexCurrent = this->mainWindowCore->tabs->currentIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move tab " << tabIndexCurrent << " to " << tabIndex);
	this->mainWindowCore->tabs->tabBar()->moveTab(tabIndexCurrent, tabIndex);
}

void main_window::MainWindow::refreshUrl(int tabIndex) {
	QWebEngineView * centerWindow = dynamic_cast<QWebEngineView *>(this->mainWindowCore->tabs->widget(tabIndex));
	QUrl currUrl = centerWindow->url();

	centerWindow->setUrl(QUrl(currUrl));
}

void main_window::MainWindow::closeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Close tab " << index);
	this->mainWindowCore->tabs->removeTab(index);
}

void main_window::MainWindow::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Close slot: exiting from the browser");
	this->close();
}

void main_window::MainWindow::toggleShowMenubar() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::keyPressEvent(QKeyEvent * event) {

	QMainWindow::keyPressEvent(event);

	this->ctrl->keyPressEvent(event);

	this->mainWindowCore->mainWidget->repaint();
}

void main_window::MainWindow::keyReleaseEvent(QKeyEvent * event) {

	QMainWindow::keyReleaseEvent(event);

	this->ctrl->keyReleaseEvent(event);

	this->mainWindowCore->mainWidget->repaint();
}
