/**
 * @copyright
 * @file main_window_popup_base.cpp
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window popup base functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "main_window_popup_base.h"
#include "logging_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowPopupBaseOverall, "mainWindowPopupBase.overall", MSG_TYPE_LEVEL)

main_window_popup_base::MainWindowPopupBase::MainWindowPopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags) : popup_base::PopupBase(parent, centerWidget, widgetPadding, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowPopupBaseOverall,  "Main window popup base constructor");

}

main_window_popup_base::MainWindowPopupBase::~MainWindowPopupBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowPopupBaseOverall,  "Main window popup base destructor");

}
