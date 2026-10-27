// wchar_t const *CCToolTip::Get_Text(int id) (0x0046E470, slot 5)
// The text the game screen has for the tip id; none while the mouse reports a negative state.
#include "shared/tool_tip.hpp"
#include "shared/mouse.hpp"
#include "shared/map_view.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_slot33@TabClass@@UAEPBGH@Z=006a20b0

wchar_t const *CCToolTip::Get_Text(int id)
{
    if (WWMouse->Get_Mouse_State() < 0) {
        return 0;
    }
    return Map.TabClass::unknown_slot33(id);
}
