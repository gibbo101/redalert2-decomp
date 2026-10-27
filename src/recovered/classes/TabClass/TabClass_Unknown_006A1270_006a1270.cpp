// void __fastcall TabClass::Unknown_006A1270(ControlClass *control, char const *label) (0x006A1270)
// Registers a control's area as a help region under the control's ID with
// the given string table label, replacing any region with that ID.
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860

void __fastcall TabClass::Unknown_006A1270(ControlClass *control, char const *label)
{
    if (control != 0) {
        ToolTip tip;
        tip.ID = control->ID;
        tip.Label = label;
        tip.Region.X = control->X;
        tip.Region.Y = control->Y;
        tip.Region.Width = control->Width;
        tip.Region.Height = control->Height;
        ToolTips->Remove(control->ID);
        ToolTips->Add(tip);
    }
}
