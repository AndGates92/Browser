/**
 * @copyright
 * @file main_window_ctrl_base.cpp
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QShortcut>

#include "main_window_ctrl_base.h"
#include "main_window_shared_types.h"
#include "key_sequence.h"
#include "global_types.h"
#include "global_macros.h"

Q_LOGGING_CATEGORY(mainWindowCtrlBaseOverall, "mainWindowCtrlBase.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlBaseUserInput, "mainWindowCtrlBase.userInput", MSG_TYPE_LEVEL)

main_window_ctrl_base::MainWindowCtrlBase::MainWindowCtrlBase(main_window_core::MainWindowCore * core, QWidget * parent, QString jsonFileName) : QObject(parent), main_window_base::MainWindowBase(core), parent(parent), commands(json_parser::JsonParser(jsonFileName, QIODevice::ReadOnly)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");
}

main_window_ctrl_base::MainWindowCtrlBase::~MainWindowCtrlBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");

}

void main_window_ctrl_base::MainWindowCtrlBase::printUserInput(const main_window_shared_types::text_action_e action, QString text) {

	QString textPrint(QString::null);
	if (text == QString::null) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Action is " << action << " for user input " << textPrint);

	this->windowCore->updateUserInput(action, text);

	main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	QString textLabel(QString::null);
	if (windowState != main_window_shared_types::state_e::IDLE) {
		QString userAction(QString::null);
		if (windowState != main_window_shared_types::state_e::COMMAND) {
			// Get action name
			userAction = this->windowCore->getActionName();
		}
		// Create string following format: :<action> <userText>
		textLabel.append(":" + userAction + " " + this->windowCore->getUserText());
	}

	this->windowCore->bottomStatusBar->getUserInputText()->setText(textLabel);

}

void main_window_ctrl_base::MainWindowCtrlBase::updateInfo() {
	QString info(QString::null);
	info = this->createTabInfo();

	this->windowCore->bottomStatusBar->getInfoText()->setText(info);
}

QString main_window_ctrl_base::MainWindowCtrlBase::createTabInfo() {

	int tabCount = this->windowCore->getTabCount();

	QString tabInfo(QString::null);
	if (tabCount == 0) {
		tabInfo.append("No tabs");
	} else {
		tabInfo.append("tab ");
		tabInfo.append(QString("%1").arg(this->windowCore->getCurrentTabIndex() + 1));
		tabInfo.append(" out of ");
		tabInfo.append(QString("%1").arg(tabCount));
	}

	return tabInfo;
}

void main_window_ctrl_base::MainWindowCtrlBase::setAllShortcutEnabledProperty(bool enabled) {
	QList<QShortcut *> shortcuts = this->parent->findChildren<QShortcut *>();

	for (QShortcut * shortcut : shortcuts) {
		key_sequence::KeySequence key(shortcut->key());
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
		shortcut->setEnabled(enabled);
	}
}
