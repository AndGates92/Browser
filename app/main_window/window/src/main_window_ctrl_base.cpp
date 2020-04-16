/**
 * @copyright
 * @file main_window_ctrl_base.cpp
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class functions
 */

#include <utility>

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QShortcut>

#include "main_window_ctrl_base.h"
#include "main_window_shared_types.h"
#include "key_sequence.h"
#include "global_types.h"
#include "logging_macros.h"

Q_LOGGING_CATEGORY(mainWindowCtrlBaseOverall, "mainWindowCtrlBase.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlBaseCheck, "mainWindowCtrlBase.check", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlBaseUserInput, "mainWindowCtrlBase.userInput", MSG_TYPE_LEVEL)

main_window_ctrl_base::MainWindowCtrlBase::MainWindowCtrlBase(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent, QString jsonFileName) : QWidget(parent), main_window_base::MainWindowBase(core), commands(json_parser::JsonParser(jsonFileName, QIODevice::ReadOnly)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");

	this->populateActionData();
}

main_window_ctrl_base::MainWindowCtrlBase::~MainWindowCtrlBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");
}

void main_window_ctrl_base::MainWindowCtrlBase::printUserInput(const main_window_shared_types::text_action_e action, const QString text) {

	QString textPrint(QString::null);
	if (text == QString::null) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Action is " << action << " for user input " << textPrint);

	this->windowCore->updateUserInput(action, text);

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

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

void main_window_ctrl_base::MainWindowCtrlBase::updateInfo(const int & currIndex) {
	const QString info(this->tabInfoStr(currIndex));

	this->windowCore->bottomStatusBar->getInfoText()->setText(info);
}

QString main_window_ctrl_base::MainWindowCtrlBase::tabInfoStr(const int & currIndex) const {

	const int tabCount = this->windowCore->getTabCount();

	QString tabInfo(QString::null);
	if (tabCount == 0) {
		tabInfo.append("No tabs");
	} else {
		tabInfo.append("tab ");
		tabInfo.append(QString("%1").arg(currIndex + 1));
		tabInfo.append(" out of ");
		tabInfo.append(QString("%1").arg(tabCount));
	}

	return tabInfo;
}

void main_window_ctrl_base::MainWindowCtrlBase::setAllShortcutEnabledProperty(const bool enabled) {
	const QList<QShortcut *> shortcuts = this->parentWidget()->findChildren<QShortcut *>();

	for (QShortcut * shortcut : shortcuts) {
		key_sequence::KeySequence key(shortcut->key());
		// If shortcut key is not defined, then do not do anything
		if (key.count() > 0) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
			shortcut->setEnabled(enabled);
		}
	}
}

void main_window_ctrl_base::MainWindowCtrlBase::populateActionData() {

	for (std::vector<std::string>::const_iterator paramIter = main_window_json_data::defaultActionParameters.cbegin(); paramIter != main_window_json_data::defaultActionParameters.cend(); paramIter++) {
		const std::map<QString, QString> paramValues = this->commands.findKeyValue(QString::fromStdString(*paramIter)).toStdMap();
		for(std::map<QString, QString>::const_iterator valIter = paramValues.cbegin(); valIter != paramValues.cend(); valIter++) {
			std::string key(valIter->first.toStdString());
			std::string value(valIter->second.toStdString());

			// If key is not in actionData map, then it must be added
			main_window_json_data::MainWindowJsonData * const newData(new main_window_json_data::MainWindowJsonData(key));
			//std::pair<std::string, main_window_json_data::MainWindowJsonData *>dataPair(key, newData);
			std::pair<std::string, main_window_json_data::MainWindowJsonData *> dataPair;

			dataPair.first=key;
			dataPair.second=newData;

			// insert returns a pair where:
			// - first points to the newly created iterator or the element with the same key
			// - second is true if the insertion is successful, false otherwise
			std::pair<std::map<std::string, main_window_json_data::MainWindowJsonData *>::iterator, bool> it = this->actionData.insert(dataPair);

			const void * valuePtr = nullptr;
			main_window_shared_types::state_e state = main_window_shared_types::state_e::IDLE;
			key_sequence::KeySequence keySeq = key_sequence::KeySequence(QString::null);

			if (paramIter->compare("State") == 0) {
				state = global_functions::QStringToQEnum<main_window_shared_types::state_e>(QString::fromStdString(value));
				valuePtr = &state;
			} else if (paramIter->compare("Shortcut") == 0) {
				std::string fullKeyName("Key_" + value);
				const QKeySequence key( global_functions::QStringToQEnum<Qt::Key>(QString::fromStdString(fullKeyName)));
				keySeq = key_sequence::KeySequence(key);
				valuePtr = &keySeq;
			} else {
				valuePtr = &value;
			}

			std::map<std::string, main_window_json_data::MainWindowJsonData *>::iterator el = it.first;
			main_window_json_data::MainWindowJsonData * & data = el->second;
			data->setValueFromMemberString(*paramIter, valuePtr);
		}
	}

	for (const auto & data : this->actionData)
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Data for key " << QString::fromStdString(data.first) << " is " << data.second->qprint());

}
