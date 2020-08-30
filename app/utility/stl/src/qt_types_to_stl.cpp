/**
 * @copyright
 * @file qt_typers_to_stl.cpp
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief Qt Types To STL definition
 */

#include "exception_macros.h"
#include "qt_types_to_stl.h"

const std::list<std::string> qt_types_to_stl::qStringListToStdList(const QStringList & qtList) {

	std::list<std::string> stlList = std::list<std::string>();

	for (const auto & str : qtList) {
		stlList.push_back(str.toStdString());
	}

	return stlList;
}

const std::map<std::string, std::string> qt_types_to_stl::qMapOfqStringToStdMapofStdStrings(const QMap<QString, QString> & qtMap) {

	std::map<std::string, std::string> stlMap = std::map<std::string, std::string>();

	for (QMap<QString, QString>::const_iterator item = qtMap.cbegin(); item != qtMap.cend(); item++) {
		stlMap.insert({item.key().toStdString(), item.value().toStdString()});
	}

	return stlMap;
}
