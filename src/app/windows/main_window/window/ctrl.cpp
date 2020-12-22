/**
 * @copyright
 * @file ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control functions
 */

// Qt libraries
#include <QtWidgets/QAction>
#include <QtGui/QKeyEvent>

#include "app/utility/logger/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/exception.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/windows/main_window/window/ctrl.h"
#include "app/windows/main_window/menu/menu_bar.h"
#include "app/windows/main_window/menu/file_menu.h"
#include "app/windows/main_window/popup/popup_container.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlOverall, mainWindowCtrl.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlUserInput, mainWindowCtrl.userInput, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlSearch, mainWindowCtrl.search, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::Ctrl::Ctrl(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : app::main_window::window::CtrlBase(parent, core) {

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

	// Update info label - as no tabs in the window, then updateInfo must be explicitely called
	const int tabIndex = this->core->getCurrentTabIndex();
	this->updateInfo(tabIndex);
}

app::main_window::window::Ctrl::~Ctrl() {

}

void app::main_window::window::Ctrl::createShortcuts() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Create shortcuts");

}

void app::main_window::window::Ctrl::connectSignals() {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	connect(this->core->topMenuBar->getFileMenu()->exitAction.get(), &QAction::triggered, this, &app::main_window::window::Ctrl::closeWindow);
	connect(this->core->popup.get(), &app::main_window::popup::PopupContainer::closeContainer,  [this] () {
		emit windowStateChangeRequested(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
	});

}

void app::main_window::window::Ctrl::actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const app::commands::KeySequence keySeq(releasedKey | keyModifiers);

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
			emit windowStateChangeRequested(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::COMMAND:
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
				this->executeCommand(this->core->getUserText(), app::main_window::state_postprocessing_e::SETUP);
			} else if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
				this->core->printUserInput(app::main_window::text_action_e::APPEND, event->text());
			}
			break;
		case app::main_window::state_e::IDLE:
			if (pressedKey == Qt::Key_Colon) {
				const app::main_window::state_e requestedWindowState = app::main_window::state_e::COMMAND;
				emit windowStateChangeRequested(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS, static_cast<Qt::Key>(pressedKey));
			}
			this->core->printUserInput(app::main_window::text_action_e::CLEAR);
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
