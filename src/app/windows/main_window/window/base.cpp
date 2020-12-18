/**
 * @copyright
 * @file base.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window base class functions
 */

#include "app/shared/enums.h"
#include "app/shared/setters_getters.h"
#include "app/windows/main_window/window/base.h"
#include "app/utility/logger/macros.h"

LOGGING_CONTEXT(mainWindowBaseOverall, mainWindowBase.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::Base::Base(const std::shared_ptr<app::main_window::window::Core> & windowCore) : core(windowCore) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowBaseOverall,  "Main window base classe constructor");
}

app::main_window::window::Base::Base(const app::main_window::window::Base & rhs) : core(rhs.core) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowBaseOverall,  "Copy constructor main window base");

}

app::main_window::window::Base & app::main_window::window::Base::operator=(const app::main_window::window::Base & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowBaseOverall,  "Copy assignment operator for main window base");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->core != rhs.core) {
		this->core = rhs.core;
	}

	return *this;
}

app::main_window::window::Base::Base(app::main_window::window::Base && rhs) : core(std::exchange(rhs.core, std::shared_ptr<app::main_window::window::Core>())) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowBaseOverall,  "Move constructor main window base");
}

app::main_window::window::Base & app::main_window::window::Base::operator=(app::main_window::window::Base && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowBaseOverall,  "Move assignment operator for main window base");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->core != rhs.core) {
		if (this->core == nullptr) {
			try {
				this->core.reset();
			} catch (const std::bad_alloc & badAllocE) {
				EXCEPTION_ACTION(throw, badAllocE.what());
			}
		}
		this->core = std::exchange(rhs.core, std::shared_ptr<app::main_window::window::Core>());
	}

	return *this;
}

app::main_window::window::Base::~Base() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowBaseOverall,  "Main window base class destructor");
}

CONST_GETTER(app::main_window::window::Base::getCore, std::shared_ptr<app::main_window::window::Core> &, this->core)
