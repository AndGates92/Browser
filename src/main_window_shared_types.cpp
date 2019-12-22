/**
 * @copyright
 * @file main_window_shared_types.cpp
 * @author Andrea Gianarda
 * @date 21st December 2019
 * @brief Main Window Shared Types functions
 */

#include "main_window_shared_types.h"

namespace main_window_shared_types {

	QDebug & operator<< (QDebug & os, const main_window_shared_types::object_type_e & object) {

		switch (object) {
			case main_window_shared_types::object_type_e::CURSOR:
				os << "CURSOR";
				break;
			case main_window_shared_types::object_type_e::TAB:
				os << "TAB";
				break;
			case main_window_shared_types::object_type_e::UNKNOWN:
				os << "UNKNOWN";
				break;
			default:
				os << "Unknown action";
				break;
		}

		return os;
	}

}

