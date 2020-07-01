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
#include "logging_macros.h"

Q_LOGGING_CATEGORY(mainWindowBaseOverall, "mainWindowBase.overall", MSG_TYPE_LEVEL)

main_window_base::MainWindowBase::MainWindowBase(std::shared_ptr<main_window_core::MainWindowCore> core) : windowCore(core) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Main window base classe constructor");
}

main_window_base::MainWindowBase::MainWindowBase(const main_window_base::MainWindowBase & rhs) : windowCore(rhs.windowCore) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Copy constructor main window base");

}

main_window_base::MainWindowBase & main_window_base::MainWindowBase::operator=(const main_window_base::MainWindowBase & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Copy assignment operator for main window base");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->windowCore != rhs.windowCore) {
		this->windowCore = rhs.windowCore;
	}

	return *this;
}

main_window_base::MainWindowBase::MainWindowBase(main_window_base::MainWindowBase && rhs) : windowCore(std::exchange(rhs.windowCore, std::shared_ptr<main_window_core::MainWindowCore>())) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Move constructor main window base");
}

main_window_base::MainWindowBase & main_window_base::MainWindowBase::operator=(main_window_base::MainWindowBase && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Move assignment operator for main window base");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->windowCore != rhs.windowCore) {
		if (this->windowCore == nullptr) {
			try {
				this->windowCore.reset();
			} catch (const std::bad_alloc & badAllocE) {
				QEXCEPTION_ACTION(throw, badAllocE.what());
			}
		}
		this->windowCore = std::exchange(rhs.windowCore, std::shared_ptr<main_window_core::MainWindowCore>());
	}

	return *this;
}

main_window_base::MainWindowBase::~MainWindowBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowBaseOverall,  "Main window base class destructor");
}
