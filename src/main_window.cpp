/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QShortcut>
#include <qt5/QtWidgets/QTabBar>
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
Q_LOGGING_CATEGORY(mainWindowSearch, "mainWindow.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	mainWindowState = main_window::MainWindow::state_e::IDLE;

	// main widget
	this->createMainWidget();

	// main window body
	this->fillMainWindow();

	// Menu bar
	this->fillMenuBar();

	// main window layout
	this->mainWindowLayout();

	// Shortcuts
	this->createShortcuts();

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

	QSize winSize(320,400);
	this->resize(winSize);
}


void main_window::MainWindow::createMainWidget() {
	this->mainWidget = new QWidget(this);
//	this->mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->mainWidget->setFocusPolicy(Qt::StrongFocus);

	this->mainWidget->setStyleSheet(
		"QWidget {"
			"background: brown; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);
	setCentralWidget(this->mainWidget);
}

QLabel * main_window::MainWindow::newWindowLabel() {
	QLabel * label = new QLabel("", this);
	label->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	label->setFixedHeight(main_window::labelHeight);
	label->setStyleSheet(
		"QLabel {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);

	return label;
}

void main_window::MainWindow::fillMainWindow() {
	// Customize MainWidget
	this->createTabs();

	// search
	this->searchText = this->newWindowLabel();
	this->searchText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	// website URL
	this->websiteText = this->newWindowLabel();
	this->websiteText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	// info
	this->infoText = this->newWindowLabel();
	this->infoText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// Emit signal to update info label
	int tabIndex = this->tabs->currentIndex();
	emit updateInfoSignal(tabIndex);
}

void main_window::MainWindow::createTabs() {
	this->tabs = new tab_widget::TabWidget(this->mainWidget);
	// size policy horintally and vertically to expanding
	this->tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	this->tabs->setStyleSheet(
		"QTabBar::tab {"
			"background: gray; "
			"color: white; "
			"text-align: center; "
		"}"
		"QTabBar::tab::selected {"
			"background: black; "
		"}"
	);

	connect(this->tabs, &QTabWidget::currentChanged, this, &main_window::MainWindow::updateInfoSlot);
	connect(this->tabs, &QTabWidget::tabCloseRequested, this, &main_window::MainWindow::updateInfoSlot);
	connect(this, &main_window::MainWindow::updateInfoSignal, this, &main_window::MainWindow::updateInfoSlot);
}

void main_window::MainWindow::mainWindowLayout() {
	// Layout
	// -------------------------------------------------
	// |                     <tabs>                    |
	// |                    <content>                  |
	// |  <search>   |      <website>     | <tab info> |
	// -------------------------------------------------

	QGridLayout * layout = new QGridLayout(this->mainWidget);
	int tabsRowSpan = 20;
	int tabsColumnSpan = 10;
	int tabsFromRow = 0;
	int tabsFromColumn = 0;
	layout->addWidget(this->tabs, tabsFromRow, tabsFromColumn, tabsRowSpan, tabsColumnSpan);
	int searchRowSpan = 1;
	int searchColumnSpan = 3;
	int searchFromRow = tabsRowSpan;
	int searchFromColumn = 0;
	layout->addWidget(this->searchText, searchFromRow, searchFromColumn, searchRowSpan, searchColumnSpan);
	int websiteRowSpan = 1;
	int websiteColumnSpan = 5;
	int websiteFromRow = tabsRowSpan;
	int websiteFromColumn = searchFromColumn + searchColumnSpan;
	layout->addWidget(this->websiteText, websiteFromRow, websiteFromColumn, websiteRowSpan, websiteColumnSpan);
	int infoRowSpan = 1;
	int infoColumnSpan = 2;
	int infoFromRow = tabsRowSpan;
	int infoFromColumn = websiteFromColumn + websiteColumnSpan;
	layout->addWidget(this->infoText, infoFromRow, infoFromColumn, infoRowSpan, infoColumnSpan);

	layout->setHorizontalSpacing(main_window::horizontalWidgetSpacing);
	layout->setVerticalSpacing(main_window::verticalWidgetSpacing);
	layout->setContentsMargins(main_window::leftMargin, main_window::topMargin, main_window::rightMargin, main_window::bottomMargin);

	this->mainWidget->setLayout(layout);
}

void main_window::MainWindow::fillMenuBar() {
	this->fileMenu = new file_menu::FileMenu(this, this->menuBar(), "File", Qt::Key_F);
	// When the file has been read, then show it on the screen
	connect(this->fileMenu, &file_menu::FileMenu::updateCenterWindow, this, &main_window::MainWindow::setCenterWindow);
	this->editMenu = new edit_menu::EditMenu(this, this->menuBar(), "Edit", Qt::Key_E);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::setAllMenuShortcutEnabledProperty(bool enabled) {
	this->fileMenu->setShortcutEnabledProperty(enabled);
	this->editMenu->setShortcutEnabledProperty(enabled);
}

void main_window::MainWindow::setAllWindowShortcutEnabledProperty(bool enabled) {
	this->toggleShowMenuBarKey->setEnabled(enabled);
	this->openNewTabKey->setEnabled(enabled);
	this->newSearchTabKey->setEnabled(enabled);
	this->closeTabKey->setEnabled(enabled);
}

void main_window::MainWindow::setAllShortcutEnabledProperty(bool enabled) {
	this->setAllMenuShortcutEnabledProperty(enabled);
	this->setAllWindowShortcutEnabledProperty(enabled);
}

void main_window::MainWindow::createShortcuts() {
	// m will hide/show the menu bar
	this->toggleShowMenuBarKey = new QShortcut(this);
	this->toggleShowMenuBarKey->setKey(Qt::Key_M);
	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window::MainWindow::toggleShowMenubarSlot);

	// o will open a new tab
	this->openNewTabKey = new QShortcut(this);
	this->openNewTabKey->setKey(Qt::Key_O);
	connect(this->openNewTabKey, &QShortcut::activated, this, &main_window::MainWindow::openNewTabSlot);

	// s will search on the current tab
	this->newSearchTabKey = new QShortcut(this);
	this->newSearchTabKey->setKey(Qt::Key_S);
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window::MainWindow::newSearchTabSlot);

	// c will close the current tab
	this->closeTabKey = new QShortcut(this);
	this->closeTabKey->setKey(Qt::Key_C);
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window::MainWindow::closeTabSlot);

}

void main_window::MainWindow::toggleShowMenubarSlot() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::closeTabSlot() {
//	this->setAllShortcutEnabledProperty(false);
//	mainWindowState = main_window::MainWindow::state_e::CLOSE_TAB;
	this->closeTab();
}

void main_window::MainWindow::closeTab() {
	int tabIndex = this->tabs->currentIndex();
	int tabCount = this->tabs->count();

	if (tabCount > 0) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Close tab " << tabIndex);
		this->tabs->removeTab(tabIndex);
		emit updateInfoSignal(tabIndex);
	}
}

void main_window::MainWindow::addNewTab(QString search) {
	QLabel * centerWindow = new QLabel(tr("Searching"), this->mainWidget);
	centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	centerWindow->setAlignment(Qt::AlignCenter);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Open tab with label " << search);
	int tabIndex = this->tabs->addTab(centerWindow, search);
	this->newSearchTab(tabIndex, search);

	// Emit signal to update info label
	emit updateInfoSignal(tabIndex);
}

void main_window::MainWindow::openNewTabSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search in new tab");
	mainWindowState = main_window::MainWindow::state_e::OPEN_TAB;
	this->setAllShortcutEnabledProperty(false);

}

void main_window::MainWindow::newSearchCurrentTab(QString search) {
	int tabIndex = this->tabs->currentIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Search " << search << " in tab " << tabIndex);
	this->newSearchTab(tabIndex, search);
}


void main_window::MainWindow::newSearchTab(int index, QString search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search " << search << " in tab " << index);
	this->tabs->setTabText(index, search);
}

void main_window::MainWindow::newSearchTabSlot() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search in current tab");
	mainWindowState = main_window::MainWindow::state_e::SEARCH;
	this->setAllShortcutEnabledProperty(false);

}

// 
void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->tabs->currentWidget());
	currentWidget->setText(str);
	currentWidget->repaint();
}

void main_window::MainWindow::keyPressEvent(QKeyEvent * event) {

	QMainWindow::keyPressEvent(event);

	int pressedKey = event->key();

	if ((pressedKey == Qt::Key_Enter) || (pressedKey == Qt::Key_Return)) {
		if (this->userText.isEmpty()) {
			this->userText.append("No text provided");
		}

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "User typed text " << this->userText << " to search");

		if (mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) {
			this->addNewTab(this->userText);
		} else if (mainWindowState == main_window::MainWindow::state_e::SEARCH) {
			this->newSearchCurrentTab(this->userText);
		}
		this->userText.clear();
		mainWindowState = main_window::MainWindow::state_e::IDLE;
		this->setAllShortcutEnabledProperty(true);
	} else {
		if ((mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) || (mainWindowState == main_window::MainWindow::state_e::SEARCH)) {
			if (pressedKey == Qt::Key_Backspace) {
				// Last position of the string
				int endString = this->userText.count() - 1;
				this->userText.remove(endString, 1);
			} else {
				this->userText.append(event->text());
			}
		} else {
			this->userText.clear();
		}
	}

	this->searchText->setText(this->userText);

	this->mainWidget->repaint();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// Function connected to both currentChanged and tabCloseRequested signals
// In the case of currentChanged signal, index is the current tab
// In the case of tabCloseRequested signal, index is the closed tab
void main_window::MainWindow::updateInfoSlot(int index) {
	QString info("");
	int tabIndex = this->tabs->currentIndex() + 1;
	int tabCount = this->tabs->count();
	if (tabCount == 0) {
		info.append("No tabs");
	} else {
		info.append("tab ");
		info.append(QString("%1").arg(tabIndex));
		info.append(" out of ");
		info.append(QString("%1").arg(tabCount));
	}
	this->infoText->setText(info);
}
#pragma GCC diagnostic pop
