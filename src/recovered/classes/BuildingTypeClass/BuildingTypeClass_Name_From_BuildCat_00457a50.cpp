// char const *__fastcall Name_From_BuildCat(BuildCat category) (0x00457A50)
// The INI name of a building AI category from the {name, value} table at
// 0x007CFC40 (DontCare, Tech, Power, Resource, Infrastructure, Combat);
// DontCare for an unknown value.
#include "shared/building_type.hpp"
// @ref ?unknown_buildcat_table_7cfc40@@3PAUUnknownBuildCatEntry@@A=007cfc40

char const *__fastcall Name_From_BuildCat(BuildCat category)
{
    for (int index = 0; index < 6; index++) {
        if (unknown_buildcat_table_7cfc40[index].Value == category) {
            return unknown_buildcat_table_7cfc40[index].Name;
        }
    }
    return unknown_buildcat_table_7cfc40[0].Name;
}
