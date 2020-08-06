/**
 * @copyright
 * @file combo_box_item.cpp
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Item functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QVariant>

#include "logging_macros.h"
#include "function_macros.h"
#include "combo_box_item.h"

// Categories
Q_LOGGING_CATEGORY(comboBoxItemOverall, "comboBoxItem.overall", MSG_TYPE_LEVEL)

combo_box_item::ComboBoxItem::ComboBoxItem(const QIcon itemIcon, const QVariant itemUserData, std::unique_ptr<action::Action> & itemAction) : icon(itemIcon), userData(itemUserData), action(std::move(itemAction)) {
	QEXCEPTION_ACTION_COND((this->action == nullptr), throw,  "Action must not be null");
	QEXCEPTION_ACTION_COND((this->action->print().empty() == true), throw,  "Action text cannot be empty");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, comboBoxItemOverall,  "combo box item constructor with action " << this->action.get());

}

combo_box_item::ComboBoxItem::ComboBoxItem(combo_box_item::ComboBoxItem && rhs) : icon(std::exchange(rhs.icon, QIcon())), userData(std::exchange(rhs.userData, QVariant())), action(std::exchange(rhs.action, Q_NULLPTR)) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, comboBoxItemOverall,  "Combo box item move constructor with action " << this->action.get());
}

combo_box_item::ComboBoxItem & combo_box_item::ComboBoxItem::operator=(combo_box_item::ComboBoxItem && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, comboBoxItemOverall,  "Move assignment operator for combo box item with action " << rhs.action.get());

	if (&rhs != this) {
		this->icon = std::exchange(rhs.icon, QIcon());
		this->userData = std::exchange(rhs.userData, QVariant());
		this->action = std::move(rhs.action);
		rhs.action.reset();
	}

	return *this;
}

CONST_GETTER(combo_box_item::ComboBoxItem::getIcon, QIcon, this->icon)
CONST_GETTER(combo_box_item::ComboBoxItem::getUserData, QVariant, this->userData)
CONST_GETTER(combo_box_item::ComboBoxItem::getAction, std::unique_ptr<action::Action> &, this->action)
CONST_GETTER(combo_box_item::ComboBoxItem::getText, std::string, this->action->print())
