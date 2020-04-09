#ifndef WEB_ENGINE_VIEW_H
#define WEB_ENGINE_VIEW_H
/**
 * @copyright
 * @file web_engine_view.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine View header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWebEngineWidgets/QWebEngineView>

#include "global_types.h"
#include "constructor_macros.h"
#include "web_engine_page.h"

/** @defgroup WebEngineViewGroup Web Engine View Doxygen Group
 *  Web Engine View functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(webEngineViewOverall)

namespace web_engine_view {

	/**
	 * @brief WebEngineView class
	 *
	 */
	class WebEngineView : public QWebEngineView {

		public:
			/**
			 * @brief Function: explicit WebEngineView(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Web engine view constructor
			 */
			explicit WebEngineView(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~WebEngineView()
			 *
			 * Web engine view destructor
			 */
			virtual ~WebEngineView();

			/**
			 * @brief Function: web_engine_page::MainWindowWebEnginePage * page()
			 *
			 * \return page of the view
			 *
			 * This function returns the page of this web engine view
			 */
			web_engine_page::WebEnginePage * page();

		protected:

		private:
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
