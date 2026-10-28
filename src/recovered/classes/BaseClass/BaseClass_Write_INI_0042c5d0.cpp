// void BaseClass::Write_INI(CCINIClass &ini, char const *section) (0x0042C5D0)
// PercentBuilt, NodeCount and each node "%03d" = type ID (or number),x,y.
#include "shared/base.hpp"
#include "shared/ccini_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
// @ref ??_C@_08NOHK@?$CFs?0?$CFd?0?$CFd?$AA@=007cf36c
// @ref ??_C@_08POMI@?$CFd?0?$CFd?0?$CFd?$AA@=007cf360
// @ref ??_C@_0N@BEF@PercentBuilt?$AA@=007cf350
// @ref ??_C@_09BKEM@NodeCount?$AA@=007cf344
// @ref ??_C@_04KAJP@?$CF03d?$AA@=007cf33c

void BaseClass::Write_INI(CCINIClass &ini, char const *section)
{
    ini.Put_Int(section, "PercentBuilt", PercentBuilt, 0);
    ini.Put_Int(section, "NodeCount", Nodes.Count(), 0);
    for (int index = 0; index < Nodes.Count(); index++) {
        char key[12];
        char buffer[128];
        sprintf(key, "%03d", index);
        if (Nodes[index].Type >= 0) {
            sprintf(buffer, "%s,%d,%d", (char const *)BuildingTypes[Nodes[index].Type]->ID, Nodes[index].Cell.X, Nodes[index].Cell.Y);
        } else {
            sprintf(buffer, "%d,%d,%d", Nodes[index].Type, Nodes[index].Cell.X, Nodes[index].Cell.Y);
        }
        ini.Put_String(section, key, buffer);
    }
}
