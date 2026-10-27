// void TabClass::Unknown_006A1EA0() (0x006A1EA0)
// Hides the closed bar's thumb button and its help region (0xF1).
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390

void TabClass::Unknown_006A1EA0()
{
    Remove_A_Button(unknown_button_abe390);
    ToolTips->Remove(0xF1);
}
