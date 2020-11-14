/**
 * @copyright
 * @file popup_base.cpp
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window popup base functions
*/

#include "windows/main_window/popup/include/popup_base.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"

// Categories
LOGGING_CONTEXT(mainWindowPopupBaseOverall, mainWindowPopupBase.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::popup::PopupBase::PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags) : app::base::popup::PopupBase(parent, centerWidget, widgetPadding, flags) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPopupBaseOverall,  "Main window popup base constructor");

}

app::main_window::popup::PopupBase::~PopupBase() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPopupBaseOverall,  "Main window popup base destructor");

}
