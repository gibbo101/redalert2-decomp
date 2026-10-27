// BuildCat __fastcall BuildCat_From_Name(char const *name) (0x00457A80)
// The building AI category whose INI name matches (case-insensitive);
// 0 (DontCare) for an unknown name.
#include "shared/building_type.hpp"
// @ref ?unknown_buildcat_table_7cfc40@@3PAUUnknownBuildCatEntry@@A=007cfc40
// @ref __stricmp=00781f20

BuildCat __fastcall BuildCat_From_Name(char const *name)
{
    for (int index = 0; index < 6; index++) {
        if (_stricmp(unknown_buildcat_table_7cfc40[index].Name, name) == 0) {
            return (BuildCat)unknown_buildcat_table_7cfc40[index].Value;
        }
    }
    return (BuildCat)0;
}
