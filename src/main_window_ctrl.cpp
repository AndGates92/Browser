/**
 * @copyright
 * @file main_window_ctrl.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window Control functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_ctrl.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlOverall, "mainWindowCtrl.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlCenterWindow, "mainWindowCtrl.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlUserInput, "mainWindowCtrl.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlSearch, "mainWindowCtrl.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabs, "mainWindowCtrl.tabs", MSG_TYPE_LEVEL)

namespace main_window_ctrl {
	// Overload << operator for state_e
	QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::state_e & state) {

		switch (state) {
			case main_window_ctrl::MainWindowCtrl::state_e::IDLE:
				os << "IDLE";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::COMMAND:
				os << "COMMAND";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::OPEN_TAB:
				os << "OPEN TAB";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB:
				os << "CLOSE TAB";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::REFRESH_TAB:
				os << "REFRESH TAB";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT:
				os << "MOVE LEFT";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT:
				os << "MOVE RIGHT";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE:
				os << "TAB MOVE";
				break;
			case main_window_ctrl::MainWindowCtrl::state_e::SEARCH:
				os << "SEARCH";
				break;
			default:
				os << "Unknown state";
				break;
		}

		return os;
	}

	QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::move_value_e & value_type) {

		switch (value_type) {
			case main_window_ctrl::MainWindowCtrl::move_value_e::IDLE:
				os << "IDLE";
				break;
			case main_window_ctrl::MainWindowCtrl::move_value_e::LEFT:
				os << "LEFT";
				break;
			case main_window_ctrl::MainWindowCtrl::move_value_e::RIGHT:
				os << "RIGHT";
				break;
			case main_window_ctrl::MainWindowCtrl::move_value_e::ABSOLUTE:
				os << "ABSOLUTE";
				break;
			default:
				os << "Unknown value type";
				break;
		}

		return os;
	}

	QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::text_action_e & action) {

		switch (action) {
			case main_window_ctrl::MainWindowCtrl::text_action_e::SET:
				os << "SET";
				break;
			case main_window_ctrl::MainWindowCtrl::text_action_e::APPEND:
				os << "APPEND";
				break;
			case main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR:
				os << "CLEAR";
				break;
			default:
				os << "Unknown action";
				break;
		}

		return os;
	}

}

main_window_ctrl::MainWindowCtrl::MainWindowCtrl(QWidget * parent, int tabIndex, int tabCount) : parent(parent), currentTabIndex(tabIndex), tabCount(tabCount) {

	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::IDLE;
	this->moveValueType = main_window_ctrl::MainWindowCtrl::move_value_e::IDLE;
	this->userText = Q_NULLPTR;

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

void main_window_ctrl::MainWindowCtrl::setAllMenuShortcutEnabledProperty(bool enabled) {
	emit enabledPropertyMenuSignal(enabled);
}

void main_window_ctrl::MainWindowCtrl::setAllWindowShortcutEnabledProperty(bool enabled) {
	this->toggleShowMenuBarKey->setEnabled(enabled);
	this->openNewTabKey->setEnabled(enabled);
	this->newSearchTabKey->setEnabled(enabled);
	this->closeTabKey->setEnabled(enabled);
	this->moveTabToKey->setEnabled(enabled);
	this->moveLeftKey->setEnabled(enabled);
	this->moveRightKey->setEnabled(enabled);
}

void main_window_ctrl::MainWindowCtrl::setAllShortcutEnabledProperty(bool enabled) {
	this->setAllMenuShortcutEnabledProperty(enabled);
	this->setAllWindowShortcutEnabledProperty(enabled);
}

void main_window_ctrl::MainWindowCtrl::createShortcuts() {
	// m will hide/show the menu bar
	this->toggleShowMenuBarKey = new QShortcut(parent);
	this->toggleShowMenuBarKey->setKey(Qt::Key_M);
	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubarSlot);

	// o will open a new tab
	this->openNewTabKey = new QShortcut(parent);
	this->openNewTabKey->setKey(Qt::Key_O);
	connect(this->openNewTabKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::openNewTabSlot);

	// s will search on the current tab
	this->newSearchTabKey = new QShortcut(parent);
	this->newSearchTabKey->setKey(Qt::Key_S);
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::newSearchTabSlot);

	// c will close a tab
	this->closeTabKey = new QShortcut(parent);
	this->closeTabKey->setKey(Qt::Key_C);
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeTabSlot);

	// t will move tab in the tab bar
	this->moveTabToKey = new QShortcut(parent);
	this->moveTabToKey->setKey(Qt::Key_T);
	connect(this->moveTabToKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::moveTabToSlot);

	// h will move left in the tab bar
	this->moveLeftKey = new QShortcut(parent);
	this->moveLeftKey->setKey(Qt::Key_H);
	connect(this->moveLeftKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::moveLeftSlot);

	// l will move right in the tab bar
	this->moveRightKey = new QShortcut(parent);
	this->moveRightKey->setKey(Qt::Key_L);
	connect(this->moveRightKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::moveRightSlot);

	// q will close the browser
	this->closeKey = new QShortcut(parent);
	this->closeKey->setKey(Qt::Key_Q);
	connect(this->closeKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeWindowSlot);

	// r will refresh a webpage
	this->refreshUrlKey = new QShortcut(parent);
	this->refreshUrlKey->setKey(Qt::Key_R);
	connect(this->refreshUrlKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::refreshUrlSlot);

}

void main_window_ctrl::MainWindowCtrl::connectSignals() {

}

void main_window_ctrl::MainWindowCtrl::toggleShowMenubarSlot() {
	emit toggleShowMenubarSignal();
}

void main_window_ctrl::MainWindowCtrl::closeWindowSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit closeWindowSignal();
}

void main_window_ctrl::MainWindowCtrl::moveTabToSlot() {
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::moveLeftSlot() {
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::moveRightSlot() {
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::closeTabSlot() {
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::refreshUrlSlot() {
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::REFRESH_TAB;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::executeAction(int userInput) {
	if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB) {
		this->executeActionOnTab(userInput);
	} else if ((this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT)) {
		this->executeActionOnOffset(userInput);
	} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE) {
	       if ((this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::LEFT) || (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::RIGHT)) {
			this->executeActionOnOffset(userInput);
		} else if (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::ABSOLUTE) {
			this->executeActionOnTab(userInput);
		}
	}

	this->updateCurrentTabIndex();
	emit updateInfoActionSignal(this->currentTabIndex);

	emit updateWebsiteSignal(this->currentTabIndex);
}

void main_window_ctrl::MainWindowCtrl::executeActionOnOffset(int offset) {
	if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT) {
		emit moveSignal(offset, 1, this->setAffectedObject());
	} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT) {
		emit moveSignal(offset, -1, this->setAffectedObject());
	} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE) {
		if (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::RIGHT) {
			emit moveSignal(offset, 1, this->setAffectedObject());
		} else if (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::LEFT) {
			emit moveSignal(offset, -1, this->setAffectedObject());
		}
	}
}

void main_window_ctrl::MainWindowCtrl::executeActionOnTab(int index) {
	int tabIndex = main_window_ctrl::emptyUserInput;
	this->updateTabCount();
	// index is main_window_ctrl::emptyUserInput if the argument is not passed
	if (index == main_window_ctrl::emptyUserInput) {
		this->updateCurrentTabIndex();
		tabIndex = this->currentTabIndex;
	} else {
		// start indexing tab to close with 0
		tabIndex = index;
	}

	if ((this->tabCount > tabIndex) && (tabIndex >= 0)) {
		if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB) {
			emit closeTabSignal(tabIndex);
		} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE) {
			emit moveSignal(tabIndex, 0, this->setAffectedObject());
		} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::REFRESH_TAB) {
			emit refreshUrlSignal(tabIndex);
		}
	} else {
		int maxTabRange = this->tabCount;
		qWarning(mainWindowCtrlTabs) << "Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << maxTabRange << "\n";
	}
}

void main_window_ctrl::MainWindowCtrl::openNewTabSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlSearch,  "Open new tab");
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::OPEN_TAB;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::executeCommand(QString command) {

	if (command.compare("open") == 0) {

	}
/*
	// m will hide/show the menu bar
	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubarSlot);

	// o will open a new tab
	connect(this->fileMenu->openTabAction, &QAction::triggered, this, &main_window_ctrl::MainWindowCtrl::openNewTabSlot);

	// s will search on the current tab
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::newSearchTabSlot);

	// c will close a tab
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeTabSlot);

	// t will move tab in the tab bar
	connect(this->moveTabToKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::moveTabToSlot);

	// h will move left in the tab bar
	connect(this->moveLeftKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::moveLeftSlot);

	// l will move right in the tab bar
	connect(this->moveRightKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::moveRightSlot);

	// q will close the browser
	connect(this->fileMenu->exitAction, &QAction::triggered, this, &main_window_ctrl::MainWindowCtrl::closeSlot);
*/
}

void main_window_ctrl::MainWindowCtrl::newSearchTabSlot() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlSearch,  "Search in current tab");
	this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::SEARCH;
	this->setAllShortcutEnabledProperty(false);
	formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
}

void main_window_ctrl::MainWindowCtrl::keyPressEvent(QKeyEvent * event) {

	int pressedKey = event->key();

	if (event->type() == QEvent::KeyPress) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " key " << event->text() << " i.e. number 0x" << hex << pressedKey);

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->userText);

				if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::OPEN_TAB) {
					emit addNewTabSignal(this->userText);
				} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::SEARCH) {
					emit searchCurrentTabSignal(this->userText);
				} else if ((this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE)) {
					this->processTabIndex(this->userText);
				}
				this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::IDLE;
				this->moveValueType = main_window_ctrl::MainWindowCtrl::move_value_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
				break;
			case Qt::Key_Escape:
				this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::IDLE;
				this->moveValueType = main_window_ctrl::MainWindowCtrl::move_value_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->userText);
				// Last position of the string
				if (this->userText.isEmpty() == 0) {
					int endString = this->userText.count() - 1;
					this->userText.remove(endString, 1);
					formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::SET, this->userText);
				}
				break;
			default:
				if ((this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::OPEN_TAB) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::SEARCH)) {
					if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
						formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::APPEND, event->text());
					}
				} else if ((this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT)) {
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::APPEND, event->text());
					} else {
						qWarning(mainWindowCtrlTabs) << "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE) {
					// If no sign is provided, the tab is considered as absolute value
					// If + or - sign is provided, then the value is considered to be relative to the current tab
					// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
					// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::APPEND, event->text());
						if (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::IDLE) {
							this->moveValueType = main_window_ctrl::MainWindowCtrl::move_value_e::ABSOLUTE;
						}
					} else if ((this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::IDLE) && ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_L) || (pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_Minus))) {
						if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
							this->moveValueType = main_window_ctrl::MainWindowCtrl::move_value_e::RIGHT;
						} else {
							this->moveValueType = main_window_ctrl::MainWindowCtrl::move_value_e::LEFT;
						}
						formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
					} else {
						qWarning(mainWindowCtrlTabs) << "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::COMMAND) {
					formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::APPEND, event->text());
					if (pressedKey >= Qt::Key_Space) {
						this->executeCommand(this->userText);
					}
				} else {
					if (pressedKey == Qt::Key_Colon) {
						this->mainWindowState = main_window_ctrl::MainWindowCtrl::state_e::COMMAND;
						this->setAllShortcutEnabledProperty(false);
					}
					formUserInputStr(main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR);
				}
				break;
		}

	}

}

void main_window_ctrl::MainWindowCtrl::processTabIndex(QString userInputStr) {
	// If indexStr is an empty string, do not pass any argument to executeAction (i.e. execute action on current tab)
	if (userInputStr.isEmpty()) {
		this->executeAction();
	} else {
		bool conversionSuccessful = false;
		int userInputInt = userInputStr.toInt(&conversionSuccessful, 10);
		if (conversionSuccessful == true) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeAction(userInputInt);
		} else {
			qWarning(mainWindowCtrlTabs) << "tab index " << userInputStr << " is not made up by numbers only\n";
		}
	}
}


void main_window_ctrl::MainWindowCtrl::setShortcutEnabledPropertySlot (bool enabled) {
	this->setAllShortcutEnabledProperty(enabled);
}

QString main_window_ctrl::MainWindowCtrl::getActionName() {
	QString actionName = Q_NULLPTR;
	switch (this->mainWindowState) {
		case main_window_ctrl::MainWindowCtrl::state_e::IDLE:
			actionName = "";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::OPEN_TAB:
			actionName = "open";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::COMMAND:
			actionName = "command";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::CLOSE_TAB:
			actionName = "close";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::REFRESH_TAB:
			actionName = "refresh";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT:
			actionName = "move left";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT:
			actionName = "move right";
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE:
			actionName = "move tab";
			if (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::RIGHT) {
				actionName.append(" right");
			} else if (this->moveValueType == main_window_ctrl::MainWindowCtrl::move_value_e::LEFT) {
				actionName.append(" left");
			}
			break;
		case main_window_ctrl::MainWindowCtrl::state_e::SEARCH:
			actionName = "search";
			break;
		default:
			actionName = "Unknown state";
			break;
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " action text " << actionName);

	return actionName;
}

void main_window_ctrl::MainWindowCtrl::formUserInputStr(const main_window_ctrl::MainWindowCtrl::text_action_e action, QString text) {

	QString textPrint = Q_NULLPTR;
	if (text == Q_NULLPTR) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "Action is " << action << " for user input " << textPrint);
	switch (action) {
		case main_window_ctrl::MainWindowCtrl::text_action_e::SET:
			this->userText.clear();
			this->userText.append(text);
			break;
		case main_window_ctrl::MainWindowCtrl::text_action_e::APPEND:
			this->userText.append(text);
			break;
		case main_window_ctrl::MainWindowCtrl::text_action_e::CLEAR:
			this->userText.clear();
			break;
		default:
			qWarning(mainWindowCtrlUserInput) << "Unknown action " << action << "\n";
			break;
	}

	QString textLabel = Q_NULLPTR;
	if (this->mainWindowState != main_window_ctrl::MainWindowCtrl::state_e::IDLE) {
		QString userAction = Q_NULLPTR;
		if (this->mainWindowState != main_window_ctrl::MainWindowCtrl::state_e::COMMAND) {
			userAction = this->getActionName();
		}
		textLabel.append(":" + userAction + " " + this->userText);

	}
	emit updateUserInputBarSignal(textLabel);
}

main_window_shared_types::object_type_e main_window_ctrl::MainWindowCtrl::setAffectedObject() {

	main_window_shared_types::object_type_e object = main_window_shared_types::object_type_e::UNKNOWN;

	if ((this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::MOVE_LEFT)) {
		object = main_window_shared_types::object_type_e::CURSOR;
	} else if (this->mainWindowState == main_window_ctrl::MainWindowCtrl::state_e::TAB_MOVE) {
		object = main_window_shared_types::object_type_e::TAB;
	}

	return object;
}

void main_window_ctrl::MainWindowCtrl::updateCurrentTabIndex() {
	emit requestCurrentTabIndexSignal();
}

void main_window_ctrl::MainWindowCtrl::receiveCurrentTabIndex(int tabIndex) {
	this->currentTabIndex = tabIndex;
}

void main_window_ctrl::MainWindowCtrl::updateTabCount() {
	emit requestTabCountSignal();
}

void main_window_ctrl::MainWindowCtrl::receiveTabCount(int tabCount) {
	this->tabCount = tabCount;
}
