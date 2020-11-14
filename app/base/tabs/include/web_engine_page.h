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
#include <QtWebEngineWidgets/QWebEnginePage>

#include "base/tabs/include/web_engine_profile.h"
#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			class Tab;

			/**
			 * @brief WebEnginePage class
			 *
			 */
			class WebEnginePage : public QWebEnginePage {
				friend class app::base::tab::Tab;

				public:
					/**
					 * @brief Function: explicit WebEnginePage(QWidget * parent, WebEngineProfile * profile = app::base::tab::WebEngineProfile::defaultProfile())
					 *
					 * \param profile: profile of the page
					 * \param parent: parent widget
					 *
					 * Web engine page constructor
					 */
					explicit WebEnginePage(QWidget * parent, app::base::tab::WebEngineProfile * profile = app::base::tab::WebEngineProfile::defaultProfile());

					/**
					 * @brief Function: virtual ~WebEnginePage()
					 *
					 * Web engine page destructor
					 */
					virtual ~WebEnginePage();

					/**
					 * @brief Function: app::base::tab::WebEngineProfile * profile() const
					 *
					 * \return profile of the page
					 *
					 * This function returns the profile of this web engine page
					 */
					app::base::tab::WebEngineProfile * profile() const;

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

	}

}
/** @} */ // End of TabGroup group

#endif // WEB_ENGINE_PAGE_H
