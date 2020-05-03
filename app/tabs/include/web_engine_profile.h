#ifndef WEB_ENGINE_PROFILE_H
#define WEB_ENGINE_PROFILE_H
/**
 * @copyright
 * @file web_engine_profile.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Profile header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWebEngineWidgets/QWebEngineProfile>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup WebEngineProfileGroup Web Engine Profile Doxygen Group
 *  Web Engine Profile functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(webEngineProfileOverall)

namespace web_engine_profile {

	/**
	 * @brief WebEngineProfile class
	 *
	 */
	class WebEngineProfile : public QWebEngineProfile {

		public:
			/**
			 * @brief Function: static web_engine_profile::WebEngineProfile * defaultProfile()
			 *
			 * \return the default profile
			 *
			 * this function constructs the default web engine profile
			 */
			static web_engine_profile::WebEngineProfile * defaultProfile();

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
/** @} */ // End of WebEngineProfileGroup group

#endif // WEB_ENGINE_PROFILE_H
