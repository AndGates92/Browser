/**
 * @copyright
 * @file combo_box_item.cpp
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Item functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtCore/QVariant>

#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/widgets/commands/action.h"
#include "app/windows/secondary_windows/shared/combo_box_item.h"

// Categories
LOGGING_CONTEXT(comboBoxItemOverall, comboBoxItem.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::combo_box_item::ComboBoxItem::ComboBoxItem(const QIcon itemIcon, const QVariant itemUserData, std::unique_ptr<app::action::Action> & itemAction) : icon(itemIcon), userData(itemUserData), action(std::move(itemAction)) {
	EXCEPTION_ACTION_COND((this->action == nullptr), throw,  "Action must not be null");
	EXCEPTION_ACTION_COND((this->action->print().empty() == true), throw,  "Action text cannot be empty");
	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxItemOverall,  "combo box item constructor with action " << this->action.get());

}

app::combo_box_item::ComboBoxItem::~ComboBoxItem() {
	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxItemOverall,  "Destructor of Combo box item class");
}

app::combo_box_item::ComboBoxItem::ComboBoxItem(app::combo_box_item::ComboBoxItem && rhs) : icon(std::exchange(rhs.icon, QIcon())), userData(std::exchange(rhs.userData, QVariant())), action(std::exchange(rhs.action, Q_NULLPTR)) {
	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxItemOverall,  "Combo box item move constructor with action " << this->action.get());
}

app::combo_box_item::ComboBoxItem & app::combo_box_item::ComboBoxItem::operator=(app::combo_box_item::ComboBoxItem && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxItemOverall,  "Move assignment operator for combo box item with action " << rhs.action.get());

	if (&rhs != this) {
		this->icon = std::exchange(rhs.icon, QIcon());
		this->userData = std::exchange(rhs.userData, QVariant());
		this->action = std::move(rhs.action);
		rhs.action.reset();
	}

	return *this;
}

CONST_GETTER(app::combo_box_item::ComboBoxItem::getIcon, QIcon &, this->icon)
CONST_GETTER(app::combo_box_item::ComboBoxItem::getUserData, QVariant &, this->userData)
CONST_GETTER(app::combo_box_item::ComboBoxItem::getAction, std::unique_ptr<app::action::Action> &, this->action)
CONST_GETTER(app::combo_box_item::ComboBoxItem::getText, std::string, this->action->print())
