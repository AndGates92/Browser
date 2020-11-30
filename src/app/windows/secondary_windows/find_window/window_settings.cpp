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

#include "app/utility/logger/macros.h"
#include "app/shared/exception.h"
#include "app/windows/secondary_windows/shared/utility.h"
#include "app/windows/secondary_windows/find_window/window_settings.h"

// Categories
LOGGING_CONTEXT(findButtonWindowSettingsOverall, findButtonWindowSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace find_window {

		namespace settings {

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

	}

}

app::find_window::Settings::Settings(QWidget * parent) : QGroupBox("Settings", parent) {

	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Creating find button window settings");

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

app::find_window::Settings::~Settings() {
	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Destructor of Settings class");
}

void app::find_window::Settings::widgetLayout() {

	// Layout
	// -------------------------------------------------
	// |         <settings group box title>            |
	// |    <direction drop down>    |     <case>      |
	// |    <direction drop down>    |   <full word>   |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(app::find_window::settings::widgetVSpacing);
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
		firstRowSettings->addWidget(this->caseSensitiveBox.get(), app::find_window::settings::defaultStretch, Qt::AlignLeft);
		firstRowSettings->addSpacing(app::find_window::settings::widgetHSpacing);
		// direction dropdown
		firstRowSettings->addWidget(this->findDirectionDropDown.get(), app::find_window::settings::defaultStretch, Qt::AlignRight);

		layout->addLayout(firstRowSettings);
		layout->addSpacing(app::find_window::settings::widgetHSpacing);
		layout->addWidget(this->matchFullWordOnlyBox.get(), app::find_window::settings::defaultStretch, Qt::AlignLeft);

	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void app::find_window::Settings::createActions() {

	this->directionItems.emplace_back(QIcon(), QVariant(), app::shared::offset_type_e::UP, std::move(app::secondary_window::createAction(this, "Up", "Search item towards the top of the page", app::key_sequence::KeySequence(Qt::Key_K))));
	this->directionItems.emplace_back(QIcon(), QVariant(), app::shared::offset_type_e::DOWN, std::move(app::secondary_window::createAction(this, "Down", "Search item towards the bottom of the page", app::key_sequence::KeySequence(Qt::Key_J))));

	this->caseSensitiveAction = std::move(app::secondary_window::createAction(this, "Case sensitive search", "Enable/Disable case sensitive search", app::key_sequence::KeySequence(Qt::Key_C)));
	this->matchFullWordOnlyAction = std::move(app::secondary_window::createAction(this, "Match full word only", "Enable/Disbale search of full words only", app::key_sequence::KeySequence(Qt::Key_M)));
}

void app::find_window::Settings::fillWidget() {

	this->findDirectionDropDown = app::secondary_window::createComboBox<app::find_window::ComboBoxFind>(this, this->directionItems);

	this->caseSensitiveBox = std::move(app::secondary_window::createCheckBox(this, this->caseSensitiveAction));
	this->matchFullWordOnlyBox = std::move(app::secondary_window::createCheckBox(this, this->matchFullWordOnlyAction));

}

void app::find_window::Settings::connectSignals() {
	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowSettingsOverall,  "Connect signals");

}

QSize app::find_window::Settings::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 3 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between 2 rows of widgets
	int height = this->matchFullWordOnlyBox->height() + std::max(this->caseSensitiveBox->height(), this->findDirectionDropDown->height()) + 3 * app::find_window::settings::widgetVSpacing;

	return QSize(width,height);
}

bool app::find_window::Settings::isCaseSensitiveSearch() const {
	return (this->caseSensitiveBox->checkState() == Qt::Checked);
}

bool app::find_window::Settings::isMatchFullWordSearch() const {
	return (this->matchFullWordOnlyBox->checkState() == Qt::Checked);
}

app::shared::offset_type_e app::find_window::Settings::getSearchDirection() const {
	const int index = this->findDirectionDropDown->currentIndex();
	EXCEPTION_ACTION_COND((index == -1), throw, "Current index " << index << " is invalid to get the direction of search");
	const QString text = this->findDirectionDropDown->itemText(index);
	const auto & itemIt = std::find_if(this->directionItems.cbegin(), this->directionItems.cend(), [&] (const app::find_window::ComboBoxFind & item) {
		return (item.getText().compare(text.toStdString()) == 0);
	});

	app::shared::offset_type_e direction = app::shared::offset_type_e::IDLE;
	if (itemIt != this->directionItems.cend()) {
		direction = itemIt->getDirection();
	}

	return direction;
}
