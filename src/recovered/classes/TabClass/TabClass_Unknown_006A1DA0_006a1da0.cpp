// void TabClass::Unknown_006A1DA0() (0x006A1DA0)
// Removes the open bar's 25 buttons and the extra one from the button list,
// and the help regions of the buttons in use and of the bar itself (0xF0).
// Removes the 25 buttons through 0x006A0D80 (inlined here; TabClass::AI's
// inlined copy of this function calls it out of line).
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?unknown_button_abe400@TabClass@@2VShapeButtonClass@@A=00abe400
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918
// @ref ?SlotButton@TabClass@@2PAHA=00abe2c8

void TabClass::Unknown_006A1DA0()
{
    Unknown_006A0D80();
    Remove_A_Button(unknown_button_abe400);
    for (int slot = 0; slot < 25; slot++) {
        ShapeButtonClass *button = Unknown_006A0600(slot);
        if (button != 0) {
            ToolTips->Remove(button->ID);
        }
    }
    ToolTips->Remove(0xF0);
}
