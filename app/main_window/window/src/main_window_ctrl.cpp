/**
 * @copyright
 * @file main_window_ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "key_sequence.h"
#include "main_window_ctrl.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlOverall, "mainWindowCtrl.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlUserInput, "mainWindowCtrl.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlSearch, "mainWindowCtrl.search", MSG_TYPE_LEVEL)

main_window_ctrl::MainWindowCtrl::MainWindowCtrl(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent) : main_window_ctrl_base::MainWindowCtrlBase(core, parent, main_window_ctrl::commandFileFullPath), tabctrl(new main_window_ctrl_tab::MainWindowCtrlTab(core, parent)) {

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

	// TODO - delete after automatic testing has been put in place
	// Testing of find capabilities into JSON file
	// Key not found
	QMap<QString, QString> testKey1 = this->commands.findKeyValue("dada");
	// Key found
	QMap<QString, QString> testKey = this->commands.findKeyValue("Help");

	for(QMap<QString, QString>::const_iterator iter = testKey.cbegin(); iter != testKey.cend(); iter++) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "key " << iter.key() << " value " << iter.value());
	}
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

	QWidget * parent = this->parentWidget();

	// m will hide/show the menu bar
	this->toggleShowMenuBarKey = new QShortcut(parent);
	this->toggleShowMenuBarKey->setKey(Qt::Key_M);

	// q will close the browser
	this->closeKey = new QShortcut(parent);
	this->closeKey->setKey(Qt::Key_Q);
}

void main_window_ctrl::MainWindowCtrl::connectSignals() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	// show hide menubar
	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubar);

	// Close window
	connect(this->closeKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeWindow);
	connect(this->windowCore->topMenuBar->getFileMenu()->exitAction, &QAction::triggered, this, &main_window_ctrl::MainWindowCtrl::closeWindow);

	// Updates to the window depending on changes in tabs
//	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::currentChanged, this, &main_window_ctrl::MainWindowCtrl::updateContent);
	// Update info bar
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::currentChanged, this, &main_window_ctrl::MainWindowCtrl::updateInfoSlot);
	connect(this->windowCore->tabs, &main_window_tab_widget::MainWindowTabWidget::tabCloseRequested, this, &main_window_ctrl::MainWindowCtrl::updateInfoSlot);

}

void main_window_ctrl::MainWindowCtrl::executeCommand(const QString & command) {

	if (command.compare("toggle-menubar") == 0) {
		this->toggleShowMenubar();
	} else if (command.compare("quit") == 0) {
		this->closeWindow();
	} else {
		this->tabctrl->executeCommand(command);
	}
}

void main_window_ctrl::MainWindowCtrl::keyReleaseEvent(QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	QString userTypedText = this->windowCore->getUserText();

	if (event->type() == QEvent::KeyRelease) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->windowCore->setMainWindowState(main_window_shared_types::state_e::IDLE);
				this->setAllShortcutEnabledProperty(true);
				this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << userTypedText);
				// Last position of the string
				if (userTypedText.isEmpty() == false) {
					// Compute position of the last character in the string
					const int endString = userTypedText.count() - 1;
					// Delete last character of the string
					userTypedText = userTypedText.remove(endString, 1);
					this->printUserInput(main_window_shared_types::text_action_e::SET, userTypedText);
				}
				break;
			default:
				break;
		}
	}

	this->tabctrl->keyReleaseEvent(event);
}

void main_window_ctrl::MainWindowCtrl::keyPressEvent(QKeyEvent * event) {

	const int pressedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
		const QString userTypedText = this->windowCore->getUserText();

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << userTypedText);
				break;
			default:
				this->setStateAction(windowState, event);
				break;
		}
	}

	this->tabctrl->keyPressEvent(event);

	if ((pressedKey == Qt::Key_Return) || (pressedKey == Qt::Key_Enter)) {
		this->windowCore->setMainWindowState(main_window_shared_types::state_e::IDLE);
		this->setAllShortcutEnabledProperty(true);
		this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	}

}

void main_window_ctrl::MainWindowCtrl::setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();
	const QString userTypedText = this->windowCore->getUserText();

	switch (windowState) {
		case main_window_shared_types::state_e::COMMAND:
			this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
			if (pressedKey >= Qt::Key_Space) {
				this->executeCommand(userTypedText);
			}
			break;
		case main_window_shared_types::state_e::IDLE:
			if (pressedKey == Qt::Key_Colon) {
				this->windowCore->setMainWindowState(main_window_shared_types::state_e::COMMAND);
				this->setAllShortcutEnabledProperty(false);
			}
			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
			break;
		default:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}
}

void main_window_ctrl::MainWindowCtrl::toggleShowMenubar() {
	const bool menubarVisible = this->windowCore->topMenuBar->isVisible();
	this->windowCore->topMenuBar->setVisible(!menubarVisible);
}

void main_window_ctrl::MainWindowCtrl::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit this->closeWindowSignal();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// Function connected to both currentChanged and tabCloseRequested signals
// In the case of currentChanged signal, index is the current tab
// In the case of tabCloseRequested signal, index is the closed tab
void main_window_ctrl::MainWindowCtrl::updateInfoSlot(const int & index) {
	this->updateInfo();
}
#pragma GCC diagnostic pop
