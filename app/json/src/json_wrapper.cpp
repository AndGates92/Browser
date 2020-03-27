/**
 * @copyright
 * @file json_wrapper.cpp
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Wrapper
 */

#include <qt5/QtCore/QJsonArray>
#include <qt5/QtCore/QJsonObject>
#include <qt5/QtCore/QJsonDocument>
#include <qt5/QtCore/QJsonParseError>

#include "json_wrapper.h"
#include "logging_macros.h"
#include "type_print_macros.h"
#include "global_types.h"
#include "exception_macros.h"

Q_LOGGING_CATEGORY(jsonWrapperOverall, "jsonWrapper.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonWrapperFile, "jsonWrapper.file", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonWrapperFileContent, "jsonWrapper.file_content", MSG_TYPE_LEVEL)


namespace json_wrapper {

	OVERLOAD_OPERATORS_CUSTOM_TYPE(json_wrapper::json_content_type_e)

}

json_wrapper::JsonWrapper::JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags) : jsonContent(QJsonValue()), openFlags(jsonOpenFlags), jsonFile(new QFile(jsonFileName)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Creating JSON Wrapper of file " << jsonFileName);

	// Ensure that the file is open for read or write or both
	Q_ASSERT_X(((this->openFlags & QIODevice::ReadOnly) || (this->openFlags & QIODevice::WriteOnly)), "JsonWrapper constructor", "JSON file not requested to be opened for read or write");

}

json_wrapper::JsonWrapper::JsonWrapper(const json_wrapper::JsonWrapper & rhs) : jsonContent(rhs.jsonContent), type(rhs.type), openFlags(rhs.openFlags), jsonFile(rhs.jsonFile) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Copy constructor json wrapper");

}

json_wrapper::JsonWrapper & json_wrapper::JsonWrapper::operator=(const json_wrapper::JsonWrapper & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Copy assignment operator for json wrapper");

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

json_wrapper::JsonWrapper::JsonWrapper(json_wrapper::JsonWrapper && rhs) : jsonContent(std::move(rhs.jsonContent)), type(std::move(rhs.type)), openFlags(std::move(rhs.openFlags)), jsonFile(std::move(rhs.jsonFile)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Move constructor json wrapper");

	// Reset rhs
	rhs.jsonContent = QJsonValue::Undefined;
	rhs.type = json_wrapper::json_content_type_e::UNKNOWN;
	rhs.openFlags = QIODevice::NotOpen;
	rhs.jsonFile = Q_NULLPTR;
}

json_wrapper::JsonWrapper & json_wrapper::JsonWrapper::operator=(json_wrapper::JsonWrapper && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Move assignment operator for json wrapper");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->jsonContent != rhs.jsonContent) {
		this->jsonContent = std::move(rhs.jsonContent);
	}
	rhs.jsonContent = QJsonValue::Undefined;

	if (this->type != rhs.type) {
		this->type = std::move(rhs.type);
	}
	rhs.type = json_wrapper::json_content_type_e::UNKNOWN;

	if (this->openFlags != rhs.openFlags) {
		this->openFlags = std::move(rhs.openFlags);
	}
	rhs.openFlags = QIODevice::NotOpen;

	if (this->jsonFile != rhs.jsonFile) {
		if (this->jsonFile != Q_NULLPTR) {
			delete this->jsonFile;
		}
		this->jsonFile = std::move(rhs.jsonFile);
	}
	rhs.jsonFile = Q_NULLPTR;

	return *this;
}

json_wrapper::JsonWrapper::~JsonWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Destructor of JsonWrapper class");

	delete this->jsonFile;

}

void json_wrapper::JsonWrapper::readJson() {

	Q_ASSERT_X((this->openFlags & QIODevice::ReadOnly), "JSON file read", "JSON file is requested to be opened for read but flags don't allow it to open it for read");

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Read JSON file " << this->jsonFile->fileName());

	// open the file
	bool openSuccess = this->jsonFile->open(this->openFlags);
	QEXCEPTION_ACTION_COND((!openSuccess), throw,  "Unable to open JSON file " << this->jsonFile->fileName() << " for read");

	// Copy content into QString
	QString content(this->jsonFile->readAll());

	this->jsonFile->close();

	// Convert JSON file content to UTF8 in order to create a JSON document
	QByteArray contentUtf8(content.toUtf8());
	QJsonParseError * jsonParseError = nullptr;

	QJsonDocument jsonDoc = QJsonDocument(QJsonDocument::fromJson(contentUtf8, jsonParseError));

	// Check if JSON parsing is successful
	QEXCEPTION_ACTION_COND((jsonDoc.isNull() == 1), throw,  "Unable to convert UTF8 QString to JSON file because of error " << jsonParseError->errorString() << "(error type " << jsonParseError->error << ")");

	delete jsonParseError;

	if (jsonDoc.isObject() == true) {
		QJsonObject jsonObj(jsonDoc.object());
		Q_ASSERT_X((jsonObj.empty() == false), "JSON object is empty", "JSON file has an empty object");
		this->jsonContent = QJsonValue(jsonObj);
	} else if (jsonDoc.isArray() == true) {
		QJsonArray jsonArray(jsonDoc.array());
		Q_ASSERT_X((jsonArray.empty() == false), "JSON array is empty", "JSON file has an empty array");
		this->jsonContent = QJsonValue(jsonArray);
	} else if (jsonDoc.isEmpty() == true) {
		QEXCEPTION_ACTION(throw,  "Cannot read empty JSON file");
	} else if (jsonDoc.isNull() == true) {
		QEXCEPTION_ACTION(throw,  "Cannot read null JSON file");
	} else {
		QEXCEPTION_ACTION(throw,  "Invalid data type");
	}

	this->walkJson(this->jsonContent);

}

void json_wrapper::JsonWrapper::walkJson(const QJsonValue & content) const {

	switch (content.type()) {
		case QJsonValue::Object:
		{
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Printing JSON Object");
			const QJsonObject & jsonObject (content.toObject());
			const QStringList & jsonKeys (jsonObject.keys());

			// Iterate over all key of the object
			for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "JSON key: " << *keyIter);
				const QJsonValue value(jsonObject.value(*keyIter));
				this->walkJson(value);
			}
			break;
		}
		case QJsonValue::Array:
		{
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Printing JSON Array");
			const QJsonArray & jsonArray (content.toArray());
			// Iterate over all elements of array
			for (QJsonArray::const_iterator arrayIter = jsonArray.begin(); arrayIter != jsonArray.end(); arrayIter++) {
				this->walkJson(*arrayIter);
			}
			break;
		}
		case QJsonValue::Null:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Value is null");
			break;
		case QJsonValue::Bool:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Value is of type boolean: " << content.toBool());
			break;
		case QJsonValue::Double:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Value is of type double: " << content.toDouble());
			break;
		case QJsonValue::String:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Value is of type string: " << content.toString());
			break;
		case QJsonValue::Undefined:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Value is undefined");
			break;
		default:
			QEXCEPTION_ACTION(throw,  "Unknown type " << content.type());
			break;
	}
}

void json_wrapper::JsonWrapper::addJsonValue(QJsonValue & content, const QJsonValue & val, const QString & key) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Append JSON value of type " << val.type());

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
				QEXCEPTION_ACTION_COND((val.isObject() == false), throw,  "Cannot add non-JSON object without key to a JSON object");
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
		QEXCEPTION_ACTION(throw,  "Cannot add new value to QJsonValue of type " << content.type());
	}

}

void json_wrapper::JsonWrapper::appendJsonObject(QJsonObject & jsonObj, const QJsonObject & newObj) {
	const QStringList & jsonKeys (newObj.keys());

	// Iterate over all key of the object
	for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
		// Warn if key already exists and subsequently replace it
		if (jsonObj.contains(*keyIter) == true) {
			QWARNING_PRINT(jsonWrapperFileContent, "key " << *keyIter << " already exists");
			QJsonObject::const_iterator objIter = jsonObj.find(*keyIter);
			this->walkJson(*objIter);
		}
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Adding JSON key: " << *keyIter);
		const QJsonValue value(newObj.value(*keyIter));
		this->walkJson(value);
		jsonObj.insert(*keyIter, value);
	}
}

void json_wrapper::JsonWrapper::insertToJsonObject(QJsonObject & jsonObj, const QString & key, const QJsonValue & val) {
	// Update JSON object
	QJsonObject::iterator iter = jsonObj.insert(key, val);
	// Ensure that the insertion was successful
	QEXCEPTION_ACTION_COND((iter != jsonObj.end()), throw,  "Unable to add JSON value of type " << val.type() << " at key " << key);
}

void json_wrapper::JsonWrapper::writeJson() {

	Q_ASSERT_X((this->openFlags & QIODevice::WriteOnly), "JSON file write", "JSON file is not requested to be opened for write therefore it cannot be written");

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Write JSON file " << this->jsonFile->fileName());

	QJsonDocument jsonDoc;

	if (this->jsonContent.isObject() == true) {
		jsonDoc = QJsonDocument(this->jsonContent.toObject());
	} else if (this->jsonContent.isArray() == true) {
		jsonDoc = QJsonDocument(this->jsonContent.toArray());
	} else {
		QEXCEPTION_ACTION(throw,  "Invalid data type of JSON file content");
	}

	// Write updated JSON content to QByteArray
	QByteArray updatedContent(jsonDoc.toJson(QJsonDocument::Indented));

	// open the file
	// Set QIODevicne to WriteOnly and Truncate to replace the content of the entire file
	bool openSuccess = this->jsonFile->open(this->openFlags);
	QEXCEPTION_ACTION_COND((!openSuccess), throw,  "Unable to open JSON file " << this->jsonFile->fileName() << " for write");

	// Write File
	qint64 writeReturn = this->jsonFile->write(updatedContent);
	QEXCEPTION_ACTION_COND((writeReturn == -1), throw,  "Write to JSON file " << this->jsonFile->fileName() << " failed");

	this->jsonFile->close();
}
