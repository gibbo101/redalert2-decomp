#include "shared/sidebar_screen.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
bool SidebarClass::StripClass::Unknown_006816D0(int value, int type, int id)
{
    for (int index = 0; index < BuildableCount; index++) {
        if (Buildables[index].unknown_04 == type && Buildables[index].unknown_00 == id) {
            Buildables[index].Factory = (UnknownFactory *)value;
            unknown_39 = true;
            unknown_38 = true;
            Map.Flag_To_Redraw(false);
            return true;
        }
    }
    return false;
}
