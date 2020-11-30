#ifndef WEB_ENGINE_SETTINGS_H
#define WEB_ENGINE_SETTINGS_H
/**
 * @copyright
 * @file web_engine_settings.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Settings header file
*/

// Qt libraries
#include <QtWebEngineWidgets/QWebEngineSettings>

#include "app/shared/enums.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			/**
			 * @brief WebEngineSettings class
			 *
			 */
			class WebEngineSettings {

				public:
					/**
					 * @brief Function: explicit WebEngineSettings(QWebEngineSettings * settings)
					 *
					 * \param settings: settings to initialize the class width
					 *
					 * Web engine settings constructor
					 */
					explicit WebEngineSettings(QWebEngineSettings * newSettings);

					// Move and copy constructor
					/**
					 * @brief Function: WebEngineSettings(const app::base::tab::WebEngineSettings & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * Web engine settings copy constructor
					 */
					explicit WebEngineSettings(const app::base::tab::WebEngineSettings & rhs);

					/**
					 * @brief Function: WebEngineSettings::WebEngineSettings(app::base::tab::WebEngineSettings && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * Web engine settings move constructor
					 */
					explicit WebEngineSettings(app::base::tab::WebEngineSettings && rhs);

					// Move and copy assignment operators
					/**
					 * @brief Function: WebEngineSettings & operator=(const app::base::tab::WebEngineSettings & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * Web engine settings copy assignment operator
					 */
					WebEngineSettings & operator=(const app::base::tab::WebEngineSettings & rhs);

					/**
					 * @brief Function: WebEngineSettings & operator=(app::base::tab::WebEngineSettings && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * Web engine settings move assignment operator
					 */
					WebEngineSettings & operator=(app::base::tab::WebEngineSettings && rhs);

					/**
					 * @brief Function: virtual ~WebEngineSettings()
					 *
					 * Web engine settings destructor
					 */
					virtual ~WebEngineSettings();

				protected:

				private:
					/**
					 * @brief settings of the tab
					 *
					 */
					QWebEngineSettings * settings;

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // WEB_ENGINE_SETTINGS_H
