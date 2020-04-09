#ifndef MAIN_WINDOW_WEB_ENGINE_PAGE_H
#define MAIN_WINDOW_WEB_ENGINE_PAGE_H
/**
 * @copyright
 * @file main_window_web_engine_page.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Web Engine Page header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "web_engine_page.h"
#include "main_window_tab_data.h"
#include "main_window_shared_types.h"
#include "main_window_web_engine_profile.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup MainWindowWebEnginePageGroup Web Engine Page Doxygen Group
 *  Web Engine Page functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEnginePageOverall)

namespace main_window_web_engine_page {

	namespace {

		/**
		 * @brief https string
		 *
		 */
		const QString https("https://");

		/**
		 * @brief www string
		 *
		 */
		const QString www("www.");

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		const QString defaultSearchEngine(https + www + "duckduckgo.com/?q=%1");

	}

	/**
	 * @brief MainWindowWebEnginePage class
	 *
	 */
	class MainWindowWebEnginePage final : public web_engine_page::WebEnginePage {

		public:
			/**
			 * @brief Function: explicit MainWindowWebEnginePage(const main_window_shared_types::tab_type_e type, const void * data, const void * tabContent, web_engine_profile::WebEngineProfile * profile, QWidget * parent = Q_NULLPTR)
			 *
			 * \param type: tab type
			 * \param data: tab extra data
			 * \param tabContent: tab content
			 * \param profile: profile of the page
			 * \param parent: parent widget
			 *
			 * Main window web engine page constructor
			 */
			explicit MainWindowWebEnginePage(const main_window_shared_types::tab_type_e type, const void * data, const void * tabContent, web_engine_profile::WebEngineProfile * profile, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: explicit MainWindowWebEnginePage(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Main window web engine page constructor
			 */
			explicit MainWindowWebEnginePage(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~MainWindowWebEnginePage()
			 *
			 * Main window web engine page destructor
			 */
			virtual ~MainWindowWebEnginePage();

			/**
			 * @brief Function: void setBody(const main_window_shared_types::tab_type_e & type, const void * content)
			 *
			 * \param type: tab type
			 * \param content: tab content
			 *
			 * Set body of the page based on the tab type
			 * if the type is WEB_CONTENT, it converts argument content to a QUrl
			 * if the type is TEXT, it converts argument content to a QString
			 */
			void setBody(const main_window_shared_types::tab_type_e & type, const void * content);

			/**
			 * @brief Function: main_window_tab_data::MainWindowTabData * getTabData() const
			 *
			 * \return tab data
			 *
			 * This function returns custom tab data
			 */
			main_window_tab_data::MainWindowTabData * getTabData() const;

			/**
			 * @brief Function: main_window_shared_types::tab_type_e getTabType() const
			 *
			 * \return tab type
			 *
			 * This function returns tab type
			 */
			main_window_shared_types::tab_type_e getTabType() const;

			/**
			 * @brief Function: const void * main_window_web_engine_page::MainWindowWebEnginePage::getTabExtraData() const
			 *
			 * \return tab extra data
			 *
			 * This function returns tab extra data
			 */
			const void * getTabExtraData() const;

			/**
			 * @brief Function: void reload()
			 *
			 * This function reloads the content of the page
			 */
			void reload();

		protected:

		private:
			/**
			 * @brief custom tab data
			 *
			 */
			main_window_tab_data::MainWindowTabData * const tabData;

			/**
			 * @brief Function: const QUrl createUrl(const QString & search) const
			 *
			 * \param search: string to search
			 *
			 * \return URL as QUrl
			 *
			 * This function is creates the URL based on the input from the user
			 * If the user writes down a URL himself/herself, it will return it adding, if required, https
			 * If the user is writing a strign to search, it will be searched in the chosen search engine
			 */
			const QUrl createUrl(const QString & search) const;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowWebEnginePage
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowWebEnginePage)

	};
}
/** @} */ // End of MainWindowWebEnginePageGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_PAGE_H
