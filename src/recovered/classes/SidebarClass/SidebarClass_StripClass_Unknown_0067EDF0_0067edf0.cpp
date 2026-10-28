// bool SidebarClass::StripClass::Unknown_0067EDF0(int type, int id) (0x0067EDF0)
// Adds a buildable unless full or present, announcing new construction
// options (except type 31).
#include "shared/sidebar.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref ?unknown_flag_8373c3@@3_NA=008373c3
// @ref ?Unknown_0067ED10@StripClass@SidebarClass@@QAEXHH@Z=0067ed10
// @ref ??_C@_0BL@JFKB@EVA_NewConstructionOptions?$AA@=007f3e40

bool SidebarClass::StripClass::Unknown_0067EDF0(int type, int id)
{
    if (BuildableCount <= 75) {
        for (int index = 0; index < BuildableCount; index++) {
            if (Buildables[index].unknown_04 == type && Buildables[index].unknown_00 == id) {
                return false;
            }
        }
        if (!unknown_a40774 && type != 31) {
            Speech_Play_Name("EVA_NewConstructionOptions", -1, -1);
        }
        Unknown_0067ED10(type, id);
        unknown_38 = true;
        unknown_flag_8373c3 = true;
        return true;
    }
    return false;
}
