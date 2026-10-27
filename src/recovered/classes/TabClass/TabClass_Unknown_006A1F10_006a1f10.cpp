// void TabClass::Unknown_006A1F10() (0x006A1F10)
// Closes the bar when it is open: swaps the bar's buttons for the thumb.
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390
// @ref ?unknown_button_abe400@TabClass@@2VShapeButtonClass@@A=00abe400
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918
// @ref ?SlotButton@TabClass@@2PAHA=00abe2c8
// @ref ??_C@_0BA@GHMH@Tip?3ThumbClosed?$AA@=007f6860

void TabClass::Unknown_006A1F10()
{
    if (unknown_4f14) {
        Unknown_006A1DA0();
        unknown_4f14 = false;
        Unknown_006A1E20();
        unknown_4f15 = true;
        Flag_To_Redraw(0);
    }
}
