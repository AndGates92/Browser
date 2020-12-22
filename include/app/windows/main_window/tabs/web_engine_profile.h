#ifndef MAIN_WINDOW_WEB_ENGINE_PROFILE_H
#define MAIN_WINDOW_WEB_ENGINE_PROFILE_H
/**
 * @copyright
 * @file web_engine_profile.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Profile header file
*/

#include "app/base/tabs/web_engine_profile.h"
#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			/**
			 * @brief WebEngineProfile class
			 *
			 */
			class WebEngineProfile final : public app::base::tab::WebEngineProfile {

				public:
					/**
					 * @brief Function: static app::main_window::tab::WebEngineProfile * defaultProfile()
					 *
					 * \return the default profile
					 *
					 * this function constructs the default web engine profile
					 */
					static app::main_window::tab::WebEngineProfile * defaultProfile();

					/**
					 * @brief Function: explicit WebEngineProfile(const QString & storageName, QObject * parent)
					 *
					 * \param storageName: name of the profile
					 * \param parent: parent object
					 *
					 * Main window web engine profile constructor
					 */
					explicit WebEngineProfile(const QString & storageName, QObject * parent);

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

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_PROFILE_H
