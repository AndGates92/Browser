#ifndef MAIN_WINDOW_POPUP_CONTAINER_H
#define MAIN_WINDOW_POPUP_CONTAINER_H
/**
 * @copyright
 * @file popup_container.h
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Main Window popup container class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "windows/main_window/popup/include/open_popup.h"
#include "windows/main_window/popup/include/label_popup.h"

#include "common/include/type_print_macros.h"
#include "common/include/smart_ptr_macros.h"
#include "base/popup/include/popup_container.h"
#include "common/include/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	/**
	 * @brief PopupContainer class
	 *
	 */
	class PopupContainer : public popup_container::PopupContainer {

		public:
			// This class cannot be instantiated directly but it needs to be derived
			/**
			 * @brief Function: explicit PopupContainer(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window prompt constructor
			 */
			explicit PopupContainer(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~PopupContainer()
			 *
			 * Main window prompt destructor
			 */
			virtual ~PopupContainer();

			/**
			 * @brief Function: bool showOpenFilePopup()
			 *
			 * \return a boolean value indicating whether the shown widget was successfully changed
			 *
			 * This function shows the widget having the open file popup
			 */
			bool showOpenFilePopup();

			/**
			 * @brief Function: std::shared_ptr<open_popup::OpenPopup> getOpenFilePopup() const
			 *
			 * \return a pointer to the open file popup
			 *
			 * This function returns a pointer to the open file popup
			 */
			std::shared_ptr<open_popup::OpenPopup> getOpenFilePopup() const;

			/**
			 * @brief Function: bool showWarningPopup()
			 *
			 * \return a boolean value indicating whether the shown widget was successfully changed
			 *
			 * This function shows the widget having the warning popup
			 */
			bool showWarningPopup();

			/**
			 * @brief Function: std::shared_ptr<label_popup::LabelPopup> getWarningPopup() const
			 *
			 * \return a pointer to the warning popup
			 *
			 * This function returns a pointer to the warning popup
			 */
			std::shared_ptr<label_popup::LabelPopup> getWarningPopup() const;

			/**
			 * @brief Define methods to get smart pointer from this
			 *
			 */
			SMART_PTR_FROM_THIS_FUNCTIONS(main_window::PopupContainer, popup_container::PopupContainer)

		protected:

		private:

			/**
			 * @brief Function: virtual void connectSignals() override
			 *
			 * This function connects signals and slots between main popup menu elements
			 */
			virtual void connectSignals() override;

			/**
			 * @brief Function: void addOpenPopup()
			 *
			 * This function adds an instance of the open popup widget to the widgets map
			 */
			void addOpenPopup();

			/**
			 * @brief Function: void addWarningPopup()
			 *
			 * This function adds an instance of the warning popup widget to the widgets map
			 */
			void addWarningPopup();

			/**
			 * @brief Function: std::shared_ptr<PopupClass> getPopup(const unsigned int index) const
			 *
			 * \param index: index of the popup to search
			 *
			 * \return a pointer to the popup
			 *
			 * This function returns a pointer to the popup at index provided as argument
			 */
			template<class PopupClass>
			std::shared_ptr<PopupClass> getPopup(const unsigned int index) const;

			/**
			 * @brief Function: bool showPopup(const unsigned int index)
			 *
			 * \param index: index of the popup to search
			 *
			 * \return whether operation was successful or not
			 *
			 * This function try to show widget at index provided as argument
			 */
			template<class PopupClass>
			bool showPopup(const unsigned int index);

	};

}

template<class PopupClass>
std::shared_ptr<PopupClass> main_window::PopupContainer::getPopup(const unsigned int index) const {
	std::shared_ptr<popup_properties::PopupProperties> widget = std::dynamic_pointer_cast<popup_properties::PopupProperties>(this->getWidget(index));
	EXCEPTION_ACTION_COND((widget == nullptr), throw, "Unable to find widget " << index);
	std::shared_ptr<PopupClass> popup = nullptr;

	if (widget != Q_NULLPTR) {
		try {
			popup = std::dynamic_pointer_cast<PopupClass>(widget);
		} catch (const std::bad_cast & badCastE) {
			EXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return popup;
}

template<class PopupClass>
bool main_window::PopupContainer::showPopup(const unsigned int index) {
	bool success = this->chooseWidgetToShow(index);

	if (success == true) {
		this->getPopup<PopupClass>((unsigned int)index)->activatePopup();
	}

	return success;
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_POPUP_CONTAINER_H
