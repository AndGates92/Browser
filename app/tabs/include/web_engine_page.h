#ifndef WEB_ENGINE_PAGE_H
#define WEB_ENGINE_PAGE_H
/**
 * @copyright
 * @file web_engine_page.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Page header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWebEngineWidgets/QWebEnginePage>

#include "web_engine_profile.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup WebEnginePageGroup Web Engine Page Doxygen Group
 *  Web Engine Page functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(webEnginePageOverall)

namespace web_engine_page {

	/**
	 * @brief WebEnginePage class
	 *
	 */
	class WebEnginePage : public QWebEnginePage {

		public:
			/**
			 * @brief Function: explicit WebEnginePage(WebEngineProfile * profile = web_engine_profile::WebEngineProfile::defaultProfile(), QWidget * parent = Q_NULLPTR)
			 *
			 * \param profile: profile of the page
			 * \param parent: parent widget
			 *
			 * Web engine page constructor
			 */
			explicit WebEnginePage(web_engine_profile::WebEngineProfile * profile = web_engine_profile::WebEngineProfile::defaultProfile(), QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: explicit WebEnginePage(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Web engine page constructor
			 */
			explicit WebEnginePage(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~WebEnginePage()
			 *
			 * Web engine page destructor
			 */
			virtual ~WebEnginePage();

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class WebEnginePage
			 *
			 */
			DISABLE_COPY_MOVE(WebEnginePage)

	};
}
/** @} */ // End of WebEnginePageGroup group

#endif // WEB_ENGINE_PAGE_H
