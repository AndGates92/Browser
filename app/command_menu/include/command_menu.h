#ifndef COMMAND_MENU_H
#define COMMAND_MENU_H

/**
 * @copyright
 * @file command_menu.h
 * @author Andrea Gianarda
 * @date 23th of January 2020
 * @brief Command Menu file
*/

#include <qt5/QtWidgets/QAbstractItemView>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QRect>
#include <qt5/QtCore/QModelIndex>
#include <qt5/QtGui/QRegion>

#include "command_menu_model.h"

/** @defgroup CommandMenuGroup Command Menu Doxygen Group
 *  Command Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(commandMenuOverall)
Q_DECLARE_LOGGING_CATEGORY(commandMenuSettings)

namespace command_menu {

	namespace {
		/**
		 * @brief command menu title
		 *
		 */
		const QString commandMenuTitle("Commands");

		/**
		 * @brief Disable auto scroll - user will have to press a key to scroll down
		 *
		 */
		const bool autoScrollProp = false;

		/**
		 * @brief Disable edit trigger
		 *
		 */
		const QAbstractItemView::EditTrigger editTrigger = QAbstractItemView::NoEditTriggers;

		/**
		 * @brief Disable drag and drop mode
		 *
		 */
		const QAbstractItemView::DragDropMode dragDropMode = QAbstractItemView::NoDragDrop;
	}

	/**
	 * @brief CommandMenu class
	 *
	 */
	class CommandMenu : public QAbstractItemView {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit CommandMenu(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent window
			 *
			 * Command menu constructor
			 */
			explicit CommandMenu(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~CommandMenu()
			 *
			 * Command menu destructor
			 */
			~CommandMenu();

		protected:

		private:
			/**
			 * @brief command menu model
			 *
			 */
			command_menu_model::CommandMenuModel * menuModel;

			/**
			 * @brief Function: void setProperties()
			 *
			 * Set properties of the command menu
			 */
			void setProperties();

			/**
			 * @brief Function: void setModel(command_menu_model::CommandMenuModel * model)
			 *
			 * \param model: model to set for the command menu
			 *
			 * Set command menu model
			 */
			void setModel(command_menu_model::CommandMenuModel * model);

			/**
			 * @brief Function: QRect visualRect(QModelIndex & index) const
			 *
			 * \return rectangle where item at index is
			 *
			 * This function returns the rectangle occupied by item at inde 
			 */
			QRect visualRect(QModelIndex & index) const;

			/**
:			 * @brief Function: void scrollTo(const QModelIndex & index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible)
			 *
			 * \param index: is the index of the model
			 * \param hint: view will position an item accoridng to the value of hint

			 * Scroll the view if required to ensure that element at item index is visible
			 */
			void scrollTo(const QModelIndex & index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible);

			/**
			 * @brief Function: QModelIndex indexAt(const QPoint & point) const
			 *
			 * \param point: points to search model for

			 * \return model index at point point
			 *
			 * This function returns the model index of item at point point
			 */
			QModelIndex indexAt(const QPoint & point) const;

			/**
			 * @brief Function: QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
			 *
			 * \param cursorAction: action execute by the cursor
			 * \param modifiers: enumeration with the keyboard modifier supported by Qt
			 *
			 * \return model index pointing to the next object in the view based on the input arguments
			 *
			 * This function returns the model index pointing to the next object in the view based on the input arguments
			 */
			QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

			/**
			 * @brief Function: int horizontalOffset() const
			 *
			 * \return the horizontal offset of the view
			 *
			 * This function returns the horizontal offset of the view
			 */
			int horizontalOffset() const;

			/**
			 * @brief Function: int verticalOffset() const
			 *
			 * \return the vertical offset of the view
			 *
			 * This function returns the vertical offset of the view
			 */
			int verticalOffset() const;

			/**
			 * @brief Function: bool isIndexHidden(const QModelIndex & index) const
			 *
			 * \param index: model index to check whether is idle while the code is running
			 *
			 * \return if an item is hidden
			 *
			 * This function returns whether an item is hidden (true) or visible (false)
			 */
			bool isIndexHidden(const QModelIndex & index) const;

			/**
			 * @brief Function: void setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags command)
			 *
			 * \param rect: rectangle limiting th earea where flags are applied
			 * \param command: flags to be used 
			 *
			 * apply flags to item inside of touched by rectangle rect
			 */
			void setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags command);

			/**
			 * @brief Function: QRegion visualRegionForSelection(const QItemSelection & selection) const
			 *
			 * \param selection: items to search for
			 *
			 * \return region that encapsulates all items in selection selection
			 *
			 * This function returns from the viewpoint of the items
			 */
			QRegion visualRegionForSelection(const QItemSelection & selection) const;

			/**
			 * @brief Function: QRect visualRect(const QModelIndex & index) const
			 *
			 * \param index: index of item to return the rectangle of
			 *
			 * \return the rectangle on the viewpoint occupied by item at index
			 *
			 * This function returns the rectangle where the item at index is occupying
			 */
			QRect visualRect(const QModelIndex & index) const;
	};

}
/** @} */ // End of CommandMenuGroup group

#endif // COMMAND_MENU_H
