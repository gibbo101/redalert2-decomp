// static void __fastcall TerrainClass::Read_INI(CCINIClass &ini) (0x006E4260)
// Creates the terrain objects listed in the [Terrain] section ("cell=type";
// the cell number is x + y * 128 before format 4, x + y * 1000 after).
#include "shared/terrain.hpp"
// @ref ?unknown_terrain_section_7ad390@@3PBDB=007ad390
// @ref ?unknown_ini_format_a40d24@@3HA=00a40d24
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Find_Or_Make@TerrainTypeClass@@SIPAV1@PBD@Z=006e5a20
// @ref ??0TerrainClass@@QAE@PAVTerrainTypeClass@@ABUCell@@@Z=006e33d0
// @ref _atoi=00782dfd
// @ref ??2@YAPAXI@Z=00782017
// An INI entry naming a type: the type found or made, else defvalue
// (TibSun findmake.h TGet_Class).
template<class T>
inline T *TGet_Class(CCINIClass &ini, char const *section, char const *entry, T *defvalue)
{
    char buffer[128];

    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer)) != 0) {
        return T::Find_Or_Make(buffer);
    }

    return defvalue;
}

void __fastcall TerrainClass::Read_INI(CCINIClass &ini)
{
    int len = ini.Entry_Count(unknown_terrain_section_7ad390);

    for (int index = 0; index < len; index++) {
        char const *entry = ini.Get_Entry(unknown_terrain_section_7ad390, index);
        TerrainTypeClass *terrain = TGet_Class<TerrainTypeClass>(ini, unknown_terrain_section_7ad390, entry, 0);

        Cell cell;
        if (unknown_ini_format_a40d24 >= 4) {
            int val = atoi(entry);
            cell = Cell(val % 1000, val / 1000);
        } else {
            int val = atoi(entry);
            cell = Cell(val % 128, val / 128);
        }

        if (terrain != 0) {
            new TerrainClass(terrain, cell);
        }
    }
}
