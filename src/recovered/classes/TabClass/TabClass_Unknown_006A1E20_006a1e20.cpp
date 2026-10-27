// void TabClass::Unknown_006A1E20() (0x006A1E20)
// Shows the closed bar's thumb button with its help region.
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390
// @ref ??_C@_0BA@GHMH@Tip?3ThumbClosed?$AA@=007f6860

void TabClass::Unknown_006A1E20()
{
    Add_A_Button(unknown_button_abe390);
    Unknown_006A1270(&unknown_button_abe390, "Tip:ThumbClosed");
}
