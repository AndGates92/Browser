/**
 * @copyright
 * @file main_window_ctrl_wrapper.cpp
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_ctrl_wrapper.h"
#include "key_sequence.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlWrapperOverall, "mainWindowCtrlWrapper.overall", MSG_TYPE_LEVEL)

main_window_ctrl_wrapper::MainWindowCtrlWrapper::MainWindowCtrlWrapper(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent) : QWidget(parent), main_window_base::MainWindowBase(core), winctrl(new main_window_ctrl::MainWindowCtrl(core, this)), tabctrl(new main_window_ctrl_tab::MainWindowCtrlTab(core, this)) {

	this->setFocus(Qt::OtherFocusReason);
}

main_window_ctrl_wrapper::MainWindowCtrlWrapper::~MainWindowCtrlWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Main window destructor");

	// deleting window control
	if (this->winctrl != Q_NULLPTR) {
		delete this->winctrl;
	}

	// deleting tab control
	if (this->tabctrl != Q_NULLPTR) {
		delete this->tabctrl;
	}

}

void main_window_ctrl_wrapper::MainWindowCtrlWrapper::keyPressEvent(QKeyEvent * event) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyPressEvent(event);
	this->tabctrl->keyPressEvent(event);

	const int pressedKey = event->key();

	// If user presses escape, enter or return key, bring the state to IDLE and delete user input
	if ((pressedKey == Qt::Key_Escape) || (pressedKey == Qt::Key_Return) || (pressedKey == Qt::Key_Enter)) {
		this->resetWindowState();
	}

	this->windowCore->mainWidget->repaint();
}

void main_window_ctrl_wrapper::MainWindowCtrlWrapper::keyReleaseEvent(QKeyEvent * event) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyReleaseEvent(event);
	this->tabctrl->keyReleaseEvent(event);

	this->windowCore->mainWidget->repaint();
}

void main_window_ctrl_wrapper::MainWindowCtrlWrapper::resetWindowState() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::IDLE;
	this->windowCore->setMainWindowState(requestedWindowState);

	this->windowCore->updateUserInput(main_window_shared_types::text_action_e::CLEAR, QString::null);
	this->windowCore->bottomStatusBar->getUserInputText()->clear();
	this->windowCore->getUserText();

	// Enable all shortcuts
	const QList<QShortcut *> shortcuts = this->window()->findChildren<QShortcut *>();

	for (QShortcut * shortcut : shortcuts) {
		key_sequence::KeySequence key(shortcut->key());
		// If shortcut key is not defined, then do not do anything
		if (key.count() > 0) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Setting enabled for key " << key.toString() << " to true");
			shortcut->setEnabled(true);
		}
	}
}

main_window_ctrl::MainWindowCtrl * main_window_ctrl_wrapper::MainWindowCtrlWrapper::getWinCtrl() {
	return this->winctrl;
}

main_window_ctrl_tab::MainWindowCtrlTab * main_window_ctrl_wrapper::MainWindowCtrlWrapper::getTabCtrl() {
	return this->tabctrl;
}
