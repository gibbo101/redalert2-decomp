// void ToolTipManager::Enable(bool enable) (0x006EB480)
// Turns the tips on or off; turning them off stops the timer and hides the tip.
// @ref ??_C@_02PHBM@on?$AA@=007ee350
// @ref ??_C@_03OJPB@off?$AA@=007ee34c
// @ref ??_C@_0BC@BFEK@Tooltips?5are?5?$CFs?4?6?$AA@=007f8588
#include "shared/tool_tip.hpp"
#include "shared/debug_printf.hpp"

void ToolTipManager::Enable(bool enable)
{
    if (Enabled != enable) {
        Enabled = enable;
        if (!enable) {
            KillTimer(Window, 0x54544950);
            if (Current != 0) {
                Hide(&Record);
            }
        }
        Debug_Printf("Tooltips are %s.\n", (Enabled == true) ? "on" : "off");
    }
}
