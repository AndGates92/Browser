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
Q_LOGGING_CATEGORY(mainWindowUserInput, "mainWindow.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowSearch, "mainWindow.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

namespace main_window {
	// Overload << operator for state_e
	QDebug & operator<< (QDebug & os, const main_window::MainWindow::state_e & state) {

		switch (state) {
			case main_window::MainWindow::state_e::IDLE:
				os << "IDLE";
				break;
			case main_window::MainWindow::state_e::OPEN_TAB:
				os << "OPEN_TAB";
				break;
			case main_window::MainWindow::state_e::CLOSE_TAB:
				os << "CLOSE_TAB";
				break;
			case main_window::MainWindow::state_e::MOVE_LEFT_TAB:
				os << "MOVE_LEFT_TAB";
				break;
			case main_window::MainWindow::state_e::MOVE_RIGHT_TAB:
				os << "MOVE_RIGHT_TAB";
				break;
			case main_window::MainWindow::state_e::SEARCH:
				os << "SEARCH";
				break;
			default:
				os << "Unknown stater";
				break;
		}

		return os;
	}
}

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	this->mainWindowState = main_window::MainWindow::state_e::IDLE;

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

	this->setAttribute(Qt::WA_DeleteOnClose);

	QSize winSize(320,400);
	this->resize(winSize);
}


void main_window::MainWindow::createMainWidget() {
	this->mainWidget = new QWidget(this);
	this->mainWidget->setAttribute(Qt::WA_DeleteOnClose);
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
	label->setAttribute(Qt::WA_DeleteOnClose);
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
	connect(this->fileMenu->openTabAction, &QAction::triggered, this, &main_window::MainWindow::openNewTabSlot);

	// s will search on the current tab
	this->newSearchTabKey = new QShortcut(this);
	this->newSearchTabKey->setKey(Qt::Key_S);
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window::MainWindow::newSearchTabSlot);

	// c will close a tab
	this->closeTabKey = new QShortcut(this);
	this->closeTabKey->setKey(Qt::Key_C);
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window::MainWindow::closeTabSlot);

	// h will move left tab
	this->moveLeftTabKey = new QShortcut(this);
	this->moveLeftTabKey->setKey(Qt::Key_H);
	connect(this->moveLeftTabKey, &QShortcut::activated, this, &main_window::MainWindow::moveLeftTabSlot);

	// l will move right tab
	this->moveRightTabKey = new QShortcut(this);
	this->moveRightTabKey->setKey(Qt::Key_L);
	connect(this->moveRightTabKey, &QShortcut::activated, this, &main_window::MainWindow::moveRightTabSlot);

	// q will close the browser
	this->closeKey = new QShortcut(this);
	this->closeKey->setKey(Qt::Key_Q);
	connect(this->closeKey, &QShortcut::activated, this, &main_window::MainWindow::closeSlot);
	connect(this->fileMenu->exitAction, &QAction::triggered, this, &main_window::MainWindow::closeSlot);

}

void main_window::MainWindow::toggleShowMenubarSlot() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::closeSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowOverall,  "Close slot: exiting from the browser");
	this->close();
}

void main_window::MainWindow::moveLeftTabSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::MOVE_LEFT_TAB;
	this->setAllShortcutEnabledProperty(false);
}

void main_window::MainWindow::moveRightTabSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::MOVE_RIGHT_TAB;
	this->setAllShortcutEnabledProperty(false);
}

void main_window::MainWindow::closeTabSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::CLOSE_TAB;
	this->setAllShortcutEnabledProperty(false);
}

void main_window::MainWindow::executeAction(int userInput) {
	if (this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) {
		this->executeActionOnTab(userInput);
	} else if ((this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT_TAB)) {
		this->executeActionOnOffset(userInput);
	}

	int tabIndex = this->tabs->currentIndex();
	emit updateInfoSignal(tabIndex);
}

void main_window::MainWindow::executeActionOnOffset(int offset) {
	if (this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT_TAB) {
		this->moveTab(offset, 1);
	} else if (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT_TAB) {
		this->moveTab(offset, -1);
	}
}

void main_window::MainWindow::moveTab(int offset, int sign) {
	// number of tabs to move by
	int distance = 0;
	// index is main_window::emptyUserInput if the argument is not passed
	if (offset == main_window::emptyUserInput) {
		distance = 1;
	} else {
		distance = offset;
	}

	int tabCount = this->tabs->count();
	int tabIndexDst = this->tabs->currentIndex() + (sign * distance);
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		qWarning(mainWindowTabs) << "Offset " << offset << " is bigger than the number of tabs " << tabCount << " Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange << ")\n";
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}
	// Keep tabIndex values within valid range (0 and (tabCount -1))
	int tabIndex = tabIndexDst % tabCount;

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move to tab " << tabIndex << " distance " << distance << " action " << this->mainWindowState << " sign " << sign);

	this->tabs->setCurrentIndex(tabIndex);
}


void main_window::MainWindow::executeActionOnTab(int index) {
	int tabIndex = main_window::emptyUserInput;
	int tabCount = this->tabs->count();
	// index is main_window::emptyUserInput if the argument is not passed
	if (index == main_window::emptyUserInput) {
		tabIndex = this->tabs->currentIndex();
	} else {
		// start indexing tab to close with 1 (by default Qt starts indexig tabs with 0, therefore substract 1)
		tabIndex = index - 1;
	}

	if ((tabCount > tabIndex) && (tabIndex >= 0)) {
		if (this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) {
			this->closeTab(tabIndex);
		}
	} else {
		int maxTabRange = tabCount;
		qWarning(mainWindowTabs) << "Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << maxTabRange << "\n";
	}
}

void main_window::MainWindow::closeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Close tab " << index);
	this->tabs->removeTab(index);
}

void main_window::MainWindow::addNewTab(QString search) {
	QWebEngineView * centerWindow = new QWebEngineView(this->mainWidget);
	centerWindow->load(QUrl(main_window::defaultSearchEngine.arg(search)));

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Open tab with label " << search);
	int tabIndex = this->tabs->addTab(centerWindow, search);
	this->newSearchTab(tabIndex, search);

	// Emit signal to update info label
	emit updateInfoSignal(tabIndex);
}

void main_window::MainWindow::openNewTabSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search in new tab");
	this->mainWindowState = main_window::MainWindow::state_e::OPEN_TAB;
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
	this->mainWindowState = main_window::MainWindow::state_e::SEARCH;
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

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "State " << this->mainWindowState << " key " << event->text());

	switch (pressedKey) {
		case Qt::Key_Enter:
		case Qt::Key_Return:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "User typed text " << this->userText);

			if (this->mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) {
				this->addNewTab(this->userText);
			} else if (this->mainWindowState == main_window::MainWindow::state_e::SEARCH) {
				this->newSearchCurrentTab(this->userText);
			} else if ((this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT_TAB)) {
				this->processTabIndex(this->userText);
			}
			this->userText.clear();
			this->mainWindowState = main_window::MainWindow::state_e::IDLE;
			this->setAllShortcutEnabledProperty(true);
			break;
		case Qt::Key_Escape:
			this->userText.clear();
			this->mainWindowState = main_window::MainWindow::state_e::IDLE;
			this->setAllShortcutEnabledProperty(true);
			break;
		case Qt::Key_Backspace:
			// Last position of the string
			if (this->userText.isEmpty() == 0) {
				int endString = this->userText.count() - 1;
				this->userText.remove(endString, 1);
			}
			break;
		default:
			if ((this->mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::SEARCH)) {
				if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
					this->userText.append(event->text());
				}
			} else if ((this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT_TAB)) {
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->userText.append(event->text());
				} else {
					qWarning(mainWindowTabs) << "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar\n";
				}
			} else {
				this->userText.clear();
			}
			break;
	}

	this->searchText->setText(this->userText);

	this->mainWidget->repaint();
}

void main_window::MainWindow::processTabIndex(QString userInputStr) {
	// If indexStr is an empty string, do not pass any argument to executeAction (i.e. execute action on current tab)
	if (userInputStr.isEmpty()) {
		this->executeAction();
	} else {
		bool conversionSuccessful = false;
		int userInputInt = userInputStr.toInt(&conversionSuccessful, 10);
		if (conversionSuccessful == true) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeAction(userInputInt);
		} else {
			qWarning(mainWindowTabs) << "tab index " << userInputStr << " is not made up by numbers only\n";
		}
	}
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
