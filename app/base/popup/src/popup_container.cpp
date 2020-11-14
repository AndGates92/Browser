/**
 * @copyright
 * @file popup_container.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Popup container menu functions
 */

#include "base/popup/include/popup_container.h"
#include "base/popup/include/popup_container_layout.h"
#include "common/include/exception_macros.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"

// Categories
LOGGING_CONTEXT(popupContainerOverall, popupContainer.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace base {

		namespace popup {

			namespace popup_container {

				namespace {

					/**
					 * @brief horizontal spacing between widgets
					 *
					 */
					constexpr int horizontalWidgetSpacing = 0;

					/**
					 * @brief left margin between widget and window
					 *
					 */
					constexpr int leftMargin = 0;

					/**
					 * @brief right margin between widget and window
					 *
					 */
					constexpr int rightMargin = 0;

					/**
					 * @brief top margin between widget and window
					 *
					 */
					constexpr int topMargin = 0;

					/**
					 * @brief bottom margin between widget and window
					 *
					 */
					constexpr int bottomMargin = 0;

					/**
					 * @brief undefined index
					 *
					 */
					static constexpr int undefinedIndex = -1;

				}

			}

		}

	}

}

app::base::popup::PopupContainer::PopupContainer(QWidget * parent, Qt::WindowFlags flags) : app::base::overlayed_widget::OverlayedWidget(parent, flags), popupWidgets(std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>()) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupContainerOverall,  "Popup container constructor");

	this->popupLayout();

}

app::base::popup::PopupContainer::~PopupContainer() {
	LOG_INFO(app::logger::info_level_e::ZERO, popupContainerOverall,  "Popup container destructor");
}

void app::base::popup::PopupContainer::popupLayout() {

	// Create layout if not already defined
	if (this->layout() == Q_NULLPTR) {
		app::base::popup::PopupContainerLayout * containerLayout = new app::base::popup::PopupContainerLayout(this);
		containerLayout->setSizeConstraint(QLayout::SetFixedSize);
		containerLayout->setStackingMode(QStackedLayout::StackOne);
		containerLayout->setSpacing(app::base::popup::popup_container::horizontalWidgetSpacing);
		containerLayout->setContentsMargins(app::base::popup::popup_container::leftMargin, app::base::popup::popup_container::topMargin, app::base::popup::popup_container::rightMargin, app::base::popup::popup_container::bottomMargin);
		this->setLayout(containerLayout);
	}

	try {
		app::base::popup::PopupContainerLayout * containerLayout = dynamic_cast<app::base::popup::PopupContainerLayout *>(this->layout());
		const int layoutSize = containerLayout->count();
		for (int idx = 0; idx < layoutSize; idx++) {
			QWidget * w(containerLayout->widget(idx));
			containerLayout->removeWidget(w);
		}
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	for (std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::const_iterator it = this->popupWidgets.cbegin(); it != this->popupWidgets.cend(); it++) {
		this->addWidgetToLayout(it->first, it->second);
	}

}

bool app::base::popup::PopupContainer::addWidget(const unsigned int & index, const std::shared_ptr<app::base::popup::PopupBase> & widget) {

	// Pair to detect whether an element is succesfully added to the map
	// The first argument is the returned iterator if an element already exists at the requested index or the newly created element
	// The second argument states wheter the addition was succesfull or not
	std::pair<std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::const_iterator, bool> insertReturn;

	// Pair to be added to the map
	// Remove constness of method arguments
	std::pair<unsigned int, std::shared_ptr<app::base::popup::PopupBase>> keyElPair(const_cast<unsigned int&>(index), widget);

	insertReturn = this->popupWidgets.insert(keyElPair);

	std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::const_iterator el(insertReturn.first);
	bool  success(insertReturn.second);
	if (success == true) {
		LOG_INFO(app::logger::info_level_e::ZERO, popupContainerOverall,  "Widget " << widget.get() << " has been successfully added to the widget map at index " << index);
		this->addWidgetToLayout(index, widget);

		// Connect close popup to close container on order to move the main window to IDLE state and re-enabke shortcuts
		connect(widget.get(), &app::base::popup::PopupBase::closePopup, [this] () {
			emit this->closeContainer();
		});

	} else {
		LOG_INFO(app::logger::info_level_e::ZERO, popupContainerOverall,  "Widget " << widget.get() << " has not been successfully added to the widget map at index " << index << " as it was already filled with widget " << el->second.get());
	}

	return success;
}

void app::base::popup::PopupContainer::addWidgetToLayout(const unsigned int & index, const std::shared_ptr<app::base::popup::PopupBase> & widget) {
	try {
		app::base::popup::PopupContainerLayout * containerLayout = dynamic_cast<app::base::popup::PopupContainerLayout *>(this->layout());
		containerLayout->insertWidget(index, widget.get());
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

int app::base::popup::PopupContainer::searchFreeIndex(const unsigned int & startIdx, const unsigned int & range) {
	// Start idx at 1 because widget with key startIdx exists
	for (unsigned int idx = 1; idx < range; idx++) {
		const unsigned int probableIndex = (startIdx + idx);
		std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::iterator it = this->popupWidgets.find(probableIndex);
		// If element at key probableIndex is not found, use this free location for the element to append
		if (it == this->popupWidgets.end()) {
			return static_cast<int>(probableIndex);
		}
	}

	return app::base::popup::popup_container::undefinedIndex;
}

unsigned int app::base::popup::PopupContainer::appendWidget(const std::shared_ptr<app::base::popup::PopupBase> & widget) {
	// TODO: find lowest available key instead of using size
	int index = app::base::popup::popup_container::undefinedIndex;
	unsigned int uIndex = 0;
	long int prevKey = app::base::popup::popup_container::undefinedIndex;
	unsigned int maxKey = 0;

	// Search gaps between indexes
	for (std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::iterator it = this->popupWidgets.begin(); it != this->popupWidgets.end(); it++) {

		maxKey = std::max(static_cast<unsigned int>(it->first), maxKey);
		if (it == this->popupWidgets.begin()) {
			// First iteration
			prevKey = static_cast<long int>(it->first);
			index = app::base::popup::popup_container::undefinedIndex;
		} else {
			// It should handle the case where the value is in the range of values not representable by a single int (i.e. 32768 to 65535)
			const long int currKey = static_cast<long int>(it->first);
			const unsigned int range = static_cast<unsigned int>(std::abs(currKey - prevKey));
			EXCEPTION_ACTION_COND((currKey < 0), throw, "value of key after conversion is negative. Converted key: " << currKey << " Expected key value: " << it->first);
			// Search free index if range is larger than 0
			index = this->searchFreeIndex(static_cast<unsigned int>(prevKey), range);
			// Keep record of previous key
			prevKey = static_cast<long int>(it->first);
		}

		EXCEPTION_ACTION_COND((prevKey < 0), throw, "value of key after conversion is negative. Converted key: " << prevKey << " Expected key value: " << it->first);

		// If an index has been found (searchFreeIndex doesn't return app::base::popup::popup_container::undefinedIndex)
		if (index != app::base::popup::popup_container::undefinedIndex) {
			uIndex = static_cast<unsigned int>(index);
			EXCEPTION_ACTION_COND((index < 0), throw, "value of key after conversion is negative. Converted key: " << index);
			break;
		}

	}
	if (index == app::base::popup::popup_container::undefinedIndex) {
		// If no available index has been found, then index is the max key + 1
		uIndex = maxKey + 1;
	}
	bool success = this->addWidget(uIndex, widget);
	EXCEPTION_ACTION_COND((success == false), throw, "Unable to add widget " << widget.get() << " at index " << uIndex);

	return uIndex;
}

bool app::base::popup::PopupContainer::replaceWidget(const unsigned int & index, const std::shared_ptr<app::base::popup::PopupBase> & widget) {

	this->removeWidget(index);

	bool success = this->addWidget(index, widget);
	EXCEPTION_ACTION_COND((success == false), throw, "Unable to replace widget at index " << index << " with " << widget.get());
	return success;

}

bool app::base::popup::PopupContainer::removeWidget(const unsigned int & index) {

	std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::iterator it = this->popupWidgets.find(index);
	bool found = (it != this->popupWidgets.end());
	if (it != this->popupWidgets.end()) {
		this->popupWidgets.erase(it);
		this->deleteWidgetFromLayout(it->second);
	}

	return found;

}

bool app::base::popup::PopupContainer::removeWidget(const std::shared_ptr<app::base::popup::PopupBase> & widget) {

	for (std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::iterator it = this->popupWidgets.begin(); it != this->popupWidgets.end(); it++) {
		if (it->second == widget) {
			bool found = this->removeWidget(it->first);
			return found;
		}
	}

	return false;
}

bool app::base::popup::PopupContainer::chooseWidgetToShow(const unsigned int & index) {

	std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::iterator it = this->popupWidgets.find(index);
	bool found = (it != this->popupWidgets.end());

	if (found == true) {
		// Forward size policy of widget to container
		this->setSizePolicy(it->second->sizePolicy());

		// Change visible attribute only if widget is found
		this->setVisible(true);

		try {
			app::base::popup::PopupContainerLayout * containerLayout = dynamic_cast<app::base::popup::PopupContainerLayout *>(this->layout());
			containerLayout->setCurrentIndex(index);
			emit this->updateGeometryRequest(this->shared_from_this());
		} catch (const std::bad_cast & badCastE) {
			EXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return found;

}

bool app::base::popup::PopupContainer::chooseWidgetToShow(const std::shared_ptr<app::base::popup::PopupBase> & widget) {

	for (std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::const_iterator it = this->popupWidgets.cbegin(); it != this->popupWidgets.cend(); it++) {
		if (it->second == widget) {
			bool found = this->chooseWidgetToShow(it->first);
			return found;
		}
	}

	return false;
}

std::shared_ptr<app::base::popup::PopupBase> app::base::popup::PopupContainer::getWidget(const unsigned int & index) const {

	std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::const_iterator it = this->popupWidgets.find(index);
	bool found = (it != this->popupWidgets.end());
	std::shared_ptr<app::base::popup::PopupBase> widget = nullptr;
	if (found == false) {
		// Print a warning if widget is not found
		LOG_WARNING(popupContainerOverall, "Unable to find widget at index " << index);
		widget = nullptr;
	} else {
		widget = it->second;
	}

	return widget;

}

void app::base::popup::PopupContainer::deleteWidgetFromLayout(const std::shared_ptr<app::base::popup::PopupBase> & widget) {
	try {
		app::base::popup::PopupContainerLayout * containerLayout = dynamic_cast<app::base::popup::PopupContainerLayout *>(this->layout());
		containerLayout->removeWidget(widget.get());
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void app::base::popup::PopupContainer::updateLayout() {
	this->popupLayout();
}

std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>>::size_type app::base::popup::PopupContainer::getWidgetCount() const {
	return this->popupWidgets.size();
}

bool app::base::popup::PopupContainer::isCentered() const {
	const std::shared_ptr<app::base::popup::PopupBase> widget = this->getCurrentWidget();

	bool centered = false;
	if (widget != Q_NULLPTR) {
		centered = widget->isCentered();
	}

	return centered;
}

int app::base::popup::PopupContainer::getPadding() const {
	const std::shared_ptr<app::base::popup::PopupBase> widget = this->getCurrentWidget();

	int padding = 0;
	if (widget != Q_NULLPTR) {
		padding = widget->getPadding();
	}

	return padding;
}

std::shared_ptr<app::base::popup::PopupBase> app::base::popup::PopupContainer::getCurrentWidget() const {
	try {
		app::base::popup::PopupContainerLayout * containerLayout = dynamic_cast<app::base::popup::PopupContainerLayout *>(this->layout());
		const int idx = containerLayout->currentIndex();
		const std::shared_ptr<app::base::popup::PopupBase> widget = this->getWidget(idx);
		return widget;
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

}

const std::map<unsigned int, std::shared_ptr<app::base::popup::PopupBase>> & app::base::popup::PopupContainer::getWidgetMap() const {
	return this->popupWidgets;
}

QSize app::base::popup::PopupContainer::sizeHint() const {

	const std::shared_ptr<app::base::popup::PopupBase> widget = this->getCurrentWidget();

	QSize hint(0,0);
	if (widget != Q_NULLPTR) {
		hint = widget->sizeHint();
	}

	return hint;
}
