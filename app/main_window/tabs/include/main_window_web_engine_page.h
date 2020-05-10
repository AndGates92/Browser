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
#include "main_window_page_data.h"
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

	/**
	 * @brief MainWindowWebEnginePage class
	 *
	 */
	class MainWindowWebEnginePage final : public web_engine_page::WebEnginePage {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit MainWindowWebEnginePage(QWidget * parent, const main_window_shared_types::page_type_e type, const QString & src, web_engine_profile::WebEngineProfile * profile, const void * data = nullptr)
			 *
			 * \param type: page type
			 * \param src: source of the page content
			 * \param profile: profile of the page
			 * \param data: page extra data
			 * \param parent: parent widget
			 *
			 * Main window web engine page constructor
			 */
			explicit MainWindowWebEnginePage(QWidget * parent, const main_window_shared_types::page_type_e type = main_window_shared_types::page_type_e::UNKNOWN, const QString & src = QString::null, main_window_web_engine_profile::MainWindowWebEngineProfile * profile = main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile(), const void * data = nullptr);

			/**
			 * @brief Function: virtual ~MainWindowWebEnginePage()
			 *
			 * Main window web engine page destructor
			 */
			virtual ~MainWindowWebEnginePage();

			/**
			 * @brief Function: void setBody()
			 *
			 * Set body of the page based on the page type
			 * if the type is WEB_CONTENT, it converts the source of the content of page to an URL
			 * if the type is TEXT, it prints the source of the content of page as plain text using UTF-8 character encoding
			 */
			void setBody();

			/**
			 * @brief Function: void setData(const main_window_page_data::MainWindowPageData * newData)
			 *
			 * \param newData: source of the page
			 *
			 * This function changes all member of the page data associated with a web engine page object
			 */
			void setData(const main_window_page_data::MainWindowPageData * newData);

			/**
			 * @brief Function: void setSource(const QString & src)
			 *
			 * \param src: source of the page
			 *
			 * Set the source of the page
			 */
			void setSource(const QString & src);

			/**
			 * @brief Function: const main_window_page_data::MainWindowPageData * getData() const
			 *
			 * \return page data
			 *
			 * This function returns custom page data
			 */
			const main_window_page_data::MainWindowPageData * getData() const;

			/**
			 * @brief Function: main_window_shared_types::page_type_e getType() const
			 *
			 * \return page type
			 *
			 * This function returns page type
			 */
			main_window_shared_types::page_type_e getType() const;

			/**
			 * @brief Function: const void * getExtraData() const
			 *
			 * \return page extra data
			 *
			 * This function returns page extra data
			 */
			const void * getExtraData() const;

			/**
			 * @brief Function: const QString getSource() const
			 *
			 * \return source of the page
			 *
			 * This function returns the source of the page
			 */
			const QString getSource() const;

			/**
			 * @brief Function: void reload()
			 *
			 * This function reloads the content of the page
			 */
			void reload();

		public slots:
			/**
			 * @brief Function: void applyScrollRequest(const int x, const int y)
			 *
			 * \param x: scroll on the x axis
			 * \param y: scroll on the y axis
			 *
			 * This function honors the scroll position change request
			 */
			void applyScrollRequest(const int x, const int y);

		signals:
			/**
			 * @brief Function: void sourceChanged(const QString & src)
			 *
			 * \param src: source fo the content of the page
			 *
			 * This signal notifies that the src of a page has changed
			 */
			void sourceChanged(const QString & src);

		protected:

		private:
			/**
			 * @brief custom page data
			 *
			 */
			main_window_page_data::MainWindowPageData * const pageData;

			/**
			 * @brief Function: QByteArray getTextFileBody() const
			 *
			 * \return content of the file set as sounce of the page
			 *
			 * This function reads a file set as sounce of the page and returns its content as a QByteArray
			 */
			QByteArray getTextFileBody() const;

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
