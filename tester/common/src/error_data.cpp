/**
 * @copyright
 * @file error_data.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Error data functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "error_data.h"
#include "base_test.h"

// Categories
Q_LOGGING_CATEGORY(errorDataOverall, "errorData.overall", MSG_TYPE_LEVEL)

error_data::ErrorData::ErrorData(const std::weak_ptr<base_test::BaseTest> & errorTest, const std::string & errorFilename, const int & errorLineNumber, const std::string & errorCondition, const std::string & errorMessage) : test(errorTest), lineNumber(errorLineNumber), filename(errorFilename), condition(errorCondition), message(errorMessage) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, errorDataOverall,  "Error data constructor");
}

error_data::ErrorData::~ErrorData() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, errorDataOverall,  "Error data destructor");
}

error_data::ErrorData::ErrorData(const error_data::ErrorData & rhs) : test(rhs.getTest()), lineNumber(rhs.lineNumber), filename(rhs.filename), condition(rhs.condition), message(rhs.message) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, errorDataOverall,  "Copy constructor error data");

}

error_data::ErrorData & error_data::ErrorData::operator=(const error_data::ErrorData & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, errorDataOverall,  "Copy assignment operator for error data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->getTest() != rhs.getTest()) {
		this->test = rhs.getTest();
	}

	if (this->lineNumber != rhs.lineNumber) {
		this->lineNumber = rhs.lineNumber;
	}

	if (this->condition != rhs.condition) {
		this->condition = rhs.condition;
	}

	if (this->filename != rhs.filename) {
		this->filename = rhs.filename;
	}

	if (this->message != rhs.message) {
		this->message = rhs.message;
	}

	return *this;
}

error_data::ErrorData::ErrorData(error_data::ErrorData && rhs) : test(std::exchange(rhs.test, std::weak_ptr<base_test::BaseTest>())), lineNumber(std::exchange(rhs.lineNumber, -1)), filename(std::exchange(rhs.filename, std::string())), condition(std::exchange(rhs.condition, std::string())), message(std::exchange(rhs.message, std::string())) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, errorDataOverall,  "Move constructor error data");
}

error_data::ErrorData & error_data::ErrorData::operator=(error_data::ErrorData && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, errorDataOverall,  "Move assignment operator for error data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->lineNumber = std::exchange(rhs.lineNumber, -1);
		this->condition = std::exchange(rhs.condition, std::string());
		this->filename = std::exchange(rhs.filename, std::string());
		this->test = std::exchange(rhs.test, std::weak_ptr<base_test::BaseTest>());
		this->message = std::exchange(rhs.message, std::string());
	}

	return *this;
}

CONST_GETTER(error_data::ErrorData::getLine, int &, this->lineNumber)
CONST_GETTER(error_data::ErrorData::getFilename, std::string &, this->filename)
CONST_GETTER(error_data::ErrorData::getCondition, std::string &, this->condition)
CONST_GETTER(error_data::ErrorData::getMessage, std::string &, this->message)

const std::shared_ptr<base_test::BaseTest> error_data::ErrorData::getTest() const {
	QEXCEPTION_ACTION_COND((this->test.expired() == true), throw,  "Unable to get test as it has already expired");
	const std::shared_ptr<base_test::BaseTest> testSharedPtr = this->test.lock();
	return testSharedPtr;
}

const std::string error_data::ErrorData::print() const {
	std::string errorInfo;

	errorInfo = errorInfo + " Test [ " + this->getTest()->getName() + " ]";
	errorInfo = errorInfo + " Line " + std::to_string(this->lineNumber);
	errorInfo = errorInfo + " in file " + this->filename + ":";
	errorInfo = errorInfo + " Condition " + this->condition;
	errorInfo = errorInfo + " Error Message " + this->message;

	return errorInfo;
}

bool error_data::ErrorData::operator== (const error_data::ErrorData & otherData) const {
	bool sameLine = (this->lineNumber == otherData.lineNumber);
	bool sameFilename = (this->filename.compare(otherData.filename) == 0);

	bool isSame = ((this->partialEqual(otherData) == true) && (sameLine == true) && (sameFilename == true));

	return isSame;
}

bool error_data::ErrorData::partialEqual (const error_data::ErrorData & otherData) const {
	bool sameFile = (this->filename.compare(otherData.filename) == 0);
	bool sameMessage = (this->message.compare(otherData.message) == 0);
	bool sameTest = (this->getTest() == otherData.getTest());

	bool isSame = ((sameFile == true) && (sameTest == true) && (sameMessage == true));

	return isSame;
}
