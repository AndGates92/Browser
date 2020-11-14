/**
 * @copyright
 * @file qt_operator.cpp
 * @author Andrea Gianarda
 * @date 24th September 2020
 * @brief Qt operator functions
 */

#include "utility/qt/include/qt_operator.h"

QTextStream & operator<<(QTextStream & stream, const std::string str) {
	stream << QString::fromStdString(str);
	return stream;
}

QDebug & operator<<(QDebug & stream, const std::string str) {
	QString qStr = QString();
	QTextStream textStream(&qStr);
	textStream << str;
	stream << textStream.string();
	return stream;
}
