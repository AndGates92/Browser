#ifndef MAIN_WINDOW_COMAND_LINE_VALIDATOR_H
#define MAIN_WINDOW_COMAND_LINE_VALIDATOR_H
/**
 * @copyright
 * @file command_line_validator.h
 * @author Andrea Gianarda
 * @date 15th of February 2021
 * @brief Main Window command line validator class header file
*/

#include <memory>

// Qt libraries
#include <QtGui/QValidator>

#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace window {

			class Core;

		}

		namespace statusbar {

			/**
			 * @brief Status Bar class
			 *
			 */
			class CommandLineValidator final : public QValidator {

				public:
					/**
					 * @brief Function: explicit CommandLineValidator(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & windowCore)
					 *
					 * \param parent: parent window
					 * \param core: main window core
					 *
					 * Main window command line argument constructor
					 */
					explicit CommandLineValidator(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & windowCore);

					/**
					 * @brief Function: virtual ~CommandLineValidator()
					 *
					 * Main window command line argument destructor
					 */
					virtual ~CommandLineValidator();

					/**
					 * @brief Function: virtual QValidator::State validate(QString & input, int & cursorPosition) const override
					 *
					 * \param input: input to check
					 * \param cursorPosition: position of the cursor
					 *
					 * This function checks that the input meets command line requirements
					 */
					virtual QValidator::State validate(QString & input, int & cursorPosition) const override;

				protected:

				private:

					/**
					 * @brief main window core
					 *
					 */
					std::weak_ptr<app::main_window::window::Core> core;

					/**
					 * @brief Function: std::shared_ptr<app::main_window::window::Core> getCore() const
					 *
					 * \return core the component belongs to
					 *
					 * This function returns the core the component belongs to
					 */
					std::shared_ptr<app::main_window::window::Core> getCore() const;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class CommandLineValidator
					 *
					 */
					DISABLE_COPY_MOVE(CommandLineValidator)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_COMAND_LINE_VALIDATORH
