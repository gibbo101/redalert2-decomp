// LightConvertClass *IsometricTileTypeClass::Find_Or_Make_Drawer(int red, int green, int blue) (0x00529590)
// The tile drawer already made for these tints, else a new one added to the list (the first
// drawer, at normal light, gets the blitters).
#include "shared/isometric_tile_type.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??0LightConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@HHH_NPBEH@Z=00538860
// @ref ?Clamp_Tile_RGB@@YIXAAH00@Z=005385a0
// @ref ?unknown_palette_837e10@@3VPaletteClass@@A=00837e10
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ??2@YAPAXI@Z=00782017

LightConvertClass *__fastcall IsometricTileTypeClass::Find_Or_Make_Drawer(int red, int green, int blue)
{
    LightConvertClass *drawer;

    if (unknown_surface_839950 == 0) {
        return 0;
    }

    if (red == 1000 && green == 1000 && blue == 1000 && unknown_LightConvertClass_list_00832398.Count() != 0) {
        return unknown_LightConvertClass_list_00832398[0];
    }

    Clamp_Tile_RGB(red, green, blue);

    for (int i = 1; i < unknown_LightConvertClass_list_00832398.Count(); i++) {
        drawer = unknown_LightConvertClass_list_00832398[i];
        if (drawer->Red == red && drawer->Green == green && drawer->Blue == blue) {
            return drawer;
        }
    }

    int shadows = 53;
    if (red + green + blue < 2000) {
        shadows = 27;
    }
    drawer = new LightConvertClass(IsoTilePalette, unknown_palette_837e10, unknown_surface_839950, red, green, blue,
        unknown_LightConvertClass_list_00832398.Count() != 0, 0, shadows);
    unknown_LightConvertClass_list_00832398.Add(drawer);

    return drawer;
}
