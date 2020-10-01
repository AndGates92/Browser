/**
 * @copyright
 * @file main_window_ctrl_tab.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Control functions
 */

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtGui/QKeyEvent>

// Required by qInfo
#include <QtCore/QtDebug>

#include "key_sequence.h"
#include "main_window_ctrl_tab.h"
#include "main_window_shared_functions.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlTabOverall, "mainWindowCtrlTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabUserInput, "mainWindowCtrlTab.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabSearch, "mainWindowCtrlTab.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabTabs, "mainWindowCtrlTab.tabs", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabUrl, "mainWindowCtrlTab.url", MSG_TYPE_LEVEL)

namespace main_window_ctrl_tab {

	namespace {

		/**
		 * @brief https string
		 *
		 */
		static const QString https("https://");

		/**
		 * @brief www string
		 *
		 */
		static const QString www("www.");

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		static const QString defaultSearchEngine(https + www + "duckduckgo.com/?q=%1");

		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const QString commandFilePath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		static const QString commandFileName("tab_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const QString commandFileFullPath(commandFilePath + commandFileName);

	}

}

main_window_ctrl_tab::MainWindowCtrlTab::MainWindowCtrlTab(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core) : main_window_ctrl_base::MainWindowCtrlBase(parent, core, main_window_ctrl_tab::commandFileFullPath), findSettings(QString(), global_enums::offset_type_e::IDLE, false, false) {

	// Shortcuts
	this->createExtraShortcuts();

	// Connect signals and slots
	this->connectExtraSignals();

}

main_window_ctrl_tab::MainWindowCtrlTab::~MainWindowCtrlTab() {

}

void main_window_ctrl_tab::MainWindowCtrlTab::createExtraShortcuts() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Create shortcuts");

}

void main_window_ctrl_tab::MainWindowCtrlTab::connectExtraSignals() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Connect signals");

	// open tab action (from fileMenu)
	connect(this->windowCore->topMenuBar->getFileMenu()->openTabAction.get(), &QAction::triggered, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab);

	std::unique_ptr<main_window_tab_widget::MainWindowTabWidget> & tabs = this->windowCore->tabs;

	// When the file has been read, then show it on the screen
	connect(this->windowCore->topMenuBar->getFileMenu().get(), &file_menu::FileMenu::updateCenterWindowSignal, tabs.get(), &main_window_tab_widget::MainWindowTabWidget::openFileInCurrentTab);
	connect(this->windowCore->popup->getOpenFilePopup().get(), &open_popup::OpenPopup::fileRead, tabs.get(), &main_window_tab_widget::MainWindowTabWidget::openFileInCurrentTab);

	// Search text in webpage
	connect(this->windowCore->topMenuBar->getEditMenu().get(), &edit_menu::EditMenu::triggerSearch, this, &main_window_ctrl_tab::MainWindowCtrlTab::setUpSearchFromMenu);

	std::unique_ptr<main_window_status_bar::MainWindowStatusBar> & statusBar = this->windowCore->bottomStatusBar;
	connect(this, &main_window_ctrl_tab::MainWindowCtrlTab::currentTabSrcChanged, statusBar.get(), &main_window_status_bar::MainWindowStatusBar::setContentPathText);

	// Updates to the window depending on changes in tabs
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::tabSourceChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::createContentPathTextFromSource);

	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::currentChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar);
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::numberTabsChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar);

	// Progress bar connections
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::tabNearlyDisconnected, this, &main_window_ctrl_tab::MainWindowCtrlTab::disconnectTab);
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::tabNearlyConnected, this, &main_window_ctrl_tab::MainWindowCtrlTab::connectTab);

	// Update info bar
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::tabCloseRequested, this, &main_window_ctrl_tab::MainWindowCtrlTab::updateStatusBar);

	// Search text in tab
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::searchResultChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::printSearchResult);
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::findTextFinished, this, &main_window_ctrl_tab::MainWindowCtrlTab::processSearchReturnValue);

	// History of the tab
	connect(tabs.get(), &main_window_tab_widget::MainWindowTabWidget::historyItemChanged, this, &main_window_ctrl_tab::MainWindowCtrlTab::historyBoundaryHit);

}

//************************************************************************************
// Start definition of set up slots
//************************************************************************************
void main_window_ctrl_tab::MainWindowCtrlTab::setUpOpenNewTab() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Open new tab");
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
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Close tab " << index);
	this->windowCore->tabs->removeTab(index);
}

void main_window_ctrl_tab::MainWindowCtrlTab::addNewTabAndSearch(const QString & search) {
	const int index = this->addNewTab(main_window_shared_types::page_type_e::UNKNOWN, nullptr);
	this->searchTab(index, search);
}

int main_window_ctrl_tab::MainWindowCtrlTab::addNewTab(const main_window_shared_types::page_type_e & type, const void * data) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Open tab of type " << type);

	const int tabCount = this->windowCore->getTabCount();
	if (tabCount > 0) {
		// Disconnect signals only if at least 1 tabs is already present
		int currentTabIndex = this->windowCore->getCurrentTabIndex();
		this->disconnectTab(currentTabIndex);
	}

	const int tabIndex = this->windowCore->tabs->addTab(type, data);

	// Connect signals from tab the cursor is pointing to
	this->connectTab(tabIndex);

	QEXCEPTION_ACTION_COND((tabIndex < 0), throw, "It cannot be negative");

	return tabIndex;
}

void main_window_ctrl_tab::MainWindowCtrlTab::searchTab(const int & index, const QString & search) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "User input " << search << " in tab " << index);
	main_window_shared_types::page_type_e type = this->windowCore->tabs->getPageType(index);

	if (type == main_window_shared_types::page_type_e::UNKNOWN) {
		if (main_window_shared_functions::isFile(search) == true) {
			type = main_window_shared_types::page_type_e::TEXT;
		} else if ((main_window_shared_functions::isUrl(search) == true) || (main_window_shared_functions::isText(search) == true)) {
			type = main_window_shared_types::page_type_e::WEB_CONTENT;
		} else {
			QEXCEPTION_ACTION(throw, "Unable to associate a  page type to search " << search);
		}
	}
	this->windowCore->tabs->changeTabContent(index, type, search, nullptr);
}

void main_window_ctrl_tab::MainWindowCtrlTab::searchCurrentTab(const QString & search) {
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	const int tabCount = this->windowCore->getTabCount();
	QEXCEPTION_ACTION_COND(((tabIndex < 0) || (tabCount <= 0)), throw, "Unable to perform search of " << search << " in tab " << tabIndex << ". Note that a negative tab index may be caused by the fact that there are no tabs opened in the browser - current count of opened tabs is " << tabCount);

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	switch (windowState) {
		case main_window_shared_types::state_e::NEW_SEARCH:
		case main_window_shared_types::state_e::EDIT_SEARCH:
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Search " << search << " in tab " << tabIndex);
			this->searchTab(tabIndex, search);
			break;
		case main_window_shared_types::state_e::FIND:
		case main_window_shared_types::state_e::FIND_DOWN:
		case main_window_shared_types::state_e::FIND_UP:
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Find: " << this->findSettings);
			this->windowCore->tabs->findInTab(tabIndex, this->findSettings);
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Undefined action to execute when in state " << windowState);
			break;
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::scrollTab(const global_enums::offset_type_e direction) {
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	this->windowCore->tabs->scrollTab(tabIndex, direction);
}

void main_window_ctrl_tab::MainWindowCtrlTab::goToPageInHistory(const main_window_shared_types::navigation_type_e direction) {
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	this->windowCore->tabs->goToHistoryItem(tabIndex, direction);
}

void main_window_ctrl_tab::MainWindowCtrlTab::extractContentPath(const int & index) {

	const int tabCount = this->windowCore->getTabCount();

	if (tabCount > 0) {
		const main_window_shared_types::page_type_e tabType = this->windowCore->tabs->getPageType(index);
		const QString tabSrc = this->windowCore->tabs->getPageSource(index);

		QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabUrl, "Set contentPathText for tab at index " << index << " of type " << tabType << " and source " << tabSrc);
		this->createContentPathTextFromSource(tabType, tabSrc);

	} else {
		emit this->currentTabSrcChanged(QString());
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::reloadTab(const int & tabIndex) {
	this->windowCore->tabs->reloadTabContent(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveTab(const int & tabIndex) {
	const int tabIndexCurrent = this->windowCore->tabs->currentIndex();
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Move tab " << tabIndexCurrent << " to " << tabIndex);
	this->windowCore->tabs->moveTab(tabIndexCurrent, tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveCursor(const int & tabIndex) {
	// Disconnect signals from tab the cursor was pointing to
	const int currentTabIndex = this->windowCore->getCurrentTabIndex();
	this->disconnectTab(currentTabIndex);

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Move cursor to tab " << tabIndex);
	this->windowCore->tabs->setCurrentIndex(tabIndex);
	// Connect signals from tab the cursor is pointing to
	this->connectTab(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::connectTab(const int & tabIndex) {
	const main_window_shared_types::page_type_e tabType = this->windowCore->tabs->getPageType(tabIndex);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");

	std::shared_ptr<main_window_tab::MainWindowTab> tab = this->windowCore->tabs->widget(tabIndex);

	std::unique_ptr<main_window_status_bar::MainWindowStatusBar> & statusBar = this->windowCore->bottomStatusBar;
	connect(tab.get(), &main_window_tab::MainWindowTab::verticalScrollChanged, statusBar.get(), &main_window_status_bar::MainWindowStatusBar::setVScroll);
	statusBar->setVScroll(tab->getVerticalScroll());

	connect(tab.get(), &main_window_tab::MainWindowTab::loadProgressChanged, statusBar.get(), &main_window_status_bar::MainWindowStatusBar::setProgressValue);
	statusBar->setProgressValue(tab->getLoadProgress());

	// Move focus to the tab index
	tab->setFocus();
}

void main_window_ctrl_tab::MainWindowCtrlTab::disconnectTab(const int & tabIndex) {
	const main_window_shared_types::page_type_e tabType = this->windowCore->tabs->getPageType(tabIndex);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Disconnect connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");

	const std::shared_ptr<main_window_tab::MainWindowTab> tab = this->windowCore->tabs->widget(tabIndex);

	std::unique_ptr<main_window_status_bar::MainWindowStatusBar> & statusBar = this->windowCore->bottomStatusBar;
	disconnect(tab.get(), &main_window_tab::MainWindowTab::verticalScrollChanged, statusBar.get(), &main_window_status_bar::MainWindowStatusBar::setVScroll);
	disconnect(tab.get(), &main_window_tab::MainWindowTab::loadProgressChanged, statusBar.get(), &main_window_status_bar::MainWindowStatusBar::setProgressValue);

}

//************************************************************************************
// End definition of actions
//************************************************************************************

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnOffset(const int & offset) {
	global_enums::sign_e sign = global_enums::sign_e::NOSIGN;

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	const global_enums::offset_type_e offsetType = this->windowCore->getOffsetType();


	if (windowState == main_window_shared_types::state_e::MOVE_RIGHT) {
		sign = global_enums::sign_e::PLUS;
	} else if (windowState == main_window_shared_types::state_e::MOVE_LEFT) {
		sign = global_enums::sign_e::MINUS;
	} else if (windowState == main_window_shared_types::state_e::MOVE_TAB) {
		if (offsetType == global_enums::offset_type_e::RIGHT) {
			sign = global_enums::sign_e::PLUS;
		} else if (offsetType == global_enums::offset_type_e::LEFT) {
			sign = global_enums::sign_e::MINUS;
		}
	} else {
		QEXCEPTION_ACTION(throw,  "Requested to execute tab action in invalid window state " << windowState);
	}

	Q_ASSERT_X(((sign == global_enums::sign_e::MINUS) || (sign == global_enums::sign_e::PLUS)), "sign check to execute movement on offset", "sign input must be either global_enums::sign_e::MINUS or global_enums::sign_e::PLUS");
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

	// Check that tabIndex is larger than 0 and there is at least a tab opened
	// By default, if not tabs are opened, the number of tabs is set to 0 and the current index is set to -1 therefore (tabCount > tabIndex) is true
	if ((tabCount > tabIndex) && (tabIndex >= 0) && (tabCount > 0)) {
		switch (windowState) {
			case main_window_shared_types::state_e::CLOSE_TAB:
				this->closeTab(tabIndex);
				break;
			case main_window_shared_types::state_e::MOVE_TAB:
				this->convertToAbsTabIndex(tabIndex, global_enums::sign_e::NOSIGN);
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
	const global_enums::offset_type_e offsetType = this->windowCore->getOffsetType();

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
			if ((offsetType == global_enums::offset_type_e::LEFT) || (offsetType == global_enums::offset_type_e::RIGHT)) {
				this->executeActionOnOffset(userInput);
			} else if (offsetType == global_enums::offset_type_e::ABSOLUTE) {
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
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeTabAction(userInputInt);
		} else {
			QWARNING_PRINT(mainWindowCtrlTabTabs, "tab index " << userInputStr << " is not made up by numbers only");
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		// Retrieve main window controller state
		QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->windowCore->setOffsetType(global_enums::offset_type_e::IDLE);
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
		case main_window_shared_types::state_e::NEW_SEARCH:
		case main_window_shared_types::state_e::EDIT_SEARCH:
			this->searchCurrentTab(userTypedText);
			break;
		case main_window_shared_types::state_e::FIND:
			this->findSettings.setDirection(global_enums::offset_type_e::DOWN);
			this->findSettings.setText(userTypedText);
			this->findSettings.setMatchFullWord(false);
			this->findSettings.setCaseSensitive(false);
			this->searchCurrentTab(QString());
			break;
		case main_window_shared_types::state_e::FIND_DOWN:
			this->findSettings.setDirection(global_enums::offset_type_e::DOWN);
			this->searchCurrentTab(QString());
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::FIND_UP:
			this->findSettings.setDirection(global_enums::offset_type_e::UP);
			this->searchCurrentTab(QString());
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::SCROLL_UP:
			this->scrollTab(global_enums::offset_type_e::UP);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::SCROLL_DOWN:
			this->scrollTab(global_enums::offset_type_e::DOWN);
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
	const global_enums::offset_type_e offsetType = this->windowCore->getOffsetType();
	const QString userTypedText = this->windowCore->getUserText();

	switch (windowState) {
		case main_window_shared_types::state_e::COMMAND:
			if (pressedKey == Qt::Key_Space) {
				this->executeCommand(userTypedText, main_window_shared_types::state_postprocessing_e::NONE);
			}
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
		case main_window_shared_types::state_e::NEW_SEARCH:
		case main_window_shared_types::state_e::EDIT_SEARCH:
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
			if (offsetType == global_enums::offset_type_e::IDLE) {
				// If no sign is provided, the tab is considered as absolute value
				// If + or - sign is provided, then the value is considered to be relative to the current tab
				// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
				// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->windowCore->setOffsetType(global_enums::offset_type_e::ABSOLUTE);
					this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
				} else if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
					this->windowCore->setOffsetType(global_enums::offset_type_e::RIGHT);
					this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				} else if ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_Minus)) {
					this->windowCore->setOffsetType(global_enums::offset_type_e::LEFT);
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
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::convertToAbsTabIndex(const int & offset, const global_enums::sign_e & sign) {

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
	if (sign == global_enums::sign_e::NOSIGN) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = this->windowCore->getCurrentTabIndex() + (signInt * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		QWARNING_PRINT(mainWindowCtrlTabTabs, "Offset " << offset << " is bigger than the number of tabs " << tabCount << ". Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange);
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	const int tabIndex = tabIndexDst % tabCount;

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Convert tab relative offset " << (signInt*offset) << " to absolute offset " << tabIndex);

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
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlTabTabs,  "Current state " << windowState << " previousState " << previousState);

	const int tabCount = this->windowCore->getTabCount();
	std::shared_ptr<main_window_tab::MainWindowTab> tab = nullptr;
	QString searchText = QString();
	if (tabCount > 0) {
		const int tabIndex = this->windowCore->getCurrentTabIndex();
		tab = this->windowCore->tabs->widget(tabIndex);
		searchText = tab->getSearchText();
	}

	// Hide search results if not in find state
	const bool isFindState = ((windowState == main_window_shared_types::state_e::FIND) || (windowState == main_window_shared_types::state_e::FIND_DOWN) || (windowState == main_window_shared_types::state_e::FIND_UP));
	std::unique_ptr<main_window_status_bar::MainWindowStatusBar> & statusBar = this->windowCore->bottomStatusBar;
	statusBar->showSearchResult(isFindState);

	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case main_window_shared_types::state_e::OPEN_FILE:
			this->setAllShortcutEnabledProperty(false);
			this->createOpenPrompt();
			// Set window state back to idle to be ready to accept a new command upon closure of the popup
			//this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::IDLE:
			this->setAllShortcutEnabledProperty(true);
			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
		case main_window_shared_types::state_e::NEW_SEARCH:
		case main_window_shared_types::state_e::REFRESH_TAB:
		case main_window_shared_types::state_e::CLOSE_TAB:
		case main_window_shared_types::state_e::MOVE_RIGHT:
		case main_window_shared_types::state_e::MOVE_LEFT:
		case main_window_shared_types::state_e::MOVE_TAB:
		case main_window_shared_types::state_e::FIND:
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		case main_window_shared_types::state_e::EDIT_SEARCH:
			QEXCEPTION_ACTION_COND((tab == nullptr), throw,  "Postprocessing state " << windowState << ": Unable to edit string used for previous search as pointer to tab is " << tab.get());
			this->printUserInput(main_window_shared_types::text_action_e::SET, searchText);
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		case main_window_shared_types::state_e::FIND_DOWN:
			this->findSettings.setDirection(global_enums::offset_type_e::DOWN);
			this->searchCurrentTab(QString());
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::FIND_UP:
			this->findSettings.setDirection(global_enums::offset_type_e::UP);
			this->searchCurrentTab(QString());
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::SCROLL_UP:
			this->scrollTab(global_enums::offset_type_e::UP);
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::SCROLL_DOWN:
			this->scrollTab(global_enums::offset_type_e::DOWN);
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
		case main_window_shared_types::state_e::OPEN_FILE:
		case main_window_shared_types::state_e::IDLE:
			// It is always possible to go to the idle state
			isValid = true;
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
			// It is only possible to open a tab if in the idle state
			isValid = (windowState == main_window_shared_types::state_e::IDLE);
			break;
		case main_window_shared_types::state_e::NEW_SEARCH:
		case main_window_shared_types::state_e::EDIT_SEARCH:
		case main_window_shared_types::state_e::REFRESH_TAB:
		case main_window_shared_types::state_e::CLOSE_TAB:
		case main_window_shared_types::state_e::FIND:
		case main_window_shared_types::state_e::FIND_DOWN:
		case main_window_shared_types::state_e::FIND_UP:
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
	this->updateScroll();
	this->extractContentPath(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::printSearchResult(const main_window_tab_search::search_data_s & data) const {
	std::unique_ptr<main_window_status_bar::MainWindowStatusBar> & statusBar = this->windowCore->bottomStatusBar;
	const bool textFound = (data.numberOfMatches > 0);
	if (textFound == true) {
		// Integers are to be converted in base 10
		const int base = 10;
		QString text = QString();
		text = QString("search: ") + QString::number(data.activeMatch, base) + QString("/") + QString::number(data.numberOfMatches, base);

		statusBar->setSearchResultText(text);
	}

	// Show search result label only of text has been found
	statusBar->showSearchResult(textFound);

}

void main_window_ctrl_tab::MainWindowCtrlTab::historyBoundaryHit(const global_enums::element_position_e & position) {

	if ((position == global_enums::element_position_e::BEGINNING) || (position == global_enums::element_position_e::END)) {
		std::shared_ptr<main_window_popup_container::MainWindowPopupContainer> container = this->windowCore->popup;
		bool success = container->showWarningPopup();
		QEXCEPTION_ACTION_COND((success == false), throw, "Unable to show Warning popup");

		std::shared_ptr<label_popup::LabelPopup> labelPopup = container->getWarningPopup();
		QString positionText = QString("unknown position");
		if (position == global_enums::element_position_e::BEGINNING) {
			positionText = "beginning";
		} else if (position == global_enums::element_position_e::END) {
			positionText = "end";
		}
		QString popupText = QString();
		popupText = QString("At the ") + positionText + QString(" of the history.");
		labelPopup->setLabelText(popupText);
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::processSearchReturnValue(const bool & found) {

	if (found == false) {
		std::shared_ptr<main_window_popup_container::MainWindowPopupContainer> container = this->windowCore->popup;
		bool success = container->showWarningPopup();
		QEXCEPTION_ACTION_COND((success == false), throw, "Unable to show Warning popup");

		std::shared_ptr<label_popup::LabelPopup> labelPopup = container->getWarningPopup();
		QString popupText = QString();
		QString text = this->findSettings.getText();
		if (text.isEmpty() == true) {
			text = "<empty string>";
		}
		popupText = QString("No match for string ") + text + QString(" in current tab.");
		labelPopup->setLabelText(popupText);
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::createContentPathTextFromSource(const main_window_shared_types::page_type_e & type, const QString & source) {

	QString text = QString();

	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
			// If the type is WEB_CONTENT, then the URL will be shown in the widget displaying the content
			text = source;
			break;
		case main_window_shared_types::page_type_e::TEXT:
			// Prepend file: to source
			text = QString("file:") + source;
			break;
		case main_window_shared_types::page_type_e::UNKNOWN:
			text = QString("Unknown tab type");
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to create string from " << source << " to print in the content path widget " << " because tab type " << type << " is not recognised");
			break;
	}

	emit this->currentTabSrcChanged(text);
}

void main_window_ctrl_tab::MainWindowCtrlTab::createOpenPrompt() {
	std::shared_ptr<main_window_popup_container::MainWindowPopupContainer> container = this->windowCore->popup;
	bool success = container->showOpenFilePopup();
	container->setFocus();

	QEXCEPTION_ACTION_COND((success == false), throw, "Unable to show OpenFile popup");
}

void main_window_ctrl_tab::MainWindowCtrlTab::setUpSearchFromMenu(const find_settings::FindSettings & settings) {
	this->findSettings = settings;

	main_window_shared_types::state_e windowState = main_window_shared_types::state_e::IDLE;
	const global_enums::offset_type_e & searchDirection = this->findSettings.getDirection();

	if (searchDirection == global_enums::offset_type_e::DOWN) {
		windowState = main_window_shared_types::state_e::FIND_UP;
	} else if (searchDirection == global_enums::offset_type_e::UP) {
		windowState = main_window_shared_types::state_e::FIND_DOWN;
	}
	this->changeWindowState(windowState, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
}