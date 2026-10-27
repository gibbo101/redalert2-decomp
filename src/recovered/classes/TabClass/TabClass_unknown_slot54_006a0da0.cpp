// bool TabClass::unknown_slot54(int control) (0x006A0DA0, slot 54)
// Shows or hides the sidebar (the sidebar's slot 54); when that changed,
// updates the side buttons and their help regions, then redraws.
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?unknown_slot54@SidebarClass@@UAE_NH@Z=0067e210
// @ref ?Unknown_006A1AB0@TabClass@@QAEXXZ=006a1ab0
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860
// @ref ?unknown_button_abe400@TabClass@@2VShapeButtonClass@@A=00abe400
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918
// @ref ?SlotButton@TabClass@@2PAHA=00abe2c8
// @ref ??_C@_0BA@GHMH@Tip?3ThumbClosed?$AA@=007f6860

bool TabClass::unknown_slot54(int control)
{
    bool changed = SidebarClass::unknown_slot54(control);
    if (changed) {
        if (unknown_4ee1) {
            if (unknown_4f14) {
                Unknown_006A1AB0();
            } else {
                Add_A_Button(unknown_button_abe390);
                Unknown_006A1270(&unknown_button_abe390, "Tip:ThumbClosed");
            }
        } else if (unknown_4f14) {
            for (int index = 0; index < 25; index++) {
                Remove_A_Button(Buttons[index]);
            }
            Remove_A_Button(unknown_button_abe400);
            for (int slot = 0; slot < 25; slot++) {
                ShapeButtonClass *button = Unknown_006A0600(slot);
                if (button != 0) {
                    ToolTips->Remove(button->ID);
                }
            }
            ToolTips->Remove(0xF0);
        } else {
            Remove_A_Button(unknown_button_abe390);
            ToolTips->Remove(0xF1);
        }
        Flag_To_Redraw(2);
    }
    return changed;
}
