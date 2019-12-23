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

	QDebug & operator<< (QDebug & os, const main_window_shared_types::move_value_e & value_type) {

		switch (value_type) {
			case main_window_shared_types::move_value_e::IDLE:
				os << "IDLE";
				break;
			case main_window_shared_types::move_value_e::LEFT:
				os << "LEFT";
				break;
			case main_window_shared_types::move_value_e::RIGHT:
				os << "RIGHT";
				break;
			case main_window_shared_types::move_value_e::ABSOLUTE:
				os << "ABSOLUTE";
				break;
			default:
				os << "Unknown value type";
				break;
		}

		return os;
	}

	// Overload << operator for state_e
	QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & state) {

		switch (state) {
			case main_window_shared_types::state_e::IDLE:
				os << "IDLE";
				break;
			case main_window_shared_types::state_e::COMMAND:
				os << "COMMAND";
				break;
			case main_window_shared_types::state_e::OPEN_TAB:
				os << "OPEN TAB";
				break;
			case main_window_shared_types::state_e::CLOSE_TAB:
				os << "CLOSE TAB";
				break;
			case main_window_shared_types::state_e::REFRESH_TAB:
				os << "REFRESH TAB";
				break;
			case main_window_shared_types::state_e::MOVE_LEFT:
				os << "MOVE LEFT";
				break;
			case main_window_shared_types::state_e::MOVE_RIGHT:
				os << "MOVE RIGHT";
				break;
			case main_window_shared_types::state_e::TAB_MOVE:
				os << "TAB MOVE";
				break;
			case main_window_shared_types::state_e::SEARCH:
				os << "SEARCH";
				break;
			default:
				os << "Unknown state";
				break;
		}

		return os;
	}

	QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & action) {

		switch (action) {
			case main_window_shared_types::text_action_e::SET:
				os << "SET";
				break;
			case main_window_shared_types::text_action_e::APPEND:
				os << "APPEND";
				break;
			case main_window_shared_types::text_action_e::CLEAR:
				os << "CLEAR";
				break;
			default:
				os << "Unknown action";
				break;
		}

		return os;
	}

}

