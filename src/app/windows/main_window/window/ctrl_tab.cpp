/**
 * @copyright
 * @file ctrl_tab.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Control functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/shared/shared_functions.h"
#include "app/shared/exception.h"
#include "app/windows/main_window/window/ctrl_tab.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlTabOverall, mainWindowCtrlTab.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlTabUserInput, mainWindowCtrlTab.userInput, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlTabSearch, mainWindowCtrlTab.search, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlTabTabs, mainWindowCtrlTab.tabs, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlTabUrl, mainWindowCtrlTab.url, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace window {

			namespace tab_ctrl {

				namespace {

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

		}

	}

}

app::main_window::window::CtrlTab::CtrlTab(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : app::main_window::window::CtrlBase(parent, core, app::main_window::window::tab_ctrl::commandFileFullPath), findSettings(QString(), app::shared::offset_type_e::IDLE, false, false) {

	// Shortcuts
	this->createExtraShortcuts();

	// Connect signals and slots
	this->connectExtraSignals();

}

app::main_window::window::CtrlTab::~CtrlTab() {

}

void app::main_window::window::CtrlTab::createExtraShortcuts() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabOverall,  "Create shortcuts");

}

void app::main_window::window::CtrlTab::connectExtraSignals() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabOverall,  "Connect signals");

	// open tab action (from fileMenu)
	connect(this->core->topMenuBar->getFileMenu()->openTabAction.get(), &QAction::triggered, this, &app::main_window::window::CtrlTab::setUpOpenNewTab);

	std::unique_ptr<app::main_window::tab::TabWidget> & tabs = this->core->tabs;

	// When the file has been read, then show it on the screen
	connect(this->core->topMenuBar->getFileMenu().get(), &app::main_window::menu::FileMenu::updateCenterWindowSignal, tabs.get(), &app::main_window::tab::TabWidget::openFileInCurrentTab);
	connect(this->core->popup->getOpenFilePopup().get(), &app::main_window::popup::OpenPopup::fileRead, tabs.get(), &app::main_window::tab::TabWidget::openFileInCurrentTab);

	// Search text in webpage
	connect(this->core->topMenuBar->getEditMenu().get(), &app::main_window::menu::EditMenu::triggerSearch, this, &app::main_window::window::CtrlTab::setUpSearchFromMenu);

	std::unique_ptr<app::main_window::status_bar::StatusBar> & statusBar = this->core->bottomStatusBar;
	connect(this, &app::main_window::window::CtrlTab::currentTabSrcChanged, statusBar.get(), &app::main_window::status_bar::StatusBar::setContentPathText);

	// Updates to the window depending on changes in tabs
	connect(tabs.get(), &app::main_window::tab::TabWidget::tabSourceChanged, this, &app::main_window::window::CtrlTab::createContentPathTextFromSource);

	connect(tabs.get(), &app::main_window::tab::TabWidget::currentChanged, this, &app::main_window::window::CtrlTab::updateStatusBar);
	connect(tabs.get(), &app::main_window::tab::TabWidget::numberTabsChanged, this, &app::main_window::window::CtrlTab::updateStatusBar);

	// Progress bar connections
	connect(tabs.get(), &app::main_window::tab::TabWidget::tabNearlyDisconnected, this, &app::main_window::window::CtrlTab::disconnectTab);
	connect(tabs.get(), &app::main_window::tab::TabWidget::tabNearlyConnected, this, &app::main_window::window::CtrlTab::connectTab);

	// Update info bar
	connect(tabs.get(), &app::main_window::tab::TabWidget::tabCloseRequested, this, &app::main_window::window::CtrlTab::updateStatusBar);

	// Search text in tab
	connect(tabs.get(), &app::main_window::tab::TabWidget::searchResultChanged, this, &app::main_window::window::CtrlTab::printSearchResult);
	connect(tabs.get(), &app::main_window::tab::TabWidget::findTextFinished, this, &app::main_window::window::CtrlTab::processSearchReturnValue);

	// History of the tab
	connect(tabs.get(), &app::main_window::tab::TabWidget::historyItemChanged, this, &app::main_window::window::CtrlTab::historyBoundaryHit);

}

//************************************************************************************
// Start definition of set up slots
//************************************************************************************
void app::main_window::window::CtrlTab::setUpOpenNewTab() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabSearch,  "Open new tab");
	const app::main_window::state_e requestedWindowState = app::main_window::state_e::OPEN_TAB;
	this->changeWindowState(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS);
}

//************************************************************************************
// End definition of set up slots
//************************************************************************************

//************************************************************************************
// Start definition of actions
//************************************************************************************
void app::main_window::window::CtrlTab::closeTab(const int & index) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Close tab " << index);
	this->core->tabs->removeTab(index);
}

void app::main_window::window::CtrlTab::addNewTabAndSearch(const QString & search) {
	const int index = this->addNewTab(app::main_window::page_type_e::UNKNOWN, nullptr);
	this->searchTab(index, search);
}

int app::main_window::window::CtrlTab::addNewTab(const app::main_window::page_type_e & type, const void * data) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Open tab of type " << type);

	const int tabCount = this->core->getTabCount();
	if (tabCount > 0) {
		// Disconnect signals only if at least 1 tabs is already present
		int currentTabIndex = this->core->getCurrentTabIndex();
		this->disconnectTab(currentTabIndex);
	}

	const int tabIndex = this->core->tabs->addTab(type, data);

	// Connect signals from tab the cursor is pointing to
	this->connectTab(tabIndex);

	EXCEPTION_ACTION_COND((tabIndex < 0), throw, "It cannot be negative");

	return tabIndex;
}

void app::main_window::window::CtrlTab::searchTab(const int & index, const QString & search) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabSearch,  "User input " << search << " in tab " << index);
	app::main_window::page_type_e type = this->core->tabs->getPageType(index);

	if (type == app::main_window::page_type_e::UNKNOWN) {
		if (app::main_window::isFile(search) == true) {
			type = app::main_window::page_type_e::TEXT;
		} else if ((app::main_window::isUrl(search) == true) || (app::main_window::isText(search) == true)) {
			type = app::main_window::page_type_e::WEB_CONTENT;
		} else {
			EXCEPTION_ACTION(throw, "Unable to associate a  page type to search " << search);
		}
	}
	this->core->tabs->changeTabContent(index, type, search, nullptr);
}

void app::main_window::window::CtrlTab::searchCurrentTab(const QString & search) {
	const int tabIndex = this->core->getCurrentTabIndex();
	const int tabCount = this->core->getTabCount();
	EXCEPTION_ACTION_COND(((tabIndex < 0) || (tabCount <= 0)), throw, "Unable to perform search of " << search << " in tab " << tabIndex << ". Note that a negative tab index may be caused by the fact that there are no tabs opened in the browser - current count of opened tabs is " << tabCount);

	const app::main_window::state_e & windowState = this->core->getMainWindowState();

	switch (windowState) {
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Search " << search << " in tab " << tabIndex);
			this->searchTab(tabIndex, search);
			break;
		case app::main_window::state_e::FIND:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Find: " << this->findSettings);
			this->core->tabs->findInTab(tabIndex, this->findSettings);
			break;
		default:
			EXCEPTION_ACTION(throw,  "Undefined action to execute when in state " << windowState);
			break;
	}
}

void app::main_window::window::CtrlTab::scrollTab(const app::shared::offset_type_e direction) {
	const int tabIndex = this->core->getCurrentTabIndex();
	this->core->tabs->scrollTab(tabIndex, direction);
}

void app::main_window::window::CtrlTab::goToPageInHistory(const app::main_window::navigation_type_e direction) {
	const int tabIndex = this->core->getCurrentTabIndex();
	this->core->tabs->goToHistoryItem(tabIndex, direction);
}

void app::main_window::window::CtrlTab::extractContentPath(const int & index) {

	const int tabCount = this->core->getTabCount();

	if (tabCount > 0) {
		const app::main_window::page_type_e tabType = this->core->tabs->getPageType(index);
		const QString tabSrc = this->core->tabs->getPageSource(index);

		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabUrl, "Set contentPathText for tab at index " << index << " of type " << tabType << " and source " << tabSrc);
		this->createContentPathTextFromSource(tabType, tabSrc);

	} else {
		emit this->currentTabSrcChanged(QString());
	}

}

void app::main_window::window::CtrlTab::reloadTab(const int & tabIndex) {
	this->core->tabs->reloadTabContent(tabIndex);
}

void app::main_window::window::CtrlTab::moveTab(const int & tabIndex) {
	const int tabIndexCurrent = this->core->tabs->currentIndex();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Move tab " << tabIndexCurrent << " to " << tabIndex);
	this->core->tabs->moveTab(tabIndexCurrent, tabIndex);
}

void app::main_window::window::CtrlTab::moveCursor(const int & tabIndex) {
	// Disconnect signals from tab the cursor was pointing to
	const int currentTabIndex = this->core->getCurrentTabIndex();
	this->disconnectTab(currentTabIndex);

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Move cursor to tab " << tabIndex);
	this->core->tabs->setCurrentIndex(tabIndex);
	// Connect signals from tab the cursor is pointing to
	this->connectTab(tabIndex);
}

void app::main_window::window::CtrlTab::connectTab(const int & tabIndex) {
	const app::main_window::page_type_e tabType = this->core->tabs->getPageType(tabIndex);
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");

	std::shared_ptr<app::main_window::tab::Tab> tab = this->core->tabs->widget(tabIndex);

	std::unique_ptr<app::main_window::status_bar::StatusBar> & statusBar = this->core->bottomStatusBar;
	connect(tab.get(), &app::main_window::tab::Tab::verticalScrollChanged, statusBar.get(), &app::main_window::status_bar::StatusBar::setVScroll);
	statusBar->setVScroll(tab->getVerticalScroll());

	connect(tab.get(), &app::main_window::tab::Tab::loadProgressChanged, statusBar.get(), &app::main_window::status_bar::StatusBar::setProgressValue);
	statusBar->setProgressValue(tab->getLoadProgress());

	// Move focus to the tab index
	tab->setFocus();
}

void app::main_window::window::CtrlTab::disconnectTab(const int & tabIndex) {
	const app::main_window::page_type_e tabType = this->core->tabs->getPageType(tabIndex);
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Disconnect connect signals from " << tabType << " object of tab " << tabIndex << " to progress bar slots");

	const std::shared_ptr<app::main_window::tab::Tab> tab = this->core->tabs->widget(tabIndex);

	std::unique_ptr<app::main_window::status_bar::StatusBar> & statusBar = this->core->bottomStatusBar;
	disconnect(tab.get(), &app::main_window::tab::Tab::verticalScrollChanged, statusBar.get(), &app::main_window::status_bar::StatusBar::setVScroll);
	disconnect(tab.get(), &app::main_window::tab::Tab::loadProgressChanged, statusBar.get(), &app::main_window::status_bar::StatusBar::setProgressValue);

}

//************************************************************************************
// End definition of actions
//************************************************************************************

void app::main_window::window::CtrlTab::executeActionOnOffset(const int & offset) {
	app::shared::sign_e sign = app::shared::sign_e::NOSIGN;

	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const app::shared::offset_type_e offsetType = this->core->getOffsetType();


	if (windowState == app::main_window::state_e::MOVE_RIGHT) {
		sign = app::shared::sign_e::PLUS;
	} else if (windowState == app::main_window::state_e::MOVE_LEFT) {
		sign = app::shared::sign_e::MINUS;
	} else if (windowState == app::main_window::state_e::MOVE_TAB) {
		if (offsetType == app::shared::offset_type_e::RIGHT) {
			sign = app::shared::sign_e::PLUS;
		} else if (offsetType == app::shared::offset_type_e::LEFT) {
			sign = app::shared::sign_e::MINUS;
		}
	} else {
		EXCEPTION_ACTION(throw,  "Requested to execute tab action in invalid window state " << windowState);
	}

	Q_ASSERT_X(((sign == app::shared::sign_e::MINUS) || (sign == app::shared::sign_e::PLUS)), "sign check to execute movement on offset", "sign input must be either app::shared::sign_e::MINUS or app::shared::sign_e::PLUS");
	this->convertToAbsTabIndex(offset, sign);
}

void app::main_window::window::CtrlTab::executeActionOnTab(const int & index) {
	int tabIndex = app::main_window::window::tab_ctrl::emptyUserInput;
	// index is app::main_window::window::tab_ctrl::emptyUserInput if the argument is not passed
	if (index == app::main_window::window::tab_ctrl::emptyUserInput) {
		tabIndex = this->core->getCurrentTabIndex();
	} else {
		// start indexing tab to close with 0
		tabIndex = index;
	}

	const int tabCount = this->core->getTabCount();

	const app::main_window::state_e windowState = this->core->getMainWindowState();

	// Check that tabIndex is larger than 0 and there is at least a tab opened
	// By default, if not tabs are opened, the number of tabs is set to 0 and the current index is set to -1 therefore (tabCount > tabIndex) is true
	if ((tabCount > tabIndex) && (tabIndex >= 0) && (tabCount > 0)) {
		switch (windowState) {
			case app::main_window::state_e::CLOSE_TAB:
				this->closeTab(tabIndex);
				break;
			case app::main_window::state_e::MOVE_TAB:
				this->convertToAbsTabIndex(tabIndex, app::shared::sign_e::NOSIGN);
				break;
			case app::main_window::state_e::REFRESH_TAB:
				this->reloadTab(tabIndex);
				break;
			default:
				EXCEPTION_ACTION(throw,  "Undefined action to execute when in state " << windowState);
				break;
		}
	} else {
		const int maxTabRange = tabCount;
		LOG_WARNING(mainWindowCtrlTabTabs, "Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << maxTabRange);
	}
}

void app::main_window::window::CtrlTab::executeTabAction(const int & userInput) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const app::shared::offset_type_e offsetType = this->core->getOffsetType();

	switch (windowState) {
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
			this->executeActionOnTab(userInput);
			break;
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
			this->executeActionOnOffset(userInput);
			break;
		case app::main_window::state_e::MOVE_TAB:
			if ((offsetType == app::shared::offset_type_e::LEFT) || (offsetType == app::shared::offset_type_e::RIGHT)) {
				this->executeActionOnOffset(userInput);
			} else if (offsetType == app::shared::offset_type_e::ABSOLUTE) {
				this->executeActionOnTab(userInput);
			} else {
				EXCEPTION_ACTION(throw,  "Undefined direction of movement of tabs. Currently set to " << offsetType);
			}
			break;
		default:
			EXCEPTION_ACTION(throw,  "Undefined tab action when in state " << windowState);
			break;
	}

}

void app::main_window::window::CtrlTab::processTabIndex(const QString & userInputStr) {
	// If indexStr is an empty string, do not pass any argument to executeTabAction (i.e. execute action on current tab)
	if (userInputStr.isEmpty()) {
		this->executeTabAction();
	} else {
		bool conversionSuccessful = false;
		// Convert string un a number in base 10
		const int userInputInt = userInputStr.toInt(&conversionSuccessful, 10);
		if (conversionSuccessful == true) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeTabAction(userInputInt);
		} else {
			LOG_WARNING(mainWindowCtrlTabTabs, "tab index " << userInputStr << " is not made up by numbers only");
		}
	}
}

void app::main_window::window::CtrlTab::actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const app::key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		// Retrieve main window controller state
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->core->setOffsetType(app::shared::offset_type_e::IDLE);
				break;
			default:
				break;
		}
	}
}

void app::main_window::window::CtrlTab::executeAction(const app::main_window::state_e & windowState) {
	const QString userTypedText = this->core->getUserText();

	switch (windowState) {
		case app::main_window::state_e::OPEN_TAB:
			this->addNewTabAndSearch(userTypedText);
			break;
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
			this->searchCurrentTab(userTypedText);
			break;
		case app::main_window::state_e::FIND:
			this->findSettings.setDirection(app::shared::offset_type_e::DOWN);
			this->findSettings.setText(userTypedText);
			this->findSettings.setMatchFullWord(false);
			this->findSettings.setCaseSensitive(false);
			this->searchCurrentTab(QString());
			break;
		case app::main_window::state_e::FIND_DOWN:
			this->findSettings.setDirection(app::shared::offset_type_e::DOWN);
			this->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::FIND_UP:
			this->findSettings.setDirection(app::shared::offset_type_e::UP);
			this->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_UP:
			this->scrollTab(app::shared::offset_type_e::UP);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_DOWN:
			this->scrollTab(app::shared::offset_type_e::DOWN);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
			this->processTabIndex(userTypedText);
			break;
		case app::main_window::state_e::COMMAND:
			this->executeCommand(userTypedText, app::main_window::state_postprocessing_e::ACTION);
			break;
		default:
			// Do nothing by default
			break;
	}
}

void app::main_window::window::CtrlTab::prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();
	const app::shared::offset_type_e offsetType = this->core->getOffsetType();
	const QString userTypedText = this->core->getUserText();

	switch (windowState) {
		case app::main_window::state_e::COMMAND:
			if (pressedKey == Qt::Key_Space) {
				this->executeCommand(userTypedText, app::main_window::state_postprocessing_e::NONE);
			}
			break;
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
		case app::main_window::state_e::FIND:
			if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
				this->printUserInput(app::main_window::text_action_e::APPEND, event->text());
			}
			break;
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::REFRESH_TAB:
			if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
				this->printUserInput(app::main_window::text_action_e::APPEND, event->text());
			} else {
				LOG_WARNING(mainWindowCtrlTabUserInput, "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar");
			}
			break;
		case app::main_window::state_e::MOVE_TAB:
			if (offsetType == app::shared::offset_type_e::IDLE) {
				// If no sign is provided, the tab is considered as absolute value
				// If + or - sign is provided, then the value is considered to be relative to the current tab
				// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
				// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->core->setOffsetType(app::shared::offset_type_e::ABSOLUTE);
					this->printUserInput(app::main_window::text_action_e::APPEND, event->text());
				} else if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
					this->core->setOffsetType(app::shared::offset_type_e::RIGHT);
					this->printUserInput(app::main_window::text_action_e::CLEAR);
				} else if ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_Minus)) {
					this->core->setOffsetType(app::shared::offset_type_e::LEFT);
					this->printUserInput(app::main_window::text_action_e::CLEAR);
				} else {
					LOG_WARNING(mainWindowCtrlTabUserInput, "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar");
				}
			} else {
				if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
					this->printUserInput(app::main_window::text_action_e::APPEND, event->text());
				} else {
					LOG_WARNING(mainWindowCtrlTabUserInput, "Pressed key " << event->text() << ". Only numbers accepted when executing actions like move tabs in the tab bar");
				}
			}
			break;
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}

}

void app::main_window::window::CtrlTab::convertToAbsTabIndex(const int & offset, const app::shared::sign_e & sign) {

	const app::main_window::state_e windowState = this->core->getMainWindowState();

	int distance = 0;
	// offset is app::main_window::window::tab_ctrl::emptyUserInput if the argument is not passed
	if (offset == app::main_window::window::tab_ctrl::emptyUserInput) {
		switch (windowState) {
			case app::main_window::state_e::MOVE_RIGHT:
			case app::main_window::state_e::MOVE_LEFT:
			case app::main_window::state_e::MOVE_TAB:
				distance = 1;
				break;
			default:
				EXCEPTION_ACTION(throw,  "Unable to compute distance when in state " << windowState);
				break;
		}
	} else {
		distance = offset;
	}

	const int tabCount = this->core->getTabCount();
	EXCEPTION_ACTION_COND((tabCount <= 0), throw,  "Current number of opened tabs is " << tabCount << ". It is not possible to execute actin related to state " << windowState);
	const int signInt = static_cast<int>(sign);

	int tabIndexDst = 0;
	if (sign == app::shared::sign_e::NOSIGN) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = this->core->getCurrentTabIndex() + (signInt * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		LOG_WARNING(mainWindowCtrlTabTabs, "Offset " << offset << " is bigger than the number of tabs " << tabCount << ". Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange);
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	const int tabIndex = tabIndexDst % tabCount;

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Convert tab relative offset " << (signInt*offset) << " to absolute offset " << tabIndex);

	switch (windowState) {
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
			this->moveCursor(tabIndex);
			break;
		case app::main_window::state_e::MOVE_TAB:
			this->moveTab(tabIndex);
			break;
		default:
			EXCEPTION_ACTION(throw,  "Undefined action when in state " << windowState);
			break;
	}
}

void app::main_window::window::CtrlTab::postprocessWindowStateChange(const app::main_window::state_e & previousState) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlTabTabs,  "Current state " << windowState << " previousState " << previousState);

	const int tabCount = this->core->getTabCount();
	std::shared_ptr<app::main_window::tab::Tab> tab = nullptr;
	QString searchText = QString();
	if (tabCount > 0) {
		const int tabIndex = this->core->getCurrentTabIndex();
		tab = this->core->tabs->widget(tabIndex);
		searchText = tab->getSearchText();
	}

	// Hide search results if not in find state
	const bool isFindState = ((windowState == app::main_window::state_e::FIND) || (windowState == app::main_window::state_e::FIND_DOWN) || (windowState == app::main_window::state_e::FIND_UP));
	std::unique_ptr<app::main_window::status_bar::StatusBar> & statusBar = this->core->bottomStatusBar;
	statusBar->showSearchResult(isFindState);

	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case app::main_window::state_e::OPEN_FILE:
			this->setAllShortcutEnabledProperty(false);
			this->createOpenPrompt();
			// Set window state back to idle to be ready to accept a new command upon closure of the popup
			//this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::IDLE:
			this->setAllShortcutEnabledProperty(true);
			this->printUserInput(app::main_window::text_action_e::CLEAR);
			break;
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
		case app::main_window::state_e::FIND:
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		case app::main_window::state_e::EDIT_SEARCH:
			EXCEPTION_ACTION_COND((tab == nullptr), throw,  "Postprocessing state " << windowState << ": Unable to edit string used for previous search as pointer to tab is " << tab.get());
			this->printUserInput(app::main_window::text_action_e::SET, searchText);
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		case app::main_window::state_e::FIND_DOWN:
			this->findSettings.setDirection(app::shared::offset_type_e::DOWN);
			this->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::FIND_UP:
			this->findSettings.setDirection(app::shared::offset_type_e::UP);
			this->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_UP:
			this->scrollTab(app::shared::offset_type_e::UP);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_DOWN:
			this->scrollTab(app::shared::offset_type_e::DOWN);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::HISTORY_PREV:
			this->goToPageInHistory(app::main_window::navigation_type_e::PREVIOUS);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::HISTORY_NEXT:
			this->goToPageInHistory(app::main_window::navigation_type_e::NEXT);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		default:
			this->setAllShortcutEnabledProperty(false);
			break;
	}
}

bool app::main_window::window::CtrlTab::isValidWindowState(const app::main_window::state_e & requestedWindowState) {
	bool isValid = false;
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const int tabCount = this->core->getTabCount();

	switch (requestedWindowState) {
		case app::main_window::state_e::OPEN_FILE:
		case app::main_window::state_e::IDLE:
			// It is always possible to go to the idle state
			isValid = true;
			break;
		case app::main_window::state_e::OPEN_TAB:
			// It is only possible to open a tab if in the idle state
			isValid = (windowState == app::main_window::state_e::IDLE);
			break;
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::FIND:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
		case app::main_window::state_e::SCROLL_UP:
		case app::main_window::state_e::SCROLL_DOWN:
		case app::main_window::state_e::HISTORY_PREV:
		case app::main_window::state_e::HISTORY_NEXT:
			// It is only possible to perform an operation on a signel tab if the current state is idle and at least 1 tab is opened
			isValid = ((tabCount > 0) && (windowState == app::main_window::state_e::IDLE));
			break;
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
			// It is only possible to perform an operation that requires movement of cursors or tabs if the current state is idle and at least 2 tab is opened
			isValid = ((tabCount > 1) && (windowState == app::main_window::state_e::IDLE));
			break;
		case app::main_window::state_e::COMMAND:
			// Set to false as transition to COMMAND state is handled in the base class by the global conditions
			isValid = false;
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}

void app::main_window::window::CtrlTab::updateStatusBar(const int & tabIndex) {
	this->updateInfo(tabIndex);
	this->updateScroll();
	this->extractContentPath(tabIndex);
}

void app::main_window::window::CtrlTab::printSearchResult(const app::main_window::tab::search_data_s & data) const {
	std::unique_ptr<app::main_window::status_bar::StatusBar> & statusBar = this->core->bottomStatusBar;
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

void app::main_window::window::CtrlTab::historyBoundaryHit(const app::shared::element_position_e & position) {

	if ((position == app::shared::element_position_e::BEGINNING) || (position == app::shared::element_position_e::END)) {
		std::shared_ptr<app::main_window::popup::PopupContainer> container = this->core->popup;
		bool success = container->showWarningPopup();
		EXCEPTION_ACTION_COND((success == false), throw, "Unable to show Warning popup");

		std::shared_ptr<app::main_window::popup::LabelPopup> labelPopup = container->getWarningPopup();
		QString positionText = QString("unknown position");
		if (position == app::shared::element_position_e::BEGINNING) {
			positionText = "beginning";
		} else if (position == app::shared::element_position_e::END) {
			positionText = "end";
		}
		QString popupText = QString();
		popupText = QString("At the ") + positionText + QString(" of the history.");
		labelPopup->setLabelText(popupText);
	}

}

void app::main_window::window::CtrlTab::processSearchReturnValue(const bool & found) {

	if (found == false) {
		std::shared_ptr<app::main_window::popup::PopupContainer> container = this->core->popup;
		bool success = container->showWarningPopup();
		EXCEPTION_ACTION_COND((success == false), throw, "Unable to show Warning popup");

		std::shared_ptr<app::main_window::popup::LabelPopup> labelPopup = container->getWarningPopup();
		QString popupText = QString();
		QString text = this->findSettings.getText();
		if (text.isEmpty() == true) {
			text = "<empty string>";
		}
		popupText = QString("No match for string ") + text + QString(" in current tab.");
		labelPopup->setLabelText(popupText);
	}

}

void app::main_window::window::CtrlTab::createContentPathTextFromSource(const app::main_window::page_type_e & type, const QString & source) {

	QString text = QString();

	switch (type) {
		case app::main_window::page_type_e::WEB_CONTENT:
			// If the type is WEB_CONTENT, then the URL will be shown in the widget displaying the content
			text = source;
			break;
		case app::main_window::page_type_e::TEXT:
			// Prepend file: to source
			text = QString(app::main_window::filePrefix) + source;
			break;
		case app::main_window::page_type_e::UNKNOWN:
			text = QString("Unknown tab type");
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to create string from " << source << " to print in the content path widget " << " because tab type " << type << " is not recognised");
			break;
	}

	emit this->currentTabSrcChanged(text);
}

void app::main_window::window::CtrlTab::createOpenPrompt() {
	std::shared_ptr<app::main_window::popup::PopupContainer> container = this->core->popup;
	bool success = container->showOpenFilePopup();
	container->setFocus();

	EXCEPTION_ACTION_COND((success == false), throw, "Unable to show OpenFile popup");
}

void app::main_window::window::CtrlTab::setUpSearchFromMenu(const app::windows::shared::FindSettings & settings) {
	this->findSettings = settings;

	app::main_window::state_e windowState = app::main_window::state_e::IDLE;
	const app::shared::offset_type_e & searchDirection = this->findSettings.getDirection();

	if (searchDirection == app::shared::offset_type_e::DOWN) {
		windowState = app::main_window::state_e::FIND_UP;
	} else if (searchDirection == app::shared::offset_type_e::UP) {
		windowState = app::main_window::state_e::FIND_DOWN;
	}
	this->changeWindowState(windowState, app::main_window::state_postprocessing_e::POSTPROCESS);
}