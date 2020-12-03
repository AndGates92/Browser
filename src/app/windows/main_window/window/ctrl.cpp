/**
 * @copyright
 * @file ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/exception.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/windows/main_window/window/ctrl.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlOverall, mainWindowCtrl.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlUserInput, mainWindowCtrl.userInput, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlSearch, mainWindowCtrl.search, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace window {

			namespace ctrl {

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

		}

	}

}

app::main_window::window::Ctrl::Ctrl(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : app::main_window::window::CtrlBase(parent, core, app::main_window::window::ctrl::commandFileFullPath) {

	// Shortcuts
	this->createExtraShortcuts();

	// Connect signals and slots
	this->connectExtraSignals();

	// Update info label - as no tabs in the window, then updateInfo must be explicitely called
	const int tabIndex = this->core->getCurrentTabIndex();
	this->updateInfo(tabIndex);
}

app::main_window::window::Ctrl::~Ctrl() {

}

void app::main_window::window::Ctrl::createExtraShortcuts() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Create shortcuts");

}

void app::main_window::window::Ctrl::connectExtraSignals() {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	connect(this->core->topMenuBar->getFileMenu()->exitAction.get(), &QAction::triggered, this, &app::main_window::window::Ctrl::closeWindow);
	connect(this->core->popup.get(), &app::main_window::popup::PopupContainer::closeContainer,  [this] () {
		this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
	});

}

void app::main_window::window::Ctrl::actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const app::key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		// Retrieve main window controller state
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			default:
				break;
		}
	}
}

void app::main_window::window::Ctrl::executeAction(const app::main_window::state_e & windowState) {
	const QString userTypedText = this->core->getUserText();
	switch (windowState) {
		case app::main_window::state_e::QUIT:
			this->closeWindow();
			break;
		case app::main_window::state_e::TOGGLE_MENUBAR:
			this->toggleShowMenubar();
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::COMMAND:
			// Cannot use userTypesText because it has been updated by the printUserInput function
			this->executeCommand(userTypedText, app::main_window::state_postprocessing_e::ACTION);
			break;
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << userTypedText);
			break;
	}
}

void app::main_window::window::Ctrl::prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();

	switch (windowState) {
		case app::main_window::state_e::COMMAND:
			if (pressedKey == Qt::Key_Space) {
				this->executeCommand(this->core->getUserText(), app::main_window::state_postprocessing_e::NONE);
			} else if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
				this->printUserInput(app::main_window::text_action_e::APPEND, event->text());
			}
			break;
		case app::main_window::state_e::IDLE:
			if (pressedKey == Qt::Key_Colon) {
				const app::main_window::state_e requestedWindowState = app::main_window::state_e::COMMAND;
				this->changeWindowState(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS, static_cast<Qt::Key>(pressedKey));
				this->setAllShortcutEnabledProperty(false);
			}
			this->printUserInput(app::main_window::text_action_e::CLEAR);
			break;
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}
}

void app::main_window::window::Ctrl::toggleShowMenubar() {
	const bool menubarVisible = this->core->topMenuBar->isVisible();
	this->core->topMenuBar->setVisible(!menubarVisible);
}

void app::main_window::window::Ctrl::closeWindow() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit this->closeWindowSignal();
}

void app::main_window::window::Ctrl::postprocessWindowStateChange(const app::main_window::state_e & previousState) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Previous windowState " << previousState << " and current windowState " << windowState );

	switch (windowState) {
		case app::main_window::state_e::IDLE:
			this->setAllShortcutEnabledProperty(true);
			this->printUserInput(app::main_window::text_action_e::CLEAR);
			break;
		case app::main_window::state_e::QUIT:
			this->closeWindow();
			break;
		case app::main_window::state_e::TOGGLE_MENUBAR:
			this->toggleShowMenubar();
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::COMMAND:
			this->setAllShortcutEnabledProperty(false);
			this->setFocus();
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to postprocess transaction to " << windowState << " is valid as state " << windowState << " doesn't have a defined postprocess action");
			break;
	}
}

bool app::main_window::window::Ctrl::isValidWindowState(const app::main_window::state_e & requestedWindowState) {
	bool isValid = false;
	const app::main_window::state_e windowState = this->core->getMainWindowState();

	switch (requestedWindowState) {
		case app::main_window::state_e::IDLE:
			// It is always possible to go to the idle state
			isValid = true;
			break;
		case app::main_window::state_e::QUIT:
		case app::main_window::state_e::COMMAND:
		case app::main_window::state_e::TOGGLE_MENUBAR:
			// It is only possible to start a new command if in the idle state
			isValid = (windowState == app::main_window::state_e::IDLE);
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}
