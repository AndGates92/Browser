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


main_window_ctrl_tab::MainWindowCtrlTab::MainWindowCtrlTab(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent) : main_window_ctrl_base::MainWindowCtrlBase(core, parent, main_window_ctrl_tab::commandFileFullPath) {

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

	QWidget * parent = this->parentWidget();

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

	// open tab action (from fileMenu)
	connect(this->windowCore->topMenuBar->getFileMenu()->openTabAction, &QAction::triggered, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab);

	// When the file has been read, then show it on the screen
	connect(this->windowCore->topMenuBar->getFileMenu(), &file_menu::FileMenu::updateCenterWindowSignal, this, &main_window_ctrl_tab::MainWindowCtrlTab::printStrInCurrentTab);
}

//************************************************************************************
// Start definition of set up slots
//************************************************************************************
void main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Open new tab");
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::OPEN_TAB;
	this->changeWindowState(requestedWindowState);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpNewSearchTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Search in current tab");
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::SEARCH;
	this->changeWindowState(requestedWindowState);
}


void main_window_ctrl_tab::MainWindowCtrlTab::setUpRefreshTabUrl() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::REFRESH_TAB;
	this->changeWindowState(requestedWindowState);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveTab() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::TAB_MOVE;
	this->changeWindowState(requestedWindowState);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveLeft() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::MOVE_LEFT;
	this->changeWindowState(requestedWindowState);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpMoveRight() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::MOVE_RIGHT;
	this->changeWindowState(requestedWindowState);
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpCloseTab() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::CLOSE_TAB;
	this->changeWindowState(requestedWindowState);
}
//************************************************************************************
// End definition of set up slots
//************************************************************************************

//************************************************************************************
// Start definition of actions
//************************************************************************************
void main_window_ctrl_tab::MainWindowCtrlTab::closeTab(const int & index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Close tab " << index);
	this->windowCore->tabs->removeTab(index);
}

void main_window_ctrl_tab::MainWindowCtrlTab::addNewTabAndSearch(const QString & search) {
	this->addNewTab(search, main_window_shared_types::tab_type_e::WEB_ENGINE, nullptr);
}

int main_window_ctrl_tab::MainWindowCtrlTab::addNewTab(const QString & search, const main_window_shared_types::tab_type_e & type, const void * data) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Open tab with label " << search);

	const int tabCount = this->windowCore->getTabCount();
	if (tabCount > 0) {
		// Disconnect signals only if at least 1 tabs is already present
		int currentTabIndex = this->windowCore->getCurrentTabIndex();
		this->disconnectProgressBar(currentTabIndex);
	}

	const int tabIndex = this->windowCore->tabs->addEmptyTab(search, type, data);

	// Connect signals from tab the cursor is pointing to
	this->connectProgressBar(tabIndex);

	QEXCEPTION_ACTION_COND((tabIndex < 0), throw, "It cannot be negative");

	// Update info label
	this->updateInfo();

	return tabIndex;
}

void main_window_ctrl_tab::MainWindowCtrlTab::newSearchTab(const int & index, const QString & search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "User input " << search << " in tab " << index);

	const QString tabTitle = search;
	const QString Url = this->createUrl(search);

	const main_window_shared_types::tab_type_e desiredTabType = main_window_shared_types::tab_type_e::WEB_ENGINE;
	this->windowCore->tabs->changeTabType(index, desiredTabType);
	this->windowCore->tabs->setTabText(index, tabTitle);

	try {
		main_window_tab::MainWindowTab * currentTab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(index));
		main_window_web_engine_view::MainWindowWebEngineView * currentTabView = currentTab->widgetView;
		currentTabView->setUrl(QUrl(Url));
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	this->updateContent(index);
}

void main_window_ctrl_tab::MainWindowCtrlTab::searchCurrentTab(const QString & search) {
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	const int tabCount = this->windowCore->getTabCount();
	QEXCEPTION_ACTION_COND(((tabIndex < 0) || (tabCount <= 0)), throw, "Unable to perform search of " << search << " in tab " << tabIndex << ". Note that a negative tab index may be cause by the fact that there are no tabs opened in the browser - current count of opened tabs is " << this->windowCore->getTabCount());
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Search " << search << " in tab " << tabIndex);
	this->newSearchTab(tabIndex, search);
}

void main_window_ctrl_tab::MainWindowCtrlTab::updateContent(const int & index) {

	const int tabCount = this->windowCore->getTabCount();
	const main_window_shared_types::tab_type_e tabType = this->windowCore->tabs->getTabType(index);

	if (tabCount > 0) {
		QString contentStr (QString::null);
		if (tabType == main_window_shared_types::tab_type_e::WEB_ENGINE) {
			try {
				const main_window_tab::MainWindowTab * currentTab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(index));
				const main_window_web_engine_view::MainWindowWebEngineView * currentTabView = currentTab->widgetView;
				const QUrl websiteUrl = currentTabView->url();
				contentStr = websiteUrl.toDisplayString(QUrl::FullyDecoded);
			} catch (const std::bad_cast & badCastE) {
				QEXCEPTION_ACTION(throw, badCastE.what());
			}
		} else if (tabType == main_window_shared_types::tab_type_e::LABEL) {
			// Return the tab title
			contentStr = this->windowCore->tabs->tabText(index);
		}
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUrl, "Set contentPathText for tab at index " << index << " of type " << tabType << " to " << contentStr);
		this->windowCore->bottomStatusBar->getContentPathText()->setText(contentStr);
	} else {
		this->windowCore->bottomStatusBar->getContentPathText()->clear();
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::refreshUrl(const int & tabIndex) {
	const main_window_shared_types::tab_type_e tabType = this->windowCore->tabs->getTabType(tabIndex);
	if (tabType == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		try {
			main_window_tab::MainWindowTab * currentTab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(tabIndex));
			main_window_web_engine_view::MainWindowWebEngineView * currentTabView = currentTab->widgetView;
			const QUrl currUrl = currentTabView->url();

			const QString urlStr (currUrl.toDisplayString(QUrl::FullyDecoded));
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUrl,  "Refresh URL " << urlStr);

			currentTabView->load(QUrl(currUrl));
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	} else if (tabType == main_window_shared_types::tab_type_e::LABEL) {
		// Retrive filename
		const void * tabData = this->windowCore->tabs->getTabData(tabIndex);
		const char * filename = static_cast<const char *>(tabData);
		const QString tabContent(QString::fromStdString(global_functions::readFile(filename)));
		try {
			QLabel * tabPage = dynamic_cast<QLabel *>(this->windowCore->tabs->widget(tabIndex, true));
			tabPage->setText(tabContent);
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}

		this->updateContent(tabIndex);

	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveTab(const int & tabIndex) {
	const int tabIndexCurrent = this->windowCore->tabs->currentIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Move tab " << tabIndexCurrent << " to " << tabIndex);
	this->windowCore->tabs->moveTab(tabIndexCurrent, tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveCursor(const int & tabIndex) {
	// Disconnect signals from tab the cursor was pointing to
	const int currentTabIndex = this->windowCore->getCurrentTabIndex();
	this->disconnectProgressBar(currentTabIndex);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Move cursor to tab " << tabIndex);
	this->windowCore->tabs->setCurrentIndex(tabIndex);
	// Connect signals from tab the cursor is pointing to
	this->connectProgressBar(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::connectProgressBar(const int & tabIndex) {
	const main_window_shared_types::tab_type_e tabType = this->windowCore->tabs->getTabType(tabIndex);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");
	if (tabType == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		try {
			const main_window_tab::MainWindowTab * currentTab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(tabIndex));
			const main_window_web_engine_view::MainWindowWebEngineView * currentTabView = currentTab->widgetView;
			const progress_bar::ProgressBar * loadBar = this->windowCore->bottomStatusBar->getLoadBar();

			connect(currentTabView, &main_window_web_engine_view::MainWindowWebEngineView::loadStarted, loadBar, &progress_bar::ProgressBar::startLoading);
			connect(currentTabView, &main_window_web_engine_view::MainWindowWebEngineView::loadProgress, loadBar, &progress_bar::ProgressBar::setValue);
			connect(currentTabView, &main_window_web_engine_view::MainWindowWebEngineView::loadFinished, loadBar, &progress_bar::ProgressBar::endLoading);

		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	} else if (tabType == main_window_shared_types::tab_type_e::LABEL) {
		// TODO
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::disconnectProgressBar(const int & tabIndex) {
	const main_window_shared_types::tab_type_e tabType = this->windowCore->tabs->getTabType(tabIndex);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Disconnect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");
	if (tabType == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		try {
			const main_window_tab::MainWindowTab * currentTab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(tabIndex));
			const main_window_web_engine_view::MainWindowWebEngineView * currentTabView = currentTab->widgetView;
			progress_bar::ProgressBar * loadBar = this->windowCore->bottomStatusBar->getLoadBar();

			disconnect(currentTabView, &main_window_web_engine_view::MainWindowWebEngineView::loadStarted, loadBar, &progress_bar::ProgressBar::startLoading);
			disconnect(currentTabView, &main_window_web_engine_view::MainWindowWebEngineView::loadProgress, loadBar, &progress_bar::ProgressBar::setValue);
			disconnect(currentTabView, &main_window_web_engine_view::MainWindowWebEngineView::loadFinished, loadBar, &progress_bar::ProgressBar::endLoading);

			// Make load bar invisible as we are disconnecting slots
				loadBar->setVisible(false);

		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	} else if (tabType == main_window_shared_types::tab_type_e::LABEL) {
		// TODO
	}
}

//************************************************************************************
// End definition of actions
//************************************************************************************

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnOffset(const int & offset) {
	global_types::sign_e sign = global_types::sign_e::NOSIGN;

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	const main_window_shared_types::offset_type_e offsetType = this->windowCore->getOffsetType();


	if (windowState == main_window_shared_types::state_e::MOVE_RIGHT) {
		sign = global_types::sign_e::PLUS;
	} else if (windowState == main_window_shared_types::state_e::MOVE_LEFT) {
		sign = global_types::sign_e::MINUS;
	} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (offsetType == main_window_shared_types::offset_type_e::RIGHT) {
			sign = global_types::sign_e::PLUS;
		} else if (offsetType == main_window_shared_types::offset_type_e::LEFT) {
			sign = global_types::sign_e::MINUS;
		}
	} else {
		QEXCEPTION_ACTION(throw,  "Requested to execute tab action in invalid window state " << windowState);
	}

	Q_ASSERT_X(((sign == global_types::sign_e::MINUS) || (sign == global_types::sign_e::PLUS)), "sign check to execute movement on offset", "sign input must be either global_types::sign_e::MINUS or global_types::sign_e::PLUS");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs, "DEBUG offset " << offset << " state " << windowState << " offset type " << offsetType);
	this->convertToAbsTabIndex(offset, sign);
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnTab(const int & index) {
	int tabIndex = main_window_ctrl_tab::emptyUserInput;
	// index is main_window_ctrl_tab::emptyUserInput if the argument is not passed
	if (index == main_window_ctrl_tab::emptyUserInput) {
		tabIndex = this->windowCore->getCurrentTabIndex();
	} else {
		// start indexing tab to close with 0
		tabIndex = index;
	}

	const int tabCount = this->windowCore->getTabCount();

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs, "DEBUG Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << tabCount);

	// Check that tabIndex is larger than 0 and there is at least a tab opened
	// By default, if not tabs are opened, the number of tabs is set to 0 and the current index is set to -1 therefore (tabCount > tabIndex) is true
	if ((tabCount > tabIndex) && (tabIndex >= 0) && (tabCount > 0)) {
		switch (windowState) {
			case main_window_shared_types::state_e::CLOSE_TAB:
				this->closeTab(tabIndex);
				break;
			case main_window_shared_types::state_e::TAB_MOVE:
				this->convertToAbsTabIndex(tabIndex, global_types::sign_e::NOSIGN);
				break;
			case main_window_shared_types::state_e::REFRESH_TAB:
				this->refreshUrl(tabIndex);
				break;
			default:
				QEXCEPTION_ACTION(throw,  "Undefined action to execute when in state " << windowState);
				break;
		}
	} else {
		const int maxTabRange = tabCount;
		QWARNING_PRINT(mainWindowCtrlTabTabs, "Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << maxTabRange);
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeTabAction(const int & userInput) {
	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	const main_window_shared_types::offset_type_e offsetType = this->windowCore->getOffsetType();

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
			if ((offsetType == main_window_shared_types::offset_type_e::LEFT) || (offsetType == main_window_shared_types::offset_type_e::RIGHT)) {
				this->executeActionOnOffset(userInput);
			} else if (offsetType == main_window_shared_types::offset_type_e::ABSOLUTE) {
				this->executeActionOnTab(userInput);
			} else {
				QEXCEPTION_ACTION(throw,  "Undefined direction of movement of tabs. Currently set to " << offsetType);
			}
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined tab action when in state " << windowState);
			break;
	}

	this->updateInfo();

	const int tabIndex = this->windowCore->getCurrentTabIndex();
	this->updateContent(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::processTabIndex(const QString & userInputStr) {
	// If indexStr is an empty string, do not pass any argument to executeTabAction (i.e. execute action on current tab)
	if (userInputStr.isEmpty()) {
		this->executeTabAction();
	} else {
		bool conversionSuccessful = false;
		// Convert string un a number in base 10
		const int userInputInt = userInputStr.toInt(&conversionSuccessful, 10);
		if (conversionSuccessful == true) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeTabAction(userInputInt);
		} else {
			QWARNING_PRINT(mainWindowCtrlTabTabs, "tab index " << userInputStr << " is not made up by numbers only");
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeCommand(const QString & command) {

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

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
		const QString userTypedText = this->windowCore->getUserText();

		// Retrieve main window controller state
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::IDLE);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "User typed text " << userTypedText);
				// If in state TAB MOVE and the windowCore->userText is empty after deleting the last character, set the move value to IDLE
				if ((userTypedText.isEmpty() == true) && (windowState == main_window_shared_types::state_e::TAB_MOVE)) {
					this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::IDLE);
					this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				}
				break;
			default:
				break;
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::keyPressEvent(QKeyEvent * event) {

	const int pressedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
		const QString userTypedText = this->windowCore->getUserText();

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
				this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::IDLE);
				break;
			default:
				this->setStateAction(windowState, event);
				break;
		}

	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();
	const main_window_shared_types::offset_type_e offsetType = this->windowCore->getOffsetType();

	switch (windowState) {
		case main_window_shared_types::state_e::OPEN_TAB:
		case main_window_shared_types::state_e::SEARCH:
			if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
				this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
			}
			break;
		case main_window_shared_types::state_e::CLOSE_TAB:
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
		case main_window_shared_types::state_e::REFRESH_TAB:
			if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
				this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
			} else {
				QWARNING_PRINT(mainWindowCtrlTabUserInput, "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar");
			}
			break;
		case main_window_shared_types::state_e::TAB_MOVE:
			if (offsetType == main_window_shared_types::offset_type_e::IDLE) {
				// If no sign is provided, the tab is considered as absolute value
				// If + or - sign is provided, then the value is considered to be relative to the current tab
				// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
				// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::ABSOLUTE);
					this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
				} else if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
					this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::RIGHT);
					this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				} else if ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_Minus)) {
					this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::LEFT);
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

void main_window_ctrl_tab::MainWindowCtrlTab::convertToAbsTabIndex(const int & offset, const global_types::sign_e & sign) {

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	int distance = 0;
	// offset is main_window_ctrl_tab::emptyUserInput if the argument is not passed
	if (offset == main_window_ctrl_tab::emptyUserInput) {
		switch (windowState) {
			case main_window_shared_types::state_e::MOVE_RIGHT:
			case main_window_shared_types::state_e::MOVE_LEFT:
			case main_window_shared_types::state_e::TAB_MOVE:
				distance = 1;
				break;
			default:
				QEXCEPTION_ACTION(throw,  "Unable to compute distance when in state " << windowState);
				break;
		}
	} else {
		distance = offset;
	}

	const int tabCount = this->windowCore->getTabCount();
	QEXCEPTION_ACTION_COND((tabCount <= 0), throw,  "Current number of opened tabs is " << tabCount << ". It is not possible to execute actin related to state " << windowState);
	const int signInt = static_cast<int>(sign);

	int tabIndexDst = 0;
	if (sign == global_types::sign_e::NOSIGN) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = this->windowCore->getCurrentTabIndex() + (signInt * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		QWARNING_PRINT(mainWindowCtrlTabTabs, "Offset " << offset << " is bigger than the number of tabs " << tabCount << ". Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange);
	}
	while (tabIndexDst < 0) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs, "DEBUG Tab " << tabIndexDst << " tab count " << tabCount << " current tab index " << this->windowCore->getCurrentTabIndex());
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	const int tabIndex = tabIndexDst % tabCount;

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Convert tab relative offset " << (signInt*offset) << " to absolute offset " << tabIndex);

	switch (windowState) {
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
			this->moveCursor(tabIndex);
			break;
		case main_window_shared_types::state_e::TAB_MOVE:
			this->moveTab(tabIndex);
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined action when in state " << windowState);
			break;
	}
}

QString main_window_ctrl_tab::MainWindowCtrlTab::createUrl(const QString & search) {
	const bool containsSpace = search.contains(" ");
	const bool containsWww = search.contains(main_window_ctrl_tab::www);
	const int numberDots = search.count(".");

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

void main_window_ctrl_tab::MainWindowCtrlTab::printStrInCurrentTab(const QString & tabTitle, const QString & tabContent, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Set text in center window with title " << tabTitle);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  tabContent);

	// Get tabs
	main_window_tab_widget::MainWindowTabWidget * tabWidget = this->windowCore->tabs;

	const main_window_shared_types::tab_type_e desiredTabType = main_window_shared_types::tab_type_e::LABEL;

	// START -> data test
	const char * filename = static_cast<const char *>(data);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "data test filename: " << filename);
	// END -> data test

	// Disable events while updating tabs
	tabWidget->setUpdatesEnabled(false);

	int tabCount = this->windowCore->getTabCount();

	// Get current tab index
	int currentTabIndex = tabWidget->currentIndex();

	// If not tabs, then create one
	if (tabCount == 0) {
		currentTabIndex = this->addNewTab(tabTitle, desiredTabType, data);
		tabCount = this->windowCore->getTabCount();
		QEXCEPTION_ACTION_COND((currentTabIndex >= tabCount), throw,  "Current tab index " << currentTabIndex << " must be larger than the number of tabs " << tabCount);
	} else {
		this->windowCore->tabs->changeTabType(currentTabIndex, desiredTabType, data);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs, "Current tab index is " << currentTabIndex << " and the tab widget has " << tabCount << " tabs");

	try {
		// Set tab title
		tabWidget->setTabText(currentTabIndex, tabTitle);
		QLabel * currentTabLabel = dynamic_cast<QLabel *>(tabWidget->widget(currentTabIndex, true));

		currentTabLabel->setText(tabContent);

		this->updateContent(currentTabIndex);

		// Disable events after updating tabs
		tabWidget->setUpdatesEnabled(true);

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

bool main_window_ctrl_tab::MainWindowCtrlTab::changeWindowState(const main_window_shared_types::state_e & requestedWindowState) {
	bool isValid = false;
	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	if (windowState == requestedWindowState) {
		// No state change is always valid
		isValid = true;
	} else {
		isValid = this->isValidWindowState(requestedWindowState);

		if (isValid == true) {
			this->windowCore->setMainWindowState(requestedWindowState);
			// If requesting to go to the idle state, do not 
			if (requestedWindowState == main_window_shared_types::state_e::IDLE) {
				this->setAllShortcutEnabledProperty(true);
			} else {
				this->setAllShortcutEnabledProperty(false);
			}
			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
		} else {
			QWARNING_PRINT(mainWindowCtrlTabTabs, "Ignoring request to go from state " << windowState << " to state " << requestedWindowState);
		}
	}

	return isValid;
}

bool main_window_ctrl_tab::MainWindowCtrlTab::isValidWindowState(const main_window_shared_types::state_e & requestedWindowState) {
	bool isValid = false;
	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	const int tabCount = this->windowCore->getTabCount();

	switch (requestedWindowState) {
		case main_window_shared_types::state_e::IDLE:
			// It is always possible to go to the idle state
			isValid = true;
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
			// It is only possible to open a tab if in the idle state
			isValid = (windowState == main_window_shared_types::state_e::IDLE);
			break;
		case main_window_shared_types::state_e::SEARCH:
		case main_window_shared_types::state_e::REFRESH_TAB:
		case main_window_shared_types::state_e::CLOSE_TAB:
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
		case main_window_shared_types::state_e::TAB_MOVE:
			// It is only possible to perform an operation other than opening a tab and going to the idle state if the current state is idle and at least 1 tab is opened
			isValid = ((tabCount > 0) && (windowState == main_window_shared_types::state_e::IDLE));
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}
