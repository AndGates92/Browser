#ifndef LINE_EDIT_H
#define LINE_EDIT_H
/**
 * @copyright
 * @file line_edit.h
 * @author Andrea Gianarda
 * @date 02nd of February 2021
 * @brief Line edit class header file
*/

// Qt libraries
#include <QtWidgets/QLineEdit>

#include "app/shared/constructor_macros.h"

/** @defgroup LineEditGroup Line Edit Doxygen Group
 *  Line edit functions and classes
 *  @{
 */
namespace app {

	namespace text_widgets {

		/**
		 * @brief Line edit class
		 *
		 */
		class LineEdit final : public QLineEdit {

			Q_OBJECT

			public:
				/**
				 * @brief Function: explicit LineEdit(QWidget * parent, const QString & text = QString())
				 *
				 * \param parent: parent window
				 * \param text: text to write into QLineEdit
				 *
				 * Line edit constructor
				 */
				explicit LineEdit(QWidget * parent, const QString & text = QString());

				/**
				 * @brief Function: virtual ~LineEdit()
				 *
				 * Line edit destructor
				 */
				virtual ~LineEdit();

			protected:

			private:

				/**
				 * @brief Function: virtual void connectSignals() final
				 *
				 * This function connects signals and slots within line edit
				 */
				void connectSignals();

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class LineEdit
				 *
				 */
				DISABLE_COPY_MOVE(LineEdit)

		};


	}

}

/** @} */ // End of LineEditGroup group

#endif // LINE_EDIT_H
