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
#include "global_macros.h"
#include "global_types.h"

Q_LOGGING_CATEGORY(jsonWrapperOverall, "jsonWrapper.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonWrapperFile, "jsonWrapper.file", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonWrapperFileContent, "jsonWrapper.file_content", MSG_TYPE_LEVEL)


namespace json_wrapper {
	QDEBUG_OVERLOAD_PRINT_OP(json_wrapper::json_content_type_e)

	QString & operator<< (QString & str, const json_wrapper::json_content_type_e & type) {

		switch (type) {
			case json_wrapper::json_content_type_e::OBJECT:
				str.append("OBJECT");
				break;
			case json_wrapper::json_content_type_e::ARRAY:
				str.append("ARRAY");
				break;
			default:
				str.append("Unknown type");
				break;
		}

		return str;
	}
}

json_wrapper::JsonWrapper::JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags) : jsonContent(QJsonValue()), openFlags(jsonOpenFlags), jsonFile(new QFile(jsonFileName)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Creating JSON Wrapper of file " << jsonFileName);

	// Ensure that the file is open for read or write or both
	Q_ASSERT_X(((this->openFlags & QIODevice::ReadOnly) || (this->openFlags & QIODevice::WriteOnly)), "JsonWrapper constructor", "JSON file not requested to be opened for read or write");

	// Create file
	this->jsonFile = new QFile(jsonFileName);

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
	QCRITICAL_PRINT((!openSuccess), jsonWrapperFile, "Unable to open JSON file " << this->jsonFile->fileName() << " for read");

	// Copy content into QString
	QString content(this->jsonFile->readAll());

	this->jsonFile->close();

	// Convert JSON file content to UTF8 in order to create a JSON document
	QByteArray contentUtf8(content.toUtf8());
	QJsonParseError * jsonParseError = nullptr;

	QJsonDocument jsonDoc = QJsonDocument(QJsonDocument::fromJson(contentUtf8, jsonParseError));

	// Check if JSON parsing is successful
	QCRITICAL_PRINT((jsonDoc.isNull() == 1), jsonWrapperFile, "Unable to convert UTF8 QString to JSON file because of error " << jsonParseError->errorString() << "(error type " << jsonParseError->error << ")");

	if (jsonDoc.isObject() == true) {
		QJsonObject jsonObj(jsonDoc.object());
		Q_ASSERT_X((jsonObj.empty() == false), "JSON object is empty", "JSON file has an empty object");
		this->jsonContent = QJsonValue(jsonObj);
	} else if (jsonDoc.isArray() == true) {
		QJsonArray jsonArray(jsonDoc.array());
		Q_ASSERT_X((jsonArray.empty() == false), "JSON array is empty", "JSON file has an empty array");
		this->jsonContent = QJsonValue(jsonArray);
	} else if (jsonDoc.isEmpty() == true) {
		QCRITICAL_PRINT(true, jsonWrapperFile, "Cannot read empty JSON file");
	} else if (jsonDoc.isNull() == true) {
		QCRITICAL_PRINT(true, jsonWrapperFile, "Cannot read null JSON file");
	} else {
		QCRITICAL_PRINT(true, jsonWrapperFile, "Invalid data type");
	}

	this->walkJson(this->jsonContent);
}

void json_wrapper::JsonWrapper::walkJson(const QJsonValue & content) {

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
			// Iterat over all elements of array
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
			QCRITICAL_PRINT(true, jsonWrapperFile, "Unknown type " << content.type());
			break;
	}
}

bool json_wrapper::JsonWrapper::addJsonValue(QJsonValue jsonVal, QString key) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Append JSON value of type " << jsonVal.type());

	bool ret = false;

	if (this->jsonContent.isObject() == true) {

		// Create a pointer to the JSON content
		QJsonObject jsonObj = this->jsonContent.toObject();

		// Update JSON object
		QJsonObject::iterator iter = jsonObj.insert(key, jsonVal);
		// Ensure that the file is open for read
		QCRITICAL_PRINT((iter != jsonObj.end()), jsonWrapperFile, "Unable to add JSON value of type " << jsonVal.type() << " at key " << key);

		// Copy back updated value
		this->jsonContent = QJsonValue(jsonObj);

		ret = true;

	} else if (this->jsonContent.isArray() == true) {

		// Create a pointer to the JSON content
		QJsonArray jsonArray = this->jsonContent.toArray();

		// Update JSON array
		jsonArray.push_front(jsonVal);

		// Copy back updated value
		this->jsonContent = QJsonValue(jsonArray);

		ret = true;

	} else if (this->jsonContent.isUndefined() == true) {
		if (key.isNull()) {
			this->jsonContent = jsonVal;
		} else {
			QJsonObject jsonObj;
			jsonObj.insert(key, jsonVal);
			this->jsonContent = QJsonValue(jsonObj);
		}
	} else {
		QCRITICAL_PRINT(true, jsonWrapperFile, "Unknown type " << this->jsonContent.type());
	}

	return ret;

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
		QCRITICAL_PRINT(true, jsonWrapperFile, "Invalid data type");
	}

	// Write updated JSON content to QByteArray
	QByteArray updatedContent(jsonDoc.toJson(QJsonDocument::Indented));

	// open the file
	// Set QIODevicne to WriteOnly and Truncate to replace the content of the entire file
	bool openSuccess = this->jsonFile->open(this->openFlags);
	QCRITICAL_PRINT((!openSuccess), jsonWrapperFile, "Unable to open JSON file " << this->jsonFile->fileName() << " for write");

	// Write File
	qint64 writeReturn = this->jsonFile->write(updatedContent);
	QCRITICAL_PRINT((writeReturn == -1), jsonWrapperFile, "Write to JSON file " << this->jsonFile->fileName() << " failed");

	this->jsonFile->close();
}
