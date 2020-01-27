/**
 * @copyright
 * @file json_wrapper.cpp
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Wrapper
 */

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
	this->filePtr = new QFile(fileName);

	this->content = QString(QString::null);

}

json_wrapper::JsonWrapper::~JsonWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperOverall,  "Destructor of JsonWrapper class");

	delete this->filePtr;
}

void json_wrapper::JsonWrapper::readJson() {

	// Ensure that the file is open for read
	Q_ASSERT_X((this->openFlags & QIODevice::ReadOnly), "JSON file read", "JSON file is not requested to be opened for write therefore if cannot be parsed");

	// open the file
	bool openSuccess = this->filePtr->open(this->openFlags);
	if (!openSuccess) {
		qCritical(jsonWrapperFile) << "Unable to open JSON file " << this->filePtr->fileName();
		exit(EXIT_FAILURE);
	}
}

void json_wrapper::JsonWrapper::writeJson() {

}
