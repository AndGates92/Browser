#ifndef MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
#define MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
/**
 * @copyright
 * @file main_window_web_engine_settings.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Settings header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "web_engine_settings.h"
#include "global_enums.h"

/** @defgroup MainWindowWebEngineSettingsGroup Web Engine Settings Doxygen Group
 *  Web Engine Settings functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineSettingsOverall)

namespace main_window_web_engine_settings {

	/**
	 * @brief MainWindowWebEngineSettings class
	 *
	 */
	class MainWindowWebEngineSettings final : public web_engine_settings::WebEngineSettings {

		public:
			/**
			 * @brief Function: explicit MainWindowWebEngineSettings(QWebEngineSettings * settings)
			 *
			 * \param settings: settings of the settings
			 *
			 * Main window web engine settings constructor
			 */
			explicit MainWindowWebEngineSettings(QWebEngineSettings * settings);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowWebEngineSettings(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main window web engine settings copy constructor
			 */
			explicit MainWindowWebEngineSettings(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs);

			/**
			 * @brief Function: MainWindowWebEngineSettings::MainWindowWebEngineSettings(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main window web engine settings move constructor
			 */
			explicit MainWindowWebEngineSettings(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: main_window_web_engine_settings::MainWindowWebEngineSettings & operator=(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main window web engine settings copy assignment operator
			 */
			main_window_web_engine_settings::MainWindowWebEngineSettings & operator=(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs);

			/**
			 * @brief Function: main_window_web_engine_settings::MainWindowWebEngineSettings & operator=(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main window web engine settings move assignment operator
			 */
			main_window_web_engine_settings::MainWindowWebEngineSettings & operator=(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs);

			/**
			 * @brief Function: virtual ~MainWindowWebEngineSettings()
			 *
			 * Main window web engine settings destructor
			 */
			virtual ~MainWindowWebEngineSettings();

		protected:

		private:

	};
}
/** @} */ // End of MainWindowWebEngineSettingsGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
