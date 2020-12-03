/**
 * @copyright
 * @file wrapper.cpp
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Wrapper
 */

// Qt libraries
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonParseError>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/utility/json/wrapper.h"
#include "app/shared/type_print_macros.h"
#include "app/shared/enums.h"
#include "app/shared/exception.h"

LOGGING_CONTEXT(jsonWrapperOverall, jsonWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(jsonWrapperFile, jsonWrapper.file, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(jsonWrapperFileContent, jsonWrapper.file_content, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace utility {

		namespace json {

			OVERLOAD_OPERATORS_CUSTOM_TYPE(app::utility::json::json_content_type_e)

		}

	}

}

app::utility::json::Wrapper::Wrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags) : jsonContent(QJsonValue()), openFlags(jsonOpenFlags), jsonFile(new QFile(jsonFileName)) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperOverall,  "Creating JSON Wrapper of file " << jsonFileName);

	// Ensure that the file is open for read or write or both
	EXCEPTION_ACTION_COND(((this->openFlags & QIODevice::ReadOnly) == 0), throw, "JSON file doesn't have read flag set to 1 when it was opened therefore it cannot be written");

}

app::utility::json::Wrapper::Wrapper(const app::utility::json::Wrapper & rhs) : jsonContent(rhs.jsonContent), type(rhs.type), openFlags(rhs.openFlags), jsonFile(rhs.jsonFile) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperOverall,  "Copy constructor json wrapper");

}

app::utility::json::Wrapper & app::utility::json::Wrapper::operator=(const app::utility::json::Wrapper & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperOverall,  "Copy assignment operator for json wrapper");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->jsonContent != rhs.jsonContent) {
		this->jsonContent = rhs.jsonContent;
	}

	if (this->type != rhs.type) {
		this->type = rhs.type;
	}

	if (this->openFlags != rhs.openFlags) {
		this->openFlags = rhs.openFlags;
	}

	if (this->jsonFile != rhs.jsonFile) {
		if (this->jsonFile != Q_NULLPTR) {
			delete this->jsonFile;
		}
		this->jsonFile = rhs.jsonFile;
	}

	return *this;
}

app::utility::json::Wrapper::Wrapper(app::utility::json::Wrapper && rhs) : jsonContent(std::exchange(rhs.jsonContent, QJsonValue::Undefined)), type(std::exchange(rhs.type, app::utility::json::json_content_type_e::UNKNOWN)), openFlags(std::exchange(rhs.openFlags, QIODevice::NotOpen)), jsonFile(std::exchange(rhs.jsonFile, Q_NULLPTR)) {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperOverall,  "Move constructor json wrapper");
}

app::utility::json::Wrapper & app::utility::json::Wrapper::operator=(app::utility::json::Wrapper && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperOverall,  "Move assignment operator for json wrapper");

	if (&rhs != this) {
		this->jsonContent = std::exchange(rhs.jsonContent, QJsonValue::Undefined);

		this->type = std::exchange(rhs.type, app::utility::json::json_content_type_e::UNKNOWN);

		this->openFlags = std::exchange(rhs.openFlags, QIODevice::NotOpen);

		if (this->jsonFile != Q_NULLPTR) {
			delete this->jsonFile;
		}
		this->jsonFile = std::exchange(rhs.jsonFile, Q_NULLPTR);
	}

	return *this;
}

app::utility::json::Wrapper::~Wrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperOverall,  "Destructor of Wrapper class");

	if (this->jsonFile != Q_NULLPTR) {
		delete this->jsonFile;
	}

}

void app::utility::json::Wrapper::readJson() {

	Q_ASSERT_X((this->openFlags & QIODevice::ReadOnly), "JSON file read", "JSON file is requested to be opened for read but flags don't allow it to open it for read");

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFile,  "Read JSON file " << this->jsonFile->fileName());

	// open the file
	bool openSuccess = this->jsonFile->open(this->openFlags);
	EXCEPTION_ACTION_COND((!openSuccess), throw,  "Unable to open JSON file " << this->jsonFile->fileName() << " for read");

	// Copy content into QString
	QString content(this->jsonFile->readAll());

	this->jsonFile->close();

	// Convert JSON file content to UTF8 in order to create a JSON document
	QByteArray contentUtf8(content.toUtf8());
	QJsonParseError jsonParseError;

	QJsonDocument jsonDoc = QJsonDocument(QJsonDocument::fromJson(contentUtf8, &jsonParseError));

	if (jsonParseError.error != QJsonParseError::NoError) {
		const int ErrorCharToPrint = 20;
		int pos = 0;
		// Trying to print a string that has the issue in the middle
		// Choosing arbitrary 20 characters so that the user can have an hint to debug it
		// If the character is in the first ErrorCharToPrint/2 character, starts at the beginning of the file
		if (jsonParseError.offset < ErrorCharToPrint/2) {
			pos = 0;
		} else {
			pos = jsonParseError.offset - ErrorCharToPrint/2;
		}

		const QString errorInFile(content.mid(pos, ErrorCharToPrint));
		// Check if JSON parsing is successful
		EXCEPTION_ACTION_COND((jsonDoc.isNull() == true), throw,  "Unable to convert content of file " << this->jsonFile->fileName() << " as UTF8 QString to JSON document because of error " << jsonParseError.errorString() << " (error type " << jsonParseError.error << ") in the following file fragment " << errorInFile);
	}

	if (jsonDoc.isObject() == true) {
		QJsonObject jsonObj(jsonDoc.object());
		EXCEPTION_ACTION_COND((jsonObj.empty() == true), throw, "JSON file is an empty object");
		this->jsonContent = QJsonValue(jsonObj);
		this->type = app::utility::json::json_content_type_e::OBJECT;
	} else if (jsonDoc.isArray() == true) {
		QJsonArray jsonArray(jsonDoc.array());
		EXCEPTION_ACTION_COND((jsonArray.empty() == true), throw, "JSON file is an empty array");
		this->jsonContent = QJsonValue(jsonArray);
		this->type = app::utility::json::json_content_type_e::ARRAY;
	} else if (jsonDoc.isEmpty() == true) {
		EXCEPTION_ACTION(throw,  "Cannot read empty JSON file");
	} else if (jsonDoc.isNull() == true) {
		EXCEPTION_ACTION(throw,  "Cannot read null JSON file");
	} else {
		EXCEPTION_ACTION(throw,  "Invalid data type");
	}

	this->walkJson(this->jsonContent);

}

void app::utility::json::Wrapper::walkJson(const QJsonValue & content) const {

	switch (content.type()) {
		case QJsonValue::Object:
		{
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Printing JSON Object");
			const QJsonObject & jsonObject (content.toObject());
			const QStringList & jsonKeys (jsonObject.keys());

			// Iterate over all key of the object
			for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
				LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "JSON key: " << *keyIter);
				const QJsonValue value(jsonObject.value(*keyIter));
				this->walkJson(value);
			}
			break;
		}
		case QJsonValue::Array:
		{
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Printing JSON Array");
			const QJsonArray & jsonArray (content.toArray());
			// Iterate over all elements of array
			for (QJsonArray::const_iterator arrayIter = jsonArray.begin(); arrayIter != jsonArray.end(); arrayIter++) {
				this->walkJson(*arrayIter);
			}
			break;
		}
		case QJsonValue::Null:
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Value is null");
			break;
		case QJsonValue::Bool:
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Value is of type boolean: " << content.toBool());
			break;
		case QJsonValue::Double:
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Value is of type double: " << content.toDouble());
			break;
		case QJsonValue::String:
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Value is of type string: " << content.toString());
			break;
		case QJsonValue::Undefined:
			LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Value is undefined");
			break;
		default:
			EXCEPTION_ACTION(throw,  "Unknown type " << content.type());
			break;
	}
}

void app::utility::json::Wrapper::addJsonValue(QJsonValue & content, const QJsonValue & val, const QString & key) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFile,  "Append JSON value of type " << val.type());

	if (content.isObject() == true) {

		// Create a pointer to the JSON content
		QJsonObject jsonObj = content.toObject();

		// If key is not provided, then it is expected that a QJsonObject is added to the input QJsonObject content.
		// All pairs key-value of QJsonValue val are added on the first level of the hierarchy
		if (key.isEmpty() == true) {

			if (val.isObject() == true) {
				QJsonObject newObject (val.toObject());
				this->appendJsonObject(jsonObj, newObject);
			} else {
				EXCEPTION_ACTION_COND((val.isObject() == false), throw,  "Cannot add non-JSON object without key to a JSON object");
			}
		} else {
			// Insert to JSON object
			this->insertToJsonObject(jsonObj, key, val);
		}

		// Copy back updated value
		content = QJsonValue(jsonObj);

	} else if (content.isArray() == true) {

		// Create a pointer to the JSON content
		QJsonArray jsonArray = content.toArray();

		if (key.isEmpty() == true) {
			// Update JSON array
			jsonArray.push_front(val);
		} else {
			QJsonObject newObj;
			// Insert to JSON object
			this->insertToJsonObject(newObj, key, val);

			// Push new QJsonObject to the front
			jsonArray.push_front(newObj);
		}

		// Copy back updated value
		content = QJsonValue(jsonArray);

	} else if ((content.isUndefined() == true) || (content.isNull() == true)) {
		if (key.isEmpty()) {
			// Copy val to content if it is an JSON object or a JSON array
			if ((content.isArray() == true) || (content.isObject() == true)) {
				content = val;
			} else {
				// Push val to an intermediate array and then copy it to content
				QJsonArray jsonArray;
				jsonArray.push_front(val);
				content = jsonArray;
			}
		} else {
			// Create an intermediate JSON object to pair key and val
			QJsonObject jsonObj;
			jsonObj.insert(key, val);
			content = QJsonValue(jsonObj);
		}
	} else {
		EXCEPTION_ACTION(throw,  "Cannot add new value to QJsonValue of type " << content.type());
	}

}

void app::utility::json::Wrapper::appendJsonObject(QJsonObject & jsonObj, const QJsonObject & newObj) {
	const QStringList & jsonKeys (newObj.keys());

	// Iterate over all key of the object
	for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
		// Warn if key already exists and subsequently replace it
		if (jsonObj.contains(*keyIter) == true) {
			LOG_WARNING(jsonWrapperFileContent, "key " << *keyIter << " already exists");
			QJsonObject::const_iterator objIter = jsonObj.find(*keyIter);
			this->walkJson(*objIter);
		}
		LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFileContent, "Adding JSON key: " << *keyIter);
		const QJsonValue value(newObj.value(*keyIter));
		this->walkJson(value);
		jsonObj.insert(*keyIter, value);
	}
}

void app::utility::json::Wrapper::insertToJsonObject(QJsonObject & jsonObj, const QString & key, const QJsonValue & val) {
	// Update JSON object
	QJsonObject::iterator iter = jsonObj.insert(key, val);
	// Ensure that the insertion was successful
	EXCEPTION_ACTION_COND((iter != jsonObj.end()), throw,  "Unable to add JSON value of type " << val.type() << " at key " << key);
}

void app::utility::json::Wrapper::writeJson() {

	EXCEPTION_ACTION_COND(((this->openFlags & QIODevice::WriteOnly) == 0), throw, "JSON file doesn't have write flag set to 1 when it was opened therefore it cannot be written");

	LOG_INFO(app::logger::info_level_e::ZERO, jsonWrapperFile,  "Write JSON file " << this->jsonFile->fileName());

	QJsonDocument jsonDoc;

	if (this->jsonContent.isObject() == true) {
		jsonDoc = QJsonDocument(this->jsonContent.toObject());
		this->type = app::utility::json::json_content_type_e::OBJECT;
	} else if (this->jsonContent.isArray() == true) {
		jsonDoc = QJsonDocument(this->jsonContent.toArray());
		this->type = app::utility::json::json_content_type_e::ARRAY;
	} else {
		EXCEPTION_ACTION(throw,  "Invalid data type of JSON file content");
	}

	// Write updated JSON content to QByteArray
	QByteArray updatedContent(jsonDoc.toJson(QJsonDocument::Indented));

	// open the file
	// Set QIODevicne to WriteOnly and Truncate to replace the content of the entire file
	bool openSuccess = this->jsonFile->open(this->openFlags);
	EXCEPTION_ACTION_COND((!openSuccess), throw,  "Unable to open JSON file " << this->jsonFile->fileName() << " for write");

	// Write File
	qint64 writeReturn = this->jsonFile->write(updatedContent);
	EXCEPTION_ACTION_COND((writeReturn == -1), throw,  "Write to JSON file " << this->jsonFile->fileName() << " failed");

	this->jsonFile->close();
}
