/**
 * @copyright
 * @file error_data.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Error data functions
 */

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/error_data.h"
#include "base/tester/include/test.h"

// Categories
LOGGING_CONTEXT(errorDataOverall, errorData.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::shared::ErrorData::ErrorData(const std::weak_ptr<tester::base::Test> & errorTest, const std::string & errorFilename, const int & errorLineNumber, const std::string & errorCondition, const std::string & errorMessage) : test(errorTest), lineNumber(errorLineNumber), filename(errorFilename), condition(errorCondition), message(errorMessage) {
	LOG_INFO(app::logger::info_level_e::ZERO, errorDataOverall,  "Error data constructor");
}

tester::shared::ErrorData::~ErrorData() {
	LOG_INFO(app::logger::info_level_e::ZERO, errorDataOverall,  "Error data destructor");
}

tester::shared::ErrorData::ErrorData(const tester::shared::ErrorData & rhs) : test(rhs.getTest()), lineNumber(rhs.lineNumber), filename(rhs.filename), condition(rhs.condition), message(rhs.message) {

	LOG_INFO(app::logger::info_level_e::ZERO, errorDataOverall,  "Copy constructor error data");

}

tester::shared::ErrorData & tester::shared::ErrorData::operator=(const tester::shared::ErrorData & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, errorDataOverall,  "Copy assignment operator for error data");

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

tester::shared::ErrorData::ErrorData(tester::shared::ErrorData && rhs) : test(std::exchange(rhs.test, std::weak_ptr<tester::base::Test>())), lineNumber(std::exchange(rhs.lineNumber, -1)), filename(std::exchange(rhs.filename, std::string())), condition(std::exchange(rhs.condition, std::string())), message(std::exchange(rhs.message, std::string())) {

	LOG_INFO(app::logger::info_level_e::ZERO, errorDataOverall,  "Move constructor error data");
}

tester::shared::ErrorData & tester::shared::ErrorData::operator=(tester::shared::ErrorData && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, errorDataOverall,  "Move assignment operator for error data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->lineNumber = std::exchange(rhs.lineNumber, -1);
		this->condition = std::exchange(rhs.condition, std::string());
		this->filename = std::exchange(rhs.filename, std::string());
		this->test = std::exchange(rhs.test, std::weak_ptr<tester::base::Test>());
		this->message = std::exchange(rhs.message, std::string());
	}

	return *this;
}

CONST_GETTER(tester::shared::ErrorData::getLine, int &, this->lineNumber)
CONST_GETTER(tester::shared::ErrorData::getFilename, std::string &, this->filename)
CONST_GETTER(tester::shared::ErrorData::getCondition, std::string &, this->condition)
CONST_GETTER(tester::shared::ErrorData::getMessage, std::string &, this->message)

const std::shared_ptr<tester::base::Test> tester::shared::ErrorData::getTest() const {
	EXCEPTION_ACTION_COND((this->test.expired() == true), throw,  "Unable to get test as it has already expired");
	const std::shared_ptr<tester::base::Test> testSharedPtr = this->test.lock();
	return testSharedPtr;
}

const std::string tester::shared::ErrorData::print() const {
	std::string errorInfo;

	errorInfo = errorInfo + " Test [ " + this->getTest()->getName() + " ]";
	errorInfo = errorInfo + " Line " + std::to_string(this->lineNumber);
	errorInfo = errorInfo + " in file " + this->filename + ":";
	if (this->condition.empty() == false) {
		errorInfo = errorInfo + " Condition " + this->condition;
	}
	errorInfo = errorInfo + " Error Message " + this->message;

	return errorInfo;
}

bool tester::shared::ErrorData::operator== (const tester::shared::ErrorData & otherData) const {
	bool sameLine = (this->lineNumber == otherData.lineNumber);
	bool sameFilename = (this->filename.compare(otherData.filename) == 0);

	bool isSame = ((this->partialEqual(otherData) == true) && (sameLine == true) && (sameFilename == true));

	return isSame;
}

bool tester::shared::ErrorData::partialEqual (const tester::shared::ErrorData & otherData) const {
	bool sameFile = (this->filename.compare(otherData.filename) == 0);
	bool sameMessage = (this->message.compare(otherData.message) == 0);
	bool sameTest = (this->getTest() == otherData.getTest());

	bool isSame = ((sameFile == true) && (sameTest == true) && (sameMessage == true));

	return isSame;
}
