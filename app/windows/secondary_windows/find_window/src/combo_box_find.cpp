/**
 * @copyright
 * @file combo_box_find.cpp
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Find functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtCore/QVariant>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "windows/secondary_windows/find_window/include/combo_box_find.h"

// Categories
LOGGING_CONTEXT(comboBoxFindOverall, comboBoxFind.overall, TYPE_LEVEL, INFO_VERBOSITY)

combo_box_find::ComboBoxFind::ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const global_enums::offset_type_e itemDirection, std::unique_ptr<action::Action> itemAction) : combo_box_item::ComboBoxItem(itemIcon, itemUserData, itemAction), direction(itemDirection) {
	LOG_INFO(logger::info_level_e::ZERO, comboBoxFindOverall,  "combo box find constructor with direction " << this->direction);

}

combo_box_find::ComboBoxFind::ComboBoxFind(combo_box_find::ComboBoxFind && rhs) : combo_box_item::ComboBoxItem(std::move(rhs)), direction(std::exchange(rhs.direction, global_enums::offset_type_e::IDLE)) {
	LOG_INFO(logger::info_level_e::ZERO, comboBoxFindOverall,  "combo box find move constructor with direction " << this->direction);
}

combo_box_find::ComboBoxFind & combo_box_find::ComboBoxFind::operator=(combo_box_find::ComboBoxFind && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, comboBoxFindOverall,  "Move assignment operator for combo box find with direction " << rhs.direction);

	if (&rhs != this) {
		combo_box_item::ComboBoxItem::operator=(std::move(rhs));
		this->direction = std::exchange(rhs.direction, global_enums::offset_type_e::IDLE);
	}

	return *this;
}

CONST_GETTER(combo_box_find::ComboBoxFind::getDirection, global_enums::offset_type_e &, this->direction)
