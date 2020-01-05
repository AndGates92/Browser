/**
 * @copyright
 * @file main_window_ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
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
Q_LOGGING_CATEGORY(mainWindowCtrlUserInput, "mainWindowCtrl.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlSearch, "mainWindowCtrl.search", MSG_TYPE_LEVEL)

main_window_ctrl::MainWindowCtrl::MainWindowCtrl(QWidget * parent, int tabIndex, int tabCount) : parent(parent) {

	this->mainWindowState = main_window_shared_types::state_e::IDLE;
	this->userText = QString::null;

	this->tabctrl = new main_window_ctrl_tab::MainWindowCtrlTab(parent, tabIndex, tabCount);

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

void main_window_ctrl::MainWindowCtrl::createShortcuts() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Create shortcuts");

	// m will hide/show the menu bar
	this->toggleShowMenuBarKey = new QShortcut(parent);
	this->toggleShowMenuBarKey->setKey(Qt::Key_M);

	// q will close the browser
	this->closeKey = new QShortcut(parent);
	this->closeKey->setKey(Qt::Key_Q);
}


void main_window_ctrl::MainWindowCtrl::setAllShortcutEnabledProperty(bool enabled) {
	QList<QShortcut *> shortcuts = this->parent->findChildren<QShortcut *>();

	for (QShortcut * shortcut : shortcuts) {
		QKeySequence key = shortcut->key();
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
		shortcut->setEnabled(enabled);
	}
}

void main_window_ctrl::MainWindowCtrl::connectSignals() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubar);
	connect(this->closeKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeWindow);

	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setShortcutEnabledPropertySignal, this, &main_window_ctrl::MainWindowCtrl::setAllShortcutEnabledProperty);
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setUserInputStrSignal, this, &main_window_ctrl::MainWindowCtrl::formUserInputStr);

	// Share window state with tab control
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setStateSignal, this, &main_window_ctrl::MainWindowCtrl::setState);
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::requestStateSignal, this, &main_window_ctrl::MainWindowCtrl::getState);
	connect(this, &main_window_ctrl::MainWindowCtrl::sendStateSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::receiveState);

	// share current tab index
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::requestCurrentTabIndexSignal, this, &main_window_ctrl::MainWindowCtrl::getCurrentTabIndex);
	connect(this, &main_window_ctrl::MainWindowCtrl::sendCurrentTabIndexSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::receiveCurrentTabIndex);

	// share tab count
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::requestTabCountSignal, this, &main_window_ctrl::MainWindowCtrl::getTabCount);
	connect(this, &main_window_ctrl::MainWindowCtrl::sendTabCountSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::receiveTabCount);

	// open tab action
	connect(this, &main_window_ctrl::MainWindowCtrl::openNewTabSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::openNewTab);

	// Update info in the info bar following action
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::updateInfoActionSignal, this, &main_window_ctrl::MainWindowCtrl::updateInfo);

	// Update website in info bar
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::updateWebsiteSignal, this, &main_window_ctrl::MainWindowCtrl::updateWebsite);

	// Add tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::addNewTabSignal, this, &main_window_ctrl::MainWindowCtrl::addNewTab);

	// Close tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::closeTabSignal, this, &main_window_ctrl::MainWindowCtrl::closeTab);

	// Move tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::moveTabSignal, this, &main_window_ctrl::MainWindowCtrl::moveTab);
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::moveCursorSignal, this, &main_window_ctrl::MainWindowCtrl::moveCursor);

	// Search in current tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::searchCurrentTabSignal, this, &main_window_ctrl::MainWindowCtrl::searchCurrentTab);

	// Refresh URL tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::refreshUrlSignal, this, &main_window_ctrl::MainWindowCtrl::refreshUrl);

}

void main_window_ctrl::MainWindowCtrl::toggleShowMenubar() {
	emit this->toggleShowMenubarSignal();
}

void main_window_ctrl::MainWindowCtrl::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit this->closeWindowSignal();
}

void main_window_ctrl::MainWindowCtrl::executeCommand(QString command) {

	if (command.compare("toggle-menubar") == 0) {
		this->toggleShowMenubar();
	} else if (command.compare("exit") == 0) {
		this->closeWindow();
	} else {
		this->tabctrl->executeCommand(command);
	}
}

void main_window_ctrl::MainWindowCtrl::keyReleaseEvent(QKeyEvent * event) {

	int releasedKey = event->key();

	if (event->type() == QEvent::KeyRelease) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " key " << event->text() << " i.e. number 0x" << hex << releasedKey);

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->mainWindowState = main_window_shared_types::state_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				this->formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->userText);
				// Last position of the string
				if (this->userText.isEmpty() == 0) {
					int endString = this->userText.count() - 1;
					this->userText.remove(endString, 1);
					this->formUserInputStr(main_window_shared_types::text_action_e::SET, this->userText);
				}
				// If in state TAB MOVE and the userText is empty after deleting the last character, set the move value to IDLE
				if ((this->userText.isEmpty() == 1) && (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE)) {
					this->tabctrl->setMoveValueType(main_window_shared_types::move_value_e::IDLE);
				}
				break;
			default:
				break;
		}
	}

	this->tabctrl->keyReleaseEvent(event);
}

void main_window_ctrl::MainWindowCtrl::keyPressEvent(QKeyEvent * event) {

	int pressedKey = event->key();

	if (event->type() == QEvent::KeyPress) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " key " << event->text() << " i.e. number 0x" << hex << pressedKey);

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->userText);

				if (this->mainWindowState == main_window_shared_types::state_e::OPEN_TAB) {
					emit this->addNewTabSignal(this->userText);
				} else if (this->mainWindowState == main_window_shared_types::state_e::SEARCH) {
					emit this->searchCurrentTabSignal(this->userText);
				} else if ((this->mainWindowState == main_window_shared_types::state_e::CLOSE_TAB) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_LEFT) || (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE)) {
					this->tabctrl->processTabIndex(this->userText);
				}
				this->mainWindowState = main_window_shared_types::state_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				this->formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
				break;
			default:
				if ((this->mainWindowState == main_window_shared_types::state_e::OPEN_TAB) || (this->mainWindowState == main_window_shared_types::state_e::SEARCH)) {
					if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
						this->formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					}
				} else if ((this->mainWindowState == main_window_shared_types::state_e::CLOSE_TAB) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_LEFT)) {
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						this->formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					} else {
						qWarning(mainWindowCtrlUserInput) << "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
					// If no sign is provided, the tab is considered as absolute value
					// If + or - sign is provided, then the value is considered to be relative to the current tab
					// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
					// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						if (this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::IDLE) {
							this->formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
						}
						this->formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					} else if ((this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::IDLE) && ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_L) || (pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_Minus))) {
						this->formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
					} else {
						qWarning(mainWindowCtrlUserInput) << "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window_shared_types::state_e::COMMAND) {
					this->formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					if (pressedKey >= Qt::Key_Space) {
						this->executeCommand(this->userText);
					}
				} else {
					if (pressedKey == Qt::Key_Colon) {
						this->mainWindowState = main_window_shared_types::state_e::COMMAND;
						this->setAllShortcutEnabledProperty(false);
					}
					this->formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
				}
				break;
		}
	}

	this->tabctrl->keyPressEvent(event);


}

void main_window_ctrl::MainWindowCtrl::setShortcutEnabledProperty(bool enabled) {
	this->setAllShortcutEnabledProperty(enabled);
}

QString main_window_ctrl::MainWindowCtrl::getActionName() {
	QString actionName(QString::null);

	actionName << this->mainWindowState;

	if (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::RIGHT) {
			actionName.append(" right");
		} else if (this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::LEFT) {
			actionName.append(" left");
		}
	}

	// Create lowercase copy of the string
	actionName = actionName.toLower();

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " action text " << actionName);

	return actionName;
}

void main_window_ctrl::MainWindowCtrl::formUserInputStr(const main_window_shared_types::text_action_e action, QString text) {

	QString textPrint(QString::null);
	if (text == QString::null) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "Action is " << action << " for user input " << textPrint);
	switch (action) {
		case main_window_shared_types::text_action_e::SET:
			this->userText.clear();
			this->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::APPEND:
			this->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::CLEAR:
			this->userText.clear();
			break;
		default:
			qWarning(mainWindowCtrlUserInput) << "Unknown action " << action << "\n";
			break;
	}

	QString textLabel(QString::null);
	if (this->mainWindowState != main_window_shared_types::state_e::IDLE) {
		QString userAction(QString::null);
		if (this->mainWindowState != main_window_shared_types::state_e::COMMAND) {
			userAction = this->getActionName();
		}
		textLabel.append(":" + userAction + " " + this->userText);

	}
	emit this->updateUserInputBarSignal(textLabel);
}

QString main_window_ctrl::MainWindowCtrl::getTabUrl(QString search) {
	return this->tabctrl->createUrl(search);
}

QString main_window_ctrl::MainWindowCtrl::getTabInfo() {
	return this->tabctrl->createTabInfo();
}

void main_window_ctrl::MainWindowCtrl::getState() {
	emit this->sendStateSignal(this->mainWindowState);
}

void main_window_ctrl::MainWindowCtrl::setState(main_window_shared_types::state_e state) {
	this->mainWindowState = state;
}

void main_window_ctrl::MainWindowCtrl::getCurrentTabIndex() {
	emit this->requestCurrentTabIndexSignal();
}

void main_window_ctrl::MainWindowCtrl::receiveCurrentTabIndex(int tabIndex) {
	emit this->sendCurrentTabIndexSignal(tabIndex);
}

void main_window_ctrl::MainWindowCtrl::getTabCount() {
	emit this->requestTabCountSignal();
}

void main_window_ctrl::MainWindowCtrl::receiveTabCount(int tabCount) {
	emit this->sendTabCountSignal(tabCount);
}

void main_window_ctrl::MainWindowCtrl::refreshUrl(int tabIndex) {
	emit this->refreshUrlSignal(tabIndex);
}

void main_window_ctrl::MainWindowCtrl::closeTab(int index) {
	emit this->closeTabSignal(index);
}

void main_window_ctrl::MainWindowCtrl::moveTab(int tabIndex) {
	emit this->moveTabSignal(tabIndex);
}

void main_window_ctrl::MainWindowCtrl::moveCursor(int tabIndex) {
	emit this->moveCursorSignal(tabIndex);
}

void main_window_ctrl::MainWindowCtrl::addNewTab(QString search) {
	emit this->addNewTabSignal(search);
}

void main_window_ctrl::MainWindowCtrl::updateInfo(int index) {
	emit this->updateInfoActionSignal(index);
}

void main_window_ctrl::MainWindowCtrl::updateWebsite(int index) {
	emit this->updateWebsiteSignal(index);
}

void main_window_ctrl::MainWindowCtrl::searchCurrentTab(QString search) {
	emit this->searchCurrentTabSignal(search);
}

void main_window_ctrl::MainWindowCtrl::openNewTab() {
	emit this->openNewTabSignal();
}
