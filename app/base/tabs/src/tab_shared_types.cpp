/**
 * @copyright
 * @file tab_shared_types.cpp
 * @author Andrea Gianarda
 * @date 11th of April 2020
 * @brief Tab Shared Types functions
 */

#include <iostream>

#include <QtCore/QTextStream>

#include "common/include/type_print_macros.h"
#include "base/tabs/include/tab_shared_types.h"

namespace app {
	namespace base {
		namespace tab {

			// Overload << operator for offset_type_e
			OVERLOAD_OPERATORS_CUSTOM_TYPE(app::base::tab::load_status_e)

			// Overload << operator for direction_e
			OVERLOAD_OPERATORS_CUSTOM_TYPE(app::base::tab::direction_e)

			// Overload << operator for direction_e
			OVERLOAD_OPERATORS_CUSTOM_TYPE(app::base::tab::stepping_e)

		}
	}
}
