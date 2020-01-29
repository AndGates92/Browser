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

json_wrapper::JsonWrapper::JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags, json_wrapper::json_content_type_e jsonContentType) : jsonContent({jsonContentType, QVariant()}), openFlags(jsonOpenFlags), jsonFile(new QFile(jsonFileName)) {

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
	if (!openSuccess) {
		qCritical(jsonWrapperFile) << "Unable to open JSON file " << this->jsonFile->fileName() << " for read";
		exit(EXIT_FAILURE);
	}

	// Copy content into QString
	QString content(this->jsonFile->readAll());

	this->jsonFile->close();

	// Convert JSON file content to UTF8 in order to create a JSON document
	QByteArray contentUtf8(content.toUtf8());
	QJsonParseError * jsonParseError = nullptr;

	QJsonDocument jsonDoc = QJsonDocument(QJsonDocument::fromJson(contentUtf8, jsonParseError));

	// Check if JSON parsing is successful
	if (jsonDoc.isNull() == 1) {
		qCritical(jsonWrapperFile) << "Unable to convert UTF8 QString to JSON file because of error " << jsonParseError->errorString() << "(error type " << jsonParseError->error << ")";
		exit(EXIT_FAILURE);
	}

	if (jsonDoc.isObject() == true) {
		this->jsonContent.contentType = json_wrapper::json_content_type_e::OBJECT;
		QJsonObject jsonObj(jsonDoc.object());
		Q_ASSERT_X((jsonObj.empty() == false), "JSON object is empty", "JSON file has an empty object");
		this->jsonContent.content = QVariant(jsonObj);
	} else if (jsonDoc.isArray() == true) {
		this->jsonContent.contentType = json_wrapper::json_content_type_e::ARRAY;
		QJsonArray jsonArray(jsonDoc.array());
		Q_ASSERT_X((jsonArray.empty() == false), "JSON array is empty", "JSON file has an empty array");
		this->jsonContent.content = QVariant(jsonArray);
	}
}

bool json_wrapper::JsonWrapper::addJsonValue(QString key, QJsonValue jsonVal) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Append JSON value of type " << jsonVal.type());

	bool ret = false;

	if (this->jsonContent.contentType == json_wrapper::json_content_type_e::OBJECT) {

		Q_ASSERT_X((this->jsonContent.content.canConvert<QJsonObject>()), "Conversion to QJsonObject", "QVariant cannot be converted to QJsonObject");

		// Create a pointer to the JSON content
		QJsonObject jsonObj = this->jsonContent.content.toJsonObject();

		// Update JSON object
		QJsonObject::iterator iter = jsonObj.insert(key, jsonVal);
		// Ensure that the file is open for read
		if (iter != jsonObj.end()) {
			qCritical(jsonWrapperFile) << "Unable to add JSON value of type " << jsonVal.type() << " at key " << key;
			exit(EXIT_FAILURE);
		}

		// Copy back updated value
		this->jsonContent.content = QVariant(jsonObj);

		ret = true;

	} else if (this->jsonContent.contentType == json_wrapper::json_content_type_e::ARRAY) {

		Q_ASSERT_X((this->jsonContent.content.canConvert<QJsonArray>()), "Conversion to QJsonArray", "QVariant cannot be converted to QJsonArray");

		// Create a pointer to the JSON content
		QJsonArray jsonArray = this->jsonContent.content.toJsonArray();

		// Update JSON array
		jsonArray.push_front(jsonVal);

		// Copy back updated value
		this->jsonContent.content = QVariant(jsonArray);

		ret = true;

	}

	return ret;

}

void json_wrapper::JsonWrapper::writeJson() {

	Q_ASSERT_X((this->openFlags & QIODevice::WriteOnly), "JSON file write", "JSON file is not requested to be opened for write therefore it cannot be written");

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Write JSON file " << this->jsonFile->fileName());

	QJsonDocument jsonDoc;

	// Cast QVariant to QJsonDocument
	if (this->jsonContent.contentType == json_wrapper::json_content_type_e::OBJECT) {
		Q_ASSERT_X((this->jsonContent.content.canConvert<QJsonObject>()), "Conversion to QJsonObject", "QVariant cannot be converted to QJsonObject");
		jsonDoc = QJsonDocument(this->jsonContent.content.toJsonObject());
	} else if (this->jsonContent.contentType == json_wrapper::json_content_type_e::ARRAY) {
		Q_ASSERT_X((this->jsonContent.content.canConvert<QJsonArray>()), "Conversion to QJsonArray", "QVariant cannot be converted to QJsonArray");
		jsonDoc = QJsonDocument(this->jsonContent.content.toJsonArray());
	}

	// Write updated JSON content to QByteArray
	QByteArray updatedContent(jsonDoc.toJson(QJsonDocument::Indented));

	// open the file
	// Set QIODevicne to WriteOnly and Truncate to replace the content of the entire file
	bool openSuccess = this->jsonFile->open(this->openFlags);
	if (!openSuccess) {
		qCritical(jsonWrapperFile) << "Unable to open JSON file " << this->jsonFile->fileName() << " for write";
		exit(EXIT_FAILURE);
	}

	// Write File
	qint64 writeReturn = this->jsonFile->write(updatedContent);
	if (writeReturn == -1) {
		qCritical(jsonWrapperFile) << "Write to JSON file " << this->jsonFile->fileName() << " failed";
		exit(EXIT_FAILURE);
	}

	this->jsonFile->close();
}
