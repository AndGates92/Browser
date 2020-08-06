#ifndef FIND_BUTTON_WINDOW_H
#define FIND_BUTTON_WINDOW_H
/**
 * @copyright
 * @file find_button_window.h
 * @author Andrea Gianarda
 * @date 17th of July 2020
 * @brief Find Button Window header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "global_enums.h"
#include "constructor_macros.h"
#include "secondary_window_interface.h"
#include "find_button_window_settings.h"
#include "action.h"
#include "find_settings.h"

/** @defgroup FindButtonWindowGroup Find Button Window Doxygen Group
 *  Find Button Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(findButtonWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(findButtonWindowCancel)
Q_DECLARE_LOGGING_CATEGORY(findButtonWindowFind)

namespace find_button_window {

	/**
	 * @brief FindButtonWindow class
	 *
	 */
	class FindButtonWindow final : public QWidget, public secondary_window_interface::SecondaryWindowInterface {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit FindButtonWindow(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Find button window constructor
			 */
			explicit FindButtonWindow(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~FindButtonWindow()
			 *
			 * Find button window destructor
			 */
			virtual ~FindButtonWindow();

		protected:

		private slots:
			/**
			 * @brief Function: virtual void apply() override
			 *
			 * This function is the slot of the find action
			 */
			virtual void apply() override;

			/**
			 * @brief Function: virtual void cancel() override
			 *
			 * This function is the slot of the cancel button
			 */
			virtual void cancel() override;

		signals:
			/**
			 * @brief Function: void find(const find_settings::FindSettings settings) const
			 *
			 * \param settings: search settings
			 *
			 * This function is the signal to trigger a find in the page
			 */
			void find(const find_settings::FindSettings settings) const;

		private:
			/**
			 * @brief Function: void windowLayout()
			 *
			 * This function creates the layout of the window
			 */
			void windowLayout();

			/**
			 * @brief Function: void createActions()
			 *
			 * This function creates actions for the find window
			 */
			void createActions();

			/**
			 * @brief Function: void fillWindow()
			 *
			 * This function creates widgets that are part of the window
			 */
			void fillWindow();

			/**
			 * @brief Function: virtual void connectSignals() override
			 *
			 * This function connects signals and slots between main window elements
			 */
			virtual void connectSignals() override;

			/**
			 * @brief Function: virtual void close() override
			 *
			 * This function closes the window
			 */
			virtual void close() override;

			/**
			 * @brief Function: virtual QSize sizeHint() const override
			 *
			 * \return return recommended size of the widget
			 *
			 * Compute recommendend size of the widget
			 */
			virtual QSize sizeHint() const override;

			/**
			 * @brief find action
			 *
			 */
			std::unique_ptr<action::Action> findAction;

			/**
			 * @brief cancel action
			 *
			 */
			std::unique_ptr<action::Action> cancelAction;

			/**
			 * @brief insert action
			 *
			 */
			std::unique_ptr<action::Action> typeAction;

			/**
			 * @brief text to find in the page
			 *
			 */
			std::shared_ptr<QLineEdit> textToFind;

			/**
			 * @brief find button
			 *
			 */
			std::unique_ptr<QPushButton> findButton;

			/**
			 * @brief cancel button
			 *
			 */
			std::unique_ptr<QPushButton> cancelButton;

			/**
			 * @brief search settings box
			 *
			 */
			std::unique_ptr<find_button_window_settings::FindButtonWindowSettings> settingsBox;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class FindButtonWindow
			 *
			 */
			DISABLE_COPY_MOVE(FindButtonWindow)

	};
}
/** @} */ // End of FindButtonWindowGroup group

#endif // FIND_BUTTON_WINDOW_H
