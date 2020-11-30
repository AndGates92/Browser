/**
 * @copyright
 * @file classes.cpp
 * @author Andrea Gianarda
 * @date 31st of March 2020
 * @brief Global class definition
 */

#include "app/shared/classes.h"

bool app::shared::StringCompare::operator() (const std::string & rhs, const std::string & lhs) const {
	return (rhs.compare(lhs) < 0);
}
