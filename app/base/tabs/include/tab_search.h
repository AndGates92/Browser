#ifndef WEB_ENGINE_SEARCH_H
#define WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file tab_search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab Search header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtCore/QString>
#include <QtWebEngineWidgets/QWebEnginePage>

#include "global_enums.h"
#include "tab_component_widget.h"
#include "constructor_macros.h"
#include "find_settings.h"

/** @defgroup TabSearchGroup Tab Search Doxygen Group
 *  Tab Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabSearchOverall)
Q_DECLARE_LOGGING_CATEGORY(tabSearchFind)

namespace tab {
	class Tab;
}

namespace tab_search {

	/**
	 * @brief TabSearch class
	 *
	 */
	class TabSearch : public tab_component_widget::TabComponentWidget<find_settings::FindSettings> {
		friend class tab::Tab;

		public:
			/**
			 * @brief Function: explicit TabSearch(QObject * parent, std::weak_ptr<tab::Tab> attachedTab)
			 *
			 * \param attachedTab: tab attached to the search instance
			 * \param parent: parent object
			 *
			 * Tab search constructor
			 */
			explicit TabSearch(QWidget * parent, std::weak_ptr<tab::Tab> attachedTab);

			/**
			 * @brief Function: virtual ~TabSearch()
			 *
			 * Tab search destructor
			 */
			virtual ~TabSearch();

		protected:
			/**
			 * @brief find settings
			 *
			 */
			find_settings::FindSettings settings;

			/**
			 * @brief callback
			 *
			 */
			std::function<void(bool)> callback;

			/**
			 * @brief Function: virtual void execute(const find_settings::FindSettings & newSettings) override final
			 *
			 * \param newSettings: new settings of search.
			 *
			 * This function searches text in a webpage
			 */
			virtual void execute(const find_settings::FindSettings & newSettings) override final;

			/**
			 * @brief Function: virtual void setCallback()
			 *
			 * This function sets the callback to be run after the search
			 */
			virtual void setCallback();

		private:
			/**
			 * @brief Function: virtual void search() final
			 *
			 * This function searches text in a webpage
			 */
			virtual void search() final;

			/**
			 * @brief Function: virtual void canProcessRequests() const override
			 *
			 * \return whether scroll requests can be processed
			 *
			 * This function check if scroll requests can be processed
			 */
			virtual bool canProcessRequests() const override;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabSearch
			 *
			 */
			DISABLE_COPY_MOVE(TabSearch)

	};
}
/** @} */ // End of TabSearchGroup group

#endif // WEB_ENGINE_SEARCH_H
