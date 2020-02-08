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

	QDEBUG_OVERLOAD_PRINT_OP(main_window_shared_types::object_type_e)

	QString & operator<< (QString & str, const main_window_shared_types::object_type_e & object) {

		switch (object) {
			case main_window_shared_types::object_type_e::CURSOR:
				str.append("CURSOR");
				break;
			case main_window_shared_types::object_type_e::TAB:
				str.append("TAB");
				break;
			case main_window_shared_types::object_type_e::UNKNOWN:
				str.append("UNKNOWN");
				break;
			default:
				str.append("Unknown action");
				break;
		}

		return str;
	}

	QDEBUG_OVERLOAD_PRINT_OP(main_window_shared_types::move_value_e)

	QString & operator<< (QString & str, const main_window_shared_types::move_value_e & value_type) {

		switch (value_type) {
			case main_window_shared_types::move_value_e::IDLE:
				str.append("IDLE");
				break;
			case main_window_shared_types::move_value_e::LEFT:
				str.append("LEFT");
				break;
			case main_window_shared_types::move_value_e::RIGHT:
				str.append("RIGHT");
				break;
			case main_window_shared_types::move_value_e::ABSOLUTE:
				str.append("ABSOLUTE");
				break;
			default:
				str.append("Unknown value type");
				break;
		}

		return str;
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

	QDEBUG_OVERLOAD_PRINT_OP(main_window_shared_types::text_action_e)

	QString & operator<< (QString & str, const main_window_shared_types::text_action_e & action) {

		switch (action) {
			case main_window_shared_types::text_action_e::SET:
				str.append("SET");
				break;
			case main_window_shared_types::text_action_e::APPEND:
				str.append("APPEND");
				break;
			case main_window_shared_types::text_action_e::CLEAR:
				str.append("CLEAR");
				break;
			default:
				str.append("Unknown action");
				break;
		}

		return str;
	}

	QDEBUG_OVERLOAD_PRINT_OP(main_window_shared_types::tab_type_e)

	QString & operator<< (QString & str, const main_window_shared_types::tab_type_e & type) {

		switch (type) {
			case main_window_shared_types::tab_type_e::LABEL:
				str.append("LABEL");
				break;
			case main_window_shared_types::tab_type_e::WEB_ENGINE:
				str.append("WEB ENGINE");
				break;
			default:
				str.append("Unknown action");
				break;
		}

		return str;
	}
}

