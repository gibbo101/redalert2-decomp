// void TabClass::Unknown_006A1EC0() (0x006A1EC0)
// Opens the bar when it is closed: swaps the thumb for the bar's buttons.
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390
// @ref ?Unknown_006A1AB0@TabClass@@QAEXXZ=006a1ab0

void TabClass::Unknown_006A1EC0()
{
    if (!unknown_4f14) {
        Unknown_006A1EA0();
        unknown_4f14 = true;
        Unknown_006A1AB0();
        unknown_4f15 = true;
        Flag_To_Redraw(0);
    }
}
