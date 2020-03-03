/**
 * @copyright
 * @file main_window_ctrl_tab.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Control functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>
#include <qt5/QtWebEngineWidgets/QWebEngineView>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "key_sequence.h"
#include "main_window_ctrl_tab.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlTabOverall, "mainWindowCtrlTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabUserInput, "mainWindowCtrlTab.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabSearch, "mainWindowCtrlTab.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabTabs, "mainWindowCtrlTab.tabs", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabUrl, "mainWindowCtrlTab.url", MSG_TYPE_LEVEL)


main_window_ctrl_tab::MainWindowCtrlTab::MainWindowCtrlTab(main_window_core::MainWindowCore * core, QWidget * parent) : main_window_ctrl_base::MainWindowCtrlBase(core, parent, main_window_ctrl_tab::commandFileFullPath) {

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

main_window_ctrl_tab::MainWindowCtrlTab::~MainWindowCtrlTab() {

	// deleting shortcuts
	delete this->openNewTabKey;
	delete this->newSearchTabKey;
	delete this->closeTabKey;
	delete this->moveTabToKey;
	delete this->moveLeftKey;
	delete this->moveRightKey;
	delete this->refreshUrlKey;

}

void main_window_ctrl_tab::MainWindowCtrlTab::createShortcuts() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Create shortcuts");

	// o will open a new tab
	this->openNewTabKey = new QShortcut(parent);
	this->openNewTabKey->setKey(Qt::Key_O);

	// s will search on the current tab
	this->newSearchTabKey = new QShortcut(parent);
	this->newSearchTabKey->setKey(Qt::Key_S);

	// c will close a tab
	this->closeTabKey = new QShortcut(parent);
	this->closeTabKey->setKey(Qt::Key_C);

	// t will move tab in the tab bar
	this->moveTabToKey = new QShortcut(parent);
	this->moveTabToKey->setKey(Qt::Key_T);

	// h will move left in the tab bar
	this->moveLeftKey = new QShortcut(parent);
	this->moveLeftKey->setKey(Qt::Key_H);

	// l will move right in the tab bar
	this->moveRightKey = new QShortcut(parent);
	this->moveRightKey->setKey(Qt::Key_L);

	// r will refresh a webpage
	this->refreshUrlKey = new QShortcut(parent);
	this->refreshUrlKey->setKey(Qt::Key_R);
}

void main_window_ctrl_tab::MainWindowCtrlTab::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Connect signals");
	connect(this->openNewTabKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab);
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpNewSearchTab);
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpCloseTab);
	connect(this->moveTabToKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveTab);
	connect(this->moveLeftKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveLeft);
	connect(this->moveRightKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveRight);
	connect(this->refreshUrlKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpRefreshTabUrl);

//	connect(this->windowCore->tabs, &QTabWidget::currentChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateContent);
	// Update info bar
	connect(this->windowCore->tabs, &QTabWidget::currentChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateInfoSlot);
	connect(this->windowCore->tabs, &QTabWidget::tabCloseRequested, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateInfoSlot);

	// open tab action (from fileMenu)
	connect(this->windowCore->topMenuBar->getFileMenu()->openTabAction, &QAction::triggered, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab);

	// When the file has been read, then show it on the screen
	connect(this->windowCore->topMenuBar->getFileMenu(), &file_menu::FileMenu::updateCenterWindowSignal, this, &main_window_ctrl_tab::MainWindowCtrlTab::printStrInCurrentTabWidget);
}

//************************************************************************************
// Start definition of set up slots
//************************************************************************************
void main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Open new tab");
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::OPEN_TAB);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpNewSearchTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Search in current tab");
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::SEARCH);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}


void main_window_ctrl_tab::MainWindowCtrlTab::setUpRefreshTabUrl() {
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::REFRESH_TAB);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveTab() {
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::TAB_MOVE);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveLeft() {
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::MOVE_LEFT);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveRight() {
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::MOVE_RIGHT);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpCloseTab() {
	this->windowCore->setMainWindowState(main_window_shared_types::state_e::CLOSE_TAB);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	this->setAllShortcutEnabledProperty(false);
}
//************************************************************************************
// End definition of set up slots
//************************************************************************************

//************************************************************************************
// Start definition of actions
//************************************************************************************
void main_window_ctrl_tab::MainWindowCtrlTab::closeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Close tab " << index);
	this->windowCore->tabs->removeTab(index);
}

void main_window_ctrl_tab::MainWindowCtrlTab::addNewTabAndSearch(QString search) {
	int tabIndex = this->addNewTab(search, main_window_shared_types::tab_type_e::WEB_ENGINE);
	this->newSearchTab(tabIndex, search);
}

int main_window_ctrl_tab::MainWindowCtrlTab::addNewTab(QString search, main_window_shared_types::tab_type_e type) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Open tab with label " << search);

	int tabIndex = this->windowCore->tabs->addEmptyTab(search, type);

	QEXCEPTION_ACTION_COND((tabIndex < 0), throw, "It cannot be negative");

	// Move to the newly opened tab
	this->windowCore->tabs->setCurrentIndex(tabIndex);

	// Update info label
	this->updateInfo();

	return tabIndex;
}

void main_window_ctrl_tab::MainWindowCtrlTab::newSearchTab(int index, QString search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "User input " << search << " in tab " << index);

	QString tabTitle = search;
	QString Url = this->createUrl(search);

	main_window_shared_types::tab_type_e desiredTabType = main_window_shared_types::tab_type_e::WEB_ENGINE;
	this->windowCore->tabs->changeTabType(index, desiredTabType);

	QWebEngineView * currentTabPage = dynamic_cast<QWebEngineView *>(this->windowCore->tabs->widget(index));
	this->windowCore->tabs->setTabText(index, tabTitle);
	currentTabPage->setUrl(QUrl(Url));

	this->updateContent(index);
}

void main_window_ctrl_tab::MainWindowCtrlTab::searchCurrentTab(QString search) {
	int tabIndex = this->windowCore->getCurrentTabIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Search " << search << " in tab " << tabIndex);
	this->newSearchTab(tabIndex, search);
}

void main_window_ctrl_tab::MainWindowCtrlTab::updateContent(int index) {

	int tabCount = this->windowCore->getTabCount();
	main_window_shared_types::tab_type_e tabType = this->windowCore->tabs->getTabType(index);

	if (tabCount > 0) {
		QString contentStr (QString::null);
		if (tabType == main_window_shared_types::tab_type_e::WEB_ENGINE) {
			QWebEngineView * currentTabPage = dynamic_cast<QWebEngineView *>(this->windowCore->tabs->widget(index));
			QUrl websiteUrl = currentTabPage->url();

			contentStr = websiteUrl.toDisplayString(QUrl::FullyDecoded);
		} else if (tabType == main_window_shared_types::tab_type_e::LABEL) {
			contentStr = this->windowCore->tabs->tabText(index);
		}
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUrl,  "Set contentPathText for tab at index " << index << " of type " << tabType << " to " << contentStr);
		this->windowCore->bottomStatusBar->getContentPathText()->setText(contentStr);
	} else {
		this->windowCore->bottomStatusBar->getContentPathText()->clear();
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::refreshUrl(int tabIndex) {
	QWebEngineView * currentTabPage = dynamic_cast<QWebEngineView *>(this->windowCore->tabs->widget(tabIndex));
	QUrl currUrl = currentTabPage->url();

	QString urlStr (currUrl.toDisplayString(QUrl::FullyDecoded));
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUrl,  "Refresh URL " << urlStr);

	currentTabPage->setUrl(QUrl(currUrl));
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveTab(int tabIndex) {
	int tabIndexCurrent = this->windowCore->tabs->currentIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Move tab " << tabIndexCurrent << " to " << tabIndex);
	this->windowCore->tabs->moveTab(tabIndexCurrent, tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveCursor(int tabIndex) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Move cursor to tab " << tabIndex);
	this->windowCore->tabs->setCurrentIndex(tabIndex);
}
//************************************************************************************
// End definition of actions
//************************************************************************************

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnOffset(int offset) {
	global_types::sign_e sign = global_types::sign_e::NOSIGN;

	main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	main_window_shared_types::move_value_e moveType = this->windowCore->getMoveValueType();

	if (windowState == main_window_shared_types::state_e::MOVE_RIGHT) {
		sign = global_types::sign_e::PLUS;
	} else if (windowState == main_window_shared_types::state_e::MOVE_LEFT) {
		sign = global_types::sign_e::MINUS;
	} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (moveType == main_window_shared_types::move_value_e::RIGHT) {
			sign = global_types::sign_e::PLUS;
		} else if (moveType == main_window_shared_types::move_value_e::LEFT) {
			sign = global_types::sign_e::MINUS;
		}
	} else {
		QEXCEPTION_ACTION(throw,  "Requested to execute tab action in invalid window state " << windowState);
	}

	Q_ASSERT_X(((sign == global_types::sign_e::MINUS) || (sign == global_types::sign_e::PLUS)), "sign check to execute movement on offset", "sign input must be either global_types::sign_e::MINUS or global_types::sign_e::PLUS");
	this->convertToAbsTabIndex(offset, sign);
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnTab(int index) {
	int tabIndex = main_window_ctrl_tab::emptyUserInput;
	// index is main_window_ctrl_tab::emptyUserInput if the argument is not passed
	if (index == main_window_ctrl_tab::emptyUserInput) {
		tabIndex = this->windowCore->getCurrentTabIndex();
	} else {
		// start indexing tab to close with 0
		tabIndex = index;
	}

	int tabCount = this->windowCore->getTabCount();

	main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	if ((tabCount > tabIndex) && (tabIndex >= 0)) {
		switch (windowState) {
			case main_window_shared_types::state_e::CLOSE_TAB:
				this->closeTab(tabIndex);
				break;
			case main_window_shared_types::state_e::TAB_MOVE:
			case main_window_shared_types::state_e::REFRESH_TAB:
				this->convertToAbsTabIndex(tabIndex, global_types::sign_e::NOSIGN);
				break;
			default:
				QEXCEPTION_ACTION(throw,  "Undefined action to execute when in state " << windowState);
				break;
		}
	} else {
		int maxTabRange = tabCount;
		QWARNING_PRINT(mainWindowCtrlTabTabs, "Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << maxTabRange);
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeTabAction(int userInput) {
	main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	main_window_shared_types::move_value_e moveType = this->windowCore->getMoveValueType();

	switch (windowState) {
		case main_window_shared_types::state_e::REFRESH_TAB:
		case main_window_shared_types::state_e::CLOSE_TAB:
			this->executeActionOnTab(userInput);
			break;
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
			this->executeActionOnOffset(userInput);
			break;
		case main_window_shared_types::state_e::TAB_MOVE:
			if ((moveType == main_window_shared_types::move_value_e::LEFT) || (moveType == main_window_shared_types::move_value_e::RIGHT)) {
				this->executeActionOnOffset(userInput);
			} else if (moveType == main_window_shared_types::move_value_e::ABSOLUTE) {
				this->executeActionOnTab(userInput);
			} else {
				QEXCEPTION_ACTION(throw,  "Undefined direction of movement of tabs. Currently set to " << moveType);
			}
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined tab action when in state " << windowState);
			break;
	}

	this->updateInfo();

	int tabIndex = this->windowCore->getCurrentTabIndex();
	this->updateContent(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::processTabIndex(QString userInputStr) {
	// If indexStr is an empty string, do not pass any argument to executeTabAction (i.e. execute action on current tab)
	if (userInputStr.isEmpty()) {
		this->executeTabAction();
	} else {
		bool conversionSuccessful = false;
		// Convert string un a number in base 10
		int userInputInt = userInputStr.toInt(&conversionSuccessful, 10);
		if (conversionSuccessful == true) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeTabAction(userInputInt);
		} else {
			QWARNING_PRINT(mainWindowCtrlTabTabs, "tab index " << userInputStr << " is not made up by numbers only");
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeCommand(QString command) {

	if (command.compare("open-tab") == 0) {
		this->setUpOpenNewTab();
	} else if (command.compare("search-tab") == 0) {
		this->setUpNewSearchTab();
	} else if (command.compare("close-tab") == 0) {
		this->setUpCloseTab();
	} else if (command.compare("move-tab") == 0) {
		this->setUpMoveTab();
	} else if (command.compare("move-cursor-left") == 0) {
		this->setUpMoveLeft();
	} else if (command.compare("move-cursor-right") == 0) {
		this->setUpMoveRight();
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::keyReleaseEvent(QKeyEvent * event) {

	int releasedKey = event->key();
	Qt::KeyboardModifiers keyModifiers = event->modifiers();

	key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

		// Retrieve main window controller state
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->windowCore->setMoveValueType(main_window_shared_types::move_value_e::IDLE);
				break;
			case Qt::Key_Backspace:
				break;
			default:
				break;
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::keyPressEvent(QKeyEvent * event) {

	int pressedKey = event->key();
	Qt::KeyboardModifiers keyModifiers = event->modifiers();

	key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
		QString userTypedText = this->windowCore->getUserText();

		// Retrieve main window controller state
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "User typed text " << userTypedText);
				switch (windowState) {
					case main_window_shared_types::state_e::OPEN_TAB:
						this->addNewTabAndSearch(userTypedText);
						break;
					case main_window_shared_types::state_e::SEARCH:
						this->searchCurrentTab(userTypedText);
						break;
					case main_window_shared_types::state_e::REFRESH_TAB:
					case main_window_shared_types::state_e::CLOSE_TAB:
					case main_window_shared_types::state_e::MOVE_RIGHT:
					case main_window_shared_types::state_e::MOVE_LEFT:
					case main_window_shared_types::state_e::TAB_MOVE:
						this->processTabIndex(userTypedText);
						break;
					default:
						// Do nothing by default
						break;
				}
				this->windowCore->setMoveValueType(main_window_shared_types::move_value_e::IDLE);
				break;
			default:
				this->setStateAction(windowState, event);
				break;
		}

	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::setStateAction(main_window_shared_types::state_e windowState, QKeyEvent * event) {

	int pressedKey = event->key();
	main_window_shared_types::move_value_e moveType = this->windowCore->getMoveValueType();

	switch (windowState) {
		case main_window_shared_types::state_e::TAB_MOVE:
			if (moveType == main_window_shared_types::move_value_e::IDLE) {
				// If no sign is provided, the tab is considered as absolute value
				// If + or - sign is provided, then the value is considered to be relative to the current tab
				// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
				// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->windowCore->setMoveValueType(main_window_shared_types::move_value_e::ABSOLUTE);
					this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
				} else if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
					this->windowCore->setMoveValueType(main_window_shared_types::move_value_e::RIGHT);
					this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				} else if ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_Minus)) {
					this->windowCore->setMoveValueType(main_window_shared_types::move_value_e::LEFT);
					this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				} else {
					QWARNING_PRINT(mainWindowCtrlTabUserInput, "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar");
				}
			} else {
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
				} else {
					QWARNING_PRINT(mainWindowCtrlTabUserInput, "Pressed key " << event->text() << ". Only numbers accepted when executing actions like move tabs in the tab bar");
				}
			}
			break;
		default:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::convertToAbsTabIndex(int offset, global_types::sign_e sign) {

	main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	int distance = 0;
	// offset is main_window_ctrl_tab::emptyUserInput if the argument is not passed
	if (offset == main_window_ctrl_tab::emptyUserInput) {
		if ((windowState == main_window_shared_types::state_e::MOVE_RIGHT) || (windowState == main_window_shared_types::state_e::MOVE_LEFT) || (windowState == main_window_shared_types::state_e::TAB_MOVE)) {
			distance = 1;
		} else if (windowState == main_window_shared_types::state_e::REFRESH_TAB) {
			distance = 0;
		}
	} else {
		distance = offset;
	}

	int tabCount = this->windowCore->getTabCount();
	int signInt = static_cast<int>(sign);

	int tabIndexDst = 0;
	if (sign == global_types::sign_e::NOSIGN) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = this->windowCore->getCurrentTabIndex() + (signInt * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		QWARNING_PRINT(mainWindowCtrlTabTabs, "Offset " << offset << " is bigger than the number of tabs " << tabCount << " Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange);
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	int tabIndex = tabIndexDst % tabCount;

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Convert tab relative offset " << (signInt*offset) << " to absolute offset " << tabIndex);

	switch (windowState) {
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
			this->moveCursor(tabIndex);
			break;
		case main_window_shared_types::state_e::TAB_MOVE:
			this->moveTab(tabIndex);
			break;
		case main_window_shared_types::state_e::REFRESH_TAB:
			this->refreshUrl(tabIndex);
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined action when in state " << windowState);
			break;
	}
}

QString main_window_ctrl_tab::MainWindowCtrlTab::createUrl(QString search) {
	bool containsSpace = search.contains(" ");
	bool containsWww = search.contains(main_window_ctrl_tab::www);
	int numberDots = search.count(".");

	QString url(QString::null);

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		url = main_window_ctrl_tab::https;
		if (containsWww == true) {
			url += search;
		} else {
			url += main_window_ctrl_tab::www + search;
		}
	} else {
		url = main_window_ctrl_tab::defaultSearchEngine.arg(search);
	}

	return url;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// Function connected to both currentChanged and tabCloseRequested signals
// In the case of currentChanged signal, index is the current tab
// In the case of tabCloseRequested signal, index is the closed tab
void main_window_ctrl_tab::MainWindowCtrlTab::updateInfoSlot(int index) {
	this->updateInfo();
}
#pragma GCC diagnostic pop

void main_window_ctrl_tab::MainWindowCtrlTab::printStrInCurrentTabWidget(const QString & tabTitle, const QString & tabContent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Set text in center window with title " << tabTitle);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  tabContent);

	// Get tabs
	tab_widget::TabWidget * tabWidget = this->windowCore->tabs;

	// Get current tab index
	int currentTabIndex = tabWidget->currentIndex();


	main_window_shared_types::tab_type_e desiredTabType = main_window_shared_types::tab_type_e::LABEL;

	// Disable events while updating tabs
	tabWidget->setUpdatesEnabled(false);

	// If not tabs, then create one
	if (currentTabIndex == -1) {
		currentTabIndex = this->addNewTab(tabTitle, desiredTabType);
		QEXCEPTION_ACTION_COND((currentTabIndex >= tabWidget->count()), throw,  "Current tab index " << currentTabIndex << " must be larger than the number of tabs " << tabWidget->count());
	} else {
		this->windowCore->tabs->changeTabType(currentTabIndex, desiredTabType);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs, "Current tab index is " << currentTabIndex << " and the tab widget has " << tabWidget->count() << " tabs");

	tabWidget->setTabText(currentTabIndex, tabTitle);
	QLabel * currentTabPage = dynamic_cast<QLabel *>(tabWidget->widget(currentTabIndex, true));
	Q_ASSERT_X((currentTabPage != nullptr), "null center window", "Center window is null");

	currentTabPage->setText(tabContent);

	this->updateContent(currentTabIndex);

	// Disable events after updating tabs
	tabWidget->setUpdatesEnabled(true);
}
