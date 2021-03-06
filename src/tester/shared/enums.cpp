/**
 * @copyright
 * @file enums.cpp
 * @author Andrea Gianarda
 * @date 14th of September 2020
 * @brief Tester Types functions
 */

#include <iostream>

#include <QtCore/QTextStream>

#include "app/shared/type_print_macros.h"
#include "tester/shared/enums.h"

namespace tester {

	namespace shared {

		OVERLOAD_OPERATORS_CUSTOM_TYPE(tester::shared::error_type_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(tester::shared::test_state_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(tester::shared::test_status_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(tester::shared::text_type_e)

	}

}
