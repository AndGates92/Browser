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

namespace popup_container {
	namespace {
		/**
		 * @brief undefined index
		 *
		 */
		static constexpr int undefinedIndex = -1;
	}
}

popup_container::PopupContainer::PopupContainer(QWidget * parent, Qt::WindowFlags flags) : overlayed_widget::OverlayedWidget(parent, flags), popupWidgets(std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>()) {

	LOG_INFO(logger::info_level_e::ZERO, popupContainerOverall,  "Popup container constructor");

	this->popupLayout();

}

popup_container::PopupContainer::~PopupContainer() {
	LOG_INFO(logger::info_level_e::ZERO, popupContainerOverall,  "Popup container destructor");
}

void popup_container::PopupContainer::popupLayout() {

	// Create layout if not already defined
	if (this->layout() == Q_NULLPTR) {
		popup_container_layout::PopupContainerLayout * containerLayout = new popup_container_layout::PopupContainerLayout(this);
		containerLayout->setSizeConstraint(QLayout::SetFixedSize);
		containerLayout->setStackingMode(QStackedLayout::StackOne);
		containerLayout->setSpacing(popup_container::horizontalWidgetSpacing);
		containerLayout->setContentsMargins(popup_container::leftMargin, popup_container::topMargin, popup_container::rightMargin, popup_container::bottomMargin);
		this->setLayout(containerLayout);
	}

	try {
		popup_container_layout::PopupContainerLayout * containerLayout = dynamic_cast<popup_container_layout::PopupContainerLayout *>(this->layout());
		const int layoutSize = containerLayout->count();
		for (int idx = 0; idx < layoutSize; idx++) {
			QWidget * w(containerLayout->widget(idx));
			containerLayout->removeWidget(w);
		}
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	for (std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::const_iterator it = this->popupWidgets.cbegin(); it != this->popupWidgets.cend(); it++) {
		this->addWidgetToLayout(it->first, it->second);
	}

}

bool popup_container::PopupContainer::addWidget(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget) {

	// Pair to detect whether an element is succesfully added to the map
	// The first argument is the returned iterator if an element already exists at the requested index or the newly created element
	// The second argument states wheter the addition was succesfull or not
	std::pair<std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::const_iterator, bool> insertReturn;

	// Pair to be added to the map
	// Remove constness of method arguments
	std::pair<unsigned int, std::shared_ptr<popup_base::PopupBase>> keyElPair(const_cast<unsigned int&>(index), widget);

	insertReturn = this->popupWidgets.insert(keyElPair);

	std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::const_iterator el(insertReturn.first);
	bool  success(insertReturn.second);
	if (success == true) {
		LOG_INFO(logger::info_level_e::ZERO, popupContainerOverall,  "Widget " << widget.get() << " has been successfully added to the widget map at index " << index);
		this->addWidgetToLayout(index, widget);

		// Connect close popup to close container on order to move the main window to IDLE state and re-enabke shortcuts
		connect(widget.get(), &popup_base::PopupBase::closePopup, [this] () {
			emit this->closeContainer();
		});

	} else {
		LOG_INFO(logger::info_level_e::ZERO, popupContainerOverall,  "Widget " << widget.get() << " has not been successfully added to the widget map at index " << index << " as it was already filled with widget " << el->second.get());
	}

	return success;
}

void popup_container::PopupContainer::addWidgetToLayout(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget) {
	try {
		popup_container_layout::PopupContainerLayout * containerLayout = dynamic_cast<popup_container_layout::PopupContainerLayout *>(this->layout());
		containerLayout->insertWidget(index, widget.get());
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

int popup_container::PopupContainer::searchFreeIndex(const unsigned int & startIdx, const unsigned int & range) {
	// Start idx at 1 because widget with key startIdx exists
	for (unsigned int idx = 1; idx < range; idx++) {
		const unsigned int probableIndex = (startIdx + idx);
		std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::iterator it = this->popupWidgets.find(probableIndex);
		// If element at key probableIndex is not found, use this free location for the element to append
		if (it == this->popupWidgets.end()) {
			return static_cast<int>(probableIndex);
		}
	}

	return popup_container::undefinedIndex;
}

unsigned int popup_container::PopupContainer::appendWidget(const std::shared_ptr<popup_base::PopupBase> & widget) {
	// TODO: find lowest available key instead of using size
	int index = popup_container::undefinedIndex;
	unsigned int uIndex = 0;
	long int prevKey = popup_container::undefinedIndex;
	unsigned int maxKey = 0;

	// Search gaps between indexes
	for (std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::iterator it = this->popupWidgets.begin(); it != this->popupWidgets.end(); it++) {

		maxKey = std::max(static_cast<unsigned int>(it->first), maxKey);
		if (it == this->popupWidgets.begin()) {
			// First iteration
			prevKey = static_cast<long int>(it->first);
			index = popup_container::undefinedIndex;
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

		// If an index has been found (searchFreeIndex doesn't return popup_container::undefinedIndex)
		if (index != popup_container::undefinedIndex) {
			uIndex = static_cast<unsigned int>(index);
			EXCEPTION_ACTION_COND((index < 0), throw, "value of key after conversion is negative. Converted key: " << index);
			break;
		}

	}
	if (index == popup_container::undefinedIndex) {
		// If no available index has been found, then index is the max key + 1
		uIndex = maxKey + 1;
	}
	bool success = this->addWidget(uIndex, widget);
	EXCEPTION_ACTION_COND((success == false), throw, "Unable to add widget " << widget.get() << " at index " << uIndex);

	return uIndex;
}

bool popup_container::PopupContainer::replaceWidget(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget) {

	this->removeWidget(index);

	bool success = this->addWidget(index, widget);
	EXCEPTION_ACTION_COND((success == false), throw, "Unable to replace widget at index " << index << " with " << widget.get());
	return success;

}

bool popup_container::PopupContainer::removeWidget(const unsigned int & index) {

	std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::iterator it = this->popupWidgets.find(index);
	bool found = (it != this->popupWidgets.end());
	if (it != this->popupWidgets.end()) {
		this->popupWidgets.erase(it);
		this->deleteWidgetFromLayout(it->second);
	}

	return found;

}

bool popup_container::PopupContainer::removeWidget(const std::shared_ptr<popup_base::PopupBase> & widget) {

	for (std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::iterator it = this->popupWidgets.begin(); it != this->popupWidgets.end(); it++) {
		if (it->second == widget) {
			bool found = this->removeWidget(it->first);
			return found;
		}
	}

	return false;
}

bool popup_container::PopupContainer::chooseWidgetToShow(const unsigned int & index) {

	std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::iterator it = this->popupWidgets.find(index);
	bool found = (it != this->popupWidgets.end());

	if (found == true) {
		// Forward size policy of widget to container
		this->setSizePolicy(it->second->sizePolicy());

		// Change visible attribute only if widget is found
		this->setVisible(true);

		try {
			popup_container_layout::PopupContainerLayout * containerLayout = dynamic_cast<popup_container_layout::PopupContainerLayout *>(this->layout());
			containerLayout->setCurrentIndex(index);
			emit this->updateGeometryRequest(this->shared_from_this());
		} catch (const std::bad_cast & badCastE) {
			EXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return found;

}

bool popup_container::PopupContainer::chooseWidgetToShow(const std::shared_ptr<popup_base::PopupBase> & widget) {

	for (std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::const_iterator it = this->popupWidgets.cbegin(); it != this->popupWidgets.cend(); it++) {
		if (it->second == widget) {
			bool found = this->chooseWidgetToShow(it->first);
			return found;
		}
	}

	return false;
}

std::shared_ptr<popup_base::PopupBase> popup_container::PopupContainer::getWidget(const unsigned int & index) const {

	std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::const_iterator it = this->popupWidgets.find(index);
	bool found = (it != this->popupWidgets.end());
	std::shared_ptr<popup_base::PopupBase> widget = nullptr;
	if (found == false) {
		// Print a warning if widget is not found
		LOG_WARNING(popupContainerOverall, "Unable to find widget at index " << index);
		widget = nullptr;
	} else {
		widget = it->second;
	}

	return widget;

}

void popup_container::PopupContainer::deleteWidgetFromLayout(const std::shared_ptr<popup_base::PopupBase> & widget) {
	try {
		popup_container_layout::PopupContainerLayout * containerLayout = dynamic_cast<popup_container_layout::PopupContainerLayout *>(this->layout());
		containerLayout->removeWidget(widget.get());
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void popup_container::PopupContainer::updateLayout() {
	this->popupLayout();
}

std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::size_type popup_container::PopupContainer::getWidgetCount() const {
	return this->popupWidgets.size();
}

bool popup_container::PopupContainer::isCentered() const {
	const std::shared_ptr<popup_base::PopupBase> widget = this->getCurrentWidget();

	bool centered = false;
	if (widget != Q_NULLPTR) {
		centered = widget->isCentered();
	}

	return centered;
}

int popup_container::PopupContainer::getPadding() const {
	const std::shared_ptr<popup_base::PopupBase> widget = this->getCurrentWidget();

	int padding = 0;
	if (widget != Q_NULLPTR) {
		padding = widget->getPadding();
	}

	return padding;
}

std::shared_ptr<popup_base::PopupBase> popup_container::PopupContainer::getCurrentWidget() const {
	try {
		popup_container_layout::PopupContainerLayout * containerLayout = dynamic_cast<popup_container_layout::PopupContainerLayout *>(this->layout());
		const int idx = containerLayout->currentIndex();
		const std::shared_ptr<popup_base::PopupBase> widget = this->getWidget(idx);
		return widget;
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

}

const std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>> & popup_container::PopupContainer::getWidgetMap() const {
	return this->popupWidgets;
}

QSize popup_container::PopupContainer::sizeHint() const {

	const std::shared_ptr<popup_base::PopupBase> widget = this->getCurrentWidget();

	QSize hint(0,0);
	if (widget != Q_NULLPTR) {
		hint = widget->sizeHint();
	}

	return hint;
}
