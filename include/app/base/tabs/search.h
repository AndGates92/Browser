#ifndef WEB_ENGINE_SEARCH_H
#define WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab Search header file
*/

#include "app/base/tabs/tab_component_widget.h"
#include "app/shared/constructor_macros.h"
#include "app/windows/shared/find_settings.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			class Tab;

			/**
			 * @brief Search class
			 *
			 */
			class Search : public app::base::tab::TabComponentWidget<app::windows::shared::FindSettings> {
				friend class app::base::tab::Tab;

				public:
					/**
					 * @brief Function: explicit Search(QObject * parent, std::weak_ptr<app::base::tab::Tab> attachedTab)
					 *
					 * \param attachedTab: tab attached to the search instance
					 * \param parent: parent object
					 *
					 * Tab search constructor
					 */
					explicit Search(QWidget * parent, std::weak_ptr<app::base::tab::Tab> attachedTab);

					/**
					 * @brief Function: virtual ~Search()
					 *
					 * Tab search destructor
					 */
					virtual ~Search();

				protected:
					/**
					 * @brief find settings
					 *
					 */
					app::windows::shared::FindSettings settings;

					/**
					 * @brief callback
					 *
					 */
					std::function<void(bool)> callback;

					/**
					 * @brief Function: virtual void execute(const app::windows::shared::FindSettings & newSettings) override final
					 *
					 * \param newSettings: new settings of search.
					 *
					 * This function searches text in a webpage
					 */
					virtual void execute(const app::windows::shared::FindSettings & newSettings) override final;

					/**
					 * @brief Function: virtual void setCallback()
					 *
					 * This function sets the callback to be run after the search
					 */
					virtual void setCallback();

				private:
					/**
					 * @brief Function: virtual void search() final
					 *
					 * This function searches text in a webpage
					 */
					virtual void search() final;

					/**
					 * @brief Function: virtual void canProcessRequests() const override
					 *
					 * \return whether scroll requests can be processed
					 *
					 * This function check if scroll requests can be processed
					 */
					virtual bool canProcessRequests() const override;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Search
					 *
					 */
					DISABLE_COPY_MOVE(Search)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // WEB_ENGINE_SEARCH_H
