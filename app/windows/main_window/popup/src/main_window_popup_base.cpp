/**
 * @copyright
 * @file main_window_popup_base.cpp
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window popup base functions
*/

#include "main_window_popup_base.h"
#include "macros.h"
#include "global_enums.h"

// Categories
LOGGING_CONTEXT(mainWindowPopupBaseOverall, mainWindowPopupBase.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_popup_base::MainWindowPopupBase::MainWindowPopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags) : popup_base::PopupBase(parent, centerWidget, widgetPadding, flags) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowPopupBaseOverall,  "Main window popup base constructor");

}

main_window_popup_base::MainWindowPopupBase::~MainWindowPopupBase() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowPopupBaseOverall,  "Main window popup base destructor");

}
