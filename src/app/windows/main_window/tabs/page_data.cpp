/**
 * @copyright
 * @file page_data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Page Data functions
 */

#include "app/windows/main_window/tabs/page_data.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/shared/exception.h"

// Categories
LOGGING_CONTEXT(mainWindowPageDataOverall, mainWindowPageData.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowPageDataPrint, mainWindowPageData.print, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace tab {

			bool operator==(const app::main_window::tab::PageData & lhs, const app::main_window::tab::PageData & rhs) {
				bool isSame = true;
				isSame &= (lhs.type == rhs.type);
				isSame &= (lhs.source.compare(rhs.source) == 0);
				isSame &= (lhs.data == rhs.data);

				return isSame;
			}

			bool operator!=(const app::main_window::tab::PageData & lhs, const app::main_window::tab::PageData & rhs) {
				bool isSame = (lhs == rhs);
				return !isSame;
			}

		}

	}

}

std::shared_ptr<app::main_window::tab::PageData> app::main_window::tab::PageData::makePageData(const app::main_window::page_type_e & type, const std::string & src, const void * data) {
	std::shared_ptr<app::main_window::tab::PageData> newData = std::make_shared<app::main_window::tab::PageData>(type, src, data);
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Creating page data: " << newData.get());
	return newData;
}

app::main_window::tab::PageData::PageData(const app::main_window::page_type_e & pageType, const std::string & src, const void * pageData): app::printable_object::PrintableObject(), type(pageType), source(src), data(pageData) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Page Data structure constructor. Data " << *this);

}

app::main_window::tab::PageData::PageData(const app::main_window::tab::PageData & rhs) : type(rhs.type), data(rhs.data) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Copy constructor main window page data");

}

app::main_window::tab::PageData & app::main_window::tab::PageData::operator=(const app::main_window::tab::PageData & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Copy assignment operator for main window page data");

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

app::main_window::tab::PageData::PageData(app::main_window::tab::PageData && rhs) : type(std::exchange(rhs.type, app::main_window::page_type_e::UNKNOWN)), data(std::exchange(rhs.data, nullptr)) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Move constructor main window page data");
}

app::main_window::tab::PageData & app::main_window::tab::PageData::operator=(app::main_window::tab::PageData && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Move assignment operator for main window page data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->type = std::exchange(rhs.type, app::main_window::page_type_e::UNKNOWN);
		this->source = std::exchange(rhs.source, std::string());
		this->data = std::exchange(rhs.data, nullptr);
	}

	return *this;
}

app::main_window::tab::PageData::~PageData() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataOverall,  "Destructor of main window page data class");
}

const std::string app::main_window::tab::PageData::print() const {
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
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPageDataPrint,  "Data pointer is null therefore no available extra data for type " << this->type);
		}
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	return structInfo;
}

CONST_REF_SETTER(app::main_window::tab::PageData::setType, app::main_window::page_type_e, this->type)
CONST_GETTER(app::main_window::tab::PageData::getType, app::main_window::page_type_e &, this->type)
BASE_SETTER(app::main_window::tab::PageData::setData, const void *, this->data)
CONST_PTR_GETTER(app::main_window::tab::PageData::getData, void, this->data)

bool app::main_window::tab::PageData::setSource(const std::string & newSource) {
	bool hasChanged = false;

	if (this->source != newSource) {
		this->source = newSource;
		hasChanged = true;
	}

	return hasChanged;
}

CONST_GETTER(app::main_window::tab::PageData::getSource, std::string &, this->source)
