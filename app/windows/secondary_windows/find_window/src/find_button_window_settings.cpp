/**
 * @copyright
 * @file find_button_window_settings.cpp
 * @author Andrea Gianarda
 * @date 29th of July 2020
 * @brief Find Button Window Settings functions
 */

#include <string>

// Qt libraries
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLayoutItem>

#include "utility/logger/include/macros.h"
#include "common/include/exception_macros.h"
#include "windows/secondary_windows/common/include/secondary_window_utility.h"
#include "windows/secondary_windows/find_window/include/find_button_window_settings.h"

// Categories
LOGGING_CONTEXT(findButtonWindowSettingsOverall, findButtonWindowSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace find_button_window_settings {

	namespace {
		/**
		 * @brief default layout stretch
		 *
		 */
		static constexpr int defaultStretch = 0;

		/**
		 * @brief vertical spacing between widgets
		 *
		 */
		static constexpr int widgetVSpacing = 10;

		/**
		 * @brief horizontal spacing between widgets
		 *
		 */
		static constexpr int widgetHSpacing = 10;
	}

}

find_button_window_settings::FindButtonWindowSettings::FindButtonWindowSettings(QWidget * parent) : QGroupBox("Settings", parent) {

	LOG_INFO(logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Creating find button window settings");

	// Create action
	this->createActions();

	// Create widgets to put in the window
	this->fillWidget();

	// define window layout
	this->widgetLayout();

	// Connect signals and slots
	this->connectSignals();

	this->setFixedHeight(this->sizeHint().height());

	this->setCheckable(false);
	this->setChecked(false);
	this->setFlat(true);

}

find_button_window_settings::FindButtonWindowSettings::~FindButtonWindowSettings() {
	LOG_INFO(logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Destructor of FindButtonWindowSettings class");
}

void find_button_window_settings::FindButtonWindowSettings::widgetLayout() {

	// Layout
	// -------------------------------------------------
	// |         <settings group box title>            |
	// |    <direction drop down>    |     <case>      |
	// |    <direction drop down>    |   <full word>   |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(find_button_window_settings::widgetVSpacing);
		this->setLayout(layout);
	}

	try {
		// Remove all widgets in the layout in order to redraw it
		QVBoxLayout * layout = dynamic_cast<QVBoxLayout *>(this->layout());
		const int layoutSize = layout->count();
		for (int idx = 0; idx < layoutSize; idx++) {

			QLayoutItem * item(layout->takeAt(idx));

			if (item != nullptr) {
				QWidget * itemWidget = item->widget();
				// If item manages a widget, then itemWidget will not be null
				if (item->widget() == nullptr) {
					layout->removeItem(item);
				} else {
					layout->removeWidget(itemWidget);
				}
				delete item;
			}
		}

		QHBoxLayout * firstRowSettings = new QHBoxLayout(this);
		// case sensitive check box
		firstRowSettings->addWidget(this->caseSensitiveBox.get(), find_button_window_settings::defaultStretch, Qt::AlignLeft);
		firstRowSettings->addSpacing(find_button_window_settings::widgetHSpacing);
		// direction dropdown
		firstRowSettings->addWidget(this->findDirectionDropDown.get(), find_button_window_settings::defaultStretch, Qt::AlignRight);

		layout->addLayout(firstRowSettings);
		layout->addSpacing(find_button_window_settings::widgetHSpacing);
		layout->addWidget(this->matchFullWordOnlyBox.get(), find_button_window_settings::defaultStretch, Qt::AlignLeft);

	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void find_button_window_settings::FindButtonWindowSettings::createActions() {

	this->directionItems.emplace_back(QIcon(), QVariant(), global_enums::offset_type_e::UP, std::move(secondary_window_utility::createAction(this, "Up", "Search item towards the top of the page", key_sequence::KeySequence(Qt::Key_K))));
	this->directionItems.emplace_back(QIcon(), QVariant(), global_enums::offset_type_e::DOWN, std::move(secondary_window_utility::createAction(this, "Down", "Search item towards the bottom of the page", key_sequence::KeySequence(Qt::Key_J))));

	this->caseSensitiveAction = std::move(secondary_window_utility::createAction(this, "Case sensitive search", "Enable/Disable case sensitive search", key_sequence::KeySequence(Qt::Key_C)));
	this->matchFullWordOnlyAction = std::move(secondary_window_utility::createAction(this, "Match full word only", "Enable/Disbale search of full words only", key_sequence::KeySequence(Qt::Key_M)));
}

void find_button_window_settings::FindButtonWindowSettings::fillWidget() {

	this->findDirectionDropDown = secondary_window_utility::createComboBox<combo_box_find::ComboBoxFind>(this, this->directionItems);

	this->caseSensitiveBox = std::move(secondary_window_utility::createCheckBox(this, this->caseSensitiveAction));
	this->matchFullWordOnlyBox = std::move(secondary_window_utility::createCheckBox(this, this->matchFullWordOnlyAction));

}

void find_button_window_settings::FindButtonWindowSettings::connectSignals() {
	LOG_INFO(logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Connect signals");

}

QSize find_button_window_settings::FindButtonWindowSettings::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 3 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between 2 rows of widgets
	int height = this->matchFullWordOnlyBox->height() + std::max(this->caseSensitiveBox->height(), this->findDirectionDropDown->height()) + 3 * find_button_window_settings::widgetVSpacing;

	return QSize(width,height);
}

bool find_button_window_settings::FindButtonWindowSettings::isCaseSensitiveSearch() const {
	return (this->caseSensitiveBox->checkState() == Qt::Checked);
}

bool find_button_window_settings::FindButtonWindowSettings::isMatchFullWordSearch() const {
	return (this->matchFullWordOnlyBox->checkState() == Qt::Checked);
}

global_enums::offset_type_e find_button_window_settings::FindButtonWindowSettings::getSearchDirection() const {
	const int index = this->findDirectionDropDown->currentIndex();
	EXCEPTION_ACTION_COND((index == -1), throw, "Current index " << index << " is invalid to get the direction of search");
	const QString text = this->findDirectionDropDown->itemText(index);
	const auto & itemIt = std::find_if(this->directionItems.cbegin(), this->directionItems.cend(), [&] (const combo_box_find::ComboBoxFind & item) {
		return (item.getText().compare(text.toStdString()) == 0);
	});

	global_enums::offset_type_e direction = global_enums::offset_type_e::IDLE;
	if (itemIt != this->directionItems.cend()) {
		direction = itemIt->getDirection();
	}

	return direction;
}
