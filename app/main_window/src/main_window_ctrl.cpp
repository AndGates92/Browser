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

#include "key_sequence.h"
#include "main_window_ctrl.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlOverall, "mainWindowCtrl.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlUserInput, "mainWindowCtrl.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlSearch, "mainWindowCtrl.search", MSG_TYPE_LEVEL)

main_window_ctrl::MainWindowCtrl::MainWindowCtrl(main_window_core::MainWindowCore * windowCore, QWidget * parent) : main_window_ctrl_base::MainWindowCtrlBase(windowCore, parent, main_window_ctrl::commandFileFullPath), tabctrl(new main_window_ctrl_tab::MainWindowCtrlTab(windowCore, parent)) {

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

main_window_ctrl::MainWindowCtrl::~MainWindowCtrl() {

	// deleting shortcuts
	delete this->toggleShowMenuBarKey;
	delete this->closeKey;

	// deleting tab control
	delete this->tabctrl;
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
		key_sequence::KeySequence key(shortcut->key());
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
		shortcut->setEnabled(enabled);
	}
}

void main_window_ctrl::MainWindowCtrl::connectSignals() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubar);
	connect(this->closeKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeWindow);

	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setShortcutEnabledPropertySignal, this, &main_window_ctrl::MainWindowCtrl::setAllShortcutEnabledProperty);

	// open tab action (from fileMenu)
	connect(this, &main_window_ctrl::MainWindowCtrl::openNewTabSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::openNewTab);

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
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: quitting from the browser");
	emit this->closeWindowSignal();
}

void main_window_ctrl::MainWindowCtrl::executeCommand(QString command) {

	if (command.compare("toggle-menubar") == 0) {
		this->toggleShowMenubar();
	} else if (command.compare("quit") == 0) {
		this->closeWindow();
	} else {
		this->tabctrl->executeCommand(command);
	}
}

void main_window_ctrl::MainWindowCtrl::keyReleaseEvent(QKeyEvent * event) {

	int releasedKey = event->key();
	Qt::KeyboardModifiers keyModifiers = event->modifiers();

	key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowCore->mainWindowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->mainWindowCore->mainWindowState = main_window_shared_types::state_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->mainWindowCore->userText);
				// Last position of the string
				if (this->mainWindowCore->userText.isEmpty() == 0) {
					int endString = this->mainWindowCore->userText.count() - 1;
					this->mainWindowCore->userText.remove(endString, 1);
					this->printUserInput(main_window_shared_types::text_action_e::SET, this->mainWindowCore->userText);
				}
				// If in state TAB MOVE and the mainWindowCore->userText is empty after deleting the last character, set the move value to IDLE
				if ((this->mainWindowCore->userText.isEmpty() == 1) && (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::TAB_MOVE)) {
					this->mainWindowCore->moveValueType = main_window_shared_types::move_value_e::IDLE;
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
	Qt::KeyboardModifiers keyModifiers = event->modifiers();

	key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowCore->mainWindowState << " key " << keySeq.toString());

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->mainWindowCore->userText);

				if (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::OPEN_TAB) {
					emit this->addNewTabSignal(this->mainWindowCore->userText);
				} else if (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::SEARCH) {
					emit this->searchCurrentTabSignal(this->mainWindowCore->userText);
				} else if ((this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::CLOSE_TAB) || (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::MOVE_RIGHT) || (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::MOVE_LEFT) || (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::TAB_MOVE)) {
					this->tabctrl->processTabIndex(this->mainWindowCore->userText);
				}
				this->mainWindowCore->mainWindowState = main_window_shared_types::state_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				break;
			default:
				if ((this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::OPEN_TAB) || (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::SEARCH)) {
					if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
						this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
					}
				} else if ((this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::CLOSE_TAB) || (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::MOVE_RIGHT) || (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::MOVE_LEFT)) {
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
					} else {
						qWarning(mainWindowCtrlUserInput) << "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar\n";
					}
				} else if (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
					// If no sign is provided, the tab is considered as absolute value
					// If + or - sign is provided, then the value is considered to be relative to the current tab
					// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
					// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						if (this->mainWindowCore->moveValueType == main_window_shared_types::move_value_e::IDLE) {
							this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
						}
						this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
					} else if ((this->mainWindowCore->moveValueType == main_window_shared_types::move_value_e::IDLE) && ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_L) || (pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_Minus))) {
						this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
					} else {
						qWarning(mainWindowCtrlUserInput) << "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar\n";
					}
				} else if (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::COMMAND) {
					this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
					if (pressedKey >= Qt::Key_Space) {
						this->executeCommand(this->mainWindowCore->userText);
					}
				} else {
					if (pressedKey == Qt::Key_Colon) {
						this->mainWindowCore->mainWindowState = main_window_shared_types::state_e::COMMAND;
						this->setAllShortcutEnabledProperty(false);
					}
					this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				}
				break;
		}
	}

	this->tabctrl->keyPressEvent(event);


}

void main_window_ctrl::MainWindowCtrl::setShortcutEnabledProperty(bool enabled) {
	this->setAllShortcutEnabledProperty(enabled);
}



QString main_window_ctrl::MainWindowCtrl::getTabUrl(QString search) {
	return this->tabctrl->createUrl(search);
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

void main_window_ctrl::MainWindowCtrl::updateWebsite(int index) {
	emit this->updateWebsiteSignal(index);
}

void main_window_ctrl::MainWindowCtrl::searchCurrentTab(QString search) {
	emit this->searchCurrentTabSignal(search);
}

void main_window_ctrl::MainWindowCtrl::openNewTab() {
	emit this->openNewTabSignal();
}
