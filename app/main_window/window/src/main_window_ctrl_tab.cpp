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


main_window_ctrl_tab::MainWindowCtrlTab::MainWindowCtrlTab(QWidget * parent, QSharedPointer<main_window_core::MainWindowCore> core) : main_window_ctrl_base::MainWindowCtrlBase(parent, core, main_window_ctrl_tab::commandFileFullPath) {

	// Shortcuts
	this->createExtraShortcuts();

	// Connect signals and slots
	this->connectExtraSignals();

	this->findDirection = main_window_shared_types::navigation_type_e::UNDEFINED;
}

main_window_ctrl_tab::MainWindowCtrlTab::~MainWindowCtrlTab() {

}

void main_window_ctrl_tab::MainWindowCtrlTab::createExtraShortcuts() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Create shortcuts");

}

void main_window_ctrl_tab::MainWindowCtrlTab::connectExtraSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Connect signals");

	// open tab action (from fileMenu)
	connect(this->windowCore->topMenuBar->getFileMenu()->openTabAction, &QAction::triggered, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab);

	// When the file has been read, then show it on the screen
	connect(this->windowCore->topMenuBar->getFileMenu(), &file_menu::FileMenu::updateCenterWindowSignal, this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::openFileInCurrentTab);

	connect(this, &main_window_ctrl_tab::MainWindowCtrlTab::currentTabSrcChanged, this->windowCore->bottomStatusBar->getContentPathText(), &elided_label::ElidedLabel::setText);

	// Updates to the window depending on changes in tabs
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::tabSourceChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::createContentPathTextFromSource);

	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::currentChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar);
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::numberTabsChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar);

	// Progress bar connections
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::tabNearlyDisconnected, this, &main_window_ctrl_tab::MainWindowCtrlTab::disconnectProgressBar);
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::tabNearlyConnected, this, &main_window_ctrl_tab::MainWindowCtrlTab::connectProgressBar);

	// Update info bar
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::tabCloseRequested, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar);

}

//************************************************************************************
// Start definition of set up slots
//************************************************************************************
void main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Open new tab");
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::OPEN_TAB;
	this->changeWindowState(requestedWindowState, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
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
	this->addNewTab(search, main_window_shared_types::page_type_e::WEB_CONTENT, nullptr);
}

int main_window_ctrl_tab::MainWindowCtrlTab::addNewTab(const QString & search, const main_window_shared_types::page_type_e & type, const void * data) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Open tab with label " << search);

	const int tabCount = this->windowCore->getTabCount();
	if (tabCount > 0) {
		// Disconnect signals only if at least 1 tabs is already present
		int currentTabIndex = this->windowCore->getCurrentTabIndex();
		this->disconnectProgressBar(currentTabIndex);
	}

	const int tabIndex = this->windowCore->tabs->addTab(type, search, data);

	// Connect signals from tab the cursor is pointing to
	this->connectProgressBar(tabIndex);

	QEXCEPTION_ACTION_COND((tabIndex < 0), throw, "It cannot be negative");

	return tabIndex;
}

void main_window_ctrl_tab::MainWindowCtrlTab::newSearchTab(const int & index, const QString & search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "User input " << search << " in tab " << index);
	const main_window_shared_types::page_type_e desiredType = main_window_shared_types::page_type_e::WEB_CONTENT;
	this->windowCore->tabs->changeTabContent(index, desiredType, search, nullptr);
}

void main_window_ctrl_tab::MainWindowCtrlTab::searchCurrentTab(const QString & search) {
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	const int tabCount = this->windowCore->getTabCount();
	QEXCEPTION_ACTION_COND(((tabIndex < 0) || (tabCount <= 0)), throw, "Unable to perform search of " << search << " in tab " << tabIndex << ". Note that a negative tab index may be cause by the fact that there are no tabs opened in the browser - current count of opened tabs is " << tabCount);

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	switch (windowState) {
		case main_window_shared_types::state_e::SEARCH:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Search " << search << " in tab " << tabIndex);
			this->newSearchTab(tabIndex, search);
			break;
		case main_window_shared_types::state_e::FIND:
		case main_window_shared_types::state_e::FIND_NEXT:
		case main_window_shared_types::state_e::FIND_PREV:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Find " << search << " in tab " << tabIndex << " direction " << this->findDirection);
			this->windowCore->tabs->findInTab(tabIndex, search, this->findDirection);
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined action to execute when in state " << windowState);
			break;
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::goToPageInHistory(const main_window_shared_types::navigation_type_e direction) {
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	this->windowCore->tabs->goToHistoryItem(tabIndex, direction);
}

void main_window_ctrl_tab::MainWindowCtrlTab::extractContentPath(const int & index) {

	QString path (QString::null);
	const int tabCount = this->windowCore->getTabCount();

	if (tabCount > 0) {
		const main_window_shared_types::page_type_e tabType = this->windowCore->tabs->getPageType(index);
		const QString tabSrc = this->windowCore->tabs->getPageSource(index);

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUrl, "Set contentPathText for tab at index " << index << " of type " << tabType << " and source " << tabSrc);
		this->createContentPathTextFromSource(tabType, tabSrc);

	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::reloadTab(const int & tabIndex) {
	this->windowCore->tabs->reloadTabContent(tabIndex);
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
	const main_window_shared_types::page_type_e tabType = this->windowCore->tabs->getPageType(tabIndex);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");
	try {
		main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(tabIndex));
		const main_window_tab_load_manager::MainWindowTabLoadManager * loadManager = tab->getLoadManager();
		progress_bar::ProgressBar * bar = this->windowCore->bottomStatusBar->getLoadBar();

		connect(loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::progressChanged, bar, &progress_bar::ProgressBar::setValue);

		bar->setValue(loadManager->getProgress());

		// Move focus to the tab index
		tab->setFocus();

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::disconnectProgressBar(const int & tabIndex) {
	const main_window_shared_types::page_type_e tabType = this->windowCore->tabs->getPageType(tabIndex);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Disconnect connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");
	try {
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->windowCore->tabs->widget(tabIndex));
		const main_window_tab_load_manager::MainWindowTabLoadManager * loadManager = tab->getLoadManager();
		const progress_bar::ProgressBar * bar = this->windowCore->bottomStatusBar->getLoadBar();

		disconnect(loadManager, &main_window_tab_load_manager::MainWindowTabLoadManager::progressChanged, bar, &progress_bar::ProgressBar::setValue);
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
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
	} else if (windowState == main_window_shared_types::state_e::MOVE_TAB) {
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
			case main_window_shared_types::state_e::MOVE_TAB:
				this->convertToAbsTabIndex(tabIndex, global_types::sign_e::NOSIGN);
				break;
			case main_window_shared_types::state_e::REFRESH_TAB:
				this->reloadTab(tabIndex);
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
		case main_window_shared_types::state_e::MOVE_TAB:
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
				if (userTypedText.isEmpty() == true) {
					if (windowState != main_window_shared_types::state_e::COMMAND) {
						if (windowState == main_window_shared_types::state_e::MOVE_TAB) {
							this->windowCore->setOffsetType(main_window_shared_types::offset_type_e::IDLE);
							this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
						}
						this->moveToCommandStateFromNonIdleState(windowState, static_cast<Qt::Key>(releasedKey));
					}
				}
				break;
			default:
				break;
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeAction(const main_window_shared_types::state_e & windowState) {
	const QString userTypedText = this->windowCore->getUserText();

	switch (windowState) {
		case main_window_shared_types::state_e::OPEN_TAB:
			this->addNewTabAndSearch(userTypedText);
			break;
		case main_window_shared_types::state_e::SEARCH:
			this->searchCurrentTab(userTypedText);
			break;
		case main_window_shared_types::state_e::FIND:
			this->findDirection = main_window_shared_types::navigation_type_e::UNDEFINED;
			this->searchCurrentTab(userTypedText);
			break;
		case main_window_shared_types::state_e::FIND_NEXT:
			this->findDirection = main_window_shared_types::navigation_type_e::NEXT;
			this->searchCurrentTab(QString::null);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::FIND_PREV:
			this->findDirection = main_window_shared_types::navigation_type_e::PREVIOUS;
			this->searchCurrentTab(QString::null);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::REFRESH_TAB:
		case main_window_shared_types::state_e::CLOSE_TAB:
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
		case main_window_shared_types::state_e::MOVE_TAB:
			this->processTabIndex(userTypedText);
			break;
		case main_window_shared_types::state_e::COMMAND:
			this->executeCommand(userTypedText, main_window_shared_types::state_postprocessing_e::ACTION);
			break;
		default:
			// Do nothing by default
			break;
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();
	const main_window_shared_types::offset_type_e offsetType = this->windowCore->getOffsetType();
	const QString userTypedText = this->windowCore->getUserText();

	switch (windowState) {
		case main_window_shared_types::state_e::COMMAND:
			if (pressedKey == Qt::Key_Space) {
				this->executeCommand(userTypedText, main_window_shared_types::state_postprocessing_e::NONE);
			}
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
		case main_window_shared_types::state_e::SEARCH:
		case main_window_shared_types::state_e::FIND:
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
		case main_window_shared_types::state_e::MOVE_TAB:
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
			case main_window_shared_types::state_e::MOVE_TAB:
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
		case main_window_shared_types::state_e::MOVE_TAB:
			this->moveTab(tabIndex);
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined action when in state " << windowState);
			break;
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) {
	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Current state " << windowState << " previousState " << previousState);
	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case main_window_shared_types::state_e::IDLE:
			this->setAllShortcutEnabledProperty(true);
			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
		case main_window_shared_types::state_e::SEARCH:
		case main_window_shared_types::state_e::REFRESH_TAB:
		case main_window_shared_types::state_e::CLOSE_TAB:
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
		case main_window_shared_types::state_e::MOVE_TAB:
		case main_window_shared_types::state_e::FIND:
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		case main_window_shared_types::state_e::FIND_NEXT:
			this->findDirection = main_window_shared_types::navigation_type_e::NEXT;
			this->searchCurrentTab(QString::null);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::FIND_PREV:
			this->findDirection = main_window_shared_types::navigation_type_e::PREVIOUS;
			this->searchCurrentTab(QString::null);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::SCROLL_UP:
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::SCROLL_DOWN:
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::HISTORY_PREV:
			this->goToPageInHistory(main_window_shared_types::navigation_type_e::PREVIOUS);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::HISTORY_NEXT:
			this->goToPageInHistory(main_window_shared_types::navigation_type_e::NEXT);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		default:
			this->setAllShortcutEnabledProperty(false);
			break;
	}
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
		case main_window_shared_types::state_e::FIND:
		case main_window_shared_types::state_e::FIND_NEXT:
		case main_window_shared_types::state_e::FIND_PREV:
		case main_window_shared_types::state_e::SCROLL_UP:
		case main_window_shared_types::state_e::SCROLL_DOWN:
		case main_window_shared_types::state_e::HISTORY_PREV:
		case main_window_shared_types::state_e::HISTORY_NEXT:
			// It is only possible to perform an operation on a signel tab if the current state is idle and at least 1 tab is opened
			isValid = ((tabCount > 0) && (windowState == main_window_shared_types::state_e::IDLE));
			break;
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
		case main_window_shared_types::state_e::MOVE_TAB:
			// It is only possible to perform an operation that requires movement of cursors or tabs if the current state is idle and at least 2 tab is opened
			isValid = ((tabCount > 1) && (windowState == main_window_shared_types::state_e::IDLE));
			break;
		case main_window_shared_types::state_e::COMMAND:
			// Set to false as transition to COMMAND state is handled in the base class by the global conditions
			isValid = false;
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}

void main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar(const int & tabIndex) {
	this->updateInfo(tabIndex);
	this->extractContentPath(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::createContentPathTextFromSource(const main_window_shared_types::page_type_e & type, const QString & source) {

	QString text(QString::null);

	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
			// If the type is WEB_CONTENT, then the URL will be shown in the widget displaying the content
			text = source;
			break;
		case main_window_shared_types::page_type_e::TEXT:
			// Prepend file: to source
			text = QString("file:") + source;
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to create string from " << source << " to print in the content path widget " << " because tab type " << type << " is not recognised");
			break;
	}

	emit this->currentTabSrcChanged(text);
}
