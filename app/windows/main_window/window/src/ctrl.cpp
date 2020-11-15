/**
 * @copyright
 * @file ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/exception_macros.h"
#include "widgets/commands/include/key_sequence.h"
#include "windows/main_window/window/include/ctrl.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlOverall, mainWindowCtrl.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlUserInput, mainWindowCtrl.userInput, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlSearch, mainWindowCtrl.search, TYPE_LEVEL, INFO_VERBOSITY)

namespace main_window {

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
		static const QString commandFileName("global_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const QString commandFileFullPath(commandFilePath + commandFileName);
	}

}

main_window::Ctrl::Ctrl(QWidget * parent, const std::shared_ptr<main_window::Core> & core) : main_window::CtrlBase(parent, core, main_window::commandFileFullPath) {

	// Shortcuts
	this->createExtraShortcuts();

	// Connect signals and slots
	this->connectExtraSignals();

	// Update info label - as no tabs in the window, then updateInfo must be explicitely called
	const int tabIndex = this->core->getCurrentTabIndex();
	this->updateInfo(tabIndex);
}

main_window::Ctrl::~Ctrl() {

}

void main_window::Ctrl::createExtraShortcuts() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Create shortcuts");

}

void main_window::Ctrl::connectExtraSignals() {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	connect(this->core->topMenuBar->getFileMenu()->exitAction.get(), &QAction::triggered, this, &main_window::Ctrl::closeWindow);
	connect(this->core->popup.get(), &main_window::PopupContainer::closeContainer,  [this] () {
		this->changeWindowState(main_window::state_e::IDLE, main_window::state_postprocessing_e::POSTPROCESS);
	});

}

void main_window::Ctrl::actionOnReleasedKey(const main_window::state_e & windowState, QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		// Retrieve main window controller state
		LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			default:
				break;
		}
	}
}

void main_window::Ctrl::executeAction(const main_window::state_e & windowState) {
	const QString userTypedText = this->core->getUserText();
	switch (windowState) {
		case main_window::state_e::QUIT:
			this->closeWindow();
			break;
		case main_window::state_e::TOGGLE_MENUBAR:
			this->toggleShowMenubar();
			this->changeWindowState(main_window::state_e::IDLE, main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window::state_e::COMMAND:
			// Cannot use userTypesText because it has been updated by the printUserInput function
			this->executeCommand(userTypedText, main_window::state_postprocessing_e::ACTION);
			break;
		default:
			LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << userTypedText);
			break;
	}
}

void main_window::Ctrl::prepareAction(const main_window::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();

	switch (windowState) {
		case main_window::state_e::COMMAND:
			if (pressedKey == Qt::Key_Space) {
				this->executeCommand(this->core->getUserText(), main_window::state_postprocessing_e::NONE);
			} else if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
				this->printUserInput(main_window::text_action_e::APPEND, event->text());
			}
			break;
		case main_window::state_e::IDLE:
			if (pressedKey == Qt::Key_Colon) {
				const main_window::state_e requestedWindowState = main_window::state_e::COMMAND;
				this->changeWindowState(requestedWindowState, main_window::state_postprocessing_e::POSTPROCESS, static_cast<Qt::Key>(pressedKey));
				this->setAllShortcutEnabledProperty(false);
			}
			this->printUserInput(main_window::text_action_e::CLEAR);
			break;
		default:
			LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}
}

void main_window::Ctrl::toggleShowMenubar() {
	const bool menubarVisible = this->core->topMenuBar->isVisible();
	this->core->topMenuBar->setVisible(!menubarVisible);
}

void main_window::Ctrl::closeWindow() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit this->closeWindowSignal();
}

void main_window::Ctrl::postprocessWindowStateChange(const main_window::state_e & previousState) {
	const main_window::state_e windowState = this->core->getMainWindowState();

	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Previous windowState " << previousState << " and current windowState " << windowState );

	switch (windowState) {
		case main_window::state_e::IDLE:
			this->setAllShortcutEnabledProperty(true);
			this->printUserInput(main_window::text_action_e::CLEAR);
			break;
		case main_window::state_e::QUIT:
			this->closeWindow();
			break;
		case main_window::state_e::TOGGLE_MENUBAR:
			this->toggleShowMenubar();
			this->changeWindowState(main_window::state_e::IDLE, main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window::state_e::COMMAND:
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to postprocess transaction to " << windowState << " is valid as state " << windowState << " doesn't have a defined postprocess action");
			break;
	}
}

bool main_window::Ctrl::isValidWindowState(const main_window::state_e & requestedWindowState) {
	bool isValid = false;
	const main_window::state_e windowState = this->core->getMainWindowState();

	switch (requestedWindowState) {
		case main_window::state_e::IDLE:
			// It is always possible to go to the idle state
			isValid = true;
			break;
		case main_window::state_e::QUIT:
		case main_window::state_e::COMMAND:
		case main_window::state_e::TOGGLE_MENUBAR:
			// It is only possible to start a new command if in the idle state
			isValid = (windowState == main_window::state_e::IDLE);
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}
