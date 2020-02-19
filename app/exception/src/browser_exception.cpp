/**
 * @copyright
 * @file browser_exception.cpp
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "global_macros.h"
#include "global_types.h"
#include "browser_exception.h"


// Categories
Q_LOGGING_CATEGORY(browserExceptionOverall, "browserException.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(browserExceptionPrint, "browserException.print", MSG_TYPE_LEVEL)

browser_exception::BrowserException::BrowserException(const QString & msg) : message(msg) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, browserExceptionOverall, "Browser exception is being created with message " << this->message);
}

browser_exception::BrowserException::~BrowserException() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, browserExceptionOverall, "Destroy browser exception with message " << this->message);
}

void browser_exception::BrowserException::raise() const {
	throw (*this);
}

browser_exception::BrowserException * browser_exception::BrowserException::clone() const {
	browser_exception::BrowserException * clonedException = new browser_exception::BrowserException(*this);
	return clonedException;
}

QString browser_exception::BrowserException::print() const {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, browserExceptionPrint, "Print exception message: " << this->message);
	return this->message;
}
