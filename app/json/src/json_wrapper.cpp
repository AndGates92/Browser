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

json_wrapper::JsonWrapper::JsonWrapper(QString fileName, QIODevice::OpenModeFlag openFlags) : openFlags(openFlags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Creating JSON Wrapper of file " << fileName);

	// Ensure that the file is open for read or write or both
	Q_ASSERT_X(((this->openFlags & QIODevice::ReadOnly) || (this->openFlags & QIODevice::WriteOnly)), "JsonWrapper constructor", "JSON file not requested to be opened for read or write");

	// Create file
	this->jsonFile = new QFile(fileName);

	this->content = QString(QString::null);

}

json_wrapper::JsonWrapper::~JsonWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Destructor of JsonWrapper class");

	delete this->jsonFile;

}

void json_wrapper::JsonWrapper::readJson() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Read JSON file " << this->jsonFile->fileName());

	QIODevice::OpenModeFlag readFlags = QIODevice::OpenModeFlag(int(this->openFlags) | int(QIODevice::ReadOnly));

	// open the file
	bool openSuccess = this->jsonFile->open(readFlags);
	if (!openSuccess) {
		qCritical(jsonWrapperFile) << "Unable to open JSON file " << this->jsonFile->fileName() << " for read";
		exit(EXIT_FAILURE);
	}

	// Copy content into QString
	this->content = QString(this->jsonFile->readAll());

	this->jsonFile->close();
}

void json_wrapper::JsonWrapper::writeJson(QString key, QJsonValue jsonVal) {

	Q_ASSERT_X((this->openFlags & QIODevice::WriteOnly), "JSON file write", "JSON file is not requested to be opened for write therefore it cannot be written");

	this->readJson();

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFile,  "Write JSON file " << this->jsonFile->fileName());

	QByteArray contentByteArray(this->content.toUtf8());
	QJsonParseError * jsonParseError = nullptr;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(contentByteArray, jsonParseError));

	// Check if JSON parsing is successful
	if (jsonDoc.isNull() == 1) {
		qCritical(jsonWrapperFile) << "Unable to parse QString to JSON file because of error " << jsonParseError->errorString() << "(error type " << jsonParseError->error << ")";
		exit(EXIT_FAILURE);
	}

	QJsonObject jsonObj(jsonDoc.object());
	QJsonArray  jsonArray(jsonDoc.array());

	// Ensure that the file is open for read
	Q_ASSERT_X((jsonObj.empty() & jsonArray.empty()), "JSON file write", "JSON document doesn't contain neither an object and array");

	if (jsonObj.empty() == 0) {
		// Update JSON object
		QJsonObject::iterator iter = jsonObj.insert(key, jsonVal);
		// Ensure that the file is open for read
		if (iter != jsonObj.end()) {
			qCritical(jsonWrapperFile) << "Unable to add element " << jsonVal.toString() << " at key " << key;
			exit(EXIT_FAILURE);
		}
		jsonDoc.setObject(jsonObj);

	} else if (jsonArray.empty() == 0) {
		// Update JSON array
		jsonArray.push_front(jsonVal);
		jsonDoc.setArray(jsonArray);
	}

	// Write updated JSON content to QByteArray
	QByteArray updatedContent(jsonDoc.toJson(QJsonDocument::Indented));

	this->content = QString(updatedContent);

	// open the file
	// Set QIODevicne to WriteOnly and Truncate to replace the content of the entire file
	bool openSuccess = this->jsonFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
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
