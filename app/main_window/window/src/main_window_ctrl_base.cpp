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
#include "global_functions.h"
#include "global_qfunctions.h"
#include "logging_macros.h"

Q_LOGGING_CATEGORY(mainWindowCtrlBaseOverall, "mainWindowCtrlBase.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlBaseCheck, "mainWindowCtrlBase.check", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlBaseUserInput, "mainWindowCtrlBase.userInput", MSG_TYPE_LEVEL)

main_window_ctrl_base::MainWindowCtrlBase::MainWindowCtrlBase(QWidget * parent, QSharedPointer<main_window_core::MainWindowCore> core, QString jsonFileName) : QWidget(parent), main_window_base::MainWindowBase(core), commands(json_parser::JsonParser(jsonFileName, QIODevice::ReadOnly)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");

	this->populateActionData();

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

main_window_ctrl_base::MainWindowCtrlBase::~MainWindowCtrlBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");

	for(std::map<std::string, main_window_json_data::MainWindowJsonData *>::const_iterator data = this->actionData.cbegin(); data != this->actionData.cend(); data++) {
		main_window_json_data::MainWindowJsonData * commandData(data->second);

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Delete command data " << *commandData);
		delete commandData;
	}

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

	this->windowCore->bottomStatusBar->setUserInputText(textLabel);

}

void main_window_ctrl_base::MainWindowCtrlBase::changeWindowStateWrapper(const main_window_json_data::MainWindowJsonData * commandData, const main_window_shared_types::state_postprocessing_e postprocess) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Command " << QString::fromStdString(commandData->getName()) << " (shortcut: " << commandData->getShortcut() << " long command: " << QString::fromStdString(commandData->getLongCmd()) << ") - moving to state " << commandData->getState());
	this->changeWindowState(commandData->getState(), postprocess);
}

void main_window_ctrl_base::MainWindowCtrlBase::executeCommand(const QString & userCommand, const main_window_shared_types::state_postprocessing_e postprocess) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Looking for command matching user input: " << userCommand);

	for(std::map<std::string, main_window_json_data::MainWindowJsonData *>::const_iterator data = this->actionData.cbegin(); data != this->actionData.cend(); data++) {
		const main_window_json_data::MainWindowJsonData * commandData(data->second);
		const QString refCommand = QString::fromStdString(commandData->getLongCmd());

		// If user command matches the command in the JSON file
		if (userCommand.compare(refCommand) == 0) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Found command " << refCommand << " matching user input: " << userCommand);
			this->changeWindowStateWrapper(commandData, postprocess);
		}
	}

}

void main_window_ctrl_base::MainWindowCtrlBase::createShortcuts() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Create shortcuts");

//	this->createExtraShortcuts();
}

void main_window_ctrl_base::MainWindowCtrlBase::connectSignals() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Connect signals");

	for(std::map<std::string, main_window_json_data::MainWindowJsonData *>::const_iterator data = this->actionData.cbegin(); data != this->actionData.cend(); data++) {
		main_window_json_data::MainWindowJsonData * commandData(data->second);
		QShortcut * shortcut = new QShortcut(commandData->getShortcut(), this->window());
		QMetaObject::Connection connection = connect(shortcut, &QShortcut::activated,
			[=] () {
				this->changeWindowStateWrapper(commandData, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			}
		);

		QEXCEPTION_ACTION_COND((static_cast<bool>(connection) == false), throw, "Unable to connect shortcut for key " << (commandData->getShortcut()) << " to trigger a change of controller state to " << commandData->getState());

	}

//	this->connectExtraSignals();

}

void main_window_ctrl_base::MainWindowCtrlBase::updateScroll() {
	const int tabCount = this->windowCore->getTabCount();

	int vScroll = -1;

	if (tabCount > 0) {
		vScroll = 0;
	}

	this->windowCore->bottomStatusBar->setVScroll(vScroll);
}

void main_window_ctrl_base::MainWindowCtrlBase::updateInfo(const int & currIndex) {
	const QString info(this->tabInfoStr(currIndex));

	this->windowCore->bottomStatusBar->setInfoText(info);
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
	const QList<QShortcut *> shortcuts = this->window()->findChildren<QShortcut *>();

	for (QShortcut * shortcut : shortcuts) {
		key_sequence::KeySequence key(shortcut->key());
		// If shortcut key is not defined, then do not do anything
		if (key.count() > 0) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
			shortcut->setEnabled(enabled);
		}
	}
}

// TODO handle shortcuts with multiple keys
std::string main_window_ctrl_base::MainWindowCtrlBase::getShortcutKey(const std::string & value) {
	const std::string delim(",");
	std::string keyName = std::string();
	std::vector<std::string> subStrs = global_functions::splitStringByDelimiter(value, delim);
	auto alphaNum = [&] (unsigned char c) {
		return (std::isalnum(c) != 0);
	};
	auto slashChar = [&] (unsigned char c) {
		return ((std::isgraph(c) != 0) && (c == '/'));
	};

	for (std::string iter : subStrs) {
		bool isAlphaNum = (std::find_if(iter.cbegin(), iter.cend(), alphaNum) != iter.cend());
		bool isSlash = (std::find_if(iter.cbegin(), iter.cend(), slashChar) != iter.cend());
		if (isAlphaNum == true) {
			// Initialize upperKey with as many spaces as the number of characters in iter in order for std::transform to access already allocated space
			std::string upperKey(iter.size(), ' ');
			std::transform(iter.begin(), iter.end(), upperKey.begin(),
				[] (unsigned char c) {
					return std::toupper(c);
				}
			);
			keyName.append("Key_");
			keyName.append(upperKey);
		} else if (isSlash == true) {
			// If string contains only 1 backslash
			keyName.append("Key_Slash");
		} else {
			QEXCEPTION_ACTION(throw,  "Value in JSON file " << QString::fromStdString(value) << " is not alphanumeric and lowercase ");
		}
	}

	return keyName;
}

std::string main_window_ctrl_base::MainWindowCtrlBase::getShortcutModifier(const std::string & value) {
	const std::string delim(",");
	std::string modifierName("Qt::");
	std::vector<std::string> subStrs = global_functions::splitStringByDelimiter(value, delim);
	auto alphaNumUpper = [&] (unsigned char c) {
		return ((std::isalnum(c) != 0) && (std::isupper(c) != 0));
	};
	for (std::string iter : subStrs) {
		bool isAlphaNumUpperCase = (std::find_if(iter.cbegin(), iter.cend(), alphaNumUpper) != iter.cend());
		if (isAlphaNumUpperCase == true) {
			modifierName.append("ShiftModifier");
		} else {
			modifierName.append("NoModifier");
		}
	}

	return modifierName;
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

			// If it is not possible to insert the new item as it already exists in the map, then destroy the data
			if ((it.second == false) && (newData != nullptr)) {
				delete newData;
			}

			void * valuePtr = nullptr;
			main_window_shared_types::state_e state = main_window_shared_types::state_e::IDLE;
			int shortcutKey = (int)Qt::Key_unknown;

			if (paramIter->compare("State") == 0) {
				state = global_qfunctions::qStringToQEnum<main_window_shared_types::state_e>(QString::fromStdString(value));
				valuePtr = &state;
			} else if (paramIter->compare("Shortcut") == 0) {
				// Get key
				std::string keyStr(this->getShortcutKey(value));
				Qt::Key key = global_qfunctions::qStringToQEnum<Qt::Key>(QString::fromStdString(keyStr));
				// Get modifier
				std::string modifierStr(this->getShortcutModifier(value));
				Qt::KeyboardModifiers modifier = global_qfunctions::qStringToQEnum<Qt::KeyboardModifiers>(QString::fromStdString(modifierStr));
				shortcutKey = ((int)key) | ((int)modifier);
				valuePtr = &shortcutKey;
			} else {
				valuePtr = &value;
			}

			std::map<std::string, main_window_json_data::MainWindowJsonData *>::iterator el = it.first;
			main_window_json_data::MainWindowJsonData * & data = el->second;
			data->setValueFromMemberName(*paramIter, valuePtr);
		}
	}

	for (const auto & data : this->actionData)
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Data for key " << QString::fromStdString(data.first) << " is " << *(data.second));

}

void main_window_ctrl_base::MainWindowCtrlBase::changeWindowState(const main_window_shared_types::state_e & nextState, const main_window_shared_types::state_postprocessing_e postprocess, const Qt::Key key) {

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	const QString userTypedText = this->windowCore->getUserText();

	// Global conditions are:
	// - it is possible to move to any state from the command state
	// - it is possible to move from any state to COMMAND command state if the user types Backspace and the user types text is empty
	const bool globalCondition = (windowState == main_window_shared_types::state_e::COMMAND) || ((windowState != main_window_shared_types::state_e::COMMAND) && (nextState == main_window_shared_types::state_e::COMMAND) && (userTypedText.isEmpty() == true) && (key == Qt::Key_Backspace));


	// Do not change state if the window is already in the one requested
	if (windowState != nextState) {
		bool isValid = this->isValidWindowState(nextState) || globalCondition;
		if (isValid == true) {
			this->windowCore->setMainWindowState(nextState);

			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);

			if (postprocess == main_window_shared_types::state_postprocessing_e::POSTPROCESS) {
				this->postprocessWindowStateChange(windowState);
			} else if (postprocess == main_window_shared_types::state_postprocessing_e::ACTION) {
				this->executeAction(nextState);
			}
			emit windowStateChanged(nextState);
		}
	} else {
		QWARNING_PRINT(mainWindowCtrlBaseOverall, "Ignoring request to go from state " << windowState << " to state " << nextState);
	}
}

void main_window_ctrl_base::MainWindowCtrlBase::keyPressEvent(QKeyEvent * event) {

	const int pressedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				this->executeAction(windowState);
				break;
			default:
				this->prepareAction(windowState, event);
				break;
		}
	}

	// If user presses escape, enter or return key, bring the state to IDLE and delete user input
	if ((pressedKey == Qt::Key_Escape) || (pressedKey == Qt::Key_Return) || (pressedKey == Qt::Key_Enter)) {
		this->resetWindowState();
	}

}

const main_window_json_data::MainWindowJsonData * main_window_ctrl_base::MainWindowCtrlBase::findDataWithFieldValue(const std::string & name, const void * value) const {

	for(std::map<std::string, main_window_json_data::MainWindowJsonData *>::const_iterator data = this->actionData.cbegin(); data != this->actionData.cend(); data++) {

		const main_window_json_data::MainWindowJsonData * commandData(data->second);
		bool found = commandData->isSameFieldValue(name, value);
		if (found == true) {
			return commandData;
		}
	}

	return nullptr;
}

void main_window_ctrl_base::MainWindowCtrlBase::moveToCommandStateFromNonIdleState(const main_window_shared_types::state_e & windowState, const Qt::Key & key) {
	// Saving long command for a given state to set it after changing state
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::COMMAND;
	const main_window_json_data::MainWindowJsonData * data(this->findDataWithFieldValue("State", &windowState));
	if (data != nullptr) {
		QString longCmd(QString::fromStdString(data->getLongCmd()));
		this->changeWindowState(requestedWindowState, main_window_shared_types::state_postprocessing_e::POSTPROCESS, key);
		// Setting the user input here because it is cleared when changing state
		this->printUserInput(main_window_shared_types::text_action_e::SET, longCmd);
	}
}

void main_window_ctrl_base::MainWindowCtrlBase::resetWindowState() {
	const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::IDLE;
	this->windowCore->setMainWindowState(requestedWindowState);

	this->windowCore->updateUserInput(main_window_shared_types::text_action_e::CLEAR, QString::null);
	this->windowCore->bottomStatusBar->setUserInputText(QString::null);
	this->windowCore->getUserText();

	// Enable all shortcuts
	this->setAllShortcutEnabledProperty(true);

	// Give the focus back to the parent widget
	this->parentWidget()->setFocus();
}

