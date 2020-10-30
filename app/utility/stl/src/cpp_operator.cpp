/**
 * @copyright
 * @file cpp_operator.cpp
 * @author Andrea Gianarda
 * @date 02nd November 2020
 * @brief C++ operator functions
 */

#include "cpp_operator.h"

std::ostream & operator<<(std::ostream & stream, const std::string & str) {
	stream << str.c_str();
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const QString & str) {
	stream << str.toStdString();
	return stream;
}
