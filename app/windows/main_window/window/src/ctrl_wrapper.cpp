/**
 * @copyright
 * @file ctrl_wrapper.cpp
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "windows/main_window/window/include/ctrl_wrapper.h"
#include "widgets/commands/include/key_sequence.h"
#include "common/include/exception_macros.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlWrapperOverall, mainWindowCtrlWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::CtrlWrapper::CtrlWrapper(QWidget * parent, const std::shared_ptr<main_window::Core> & core) : QWidget(parent), main_window::Base(core), winctrl(new main_window::Ctrl(this, core)), tabctrl(new main_window::CtrlTab(this, core)) {

}

main_window::CtrlWrapper::~CtrlWrapper() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Main window destructor");
}

void main_window::CtrlWrapper::keyPressEvent(QKeyEvent * event) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyPressEvent(event);
	this->tabctrl->keyPressEvent(event);

	this->core->mainWidget->repaint();

}

void main_window::CtrlWrapper::keyReleaseEvent(QKeyEvent * event) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyReleaseEvent(event);
	this->tabctrl->keyReleaseEvent(event);

	this->core->mainWidget->repaint();

}
