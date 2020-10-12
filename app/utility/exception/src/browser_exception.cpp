/**
 * @copyright
 * @file browser_exception.cpp
 * @author Andrea Gianarda
 * @date 16th Febraury 2020
 * @brief Browser exception functions
 */

// Qt libraries
#include <QtCore/QtGlobal>

// Required by qInfo
#include <QtCore/QtDebug>

#include "function_macros.h"
#include "logging_macros.h"
#include "global_enums.h"
#include "browser_exception.h"

// Categories
Q_LOGGING_CATEGORY(browserExceptionOverall, "browserException.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(browserExceptionPrint, "browserException.print", MSG_TYPE_LEVEL)

browser_exception::BrowserException::BrowserException(const QString exceptionTimestamp, const int & exceptionLine, const QString & exceptionFile, const QString & exceptionCondition, const QString & exceptionMsg) : timestamp(exceptionTimestamp), line(exceptionLine), filename(exceptionFile), condition(exceptionCondition), message(exceptionMsg) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, browserExceptionOverall, "Browser exception is being created with message " << this->message);
}

browser_exception::BrowserException::~BrowserException() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, browserExceptionOverall, "Destroy browser exception with message " << this->message);
}

void browser_exception::BrowserException::raise() const {
	throw (*this);
}

browser_exception::BrowserException * browser_exception::BrowserException::clone() const {
	browser_exception::BrowserException * clonedException = new browser_exception::BrowserException(*this);
	return clonedException;
}

QString browser_exception::BrowserException::print() const {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, browserExceptionPrint, "Print exception message: " << this->message);
	QString str = QString();
	QTextStream(&str) << "[" << this->timestamp << "] Exception caught on file " << this->filename << " at line " << this->line;
	if (this->condition.isEmpty() == false) {
		QTextStream(&str) << " for condition" << this->condition;
	}
	QTextStream(&str) << " : " << this->message;
	return str;
}

void browser_exception::printException(QString message) {
	QTextStream errStream(stderr);
	// Qt::endl write a carriage return and flushed the stream
	errStream << "Exception caught: " << message;
	#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
	errStream << Qt::endl;
	#else
	errStream << endl;
	#endif
}

CONST_GETTER(browser_exception::BrowserException::getLine, int &, this->line)
CONST_GETTER(browser_exception::BrowserException::getFilename, QString &, this->filename)
CONST_GETTER(browser_exception::BrowserException::getCondition, QString &, this->condition)
CONST_GETTER(browser_exception::BrowserException::getTimestamp, QString &, this->timestamp)
CONST_GETTER(browser_exception::BrowserException::getMessage, QString &, this->message)
