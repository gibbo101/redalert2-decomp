// RulesClass::Sides (0x0064BC10)
// @ref ??_C@_05NJEG@?5?5?$CFs?6?$AA@=007f163c
// @ref ??_C@_0BD@FIFF@Processing?5sides?4?6?$AA@=007f1654
// @ref ??_C@_0O@MAOP@Side?5?$CFd?3?5?$CFs?5?6?$AA@=007f1644
// @ref _RulesSection_Sides=007a9074
// @ref ??_C@_05HFA@Sides?$AA@=007eec54
// Makes (or finds) every side listed in [Sides], reads its house list and
// tells each listed house type its side.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/side.hpp"
#include "shared/house_type.hpp"
#include "shared/debug_printf.hpp"

bool RulesClass::Sides(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_Sides);
    Debug_Printf("Processing sides.\n");
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(RulesSection_Sides, index);
        int found = SideClass::Find_Index(entry);
        SideClass *side;
        if (found == -1) {
            side = new SideClass(entry);
        } else {
            side = ::Sides[found];
        }
        Debug_Printf("Side %d: %s \n", index, (char const *)side->ID);
        side->Houses = ini.Get_House_List(RulesSection_Sides, entry, side->Houses);
        for (int house = 0; house < side->Houses.Count(); house++) {
            int type = side->Houses[house];
            HouseTypes[type]->Side = ::Sides.ID(side);
            Debug_Printf("  %s\n", (char const *)HouseTypes[type]->ID);
        }
    }
    return count > 0;
}
