#ifndef POPUP_CONTAINER_H
#define POPUP_CONTAINER_H
/**
 * @copyright
 * @file popup_container.h
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Popup container class header file
 */

#include <memory>

#include <QtCore/QLoggingCategory>

#include "constructor_macros.h"
#include "smart_ptr_macros.h"
#include "overlayed_widget.h"
#include "popup_base.h"


/** @defgroup PopupContainerGroup Popup Container Doxygen Group
 *  Pop up container functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(popupContainerOverall)

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

	}

	/**
	 * @brief PopupContainer class
	 *
	 */
	class PopupContainer : public overlayed_widget::OverlayedWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::size_type getWidgetCount() const
			 *
			 * This function returns the number of widgets in the container
			 */
			std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>>::size_type getWidgetCount() const;

			/**
			 * @brief Function: std::shared_ptr<popup_base::PopupBase> getWidget(const unsigned int & index) const
			 *
			 * \param index: index of the widget to return
			 *
			 * \return a pointer to the widget at index index or nullptr if it is not found
			 *
			 * This function returns a pointer to the widget at index index or nullptr if it is not found
			 */
			std::shared_ptr<popup_base::PopupBase> getWidget(const unsigned int & index) const;

			/**
			 * @brief Function: virtual bool isCentered() const override
			 *
			 * \return boolean whether the widget shown in the container has to be centered or not
			 *
			 * This function returns whether the widget shown in the container has to be centered or not
			 */
			virtual bool isCentered() const override;

			/**
			 * @brief Function: virtual int getPadding() const override
			 *
			 * \return padding of the widget shown in the container
			 *
			 * This function returns the padding of the widget shown in the container
			 */
			virtual int getPadding() const override;

			/**
			 * @brief Define methods to get smart pointer from this
			 *
			 */
			SMART_PTR_FROM_THIS_FUNCTIONS(popup_container::PopupContainer, overlayed_widget::OverlayedWidget)

		signals:
			/**
			 * @brief Function: void closeContainer()
			 *
			 * This function is a signal emitted when the popup is closed
			 */
			void closeContainer();

		protected:
			// This class cannot be instantiated directly but it needs to be derived
			/**
			 * @brief Function: explicit PopupContainer(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Pop up container constructor
			 */
			explicit PopupContainer(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~PopupContainer()
			 *
			 * Pop up container destructor
			 */
			virtual ~PopupContainer();

			/**
			 * @brief Function: bool addWidget(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param index: index the widget has to be added to
			 * \param widget: widget to add
			 *
			 * \return a boolean value indicating whether the widget was successfully added at the desired index
			 *
			 * This function adds a widget to the desired index to the stacked layout and widget map
			 */
			bool addWidget(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: unsigned int appendWidget(const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param widget: widget to add
			 *
			 * \returns the value of the index the widget was added to
			 *
			 * This function appends a widget to the stacked layout and widget map
			 * It searches the lowest possible index free to use as key for the widget
			 */
			unsigned int appendWidget(const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: bool replaceWidget(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param index: index of the widget to replace
			 * \param widget: replacement widget
			 *
			 * \return a boolean value indicating whether the widget was successfully put at the desired index
			 *
			 * This function replaces a widget to the desired index in the stacked layout and widget map
			 * If no widget is present at the requested index, it will be added
			 */
			bool replaceWidget(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: bool removeWidget(const unsigned int & index)
			 *
			 * \param index: index of the widget to remove
			 *
			 * \return a boolean value indicating whether the widget was successfully removed
			 *
			 * This function removes a widget at the desired index fromo the stacked layout and widget map
			 */
			bool removeWidget(const unsigned int & index);

			/**
			 * @brief Function: bool removeWidget(const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param widget: widget to remove
			 *
			 * \return a boolean value indicating whether the widget was successfully removed
			 *
			 * This function removes a widget from the stacked layout and widget map
			 */
			bool removeWidget(const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: bool chooseWidgetToShow(const unsigned int & index)
			 *
			 * \param index: index of the widget to choose
			 *
			 * \return a boolean value indicating whether the shown widget was successfully changed
			 *
			 * This function removes a widget at the desired index from the stacked layout and widget map
			 */
			bool chooseWidgetToShow(const unsigned int & index);

			/**
			 * @brief Function: bool chooseWidgetToShow(const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param widget: widget to remove
			 *
			 * \return a boolean value indicating whether the shown widget was successfully changed
			 *
			 * This function selects the widget from the stacked layout to show
			 */
			bool chooseWidgetToShow(const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: void updateLayout()
			 *
			 * This function updates the layout of the popup container
			 */
			void updateLayout();

			/**
			 * @brief Function: virtual std::shared_ptr<popup_base::PopupBase> getCurrentWidget() const final
			 *
			 * \return widget shown in the container
			 *
			 * This function returns the widget shown in the container
			 */
			virtual std::shared_ptr<popup_base::PopupBase> getCurrentWidget() const final;

			/**
			 * @brief Function: std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>> getWidgetMap() const
			 *
			 * This function returns the widget map in the container
			 */
			const std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>> getWidgetMap() const;

		private:

			/**
			 * @brief List of widgets in the popup container
			 * - the key of the map is the index the widget will be in the stacked layout
			 * - the element is the widget to be added to the list
			 *
			 */
			std::map<unsigned int, std::shared_ptr<popup_base::PopupBase>> popupWidgets;

			/**
			 * @brief Function: virtual void promptLayout()
			 *
			 * This function creates the layout of the popup container
			 * It will be a stacked layout where only one widget will be shown at any given time if the container is visible
			 */
			virtual void popupLayout() final;

			/**
			 * @brief Function: void addWidgetToLayout(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param index: index of the widget in the layout
			 * \param widget: widget to add to the layout
			 *
			 * This function adds a widget to the layout
			 */
			void addWidgetToLayout(const unsigned int & index, const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: bool removeWidget(const std::shared_ptr<popup_base::PopupBase> & widget)
			 *
			 * \param widget: widget to remove from layout
			 *
			 * This function removes a widget from the layout
			 */
			void deleteWidgetFromLayout(const std::shared_ptr<popup_base::PopupBase> & widget);

			/**
			 * @brief Function: int searchFreeIndex(const unsigned int & startIdx, const unsigned int & range)
			 *
			 * \param startIdx: index to start the search with
			 * \param range: range to search a free key in the map
			 *
			 * This function searches a free key in the widget map starting at key startIdx and lookign the following (range-1) values
			 */
			int searchFreeIndex(const unsigned int & startIdx, const unsigned int & range);

			/**
			 * @brief Function: virtual void connectSignals() = 0
			 *
			 * This function connects signals and slots between popup container elements
			 */
			virtual void connectSignals() = 0;

			/**
			 * @brief Function: virtual QSize sizeHint() const override
			 *
			 * \return return recommended size of the widget
			 *
			 * Compute recommendend size of the widget
			 */
			virtual QSize sizeHint() const override;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class PopupContainer
			 *
			 */
			DISABLE_COPY_MOVE(PopupContainer)

	};

}

/** @} */ // End of PopupContainerGroup group

#endif // POPUP_CONTAINER_H
