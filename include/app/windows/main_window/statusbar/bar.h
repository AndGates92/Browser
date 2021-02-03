#ifndef MAIN_WINDOW_STATUS_BAR_H
#define MAIN_WINDOW_STATUS_BAR_H
/**
 * @copyright
 * @file bar.h
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar class header file
*/

#include <memory>

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace text_widgets {

		class ElidedLabel;
		class LineEdit;

	}

	namespace progress_bar {

		class Bar;

	}

	namespace main_window {

		namespace statusbar {

			/**
			 * @brief Status Bar class
			 *
			 */
			class Bar final : public QWidget {

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit Bar(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
					 *
					 * \param parent: parent window
					 * \param flags: window flags
					 *
					 * Main window statusbar constructor
					 */
					explicit Bar(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

					/**
					 * @brief Function: virtual ~Bar()
					 *
					 * Main window statusbar destructor
					 */
					virtual ~Bar();

					/**
					 * Function: const std::unique_ptr<app::text_widgets::LineEdit> & getUserInput() const
					 *
					 * \return command argument
					 *
					 * This function returns the command argument
					 */
					const std::unique_ptr<app::text_widgets::LineEdit> & getUserInput() const;

					/**
					 * Function: const std::unique_ptr<app::text_widgets::LineEdit> & getContentPath() const
					 *
					 * \return content path
					 *
					 * This function returns the content path
					 */
					const std::unique_ptr<app::text_widgets::LineEdit> & getContentPath() const;

					/**
					 * Function: const std::unique_ptr<app::text_widgets::ElidedLabel> & getScroll() const
					 *
					 * \return web page scroll
					 *
					 * This function returns the web page scroll
					 */
					const std::unique_ptr<app::text_widgets::ElidedLabel> & getScroll() const;

					/**
					 * Function: const std::unique_ptr<app::text_widgets::ElidedLabel> & getInfo() const
					 *
					 * \return web page informations
					 *
					 * This function returns the web page informations
					 */
					const std::unique_ptr<app::text_widgets::ElidedLabel> & getInfo() const;

					/**
					 * Function: const std::unique_ptr<app::text_widgets::ElidedLabel> & getSearchResult() const
					 *
					 * \return search results
					 *
					 * This function returns the search result
					 */
					const std::unique_ptr<app::text_widgets::ElidedLabel> & getSearchResult() const;

					/**
					 * Function: const std::unique_ptr<app::progress_bar::Bar> & getLoadBar() const
					 *
					 * \return progress bar
					 *
					 * This function returns the progress bar
					 */
					const std::unique_ptr<app::progress_bar::Bar> & getLoadBar() const;

					/**
					 * Function: void showSearchResult(const bool & showWidget)
					 *
					 * \param showWidget: boolean indicating whether to show the search result or not
					 *
					 * This function shows or hides the search result label
					 */
					void showSearchResult(const bool & showWidget);

					/**
					 * Function: const QString getContentPathText() const
					 *
					 * \return text of the label
					 *
					 * This function returns the text in the search result label
					 */
					const QString getSearchResultText() const;

					/**
					 * Function: bool getLoadBarVisibility() const
					 *
					 * \returns the boolean value of the visibility attribute of the load bar
					 *
					 * This function returns the visibility attribute of the load bar as a boolean
					 */
					bool getLoadBarVisibility() const;

					/**
					 * Function: int getProgressValue() const
					 *
					 * \returns the value of the progress
					 *
					 * This function returns the value of the progress bar
					 */
					int getProgressValue() const;

					/**
					 * Function: int getVScroll() const
					 *
					 * \returns the vertical scroll percentage
					 *
					 * This function returns the vertical scroll percentage
					 */
					int getVScroll() const;

					/**
					 * Function: const QString getInfoText() const
					 *
					 * \return text of the label
					 *
					 * This function returns the text in the info label
					 */
					const QString getInfoText() const;

					/**
					 * Function: const QString getUserInputText() const
					 *
					 * \return text of the label
					 *
					 * This function returns the text in the user input label
					 */
					const QString getUserInputText() const;

					/**
					 * Function: const QString getContentPathText() const
					 *
					 * \return text of the label
					 *
					 * This function returns the text in the content path label
					 */
					const QString getContentPathText() const;

					/**
					 * Function: void setContentPathText(const QString & text)
					 *
					 * \param text: text to set the label to
					 *
					 * This function sets the text in the search result label
					 */
					void setSearchResultText(const QString & text);

					/**
					 * @brief Function: virtual void keyPressEvent(QKeyEvent * event) override final
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles events coming from the keyboard
					 * Escape is not triggered in keyPressedEvent
					 * Re-implement key pressed event
					 */
					virtual void keyPressEvent(QKeyEvent * event) override final;

					/**
					 * @brief Function: virtual void keyReleaseEvent(QKeyEvent * event) override final
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles event coming from the keyboard
					 * Re-implement key released event
					 */
					virtual void keyReleaseEvent(QKeyEvent * event) override final;

				public slots:
					/**
					 * Function: void setProgressValue(const int & value)
					 *
					 * \param value: value of the progress
					 *
					 * This function sets the text in the load bar from the integer value provided as argument
					 */
					void setProgressValue(const int & value);

					/**
					 * Function: void setVScroll(const int & vScroll)
					 *
					 * \param vScroll: vertical scroll percentage
					 *
					 * This function sets the text in the scroll label from the integer value provided as argument
					 */
					void setVScroll(const int & vScroll);

					/**
					 * Function: void setInfoText(const QString & text)
					 *
					 * \param text: text to set the label to
					 *
					 * This function sets the text in the info label
					 */
					void setInfoText(const QString & text);

					/**
					 * Function: void setUserInputText(const QString & text)
					 *
					 * \param text: text to set the label to
					 *
					 * This function sets the text in the user input label
					 */
					void setUserInputText(const QString & text);

					/**
					 * Function: void setContentPathText(const QString & text)
					 *
					 * \param text: text to set the label to
					 *
					 * This function sets the text in the content path label
					 */
					void setContentPathText(const QString & text);

				signals:
					/**
					 * @brief Function: void childFocusIn();
					 *
					 * This function is a signal triggered when a child widget gets the focus
					 */
					void childFocusIn();

					/**
					 * @brief Function: void childFocusOut();
					 *
					 * This function is a signal triggered when a child widget loses the focus
					 */
					void childFocusOut();

				protected:
					/**
					 * @brief Function: virtual void mousePressEvent(QMouseEvent * event) override final
					 *
					 * \param event: event coming from mouse
					 *
					 * This function handles events coming from the mouse
					 * Re-implement mouse pressed event
					 */
					virtual void mousePressEvent(QMouseEvent * event) override final;

				private:

					// Labels placed at the bottom of the window
					/**
					 * @brief user input
					 *
					 */
					std::unique_ptr<app::text_widgets::LineEdit> userInput;

					/**
					 * @brief content
					 *
					 */
					std::unique_ptr<app::text_widgets::LineEdit> contentPath;

					/**
					 * @brief scroll position
					 *
					 */
					std::unique_ptr<app::text_widgets::ElidedLabel> scroll;

					/**
					 * @brief info
					 *
					 */
					std::unique_ptr<app::text_widgets::ElidedLabel> info;

					/**
					 * @brief search result
					 *
					 */
					std::unique_ptr<app::text_widgets::ElidedLabel> searchResult;

					/**
					 * @brief load bar
					 *
					 */
					std::unique_ptr<app::progress_bar::Bar> loadBar;

					/**
					 * @brief Function: std::unique_ptr<app::text_widgets::LineEdit> newLineEdit()
					 *
					 * \return configured text edit widget
					 *
					 * This function configures text edit
					 */
					std::unique_ptr<app::text_widgets::LineEdit> newLineEdit();

					/**
					 * @brief Function: std::unique_ptr<app::text_widgets::ElidedLabel> newLabel()
					 *
					 * \return configured label
					 *
					 * This function configures window label
					 */
					std::unique_ptr<app::text_widgets::ElidedLabel> newLabel();

					/**
					 * @brief Function: std::unique_ptr<app::progress_bar::Bar> newProgressBar()
					 *
					 * \return configured progress bar
					 *
					 * This function configures progress bar
					 */
					std::unique_ptr<app::progress_bar::Bar> newProgressBar();

					/**
					 * @brief Function: void fillStatusBar()
					 *
					 * This function fills the status bar
					 */
					void fillStatusBar();

					/**
					 * @brief Function: QSize minimumSizeHint() const override
					 *
					 * \return return minimum size of the widget
					 *
					 * Compute minimum size of the widget
					 */
					QSize minimumSizeHint() const override;

					/**
					 * Function: bool isValidScrollValue(const int & value) const
					 *
					 * \param value: value of scrolling
					 *
					 * \return a boolean to indicate whether the input value is valid
					 *
					 * This function returns whether the input value is valid
					 */
					bool isValidScrollValue(const int & value) const;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Bar
					 *
					 */
					DISABLE_COPY_MOVE(Bar)

			};

		}

	}

}

/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_STATUS_BAR_H
