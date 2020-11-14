#ifndef WEB_ENGINE_PROFILE_H
#define WEB_ENGINE_PROFILE_H
/**
 * @copyright
 * @file web_engine_profile.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Profile header file
*/

#include <QtWebEngineWidgets/QWebEngineProfile>

#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			/**
			 * @brief WebEngineProfile class
			 *
			 */
			class WebEngineProfile : public QWebEngineProfile {

				public:
					/**
					 * @brief Function: static app::base::tab::WebEngineProfile * defaultProfile()
					 *
					 * \return the default profile
					 *
					 * this function constructs the default web engine profile
					 */
					static app::base::tab::WebEngineProfile * defaultProfile();

					/**
					 * @brief Function: explicit WebEngineProfile(QObject * parent, const QString & storageName)
					 *
					 * \param storageName: name of the profile
					 * \param parent: parent object
					 *
					 * Web engine profile constructor
					 */
					explicit WebEngineProfile(QObject * parent, const QString & storageName);

					/**
					 * @brief Function: virtual ~WebEngineProfile()
					 *
					 * Web engine profile destructor
					 */
					virtual ~WebEngineProfile();

				protected:

				private:
					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class WebEngineProfile
					 *
					 */
					DISABLE_COPY_MOVE(WebEngineProfile)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // WEB_ENGINE_PROFILE_H
