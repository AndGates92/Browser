/**
 * @copyright
 * @file page_data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Page Data functions
 */

#include "windows/main_window/tabs/include/page_data.h"
#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/exception_macros.h"

// Categories
LOGGING_CONTEXT(mainWindowPageDataOverall, mainWindowPageData.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowPageDataPrint, mainWindowPageData.print, TYPE_LEVEL, INFO_VERBOSITY)

namespace main_window {
	bool operator==(const main_window::PageData & lhs, const main_window::PageData & rhs) {
		bool isSame = true;
		isSame &= (lhs.type == rhs.type);
		isSame &= (lhs.source.compare(rhs.source) == 0);
		isSame &= (lhs.data == rhs.data);

		return isSame;
	}

	bool operator!=(const main_window::PageData & lhs, const main_window::PageData & rhs) {
		bool isSame = (lhs == rhs);
		return !isSame;
	}

}

std::shared_ptr<main_window::PageData> main_window::PageData::makePageData(const main_window::page_type_e & type, const std::string & src, const void * data) {
	std::shared_ptr<main_window::PageData> newData = std::make_shared<main_window::PageData>(type, src, data);
	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Creating page data: " << newData.get());
	return newData;
}

main_window::PageData::PageData(const main_window::page_type_e & pageType, const std::string & src, const void * pageData): printable_object::PrintableObject(), type(pageType), source(src), data(pageData) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Page Data structure constructor. Data " << *this);

}

main_window::PageData::PageData(const main_window::PageData & rhs) : type(rhs.type), data(rhs.data) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Copy constructor main window page data");

}

main_window::PageData & main_window::PageData::operator=(const main_window::PageData & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Copy assignment operator for main window page data");

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

main_window::PageData::PageData(main_window::PageData && rhs) : type(std::exchange(rhs.type, main_window::page_type_e::UNKNOWN)), data(std::exchange(rhs.data, nullptr)) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Move constructor main window page data");
}

main_window::PageData & main_window::PageData::operator=(main_window::PageData && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Move assignment operator for main window page data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->type = std::exchange(rhs.type, main_window::page_type_e::UNKNOWN);
		this->source = std::exchange(rhs.source, std::string());
		this->data = std::exchange(rhs.data, nullptr);
	}

	return *this;
}

main_window::PageData::~PageData() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Destructor of main window page data class");
}

const std::string main_window::PageData::print() const {
	std::string structInfo;

	structInfo = structInfo + " type: " + this->type;
	structInfo = structInfo + " source of the content: " + this->source;
	std::size_t dataAddress = reinterpret_cast<std::size_t>(this->data);
	structInfo = structInfo + " extra data at address " + std::to_string(dataAddress);

	const void * thisData = this->data;

	try {
		if (thisData != nullptr) {
			EXCEPTION_ACTION(throw, "Unexpected non-null pointer for type " << this->type);
		} else {
			LOG_INFO(logger::info_level_e::ZERO, mainWindowPageDataPrint,  "Data pointer is null therefore no available extra data for type " << this->type);
		}
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	return structInfo;
}

CONST_REF_SETTER(main_window::PageData::setType, main_window::page_type_e, this->type)
CONST_GETTER(main_window::PageData::getType, main_window::page_type_e &, this->type)
BASE_SETTER(main_window::PageData::setData, const void *, this->data)
CONST_PTR_GETTER(main_window::PageData::getData, void, this->data)

bool main_window::PageData::setSource(const std::string & newSource) {
	bool hasChanged = false;

	if (this->source != newSource) {
		this->source = newSource;
		hasChanged = true;
	}

	return hasChanged;
}

CONST_GETTER(main_window::PageData::getSource, std::string &, this->source)
