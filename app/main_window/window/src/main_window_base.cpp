/**
 * @copyright
 * @file main_window_base.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window base class functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "main_window_base.h"
#include "global_types.h"
#include "global_macros.h"

Q_LOGGING_CATEGORY(mainWindowBaseOverall, "mainWindowBase.overall", MSG_TYPE_LEVEL)

main_window_base::MainWindowBase::MainWindowBase(QSharedPointer<main_window_core::MainWindowCore> core) : windowCore(core) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Main window base classe constructor");
}

main_window_base::MainWindowBase::~MainWindowBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Main window base class destructor");

	this->windowCore.clear();
}
