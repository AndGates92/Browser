#ifndef MAIN_WINDOW_WEB_ENGINE_PROFILE_H
#define MAIN_WINDOW_WEB_ENGINE_PROFILE_H
/**
 * @copyright
 * @file web_engine_profile.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Profile header file
*/

#include "base/tabs/include/web_engine_profile.h"
#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	/**
	 * @brief WebEngineProfile class
	 *
	 */
	class WebEngineProfile final : public web_engine_profile::WebEngineProfile {

		public:
			/**
			 * @brief Function: static main_window::WebEngineProfile * defaultProfile()
			 *
			 * \return the default profile
			 *
			 * this function constructs the default web engine profile
			 */
			static main_window::WebEngineProfile * defaultProfile();

			/**
			 * @brief Function: explicit WebEngineProfile(const QString & storageName, QObject * parent)
			 *
			 * \param storageName: name of the profile
			 * \param parent: parent object
			 *
			 * Main window web engine profile constructor
			 */
			explicit WebEngineProfile(QObject * parent, const QString & storageName);

			/**
			 * @brief Function: virtual ~WebEngineProfile()
			 *
			 * Main window web engine profile destructor
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
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_PROFILE_H
