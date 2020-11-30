#ifndef OPEN_CONTENT_H
#define OPEN_CONTENT_H
/**
 * @copyright
 * @file open_content.h
 * @author Andrea Gianarda
 * @date 14th June 2020
 * @brief Open Content header file
*/

#include <string>

#include "app/widgets/commands/action.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/shared/constructor_macros.h"

#include "app/base/window/file_handling_widgets.h"

/** @defgroup WindowGroup Window Doxygen Group
 *  Window functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace window {

			/**
			 * @brief OpenContent class
			 *
			 */
			class OpenContent : public app::base::window::FileHandlingWidgets {

				public:

					/**
					 * @brief Function: const QString getTypedPath() const
					 *
					 * \return text typed by the user
					 *
					 * This method return the path typed by the user
					 */
					const QString getTypedPath() const;

				protected:
					/**
					 * @brief Function: explicit OpenContent(QWidget *widgetParent)
					 *
					 * \param widgetParent: parent of widgets
					 *
					 * Open content constructor
					 */
					explicit OpenContent(QWidget *widgetParent);

					/**
					 * @brief Function: virtual ~OpenContent()
					 *
					 * Open content destructor
					 */
					virtual ~OpenContent();

					/**
					 * @brief Function: void openPath()
					 *
					 * This function handle the action to execute when the user opens a path
					 * If the path is a file, then it will call openItem that has to be reimplemented by the class
					 * If the path is a directory, it will move the file view to that directory
					 */
					void openPath();

					/**
					 * @brief Function: virtual void openItem(const QString & path)
					 *
					 * \param path: path of the file
					 *
					 * This function triggers the opening of the item
					 */
					virtual void openItem(const QString & path) = 0;

					/**
					 * @brief Function: virtual void doubleClickOnFile(const QFileInfo & pathInfo) override
					 *
					 * \param pathInfo: path to the file
					 *
					 * This function execute actions when the user double clicks on a file
					 */
					virtual void doubleClickOnFile(const QFileInfo & pathInfo) override;

				private:

			};

		}

	}

}
/** @} */ // End of WindowGroup group

#endif // OPEN_CONTENT_H
