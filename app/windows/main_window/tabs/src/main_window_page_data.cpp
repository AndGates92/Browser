/**
 * @copyright
 * @file main_window_page_data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Page Data functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_page_data.h"
#include "global_enums.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowPageDataOverall, "mainWindowPageData.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowPageDataPrint, "mainWindowPageData.print", MSG_TYPE_LEVEL)

namespace main_window_page_data {
	bool operator==(const main_window_page_data::MainWindowPageData & lhs, const main_window_page_data::MainWindowPageData & rhs) {
		bool isSame = true;
		isSame &= (lhs.type == rhs.type);
		isSame &= (lhs.source.compare(rhs.source) == 0);
		isSame &= (lhs.data == rhs.data);

		return isSame;
	}

	bool operator!=(const main_window_page_data::MainWindowPageData & lhs, const main_window_page_data::MainWindowPageData & rhs) {
		bool isSame = (lhs == rhs);
		return !isSame;
	}

	QDebug & operator<<(QDebug & os, const main_window_page_data::MainWindowPageData & data) {
		QString str(QString::null);
		str << data;
		os << str;
		return os;
	}

	QString & operator<<(QString & str, const main_window_page_data::MainWindowPageData & data) {
		str.append(data.qprint());
		return str;
	}

	std::string & operator<<(std::string & str, const main_window_page_data::MainWindowPageData & data) {
		str.append(data.print());
		return str;
	}

}

std::shared_ptr<main_window_page_data::MainWindowPageData> main_window_page_data::MainWindowPageData::makePageData(const main_window_shared_types::page_type_e & type, const std::string src, const void * data) {
	std::shared_ptr<main_window_page_data::MainWindowPageData> newData = std::make_shared<main_window_page_data::MainWindowPageData>(type, src, data);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Creating page data: " << newData.get());
	return newData;
}

main_window_page_data::MainWindowPageData::MainWindowPageData(main_window_shared_types::page_type_e pageType, std::string src, const void * pageData): type(pageType), source(src), data(pageData) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Page Data structure constructor. Data " << *this);

}

main_window_page_data::MainWindowPageData::MainWindowPageData(const main_window_page_data::MainWindowPageData & rhs) : type(rhs.type), data(rhs.data) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Copy constructor main window page data");

}

main_window_page_data::MainWindowPageData & main_window_page_data::MainWindowPageData::operator=(const main_window_page_data::MainWindowPageData & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Copy assignment operator for main window page data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->type != rhs.type) {
		this->type = rhs.type;
	}

	if (this->source != rhs.source) {
		this->source = rhs.source;
	}

	if (this->data != rhs.data) {
		this->data = rhs.data;
	}

	return *this;
}

main_window_page_data::MainWindowPageData::MainWindowPageData(main_window_page_data::MainWindowPageData && rhs) : type(std::exchange(rhs.type, main_window_shared_types::page_type_e::UNKNOWN)), data(std::exchange(rhs.data, nullptr)) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Move constructor main window page data");
}

main_window_page_data::MainWindowPageData & main_window_page_data::MainWindowPageData::operator=(main_window_page_data::MainWindowPageData && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Move assignment operator for main window page data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->type = std::exchange(rhs.type, main_window_shared_types::page_type_e::UNKNOWN);
		this->source = std::exchange(rhs.source, std::string());
		this->data = std::exchange(rhs.data, nullptr);
	}

	return *this;
}

main_window_page_data::MainWindowPageData::~MainWindowPageData() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataOverall,  "Destructor of main window page data class");
}

const QString main_window_page_data::MainWindowPageData::qprint() const {
	const std::string mainWindowPageDataInfo = this->print();
	const QString qStr (QString::fromStdString(mainWindowPageDataInfo));

	return qStr;
}

std::string main_window_page_data::MainWindowPageData::print() const {
	std::string structInfo;

	structInfo = structInfo + " type: " + this->type;
	structInfo = structInfo + " source of the content: " + this->source;
	std::size_t dataAddress = reinterpret_cast<std::size_t>(this->data);
	structInfo = structInfo + " extra data at address " + std::to_string(dataAddress);

	const void * thisData = this->data;

	try {
		if (thisData != nullptr) {
			QEXCEPTION_ACTION(throw, "Unexpected non-null pointer for type " << this->type);
		} else {
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowPageDataPrint,  "Data pointer is null therefore no available extra data for type " << this->type);
		}
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return structInfo;
}

CONST_REF_SETTER(main_window_page_data::MainWindowPageData::setType, main_window_shared_types::page_type_e, this->type)
BASE_GETTER(main_window_page_data::MainWindowPageData::getType, main_window_shared_types::page_type_e, this->type)
BASE_SETTER(main_window_page_data::MainWindowPageData::setData, const void *, this->data)
CONST_PTR_GETTER(main_window_page_data::MainWindowPageData::getData, void, this->data)

bool main_window_page_data::MainWindowPageData::setSource(const std::string & newSource) {
	bool hasChanged = false;

	if (this->source != newSource) {
		this->source = newSource;
		hasChanged = true;
	}

	return hasChanged;
}

CONST_GETTER(main_window_page_data::MainWindowPageData::getSource, std::string, this->source)
