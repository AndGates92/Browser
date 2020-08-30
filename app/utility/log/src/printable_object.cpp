/**
 * @copyright
 * @file printable_object.cpp
 * @author Andrea Gianarda
 * @date 7th of August 2020
 * @brief Printable Object functions
 */

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "logging_macros.h"
#include "global_enums.h"
#include "printable_object.h"

// Categories
Q_LOGGING_CATEGORY(printableObjectOverall, "printableObject.overall", MSG_TYPE_LEVEL)

namespace printable_object {
	QDebug & operator<<(QDebug & os, const printable_object::PrintableObject & object) {
		QString str = QString();
		str << object;
		os << str;
		return os;
	}

	QString & operator<<(QString & str, const printable_object::PrintableObject & object) {
		str.append(object.qprint());
		return str;
	}

	QTextStream & operator<<(QTextStream & str, const printable_object::PrintableObject & object) {
		str << object.qprint();
		return str;
	}

	std::string operator<<(std::string str, const printable_object::PrintableObject & object) {
		str.append(object.print());
		return str;
	}

	std::string operator+(std::string str, const printable_object::PrintableObject & object) {
		str.append(object.print());
		return str;
	}
}

printable_object::PrintableObject::PrintableObject() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, printableObjectOverall,  "Creating printable object");

}

printable_object::PrintableObject::~PrintableObject() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, printableObjectOverall,  "Destructor of printable object class");

}

const QString printable_object::PrintableObject::qprint() const {
	const std::string info = this->print();
	const QString qStr (QString::fromStdString(info));

	return qStr;
}

