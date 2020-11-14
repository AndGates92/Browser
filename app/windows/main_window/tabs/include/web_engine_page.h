#ifndef MAIN_WINDOW_WEB_ENGINE_PAGE_H
#define MAIN_WINDOW_WEB_ENGINE_PAGE_H
/**
 * @copyright
 * @file web_engine_page.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Web Engine Page header file
*/

#include "base/tabs/include/web_engine_page.h"
#include "windows/main_window/tabs/include/page_data.h"
#include "windows/main_window/common/include/shared_types.h"
#include "windows/main_window/tabs/include/web_engine_profile.h"
#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class Tab;
			class TabWidget;
			class WebEngineView;

			/**
			 * @brief WebEnginePage class
			 *
			 */
			class WebEnginePage final : public app::base::tab::WebEnginePage {
				friend class app::main_window::tab::Tab;
				friend class app::main_window::tab::WebEngineView;
				friend class app::main_window::tab::TabWidget;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit WebEnginePage(QWidget * parent, const app::main_window::page_type_e & type, const QString & src, app::base::tab::WebEngineProfile * profile, const void * data = nullptr)
					 *
					 * \param type: page type
					 * \param src: source of the page content
					 * \param profile: profile of the page
					 * \param data: page extra data
					 * \param parent: parent widget
					 *
					 * Main window web engine page constructor
					 */
					explicit WebEnginePage(QWidget * parent, const app::main_window::page_type_e & type = app::main_window::page_type_e::UNKNOWN, const QString & src = QString(), app::main_window::tab::WebEngineProfile * profile = app::main_window::tab::WebEngineProfile::defaultProfile(), const void * data = nullptr);

					/**
					 * @brief Function: virtual ~WebEnginePage()
					 *
					 * Main window web engine page destructor
					 */
					virtual ~WebEnginePage();

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::PageData> & getData() const
					 *
					 * \return page data
					 *
					 * This function returns custom page data
					 */
					const std::shared_ptr<app::main_window::tab::PageData> & getData() const;

					/**
					 * @brief Function: const app::main_window::page_type_e & getType() const
					 *
					 * \return page type
					 *
					 * This function returns page type
					 */
					const app::main_window::page_type_e & getType() const;

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

				private slots:
					/**
					 * @brief Function: void applyScrollRequest(const int & x, const int & y)
					 *
					 * \param x: scroll on the x axis
					 * \param y: scroll on the y axis
					 *
					 * This function honors the scroll position change request
					 */
					void applyScrollRequest(const int & x, const int & y);

				private:
					/**
					 * @brief custom page data
					 *
					 */
					std::shared_ptr<app::main_window::tab::PageData> pageData;

					/**
					 * @brief Function: QByteArray getTextFileBody() const
					 *
					 * \return content of the file set as sounce of the page
					 *
					 * This function reads a file set as sounce of the page and returns its content as a QByteArray
					 */
					QByteArray getTextFileBody() const;

					/**
					 * @brief Function: void setBody()
					 *
					 * Set body of the page based on the page type
					 * if the type is WEB_CONTENT, it converts the source of the content of page to an URL
					 * if the type is TEXT, it prints the source of the content of page as plain text using UTF-8 character encoding
					 */
					void setBody();

					/**
					 * @brief Function: void setData(const std::shared_ptr<app::main_window::tab::PageData> & newData)
					 *
					 * \param newData: source of the page
					 *
					 * This function changes all member of the page data associated with a web engine page object
					 */
					void setData(const std::shared_ptr<app::main_window::tab::PageData> & newData);

					/**
					 * @brief Function: void setSource(const QString & src)
					 *
					 * \param src: source of the page
					 *
					 * Set the source of the page
					 */
					void setSource(const QString & src);

					/**
					 * @brief Function: void reload()
					 *
					 * This function reloads the content of the page
					 */
					void reload();

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class WebEnginePage
					 *
					 */
					DISABLE_COPY_MOVE(WebEnginePage)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_PAGE_H
