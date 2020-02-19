/**
 * @copyright
 * @file main_window_shared_types.cpp
 * @author Andrea Gianarda
 * @date 21st December 2019
 * @brief Main Window Shared Types functions
 */

#include <iostream>

#include <qt5/QtCore/QTextStream>

#include "global_macros.h"
#include "main_window_shared_types.h"

namespace main_window_shared_types {

	// Overload << operator for move_value_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::move_value_e)

	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::move_value_e & value_type) {

		switch (value_type) {
			case main_window_shared_types::move_value_e::IDLE:
				str << "IDLE";
				break;
			case main_window_shared_types::move_value_e::LEFT:
				str << "LEFT";
				break;
			case main_window_shared_types::move_value_e::RIGHT:
				str << "RIGHT";
				break;
			case main_window_shared_types::move_value_e::ABSOLUTE:
				str << "ABSOLUTE";
				break;
			default:
				str << "Unknown value type";
				break;
		}

		return str;
	}

	// Overload << operator for state_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::state_e)

	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::state_e & state) {

		switch (state) {
			case main_window_shared_types::state_e::IDLE:
				str << "IDLE";
				break;
			case main_window_shared_types::state_e::COMMAND:
				str << "COMMAND";
				break;
			case main_window_shared_types::state_e::OPEN_TAB:
				str << "OPEN TAB";
				break;
			case main_window_shared_types::state_e::CLOSE_TAB:
				str << "CLOSE TAB";
				break;
			case main_window_shared_types::state_e::REFRESH_TAB:
				str << "REFRESH TAB";
				break;
			case main_window_shared_types::state_e::MOVE_LEFT:
				str << "MOVE LEFT";
				break;
			case main_window_shared_types::state_e::MOVE_RIGHT:
				str << "MOVE RIGHT";
				break;
			case main_window_shared_types::state_e::TAB_MOVE:
				str << "TAB MOVE";
				break;
			case main_window_shared_types::state_e::SEARCH:
				str << "SEARCH";
				break;
			default:
				str << "Unknown state";
				break;
		}

		return str;
	}

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::text_action_e)

	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::text_action_e & action) {

		switch (action) {
			case main_window_shared_types::text_action_e::SET:
				str << "SET";
				break;
			case main_window_shared_types::text_action_e::APPEND:
				str << "APPEND";
				break;
			case main_window_shared_types::text_action_e::CLEAR:
				str << "CLEAR";
				break;
			default:
				str << "Unknown action";
				break;
		}

		return str;
	}

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::tab_type_e)

	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::tab_type_e & type) {

		switch (type) {
			case main_window_shared_types::tab_type_e::LABEL:
				str << "LABEL";
				break;
			case main_window_shared_types::tab_type_e::WEB_ENGINE:
				str << "WEB ENGINE";
				break;
			default:
				str << "Unknown action";
				break;
		}

		return str;
	}
}

