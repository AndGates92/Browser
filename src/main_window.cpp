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
			case main_window::MainWindow::state_e::COMMAND:
				os << "COMMAND";
				break;
			case main_window::MainWindow::state_e::OPEN_TAB:
				os << "OPEN TAB";
				break;
			case main_window::MainWindow::state_e::CLOSE_TAB:
				os << "CLOSE TAB";
				break;
			case main_window::MainWindow::state_e::MOVE_LEFT:
				os << "MOVE LEFT";
				break;
			case main_window::MainWindow::state_e::MOVE_RIGHT:
				os << "MOVE RIGHT";
				break;
			case main_window::MainWindow::state_e::TAB_MOVE:
				os << "TAB MOVE";
				break;
			case main_window::MainWindow::state_e::SEARCH:
				os << "SEARCH";
				break;
			default:
				os << "Unknown state";
				break;
		}

		return os;
	}

	QDebug & operator<< (QDebug & os, const main_window::MainWindow::move_value_e & value_type) {

		switch (value_type) {
			case main_window::MainWindow::move_value_e::IDLE:
				os << "IDLE";
				break;
			case main_window::MainWindow::move_value_e::LEFT:
				os << "LEFT";
				break;
			case main_window::MainWindow::move_value_e::RIGHT:
				os << "RIGHT";
				break;
			case main_window::MainWindow::move_value_e::ABSOLUTE:
				os << "ABSOLUTE";
				break;
			default:
				os << "Unknown value type";
				break;
		}

		return os;
	}

	QDebug & operator<< (QDebug & os, const main_window::MainWindow::text_action_e & action) {

		switch (action) {
			case main_window::MainWindow::text_action_e::SET:
				os << "SET";
				break;
			case main_window::MainWindow::text_action_e::APPEND:
				os << "APPEND";
				break;
			case main_window::MainWindow::text_action_e::CLEAR:
				os << "CLEAR";
				break;
			default:
				os << "Unknown action";
				break;
		}

		return os;
	}

}

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	this->mainWindowState = main_window::MainWindow::state_e::IDLE;
	this->moveValueType = main_window::MainWindow::move_value_e::IDLE;
	this->setFocusPolicy(Qt::StrongFocus);

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
			"border-right: 1px solid black; "
			"border-left: 1px solid black; "
		"}"
	);

	return label;
}

void main_window::MainWindow::fillMainWindow() {
	// Customize MainWidget
	this->createTabs();

	// user input
	this->userInputText = this->newWindowLabel();
	this->userInputText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	// website URL
	this->websiteText = this->newWindowLabel();
	this->websiteText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

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
	connect(this, &main_window::MainWindow::updateUserInputSignal, this, &main_window::MainWindow::updateUserInputSlot);
//	connect(this->tabs, &QTabWidget::currentChanged, this, &main_window::MainWindow::updateWebsiteSlot);
	connect(this, &main_window::MainWindow::updateWebsiteSignal, this, &main_window::MainWindow::updateWebsiteSlot);
	connect(this->tabs, &tab_widget::TabWidget::setShortcutEnabledPropertySignal, this, &main_window::MainWindow::setShortcutEnabledPropertySlot);
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
	layout->addWidget(this->userInputText, searchFromRow, searchFromColumn, searchRowSpan, searchColumnSpan);
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
	this->moveTabToKey->setEnabled(enabled);
	this->moveLeftKey->setEnabled(enabled);
	this->moveRightKey->setEnabled(enabled);
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

	// t will move tab in the tab bar
	this->moveTabToKey = new QShortcut(this);
	this->moveTabToKey->setKey(Qt::Key_T);
	connect(this->moveTabToKey, &QShortcut::activated, this, &main_window::MainWindow::moveTabToSlot);

	// h will move left in the tab bar
	this->moveLeftKey = new QShortcut(this);
	this->moveLeftKey->setKey(Qt::Key_H);
	connect(this->moveLeftKey, &QShortcut::activated, this, &main_window::MainWindow::moveLeftSlot);

	// l will move right in the tab bar
	this->moveRightKey = new QShortcut(this);
	this->moveRightKey->setKey(Qt::Key_L);
	connect(this->moveRightKey, &QShortcut::activated, this, &main_window::MainWindow::moveRightSlot);

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

void main_window::MainWindow::moveTabToSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::TAB_MOVE;
	this->setAllShortcutEnabledProperty(false);
	emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
}

void main_window::MainWindow::moveLeftSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::MOVE_LEFT;
	this->setAllShortcutEnabledProperty(false);
	emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
}

void main_window::MainWindow::moveRightSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::MOVE_RIGHT;
	this->setAllShortcutEnabledProperty(false);
	emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
}

void main_window::MainWindow::closeTabSlot() {
	this->mainWindowState = main_window::MainWindow::state_e::CLOSE_TAB;
	this->setAllShortcutEnabledProperty(false);
	emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
}

void main_window::MainWindow::executeAction(int userInput) {
	if (this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) {
		this->executeActionOnTab(userInput);
	} else if ((this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT)) {
		this->executeActionOnOffset(userInput);
	} else if (this->mainWindowState == main_window::MainWindow::state_e::TAB_MOVE) {
	       if ((this->moveValueType == main_window::MainWindow::move_value_e::LEFT) || (this->moveValueType == main_window::MainWindow::move_value_e::RIGHT)) {
			this->executeActionOnOffset(userInput);
		} else if (this->moveValueType == main_window::MainWindow::move_value_e::ABSOLUTE) {
			this->executeActionOnTab(userInput);
		}
	}

	int tabIndex = this->tabs->currentIndex();
	emit updateInfoSignal(tabIndex);

	emit updateWebsiteSignal(tabIndex);
}

void main_window::MainWindow::executeActionOnOffset(int offset) {
	if (this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT) {
		this->move(offset, 1);
	} else if (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT) {
		this->move(offset, -1);
	} else if (this->mainWindowState == main_window::MainWindow::state_e::TAB_MOVE) {
		if (this->moveValueType == main_window::MainWindow::move_value_e::RIGHT) {
			this->move(offset, 1);
		} else if (this->moveValueType == main_window::MainWindow::move_value_e::LEFT) {
			this->move(offset, -1);
		}
	}
}

void main_window::MainWindow::move(int offset, int sign) {

	Q_ASSERT_X(((sign == 0) || (sign == -1) || (sign == 1)), "main window move", "sign input must be either 0 or -1 or 1");
	// number of tabs to move by
	int distance = 0;
	// index is main_window::emptyUserInput if the argument is not passed
	if (offset == main_window::emptyUserInput) {
		distance = 1;
	} else {
		distance = offset;
	}

	int tabCount = this->tabs->count();
	int tabIndexCurrent = this->tabs->currentIndex();
	int tabIndexDst = 0;
	if (sign == 0) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = tabIndexCurrent + (sign * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		qWarning(mainWindowTabs) << "Offset " << offset << " is bigger than the number of tabs " << tabCount << " Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange << ")\n";
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	int tabIndex = tabIndexDst % tabCount;

	if ((this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT)) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move to tab " << tabIndex << " distance " << distance << " action " << this->mainWindowState << " sign " << sign);
		this->tabs->setCurrentIndex(tabIndex);
	} else if (this->mainWindowState == main_window::MainWindow::state_e::TAB_MOVE) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move tab " << tabIndexCurrent << " to position " << tabIndex << " action " << this->mainWindowState << " sign " << sign);
		this->tabs->tabBar()->moveTab(tabIndexCurrent, tabIndex);
	}
}

void main_window::MainWindow::executeActionOnTab(int index) {
	int tabIndex = main_window::emptyUserInput;
	int tabCount = this->tabs->count();
	// index is main_window::emptyUserInput if the argument is not passed
	if (index == main_window::emptyUserInput) {
		tabIndex = this->tabs->currentIndex();
	} else {
		// start indexing tab to close with 0
		tabIndex = index;
	}

	if ((tabCount > tabIndex) && (tabIndex >= 0)) {
		if (this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) {
			this->closeTab(tabIndex);
		} else if (this->mainWindowState == main_window::MainWindow::state_e::TAB_MOVE) {
			this->move(tabIndex);
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

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Open tab with label " << search);
	int tabIndex = this->tabs->addTab(centerWindow, search);
	this->newSearchTab(tabIndex, search);

	// Move to the newly opened tab
	this->tabs->setCurrentIndex(tabIndex);

	// Emit signal to update info label
	emit updateInfoSignal(tabIndex);
}

void main_window::MainWindow::openNewTabSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Open new tab");
	this->mainWindowState = main_window::MainWindow::state_e::OPEN_TAB;
	this->setAllShortcutEnabledProperty(false);
	emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
}

void main_window::MainWindow::newSearchCurrentTab(QString search) {
	int tabIndex = this->tabs->currentIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Search " << search << " in tab " << tabIndex);
	this->newSearchTab(tabIndex, search);
}

void main_window::MainWindow::executeCommand(QString command) {

	if (command.compare("open") == 0) {

	}
/*
	// m will hide/show the menu bar
	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window::MainWindow::toggleShowMenubarSlot);

	// o will open a new tab
	connect(this->fileMenu->openTabAction, &QAction::triggered, this, &main_window::MainWindow::openNewTabSlot);

	// s will search on the current tab
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window::MainWindow::newSearchTabSlot);

	// c will close a tab
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window::MainWindow::closeTabSlot);

	// t will move tab in the tab bar
	connect(this->moveTabToKey, &QShortcut::activated, this, &main_window::MainWindow::moveTabToSlot);

	// h will move left in the tab bar
	connect(this->moveLeftKey, &QShortcut::activated, this, &main_window::MainWindow::moveLeftSlot);

	// l will move right in the tab bar
	connect(this->moveRightKey, &QShortcut::activated, this, &main_window::MainWindow::moveRightSlot);

	// q will close the browser
	connect(this->fileMenu->exitAction, &QAction::triggered, this, &main_window::MainWindow::closeSlot);
*/
}

void main_window::MainWindow::newSearchTab(int index, QString search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "User input " << search << " in tab " << index);

	QWebEngineView * centerWindow = (QWebEngineView *) this->tabs->widget(index);

	bool containsSpace = search.contains(" ");
	bool containsWww = search.contains(main_window::www);
	int numberDots = search.count(".");

	QString tabTitle = Q_NULLPTR;
	QString Url = Q_NULLPTR;

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		Url = main_window::https;
		tabTitle = search;
		if (containsWww == true) {
			Url += search;
		} else {
			Url += main_window::www + search;
		}
	} else {
		tabTitle = search;
		Url = main_window::defaultSearchEngine.arg(search);
	}
	this->tabs->setTabText(index, tabTitle);
	centerWindow->setUrl(QUrl(Url));

	emit updateWebsiteSignal(index);
}

void main_window::MainWindow::newSearchTabSlot() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search in current tab");
	this->mainWindowState = main_window::MainWindow::state_e::SEARCH;
	this->setAllShortcutEnabledProperty(false);
	emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
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

	if (event->type() == QEvent::KeyPress) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "State " << this->mainWindowState << " key " << event->text() << " i.e. number 0x" << hex << pressedKey);

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "User typed text " << this->userText);

				if (this->mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) {
					this->addNewTab(this->userText);
				} else if (this->mainWindowState == main_window::MainWindow::state_e::SEARCH) {
					this->newSearchCurrentTab(this->userText);
				} else if ((this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT) || (this->mainWindowState == main_window::MainWindow::state_e::TAB_MOVE)) {
					this->processTabIndex(this->userText);
				}
				this->mainWindowState = main_window::MainWindow::state_e::IDLE;
				this->moveValueType = main_window::MainWindow::move_value_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
				break;
			case Qt::Key_Escape:
				this->mainWindowState = main_window::MainWindow::state_e::IDLE;
				this->moveValueType = main_window::MainWindow::move_value_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "User typed text " << this->userText);
				// Last position of the string
				if (this->userText.isEmpty() == 0) {
					int endString = this->userText.count() - 1;
					this->userText.remove(endString, 1);
					emit updateUserInputSignal(main_window::MainWindow::text_action_e::SET, this->userText);
				}
				break;
			default:
				if ((this->mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::SEARCH)) {
					if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
						emit updateUserInputSignal(main_window::MainWindow::text_action_e::APPEND, event->text());
					}
				} else if ((this->mainWindowState == main_window::MainWindow::state_e::CLOSE_TAB) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window::MainWindow::state_e::MOVE_LEFT)) {
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						emit updateUserInputSignal(main_window::MainWindow::text_action_e::APPEND, event->text());
					} else {
						qWarning(mainWindowTabs) << "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window::MainWindow::state_e::TAB_MOVE) {
					// If no sign is provided, the tab is considered as absolute value
					// If + or - sign is provided, then the value is considered to be relative to the current tab
					// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
					// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						emit updateUserInputSignal(main_window::MainWindow::text_action_e::APPEND, event->text());
						if (this->moveValueType == main_window::MainWindow::move_value_e::IDLE) {
							this->moveValueType = main_window::MainWindow::move_value_e::ABSOLUTE;
						}
					} else if ((this->moveValueType == main_window::MainWindow::move_value_e::IDLE) && ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_L) || (pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_Minus))) {
						if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
							this->moveValueType = main_window::MainWindow::move_value_e::RIGHT;
						} else {
							this->moveValueType = main_window::MainWindow::move_value_e::LEFT;
						}
						emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
					} else {
						qWarning(mainWindowTabs) << "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window::MainWindow::state_e::COMMAND) {
					emit updateUserInputSignal(main_window::MainWindow::text_action_e::APPEND, event->text());
					if (pressedKey >= Qt::Key_Space) {
						this->executeCommand(this->userText);
					}
				} else {
					if (pressedKey == Qt::Key_Colon) {
						this->mainWindowState = main_window::MainWindow::state_e::COMMAND;
						this->setAllShortcutEnabledProperty(false);
					}
					emit updateUserInputSignal(main_window::MainWindow::text_action_e::CLEAR);
				}
				break;
		}

	}

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

void main_window::MainWindow::setShortcutEnabledPropertySlot (bool enabled) {
	this->setAllShortcutEnabledProperty(enabled);
}

void main_window::MainWindow::updateWebsiteSlot(int index) {

	int tabCount = this->tabs->count();

	if (tabCount > 0) {
		QWebEngineView * centerWindow = dynamic_cast<QWebEngineView *>(this->tabs->widget(index));
		QUrl websiteUrl = centerWindow->url();

		QString websiteStr (websiteUrl.toDisplayString(QUrl::FullyDecoded));
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Set URL in websiteText to " << websiteStr);
		this->websiteText->setText(websiteStr);
	} else {
		this->websiteText->clear();
	}
}

void main_window::MainWindow::updateUserInputSlot(const main_window::MainWindow::text_action_e action, QString text) {

	QString textPrint = Q_NULLPTR;
	if (text == Q_NULLPTR) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	this->userInputText->setFocus(Qt::OtherFocusReason);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "Action is " << action << " for user input " << textPrint);
	switch (action) {
		case main_window::MainWindow::text_action_e::SET:
			this->userText.clear();
			this->userText.append(text);
			break;
		case main_window::MainWindow::text_action_e::APPEND:
			this->userText.append(text);
			break;
		case main_window::MainWindow::text_action_e::CLEAR:
			this->userText.clear();
			break;
		default:
			qWarning(mainWindowUserInput) << "Unknown action " << action << "\n";
			break;
	}

	if (this->mainWindowState == main_window::MainWindow::state_e::IDLE) {
		this->userInputText->clear();
	} else {
		QString userAction = Q_NULLPTR;
		if (this->mainWindowState != main_window::MainWindow::state_e::COMMAND) {
			userAction = this->getActionName();
		}
		QString textLabel = Q_NULLPTR;
		textLabel.append(":" + userAction + " " + this->userText);

		this->userInputText->setText(textLabel);
	}
}

QString main_window::MainWindow::getActionName() {
	QString actionName = Q_NULLPTR;
	switch (this->mainWindowState) {
		case main_window::MainWindow::state_e::IDLE:
			actionName = "";
			break;
		case main_window::MainWindow::state_e::OPEN_TAB:
			actionName = "open";
			break;
		case main_window::MainWindow::state_e::COMMAND:
			actionName = "command";
			break;
		case main_window::MainWindow::state_e::CLOSE_TAB:
			actionName = "close";
			break;
		case main_window::MainWindow::state_e::MOVE_LEFT:
			actionName = "move left";
			break;
		case main_window::MainWindow::state_e::MOVE_RIGHT:
			actionName = "move right";
			break;
		case main_window::MainWindow::state_e::TAB_MOVE:
			actionName = "move tab";
			if (this->moveValueType == main_window::MainWindow::move_value_e::RIGHT) {
				actionName.append(" right");
			} else if (this->moveValueType == main_window::MainWindow::move_value_e::LEFT) {
				actionName.append(" left");
			}
			break;
		case main_window::MainWindow::state_e::SEARCH:
			actionName = "search";
			break;
		default:
			actionName = "Unknown state";
			break;
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowUserInput,  "State " << this->mainWindowState << " action text " << actionName);

	return actionName;
}
