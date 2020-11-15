/**
 * @copyright
 * @file base.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window base class functions
 */

#include "windows/main_window/window/include/base.h"
#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"

LOGGING_CONTEXT(mainWindowBaseOverall, mainWindowBase.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::Base::Base(const std::shared_ptr<main_window::Core> & windowCore) : core(windowCore) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowBaseOverall,  "Main window base classe constructor");
}

main_window::Base::Base(const main_window::Base & rhs) : core(rhs.core) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowBaseOverall,  "Copy constructor main window base");

}

main_window::Base & main_window::Base::operator=(const main_window::Base & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowBaseOverall,  "Copy assignment operator for main window base");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->core != rhs.core) {
		this->core = rhs.core;
	}

	return *this;
}

main_window::Base::Base(main_window::Base && rhs) : core(std::exchange(rhs.core, std::shared_ptr<main_window::Core>())) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowBaseOverall,  "Move constructor main window base");
}

main_window::Base & main_window::Base::operator=(main_window::Base && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowBaseOverall,  "Move assignment operator for main window base");

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
		this->core = std::exchange(rhs.core, std::shared_ptr<main_window::Core>());
	}

	return *this;
}

main_window::Base::~Base() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowBaseOverall,  "Main window base class destructor");
}

CONST_GETTER(main_window::Base::getCore, std::shared_ptr<main_window::Core> &, this->core)
