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

#include "logging_macros.h"
#include "function_macros.h"
#include "combo_box_find.h"

// Categories
Q_LOGGING_CATEGORY(comboBoxFindOverall, "comboBoxFind.overall", MSG_TYPE_LEVEL)

combo_box_find::ComboBoxFind::ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const global_enums::offset_type_e itemDirection, std::unique_ptr<action::Action> itemAction) : combo_box_item::ComboBoxItem(itemIcon, itemUserData, itemAction), direction(itemDirection) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, comboBoxFindOverall,  "combo box find constructor with direction " << this->direction);

}

combo_box_find::ComboBoxFind::ComboBoxFind(combo_box_find::ComboBoxFind && rhs) : combo_box_item::ComboBoxItem(std::move(rhs)), direction(std::exchange(rhs.direction, global_enums::offset_type_e::IDLE)) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, comboBoxFindOverall,  "combo box find move constructor with direction " << this->direction);
}

combo_box_find::ComboBoxFind & combo_box_find::ComboBoxFind::operator=(combo_box_find::ComboBoxFind && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, comboBoxFindOverall,  "Move assignment operator for combo box find with direction " << rhs.direction);

	if (&rhs != this) {
		combo_box_item::ComboBoxItem::operator=(std::move(rhs));
		this->direction = std::exchange(rhs.direction, global_enums::offset_type_e::IDLE);
	}

	return *this;
}

BASE_GETTER(combo_box_find::ComboBoxFind::getDirection, global_enums::offset_type_e, this->direction)
