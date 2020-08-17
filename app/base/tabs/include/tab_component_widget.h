#ifndef TAB_COMPONENT_WIDGET_H
#define TAB_COMPONENT_WIDGET_H
/**
 * @copyright
 * @file tab_component_widget.h
 * @author Andrea Gianarda
 * @date 13th of May 2020
 * @brief Tab Component Widget header file
*/

#include <memory>
#include <list>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWidgets/QWidget>

#include "global_enums.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "tab_shared_types.h"
#include "constructor_macros.h"
#include "tab.h"

/** @defgroup TabComponentWidgetGroup Tab Component Widget Doxygen Group
 *  Tab Component Widget functions and classes
 *  @{
 */

namespace tab {
	class Tab;
}


Q_DECLARE_LOGGING_CATEGORY(tabComponentWidgetOverall)

namespace tab_component_widget {

	/**
	 * @brief TabComponentWidget class
	 *
	 */
	template<typename type>
	class TabComponentWidget : public QWidget {
		public:
			/**
			 * @brief Function: explicit TabComponentWidget(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab)
			 *
			 * \param parent: parent widget
			 *
			 * Tab Component Widget constructor
			 */
			explicit TabComponentWidget(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab);

			/**
			 * @brief Function: virtual ~TabComponentWidget()
			 *
			 * Tab Component Widget destructor
			 */
			virtual ~TabComponentWidget();

		protected:

			/**
			 * @brief Function: virtual void pushRequestQueue(const type & entry) final
			 *
			 * \param entry: direction of scrolling
			 *
			 * This function pushes a new entry to the queue
			 */
			virtual void pushRequestQueue(const type & entry) final;

			/**
			 * @brief Function: virtual bool canProcessRequests() const
			 *
			 * \return whether requests can be processed
			 *
			 * This function check if requests can be processed
			 */
			virtual bool canProcessRequests() const = 0;

			/**
			 * @brief Function: virtual void execute(const type & element)
			 *
			 * \param element: element ot execute action on.
			 *
			 * This function execute the action of the component
			 */
			virtual void execute(const type & newSettings) = 0;

			/**
			 * @brief Function: virtual void emptyRequestQueue() final
			 *
			 * This function empties the queue of scroll requests
			 */
			virtual void emptyRequestQueue() final;

			/**
			 * @brief Function: void setTab(std::weak_ptr<QWidget> newTab)
			 *
			 * \param tab: tab the component belongs to
			 *
			 * This function sets the tab the component belongs to
			 * This is a convenience function. The argument must be able to be casted as tab::Tab
			 */
			void setTab(std::weak_ptr<QWidget> newTab);

			/**
			 * @brief Function: void setTab(std::weak_ptr<tab::Tab> value)
			 *
			 * \param tab: tab the component belongs to
			 *
			 * This function sets the tab the component belongs to
			 */
			void setTab(std::weak_ptr<tab::Tab> value);

			/**
			 * @brief Function: std::shared_ptr<tab::Tab> getTab() const
			 *
			 * \return tab the component belongs to
			 *
			 * This function returns the tab the component belongs to
			 */
			std::shared_ptr<tab::Tab> getTab() const;

			/**
			 * @brief queue of outstanding scroll requests
			 *
			 */
			std::list<type> requestQueue;

		private:
			/**
			 * @brief tab the scroll manager belongs to
			 *
			 */
			std::weak_ptr<tab::Tab> browserTab;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overscrolling for class TabComponentWidget
			 *
			 */
			DISABLE_COPY_MOVE(TabComponentWidget)

	};
}
/** @} */ // End of TabComponentWidgetGroup group

template<typename type>
tab_component_widget::TabComponentWidget<type>::TabComponentWidget(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab): QWidget(parent) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabComponentWidgetOverall,  "TabComponentWidget constructor");

	this->browserTab.reset();

	// Make widget invisible
	this->setVisible(false);

	this->setTab(attachedTab);
}

template<typename type>
tab_component_widget::TabComponentWidget<type>::~TabComponentWidget() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, tabComponentWidgetOverall,  "TabComponentWidget destructor");
}

template<typename type>
void tab_component_widget::TabComponentWidget<type>::setTab(std::weak_ptr<QWidget> newTab) {
	try {
		std::weak_ptr<tab::Tab> thisTab = std::static_pointer_cast<tab::Tab>(newTab.lock());
		this->setTab(thisTab);
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

template<typename type>
void tab_component_widget::TabComponentWidget<type>::setTab(std::weak_ptr<tab::Tab> value) {
	this->browserTab = value;
}

template<typename type>
void tab_component_widget::TabComponentWidget<type>::pushRequestQueue(const type & entry) {
	this->requestQueue.push_back(entry);
}

template<typename type>
void tab_component_widget::TabComponentWidget<type>::emptyRequestQueue() {
	for (auto & element : this->requestQueue) {
		if ((this->requestQueue.empty() == false) && (this->canProcessRequests() == true)) {
			this->execute(element);
		}
	}

	this->requestQueue.clear();
}

template<typename type>
BASE_GETTER(tab_component_widget::TabComponentWidget<type>::getTab, std::shared_ptr<tab::Tab>, this->browserTab.lock())

#endif // TAB_COMPONENT_WIDGET_H
