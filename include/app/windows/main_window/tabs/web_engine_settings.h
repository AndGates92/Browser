#ifndef MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
#define MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
/**
 * @copyright
 * @file web_engine_settings.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Settings header file
*/

#include "app/base/tabs/web_engine_settings.h"
#include "app/shared/enums.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			/**
			 * @brief WebEngineSettings class
			 *
			 */
			class WebEngineSettings final : public app::base::tab::WebEngineSettings {

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
					 * @brief Function: WebEngineSettings(const app::main_window::tab::WebEngineSettings & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * Main window web engine settings copy constructor
					 */
					explicit WebEngineSettings(const app::main_window::tab::WebEngineSettings & rhs);

					/**
					 * @brief Function: WebEngineSettings::WebEngineSettings(app::main_window::tab::WebEngineSettings && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * Main window web engine settings move constructor
					 */
					explicit WebEngineSettings(app::main_window::tab::WebEngineSettings && rhs);

					// Move and copy assignment operators
					/**
					 * @brief Function: app::main_window::tab::WebEngineSettings & operator=(const app::main_window::tab::WebEngineSettings & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * Main window web engine settings copy assignment operator
					 */
					app::main_window::tab::WebEngineSettings & operator=(const app::main_window::tab::WebEngineSettings & rhs);

					/**
					 * @brief Function: app::main_window::tab::WebEngineSettings & operator=(app::main_window::tab::WebEngineSettings && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * Main window web engine settings move assignment operator
					 */
					app::main_window::tab::WebEngineSettings & operator=(app::main_window::tab::WebEngineSettings && rhs);

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

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_SETTINGS_H
