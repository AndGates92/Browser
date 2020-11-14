#ifndef WEB_ENGINE_VIEW_H
#define WEB_ENGINE_VIEW_H
/**
 * @copyright
 * @file web_engine_view.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine View header file
*/

#include <memory>

// Qt libraries
#include <QtWebEngineWidgets/QWebEngineView>

#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"
#include "base/tabs/include/web_engine_page.h"

/** @defgroup WebEngineViewGroup Web Engine View Doxygen Group
 *  Web Engine View functions and classes
 *  @{
 */

namespace tab {
	class Tab;
}

namespace web_engine_view {

	/**
	 * @brief WebEngineView class
	 *
	 */
	class WebEngineView : public QWebEngineView {
		friend class tab::Tab;

		public:
			/**
			 * @brief Function: explicit WebEngineView(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Web engine view constructor
			 */
			explicit WebEngineView(QWidget * parent);

			/**
			 * @brief Function: virtual ~WebEngineView()
			 *
			 * Web engine view destructor
			 */
			virtual ~WebEngineView();

			/**
			 * @brief Function: std::shared_ptr<web_engine_page::WebEnginePage> page() const
			 *
			 * \return page of the view
			 *
			 * This function returns the page of this web engine view
			 */
			std::shared_ptr<web_engine_page::WebEnginePage> page() const;

		protected:

			/**
			 * @brief Function: void updatePage(const std::shared_ptr<web_engine_page::WebEnginePage> & newPage)
			 *
			 * \param: new page to be used for this view
			 *
			 * This function changes the page of this web engine view
			 */
			void updatePage(const std::shared_ptr<web_engine_page::WebEnginePage> & newPage);

		private:
			/**
			 * @brief current page linked to the web view
			 *
			 */
			std::shared_ptr<web_engine_page::WebEnginePage> currentPage;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class WebEngineView
			 *
			 */
			DISABLE_COPY_MOVE(WebEngineView)

	};
}
/** @} */ // End of WebEngineViewGroup group

#endif // WEB_ENGINE_VIEW_H
