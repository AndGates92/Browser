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
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#include <QtWebEngineCore/QWebEngineFindTextResult>
#endif

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

		Q_OBJECT

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
			 * @brief Function: virtual void find(const find_settings::FindSettings & newSettings, std::function<void(bool)> cb = std::function<void(bool)>()) final
			 *
			 * \param newSettings: new settings of search.
			 * \param cb: callback to call
			 *
			 * This function searches text in a webpage
			 */
			virtual void find(const find_settings::FindSettings & newSettings, std::function<void(bool)> cb = std::function<void(bool)>()) final;

			/**
			 * @brief Function: virtual void popRequestQueue() override
			 *
			 * This function empties the queue of scroll requests
			 */
			virtual void popRequestQueue() override;

		private:
			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots within the tab search
			 */
			void connectSignals();

			/**
			 * @brief Function: virtual void search() final
			 *
			 * This function searches text in a webpage
			 */
			virtual void search() final;

			/**
			 * @brief Function: virtual void pushRequestQueue(const find_settings::FindSettings & newSettings) override
			 *
			 * \param settings: settings of the search
			 *
			 * This function pushes a new entry to the queue
			 */
			virtual void pushRequestQueue(const find_settings::FindSettings & newSettings) override;

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

		private slots:
			//#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
			// Dirty workaround for bug QTBUG-57121
			#if QT_VERSION >= 0x050e00
			/**
			 * @brief Function: void postProcessSearch(const QWebEngineFindTextResult & result)
			 *
			 * \param result: result of search
			 *
			 * This function is the slot that receives the result of the text search
			 */
			void postProcessSearch(const QWebEngineFindTextResult & result);
			#endif
	};
}
/** @} */ // End of TabSearchGroup group

#endif // WEB_ENGINE_SEARCH_H
