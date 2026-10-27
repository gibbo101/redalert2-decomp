// static void __fastcall TerrainClass::Write_INI(CCINIClass &ini) (0x006E4380)
// Rewrites the [Terrain] section ("x + y * 1000=type") from the terrain
// objects that are on the map and marked for saving (unknown_7d).
#include "shared/terrain.hpp"
// @ref ?unknown_terrain_section_7ad390@@3PBDB=007ad390
// @ref _sprintf=007820f4

void __fastcall TerrainClass::Write_INI(CCINIClass &ini)
{
    ini.Clear(unknown_terrain_section_7ad390);
    for (int index = 0; index < Terrains.Count(); index++) {
        TerrainClass *terrain = Terrains[index];
        if (terrain != 0 && !terrain->unknown_76 && terrain->unknown_7d) {
            Cell cell = terrain->unknown_slot104();
            char entry[12];
            sprintf(entry, "%d", cell.X + cell.Y * 1000);
            ini.Put_String(unknown_terrain_section_7ad390, entry, terrain->Class->ID);
        }
    }
}
