// void PowerClass::unknown_slot34() (0x0061D130, slot 34)
// After the radar's, registers the power bar's help region (id 999): 8
// pixels wide at the sidebar origin (5 pixels further right when
// unknown_id_source_a3d290->unknown_2239 is set), 0x45 below its top.
#include "shared/power.hpp"
#include "shared/tool_tip.hpp"
#include "shared/abstract.hpp"
// @ref ?unknown_slot34@RadarClass@@UAEXXZ=006306d0
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_839620@@3HA=00839620
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_int_abcd70@@3HA=00abcd70

void PowerClass::unknown_slot34()
{
    RadarClass::unknown_slot34();
    if (ToolTips != 0) {
        ToolTip tip;
        tip.Label = 0;
        tip.ID = 999;
        int shift;
        if (unknown_id_source_a3d290->unknown_2239) {
            shift = 5;
        } else {
            shift = 0;
        }
        tip.Region.X = unknown_int_839620 + shift;
        tip.Region.Y = unknown_int_839624 + 0x45;
        tip.Region.Width = 8;
        tip.Region.Height = unknown_int_abcd70;
        ToolTips->Remove(999);
        ToolTips->Add(tip);
    }
}
