// void CCToolTip::Hide(ToolTipRecord *record) (0x0046E1D0, slot 2)
// When the tip sits over the tactical area, flags the screen for a redraw,
// then clears the base record.
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Hide@ToolTipManager@@UAEXPAUToolTipRecord@@@Z=006ebd90
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_rect_839620@@3VRect@@A=00839620
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_flag_8373c3@@3_NA=008373c3
// @ref ?unknown_flag_8373c2@@3_NA=008373c2

void CCToolTip::Hide(ToolTipRecord *record)
{
    if (unknown_flag_a40b30 == true) {
        if (record->unknown_00 >= unknown_rect_839630.X + unknown_rect_839630.Width) {
            unknown_flag_8373c2 = true;
            unknown_flag_8373c3 = true;
        }
    } else if (record->unknown_00 <= unknown_rect_839620.X + unknown_rect_839620.Width) {
        unknown_flag_8373c2 = true;
        unknown_flag_8373c3 = true;
    }
    Map.GScreenClass::Flag_To_Redraw(0);
    ToolTipManager::Hide(record);
}
