#ifndef MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
#define MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
/**
 * @copyright
 * @file web_engine_settings.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Settings header file
*/

#include "base/tabs/include/web_engine_settings.h"
#include "common/include/global_enums.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	/**
	 * @brief WebEngineSettings class
	 *
	 */
	class WebEngineSettings final : public web_engine_settings::WebEngineSettings {

		public:
			/**
			 * @brief Function: explicit WebEngineSettings(QWebEngineSettings * settings)
			 *
			 * \param settings: settings of the settings
			 *
			 * Main window web engine settings constructor
			 */
			explicit WebEngineSettings(QWebEngineSettings * settings);

			// Move and copy constructor
			/**
			 * @brief Function: WebEngineSettings(const main_window::WebEngineSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main window web engine settings copy constructor
			 */
			explicit WebEngineSettings(const main_window::WebEngineSettings & rhs);

			/**
			 * @brief Function: WebEngineSettings::WebEngineSettings(main_window::WebEngineSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main window web engine settings move constructor
			 */
			explicit WebEngineSettings(main_window::WebEngineSettings && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: main_window::WebEngineSettings & operator=(const main_window::WebEngineSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main window web engine settings copy assignment operator
			 */
			main_window::WebEngineSettings & operator=(const main_window::WebEngineSettings & rhs);

			/**
			 * @brief Function: main_window::WebEngineSettings & operator=(main_window::WebEngineSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main window web engine settings move assignment operator
			 */
			main_window::WebEngineSettings & operator=(main_window::WebEngineSettings && rhs);

			/**
			 * @brief Function: virtual ~WebEngineSettings()
			 *
			 * Main window web engine settings destructor
			 */
			virtual ~WebEngineSettings();

		protected:

		private:

	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
