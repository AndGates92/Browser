#ifndef FIND_BUTTON_WINDOW_H
#define FIND_BUTTON_WINDOW_H
/**
 * @copyright
 * @file window.h
 * @author Andrea Gianarda
 * @date 17th of July 2020
 * @brief Find Window header file
*/

#include <memory>

#include <QtWidgets/QWidget>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"
#include "app/base/window/action_interface.h"

// Including here because it is used in a signal
#include "app/windows/shared/find_settings.h"

/** @defgroup FindWindowGroup Find Window Doxygen Group
 *  Find Window functions and classes
 *  @{
 */
namespace app {

	namespace commands {

		class Action;

	}

	namespace find_window {

		class Settings;

		/**
		 * @brief Window class
		 *
		 */
		class Window final : public QWidget, public app::base::window::ActionInterface {

			Q_OBJECT

			public:
				/**
				 * @brief Function: explicit Window(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
				 *
				 * \param parent: parent window
				 * \param flags: window flags
				 *
				 * Find button window constructor
				 */
				explicit Window(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

				/**
				 * @brief Function: virtual ~Window()
				 *
				 * Find button window destructor
				 */
				virtual ~Window();

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
				 * @brief Function: void find(const app::windows::shared::FindSettings settings) const
				 *
				 * \param settings: search settings
				 *
				 * This function is the signal to trigger a find in the page
				 */
				void find(const app::windows::shared::FindSettings settings) const;

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
				std::unique_ptr<app::commands::Action> findAction;

				/**
				 * @brief cancel action
				 *
				 */
				std::unique_ptr<app::commands::Action> cancelAction;

				/**
				 * @brief insert action
				 *
				 */
				std::unique_ptr<app::commands::Action> typeAction;

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
				std::unique_ptr<app::find_window::Settings> settingsBox;

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class Window
				 *
				 */
				DISABLE_COPY_MOVE(Window)

		};

	}

}
/** @} */ // End of FindWindowGroup group

#endif // FIND_BUTTON_WINDOW_H
