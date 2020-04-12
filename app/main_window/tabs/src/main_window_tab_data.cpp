/**
 * @copyright
 * @file main_window_tab_data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Tab Data functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_tab_data.h"
#include "function_macros.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabDataOverall, "mainWindowTabData.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabDataPrint, "mainWindowTabData.print", MSG_TYPE_LEVEL)

main_window_tab_data::MainWindowTabData * main_window_tab_data::MainWindowTabData::makeTabData(const main_window_shared_types::tab_type_e & type, const std::string src, const void * data) {
	main_window_tab_data::MainWindowTabData * newData = new main_window_tab_data::MainWindowTabData(type, src, data);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataOverall,  "Creating tab data: " << newData->qprint());
	return newData;
}

main_window_tab_data::MainWindowTabData::MainWindowTabData(main_window_shared_types::tab_type_e tabType, std::string src, const void * tabData): type(tabType), source(src), data(tabData) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataOverall,  "Tab Data structure constructor. Data " << this->qprint());

}

main_window_tab_data::MainWindowTabData::MainWindowTabData(const main_window_tab_data::MainWindowTabData & rhs) : type(rhs.type), data(rhs.data) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataOverall,  "Copy constructor main window tab data");

}

main_window_tab_data::MainWindowTabData & main_window_tab_data::MainWindowTabData::operator=(const main_window_tab_data::MainWindowTabData & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataOverall,  "Copy assignment operator for main window tab data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->type != rhs.type) {
		this->type = rhs.type;
	}

	if (this->data != rhs.data) {
		this->data = rhs.data;
	}

	return *this;
}

main_window_tab_data::MainWindowTabData::MainWindowTabData(main_window_tab_data::MainWindowTabData && rhs) : type(std::exchange(rhs.type, main_window_shared_types::tab_type_e::UNKNOWN)), data(std::exchange(rhs.data, nullptr)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataOverall,  "Move constructor main window tab data");
}

main_window_tab_data::MainWindowTabData & main_window_tab_data::MainWindowTabData::operator=(main_window_tab_data::MainWindowTabData && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataOverall,  "Move assignment operator for main window tab data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->type = std::exchange(rhs.type, main_window_shared_types::tab_type_e::UNKNOWN);
		this->data = std::exchange(rhs.data, nullptr);
	}

	return *this;
}

main_window_tab_data::MainWindowTabData::~MainWindowTabData() {

}

const QString main_window_tab_data::MainWindowTabData::qprint() const {
	const std::string mainWindowTabDataInfo = this->print();
	const QString qStr (QString::fromStdString(mainWindowTabDataInfo));

	return qStr;
}

std::string main_window_tab_data::MainWindowTabData::print() const {
	std::string structInfo;

	const main_window_shared_types::tab_type_e thisType = this->type;

	structInfo = structInfo + " type: " + type;

	const void * thisData = this->data;

	try {
		if (thisData != nullptr) {
			if (type == main_window_shared_types::tab_type_e::WEB_CONTENT) {
				QEXCEPTION_ACTION(throw, "Unexpected non-null pointer for type " << type);
			} else if (type == main_window_shared_types::tab_type_e::TEXT) {
				const char * filename = static_cast<const char *>(data);

				structInfo = structInfo + " filename: " + filename;
			} else {
				QEXCEPTION_ACTION(throw, "Unknown type " << type << ". Cannot get extra data.");
			}
		} else {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabDataPrint,  "Data pointer is null therefore no available extra data for type " << thisType);
		}
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return structInfo;
}

BASE_SETTER_GETTER(main_window_tab_data::MainWindowTabData::setType, main_window_tab_data::MainWindowTabData::getType, main_window_shared_types::tab_type_e, this->type)
CONST_GETTER(main_window_tab_data::MainWindowTabData::getSource, std::string, this->source)
BASE_SETTER(main_window_tab_data::MainWindowTabData::setData, const void *, this->data)
CONST_PTR_GETTER(main_window_tab_data::MainWindowTabData::getData, void, this->data)

bool main_window_tab_data::MainWindowTabData::setSource(const std::string newSource) {
	bool hasChanged = false;

	if (this->source != newSource) {
		this->source = newSource;
		hasChanged = true;
	}

	return hasChanged;
}
