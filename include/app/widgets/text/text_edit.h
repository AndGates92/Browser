#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H
/**
 * @copyright
 * @file text_edit.h
 * @author Andrea Gianarda
 * @date 02nd of February 2021
 * @brief Text edit class header file
*/

// Qt libraries
#include <QtWidgets/QTextEdit>

#include "app/shared/constructor_macros.h"

/** @defgroup TextEditGroup Text Edit Doxygen Group
 *  Text edit functions and classes
 *  @{
 */
namespace app {

	namespace text_widgets {

		/**
		 * @brief Text edit class
		 *
		 */
		class TextEdit final : public QTextEdit {

			Q_OBJECT

			public:
				/**
				 * @brief Function: explicit TextEdit(QWidget * parent, const QString & text = QString())
				 *
				 * \param parent: parent window
				 * \param text: text to write into QTextEdit
				 *
				 * Text edit constructor
				 */
				explicit TextEdit(QWidget * parent, const QString & text = QString());

				/**
				 * @brief Function: virtual ~TextEdit()
				 *
				 * Text edit destructor
				 */
				virtual ~TextEdit();

			public slots:

			protected:

			private:

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class TextEdit
				 *
				 */
				DISABLE_COPY_MOVE(TextEdit)
		};

	}

}

/** @} */ // End of TextEditGroup group

#endif // TEXT_EDIT_H
