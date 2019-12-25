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
	QDEBUG_OVERLOAD_PRINT_OP(main_window_shared_types::state_e)

	QString & operator<< (QString & str, const main_window_shared_types::state_e & state) {

		switch (state) {
			case main_window_shared_types::state_e::IDLE:
				str.append("IDLE");
				break;
			case main_window_shared_types::state_e::COMMAND:
				str.append("COMMAND");
				break;
			case main_window_shared_types::state_e::OPEN_TAB:
				str.append("OPEN TAB");
				break;
			case main_window_shared_types::state_e::CLOSE_TAB:
				str.append("CLOSE TAB");
				break;
			case main_window_shared_types::state_e::REFRESH_TAB:
				str.append("REFRESH TAB");
				break;
			case main_window_shared_types::state_e::MOVE_LEFT:
				str.append("MOVE LEFT");
				break;
			case main_window_shared_types::state_e::MOVE_RIGHT:
				str.append("MOVE RIGHT");
				break;
			case main_window_shared_types::state_e::TAB_MOVE:
				str.append("TAB MOVE");
				break;
			case main_window_shared_types::state_e::SEARCH:
				str.append("SEARCH");
				break;
			default:
				str.append("Unknown state");
				break;
		}

		return str;
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

