/**
 * @copyright
 * @file browser_exception.cpp
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

#include <iostream>

#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "utility/qt/include/qt_operator.h"
#include "utility/exception/include/browser_exception.h"

// Categories
LOGGING_CONTEXT(browserExceptionOverall, browserException.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(browserExceptionPrint, browserException.print, TYPE_LEVEL, INFO_VERBOSITY)

app::browser_exception::BrowserException::BrowserException(const std::string exceptionTimestamp, const int & exceptionLine, const std::string & exceptionFile, const std::string & exceptionCondition, const std::string & exceptionMsg) : timestamp(exceptionTimestamp), line(exceptionLine), filename(exceptionFile), condition(exceptionCondition), message(exceptionMsg) {
	//LOG_INFO(app::logger::info_level_e::ZERO, browserExceptionOverall, "Browser exception is being created with message " << this->message);
}

app::browser_exception::BrowserException::~BrowserException() {
	//LOG_INFO(app::logger::info_level_e::ZERO, browserExceptionOverall, "Destroy browser exception with message " << this->message);
}

void app::browser_exception::BrowserException::raise() const {
	throw (*this);
}

app::browser_exception::BrowserException * app::browser_exception::BrowserException::clone() const {
	app::browser_exception::BrowserException * clonedException = new app::browser_exception::BrowserException(*this);
	return clonedException;
}

std::string app::browser_exception::BrowserException::print() const {
	//LOG_INFO(app::logger::info_level_e::ZERO, browserExceptionPrint, "Print exception message: " << this->message);
	std::stringstream msgStream;
	msgStream << "[" << this->timestamp << "] Exception caught on file " << this->filename << " at line " << this->line;
	if (this->condition.empty() == false) {
		msgStream << " for condition" << this->condition;
	}
	msgStream << ": " << this->message;
	return msgStream.str();
}

const char * app::browser_exception::BrowserException::what() const noexcept {
	return this->print().c_str();
}

CONST_GETTER(app::browser_exception::BrowserException::getLine, int &, this->line)
CONST_GETTER(app::browser_exception::BrowserException::getFilename, std::string &, this->filename)
CONST_GETTER(app::browser_exception::BrowserException::getCondition, std::string &, this->condition)
CONST_GETTER(app::browser_exception::BrowserException::getTimestamp, std::string &, this->timestamp)
CONST_GETTER(app::browser_exception::BrowserException::getMessage, std::string &, this->message)

void app::browser_exception::printException(std::string message) {
	std::cerr << "Exception caught: " << message;
	// std::endl write a carriage return and flushed the stream
	std::cerr << std::endl;
}
