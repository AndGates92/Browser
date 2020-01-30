/**
 * @copyright
 * @file main_window_ctrl_base.cpp
 * @author Andrea Gianarda
 * @date 29th of January 2019
 * @brief Main Window Control base class functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "main_window_ctrl_base.h"
#include "global_types.h"
#include "global_macros.h"

Q_LOGGING_CATEGORY(mainWindowCtrlBaseOverall, "mainWindowCtrlBase.overall", MSG_TYPE_LEVEL)

main_window_ctrl_base::MainWindowCtrlBase::MainWindowCtrlBase(QWidget * parent, int tabIndex, int tabCount, QString jsonFileName) : parent(parent), currentTabIndex(tabIndex), tabCount(tabCount), mainWindowState(main_window_shared_types::state_e::IDLE), commands(json_parser::JsonParser(jsonFileName, QIODevice::ReadOnly)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");
}

main_window_ctrl_base::MainWindowCtrlBase::~MainWindowCtrlBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");

}