#include "shared/mouse_class.hpp"
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Save_Delay@ToolTipManager@@QAEXXZ=006eb810
// @ref ?Set_Delay@ToolTipManager@@QAEXH@Z=006eb800
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0

extern bool unknown_flag_abcd84;                        // 0x00ABCD84

void SidebarClass::StripClass::SelectClass::Mouse_Enter()
{
    ToolTips->Save_Delay();
    ToolTips->Set_Delay(0);
    unknown_34 = true;
    Strip->unknown_38 = true;
    Map.Flag_To_Redraw(false);
    Map.unknown_4ee3 = true;
    unknown_flag_abcd84 = true;
}
