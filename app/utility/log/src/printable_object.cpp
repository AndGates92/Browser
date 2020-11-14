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

namespace app {

	namespace printable_object {

		QDebug & operator<<(QDebug & os, const app::printable_object::PrintableObject & object) {
			QString str = QString();
			str << object;
			os << str;
			return os;
		}

		QString & operator<<(QString & str, const app::printable_object::PrintableObject & object) {
			str.append(object.qprint());
			return str;
		}

		QTextStream & operator<<(QTextStream & str, const app::printable_object::PrintableObject & object) {
			str << object.qprint();
			return str;
		}

		std::string operator<<(std::string str, const app::printable_object::PrintableObject & object) {
			str.append(object.print());
			return str;
		}

		std::ostream & operator<<(std::ostream & os, const app::printable_object::PrintableObject & object) {
			os << object.print();
			return os;
		}

		std::string operator+(std::string str, const app::printable_object::PrintableObject & object) {
			str.append(object.print());
			return str;
		}

		app::logger::Logger & operator<< (app::logger::Logger & log, const app::printable_object::PrintableObject & object) {
			log << object.print();
			return log;
		}

		app::logger::Logger & operator+ (app::logger::Logger & log, const app::printable_object::PrintableObject & object) {
			log << object;
			return log;
		}

	}

}

app::printable_object::PrintableObject::PrintableObject() {

	LOG_INFO(app::logger::info_level_e::ZERO, printableObjectOverall,  "Creating printable object");

}

app::printable_object::PrintableObject::~PrintableObject() {
	LOG_INFO(app::logger::info_level_e::ZERO, printableObjectOverall,  "Destructor of printable object class");

}

const QString app::printable_object::PrintableObject::qprint() const {
	const std::string info = this->print();
	const QString qStr (QString::fromStdString(info));

	return qStr;
}

