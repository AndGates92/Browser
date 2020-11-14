/**
 * @copyright
 * @file printable_object.cpp
 * @author Andrea Gianarda
 * @date 7th of August 2020
 * @brief Printable Object functions
 */

#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "utility/log/include/printable_object.h"

// Categories
LOGGING_CONTEXT(printableObjectOverall, printableObject.overall, TYPE_LEVEL, INFO_VERBOSITY)

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

	std::ostream & operator<<(std::ostream & os, const printable_object::PrintableObject & object) {
		os << object.print();
		return os;
	}

	std::string operator+(std::string str, const printable_object::PrintableObject & object) {
		str.append(object.print());
		return str;
	}

	logger::Logger & operator<< (logger::Logger & log, const printable_object::PrintableObject & object) {
		log << object.print();
		return log;
	}

	logger::Logger & operator+ (logger::Logger & log, const printable_object::PrintableObject & object) {
		log << object;
		return log;
	}
}

printable_object::PrintableObject::PrintableObject() {

	LOG_INFO(logger::info_level_e::ZERO, printableObjectOverall,  "Creating printable object");

}

printable_object::PrintableObject::~PrintableObject() {
	LOG_INFO(logger::info_level_e::ZERO, printableObjectOverall,  "Destructor of printable object class");

}

const QString printable_object::PrintableObject::qprint() const {
	const std::string info = this->print();
	const QString qStr (QString::fromStdString(info));

	return qStr;
}

