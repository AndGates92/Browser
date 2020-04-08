#ifndef MAIN_WINDOW_WEB_ENGINE_PROFILE_H
#define MAIN_WINDOW_WEB_ENGINE_PROFILE_H
/**
 * @copyright
 * @file main_window_web_engine_profile.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Profile header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "web_engine_profile.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup MainWindowWebEngineProfileGroup Web Engine Profile Doxygen Group
 *  Web Engine Profile functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineProfileOverall)

namespace main_window_web_engine_profile {

	/**
	 * @brief MainWindowWebEngineProfile class
	 *
	 */
	class MainWindowWebEngineProfile final : public web_engine_profile::WebEngineProfile {

		public:
			/**
			 * @brief Function: static main_window_web_engine_profile::MainWindowWebEngineProfile * defaultProfile()
			 *
			 * \return the default profile
			 *
			 * this function constructs the default web engine profile
			 */
			static main_window_web_engine_profile::MainWindowWebEngineProfile * defaultProfile();

			/**
			 * @brief Function: explicit MainWindowWebEngineProfile(const QString & storageName, QObject * parent = Q_NULLPTR)
			 *
			 * \param storageName: name of the profile
			 * \param parent: parent object
			 *
			 * Main window web engine profile constructor
			 */
			explicit MainWindowWebEngineProfile(const QString & storageName, QObject * parent = Q_NULLPTR);

			/**
			 * @brief Function: explicit MainWindowWebEngineProfile(QObject * parent = Q_NULLPTR)
			 *
			 * \param parent: parent object
			 *
			 * Main window web engine profile constructor
			 */
			explicit MainWindowWebEngineProfile(QObject * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~MainWindowWebEngineProfile()
			 *
			 * Main window web engine profile destructor
			 */
			virtual ~MainWindowWebEngineProfile();

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowWebEngineProfile
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowWebEngineProfile)

	};

}
/** @} */ // End of MainWindowWebEngineProfileGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_PROFILE_H
