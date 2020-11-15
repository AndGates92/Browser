/**
 * @copyright
 * @file window_settings.cpp
 * @author Andrea Gianarda
 * @date 29th of July 2020
 * @brief Find Window Settings functions
 */

#include <string>

// Qt libraries
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLayoutItem>

#include "utility/logger/include/macros.h"
#include "common/include/exception_macros.h"
#include "windows/secondary_windows/common/include/utility.h"
#include "windows/secondary_windows/find_window/include/window_settings.h"

// Categories
LOGGING_CONTEXT(findButtonWindowSettingsOverall, findButtonWindowSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace find_window {

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

find_window::WindowSettings::WindowSettings(QWidget * parent) : QGroupBox("Settings", parent) {

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

find_window::WindowSettings::~WindowSettings() {
	LOG_INFO(logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Destructor of WindowSettings class");
}

void find_window::WindowSettings::widgetLayout() {

	// Layout
	// -------------------------------------------------
	// |         <settings group box title>            |
	// |    <direction drop down>    |     <case>      |
	// |    <direction drop down>    |   <full word>   |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(find_window::widgetVSpacing);
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
		firstRowSettings->addWidget(this->caseSensitiveBox.get(), find_window::defaultStretch, Qt::AlignLeft);
		firstRowSettings->addSpacing(find_window::widgetHSpacing);
		// direction dropdown
		firstRowSettings->addWidget(this->findDirectionDropDown.get(), find_window::defaultStretch, Qt::AlignRight);

		layout->addLayout(firstRowSettings);
		layout->addSpacing(find_window::widgetHSpacing);
		layout->addWidget(this->matchFullWordOnlyBox.get(), find_window::defaultStretch, Qt::AlignLeft);

	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void find_window::WindowSettings::createActions() {

	this->directionItems.emplace_back(QIcon(), QVariant(), global_enums::offset_type_e::UP, std::move(secondary_window::createAction(this, "Up", "Search item towards the top of the page", key_sequence::KeySequence(Qt::Key_K))));
	this->directionItems.emplace_back(QIcon(), QVariant(), global_enums::offset_type_e::DOWN, std::move(secondary_window::createAction(this, "Down", "Search item towards the bottom of the page", key_sequence::KeySequence(Qt::Key_J))));

	this->caseSensitiveAction = std::move(secondary_window::createAction(this, "Case sensitive search", "Enable/Disable case sensitive search", key_sequence::KeySequence(Qt::Key_C)));
	this->matchFullWordOnlyAction = std::move(secondary_window::createAction(this, "Match full word only", "Enable/Disbale search of full words only", key_sequence::KeySequence(Qt::Key_M)));
}

void find_window::WindowSettings::fillWidget() {

	this->findDirectionDropDown = secondary_window::createComboBox<find_window::ComboBoxFind>(this, this->directionItems);

	this->caseSensitiveBox = std::move(secondary_window::createCheckBox(this, this->caseSensitiveAction));
	this->matchFullWordOnlyBox = std::move(secondary_window::createCheckBox(this, this->matchFullWordOnlyAction));

}

void find_window::WindowSettings::connectSignals() {
	LOG_INFO(logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Connect signals");

}

QSize find_window::WindowSettings::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 3 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between 2 rows of widgets
	int height = this->matchFullWordOnlyBox->height() + std::max(this->caseSensitiveBox->height(), this->findDirectionDropDown->height()) + 3 * find_window::widgetVSpacing;

	return QSize(width,height);
}

bool find_window::WindowSettings::isCaseSensitiveSearch() const {
	return (this->caseSensitiveBox->checkState() == Qt::Checked);
}

bool find_window::WindowSettings::isMatchFullWordSearch() const {
	return (this->matchFullWordOnlyBox->checkState() == Qt::Checked);
}

global_enums::offset_type_e find_window::WindowSettings::getSearchDirection() const {
	const int index = this->findDirectionDropDown->currentIndex();
	EXCEPTION_ACTION_COND((index == -1), throw, "Current index " << index << " is invalid to get the direction of search");
	const QString text = this->findDirectionDropDown->itemText(index);
	const auto & itemIt = std::find_if(this->directionItems.cbegin(), this->directionItems.cend(), [&] (const find_window::ComboBoxFind & item) {
		return (item.getText().compare(text.toStdString()) == 0);
	});

	global_enums::offset_type_e direction = global_enums::offset_type_e::IDLE;
	if (itemIt != this->directionItems.cend()) {
		direction = itemIt->getDirection();
	}

	return direction;
}
