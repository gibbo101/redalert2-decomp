#include "shared/tool_tip.hpp"
void SidebarClass::StripClass::SelectClass::Mouse_Leave()
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Restore_Delay@ToolTipManager@@QAEXXZ=006eb820
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
{
    ToolTips->Restore_Delay();
    unknown_34 = false;
    Strip->unknown_38 = true;
    Map.Flag_To_Redraw(false);
    Map.unknown_4ee3 = true;
    unknown_flag_abcd84 = true;
}
