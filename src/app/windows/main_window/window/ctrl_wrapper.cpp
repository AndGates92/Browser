/**
 * @copyright
 * @file ctrl_wrapper.cpp
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/windows/main_window/window/ctrl_wrapper.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/shared/exception.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlWrapperOverall, mainWindowCtrlWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::CtrlWrapper::CtrlWrapper(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : QWidget(parent), app::main_window::window::Base(core), winctrl(new app::main_window::window::Ctrl(this, core)), tabctrl(new app::main_window::window::CtrlTab(this, core)) {

}

app::main_window::window::CtrlWrapper::~CtrlWrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Main window destructor");
}

void app::main_window::window::CtrlWrapper::keyPressEvent(QKeyEvent * event) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyPressEvent(event);
	this->tabctrl->keyPressEvent(event);

	this->core->mainWidget->repaint();

}

void app::main_window::window::CtrlWrapper::keyReleaseEvent(QKeyEvent * event) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyReleaseEvent(event);
	this->tabctrl->keyReleaseEvent(event);

	this->core->mainWidget->repaint();

}
