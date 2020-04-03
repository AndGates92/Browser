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
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWebEngineWidgets/QWebEngineSettings>

#include "global_types.h"

/** @defgroup WebEngineSettingsGroup Web Engine Settings Doxygen Group
 *  Web Engine Settings functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(webEngineSettingsOverall)

namespace web_engine_settings {

	/**
	 * @brief WebEngineSettings class
	 *
	 */
	class WebEngineSettings {

		public:
			/**
			 * @brief Function: explicit WebEngineSettings(QWebEngineSettings * settings = Q_NULLPTR)
			 *
			 * \param settings: settings to initialize the class width
			 *
			 * Web engine settings constructor
			 */
			explicit WebEngineSettings(QWebEngineSettings * newSettings = Q_NULLPTR);

			// Move and copy constructor
			/**
			 * @brief Function: WebEngineSettings(const web_engine_settings::WebEngineSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Web engine settings copy constructor
			 */
			explicit WebEngineSettings(const web_engine_settings::WebEngineSettings & rhs);

			/**
			 * @brief Function: WebEngineSettings::WebEngineSettings(web_engine_settings::WebEngineSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Web engine settings move constructor
			 */
			explicit WebEngineSettings(web_engine_settings::WebEngineSettings && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: WebEngineSettings & operator=(const web_engine_settings::WebEngineSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Web engine settings copy assignment operator
			 */
			WebEngineSettings & operator=(const web_engine_settings::WebEngineSettings & rhs);

			/**
			 * @brief Function: WebEngineSettings & operator=(web_engine_settings::WebEngineSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Web engine settings move assignment operator
			 */
			WebEngineSettings & operator=(web_engine_settings::WebEngineSettings && rhs);

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
/** @} */ // End of WebEngineSettingsGroup group

#endif // WEB_ENGINE_SETTINGS_H
