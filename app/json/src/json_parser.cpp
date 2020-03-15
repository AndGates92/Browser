/**
 * @copyright
 * @file json_parser.cpp
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Parser
 */

#include <qt5/QtCore/QJsonObject>
#include <qt5/QtCore/QJsonArray>

#include "json_parser.h"
#include "global_macros.h"
#include "global_types.h"
#include "exception_macros.h"

Q_LOGGING_CATEGORY(jsonParserOverall, "jsonParser.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonParserFile, "jsonParser.file", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonParserValue, "jsonParser.value", MSG_TYPE_LEVEL)

json_parser::JsonParser::JsonParser(QString fileName, QIODevice::OpenModeFlag openFlags) : json_wrapper::JsonWrapper::JsonWrapper(fileName,openFlags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Creating JSON Parser of file " << fileName);

	this->readJson();

}

json_parser::JsonParser::JsonParser(const json_parser::JsonParser & rhs) : json_wrapper::JsonWrapper(rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Copy constructor json parser");

}

json_parser::JsonParser & json_parser::JsonParser::operator=(const json_parser::JsonParser & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Copy assignment operator for json parser");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	this->json_wrapper::JsonWrapper::operator=(rhs);
	return *this;
}

json_parser::JsonParser::JsonParser(json_parser::JsonParser && rhs) : json_wrapper::JsonWrapper(std::move(rhs)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Move constructor json parser");
}

json_parser::JsonParser & json_parser::JsonParser::operator=(json_parser::JsonParser && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Move assignment operator for json parser");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	this->json_wrapper::JsonWrapper::operator=(rhs);

	return *this;
}

json_parser::JsonParser::~JsonParser() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Destructor of JsonParser class");

}

QMap<QString, QString> json_parser::JsonParser::findKeyValue(QString key) {

	QMap<QString, QString> foundMap;

	// If it is a QJsonObject, get all keys otherwise throw an exception
	if (this->jsonContent.type() == QJsonValue::Object) {
		const QJsonObject jsonObject(this->jsonContent.toObject());
		const QStringList jsonKeys (jsonObject.keys());
		// Iterate over all key of the object
		for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "JSON key: " << *keyIter);
			const QJsonValue value(jsonObject.value(*keyIter));
			QString valueStr(this->searchJson(value, key));

			// Match key and value and add to QMap
			foundMap.insert(*keyIter, valueStr);
		}
	} else {
		QEXCEPTION_ACTION(throw,  "JSON file content is of type " << this->jsonContent.type() << ". It was expected to be an object");
	}

	return foundMap;

}

QString json_parser::JsonParser::searchJson(const QJsonValue & content, QString key) const {

	QString value(QString::null);
	switch (content.type()) {
		case QJsonValue::Object:
		{
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Searching in JSON Object");
			const QJsonObject jsonObject (content.toObject());

			// search key in current JSON object or keep looking for it
			value = this->searchJsonObject(jsonObject, key);

			break;
		}
		case QJsonValue::Array:
		{
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Searching in JSON Array");
			const QJsonArray & jsonArray (content.toArray());
			// Iterate over all elements of array
			for (QJsonArray::const_iterator arrayIter = jsonArray.begin(); arrayIter != jsonArray.end(); arrayIter++) {
				this->searchJson(*arrayIter, key);
			}
			break;
		}
		default:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "Cannot find key in type " << content.type() << ". Expected values are array (" << QJsonValue::Array << ") or object (" << QJsonValue::Object << ")");
			break;
	}

	return value;
}

QString json_parser::JsonParser::searchJsonObject(const QJsonObject & object, QString key) const {
	QString valueStr(QString::null);
	if (object.contains(key) == true) {
		QJsonObject::const_iterator iter = object.constFind(key);
		QJsonValue value(iter.value());
		if (value.isString() == true) {
			valueStr = value.toString();
		} else {
			QEXCEPTION_ACTION(throw,  "Found value is not of type string but of type " << value.type());
		}
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserValue, "Found key " << key << " with value " << valueStr);
	} else {
		const QStringList jsonKeys (object.keys());
		// Iterate over all key of the object
		for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonWrapperFileContent, "JSON key: " << *keyIter);
			const QJsonValue value(object.value(*keyIter));
			valueStr = this->searchJson(value, key);
			if (valueStr != QString::null) {
				break;
			}
		}
	}

	return valueStr;
}
