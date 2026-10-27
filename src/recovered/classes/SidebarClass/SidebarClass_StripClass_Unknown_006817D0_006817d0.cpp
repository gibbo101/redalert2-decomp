// bool SidebarClass::StripClass::Unknown_006817D0(UnknownFactory *factory) (0x006817D0)
// Drops a factory from the strip's icons (a building's placement is
// forgotten first); true when an icon used it. The strip stops counting as
// busy (+0x39) when no icon has a factory left.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
#include "shared/sidebar_building.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Get_Object@UnknownFactory@@QAEPAVObjectClass@@XZ=004b9930
// @ref ?Unknown_004B97C0@UnknownFactory@@QAEXXZ=004b97c0
// @ref ?Unknown_006F8A20@@YIXPAVBuildingClass@@@Z=006f8a20
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?unknown_flag_8373c3@@3_NA=008373c3


bool SidebarClass::StripClass::Unknown_006817D0(UnknownFactory *factory)
{
    if (factory && factory->Get_Object() && Is_Building(factory->Get_Object())) {
        Unknown_006F8A20(As_Building(factory->Get_Object()));
    }
    bool found = false;
    bool idle = true;
    for (int index = 0; index < BuildableCount; index++) {
        if (Buildables[index].Factory == factory) {
            factory->Unknown_004B97C0();
            Buildables[index].Factory = 0;
            found = true;
            Buildables[index].unknown_10 = 0;
        } else if (Buildables[index].Factory) {
            idle = false;
        }
    }
    if (found) {
        unknown_38 = true;
        Map.Flag_To_Redraw(false);
        unknown_flag_8373c3 = true;
    }
    if (idle) {
        unknown_39 = false;
    }
    return found;
}
