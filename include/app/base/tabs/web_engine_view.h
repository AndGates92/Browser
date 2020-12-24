#ifndef WEB_ENGINE_VIEW_H
#define WEB_ENGINE_VIEW_H
/**
 * @copyright
 * @file web_engine_view.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine View header file
*/

#include <memory>

// Qt libraries
#include <QtWebEngineWidgets/QWebEngineView>

#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			class Tab;
			class WebEnginePage;

			/**
			 * @brief WebEngineView class
			 *
			 */
			class WebEngineView : public QWebEngineView {
				friend class app::base::tab::Tab;

				public:
					/**
					 * @brief Function: explicit WebEngineView(QWidget * parent, std::weak_ptr<app::base::tab::Tab> attachedTab)
					 *
					 * \param parent: parent widget
					 * \param attachedTab: tab attached to this view
					 *
					 * Web engine view constructor
					 */
					explicit WebEngineView(QWidget * parent, std::weak_ptr<app::base::tab::Tab> attachedTab);

					/**
					 * @brief Function: virtual ~WebEngineView()
					 *
					 * Web engine view destructor
					 */
					virtual ~WebEngineView();

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::WebEnginePage> page() const
					 *
					 * \return page of the view
					 *
					 * This function returns the page of this web engine view
					 */
					std::shared_ptr<app::base::tab::WebEnginePage> page() const;

					/**
					 * @brief Function: const std::shared_ptr<app::base::tab::Tab> getTab() const
					 *
					 * \return tab the view belongs to
					 *
					 * This function returns the tab the web widget view belongs to
					 */
					const std::shared_ptr<app::base::tab::Tab> getTab() const;

				protected:

					/**
					 * @brief Function: void updatePage(const std::shared_ptr<app::base::tab::WebEnginePage> & newPage)
					 *
					 * \param: new page to be used for this view
					 *
					 * This function changes the page of this web engine view
					 */
					void updatePage(const std::shared_ptr<app::base::tab::WebEnginePage> & newPage);

					/**
					 * @brief Function: void setTab(std::weak_ptr<app::base::tab::Tab> value)
					 *
					 * \param tab: tab the component belongs to
					 *
					 * This function sets the tab the component belongs to
					 */
					void setTab(std::weak_ptr<app::base::tab::Tab> value);

				private:
					/**
					 * @brief current page linked to the web view
					 *
					 */
					std::shared_ptr<app::base::tab::WebEnginePage> currentPage;

					/**
					 * @brief tab the scroll manager belongs to
					 *
					 */
					std::weak_ptr<app::base::tab::Tab> browserTab;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class WebEngineView
					 *
					 */
					DISABLE_COPY_MOVE(WebEngineView)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // WEB_ENGINE_VIEW_H
