/**
 * @copyright
 * @file qt_operator.cpp
 * @author Andrea Gianarda
 * @date 24th September 2020
 * @brief Qt operator functions
 */

#include <QtCore/QtDebug>

#include "qt_operator.h"

QTextStream & operator<<(QTextStream & stream, const std::string str) {
	stream << QString::fromStdString(str);
	return stream;
}

QDebug & operator<<(QDebug & os, const std::string str) {
	os << QString::fromStdString(str);
	return os;
}
