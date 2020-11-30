/**
 * @copyright
 * @file exception.cpp
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

#include <iostream>

#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/exception/exception.h"

// Categories
LOGGING_CONTEXT(browserExceptionOverall, browserException.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(browserExceptionPrint, browserException.print, TYPE_LEVEL, INFO_VERBOSITY)

app::exception::Exception::Exception(const std::string exceptionTimestamp, const int & exceptionLine, const std::string & exceptionFile, const std::string & exceptionCondition, const std::string & exceptionMsg) : timestamp(exceptionTimestamp), line(exceptionLine), filename(exceptionFile), condition(exceptionCondition), message(exceptionMsg) {
	//LOG_INFO(app::logger::info_level_e::ZERO, browserExceptionOverall, "Browser exception is being created with message " << this->message);
}

app::exception::Exception::~Exception() {
	//LOG_INFO(app::logger::info_level_e::ZERO, browserExceptionOverall, "Destroy browser exception with message " << this->message);
}

void app::exception::Exception::raise() const {
	throw (*this);
}

app::exception::Exception * app::exception::Exception::clone() const {
	app::exception::Exception * clonedException = new app::exception::Exception(*this);
	return clonedException;
}

std::string app::exception::Exception::print() const {
	//LOG_INFO(app::logger::info_level_e::ZERO, browserExceptionPrint, "Print exception message: " << this->message);
	std::stringstream msgStream;
	msgStream << "[" << this->timestamp << "] Exception caught on file " << this->filename << " at line " << this->line;
	if (this->condition.empty() == false) {
		msgStream << " for condition" << this->condition;
	}
	msgStream << ": " << this->message;
	return msgStream.str();
}

const char * app::exception::Exception::what() const noexcept {
	return this->print().c_str();
}

CONST_GETTER(app::exception::Exception::getLine, int &, this->line)
CONST_GETTER(app::exception::Exception::getFilename, std::string &, this->filename)
CONST_GETTER(app::exception::Exception::getCondition, std::string &, this->condition)
CONST_GETTER(app::exception::Exception::getTimestamp, std::string &, this->timestamp)
CONST_GETTER(app::exception::Exception::getMessage, std::string &, this->message)

void app::exception::printException(std::string message) {
	std::cerr << "Exception caught: " << message;
	// std::endl write a carriage return and flushed the stream
	std::cerr << std::endl;
}
