/**
 * @copyright
 * @file main_window_ctrl_wrapper.cpp
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper functions
 */

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtGui/QKeyEvent>

// Required by qInfo
#include <QtCore/QtDebug>

#include "main_window_ctrl_wrapper.h"
#include "key_sequence.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlWrapperOverall, "mainWindowCtrlWrapper.overall", MSG_TYPE_LEVEL)

main_window_ctrl_wrapper::MainWindowCtrlWrapper::MainWindowCtrlWrapper(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core) : QWidget(parent), main_window_base::MainWindowBase(core), winctrl(new main_window_ctrl::MainWindowCtrl(this, core)), tabctrl(new main_window_ctrl_tab::MainWindowCtrlTab(this, core)) {

}

main_window_ctrl_wrapper::MainWindowCtrlWrapper::~MainWindowCtrlWrapper() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Main window destructor");
}

void main_window_ctrl_wrapper::MainWindowCtrlWrapper::keyPressEvent(QKeyEvent * event) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyPressEvent(event);
	this->tabctrl->keyPressEvent(event);

	this->core->mainWidget->repaint();

}

void main_window_ctrl_wrapper::MainWindowCtrlWrapper::keyReleaseEvent(QKeyEvent * event) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyReleaseEvent(event);
	this->tabctrl->keyReleaseEvent(event);

	this->core->mainWidget->repaint();

}
