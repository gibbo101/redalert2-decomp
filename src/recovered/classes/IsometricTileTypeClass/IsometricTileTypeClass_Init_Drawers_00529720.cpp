// void IsometricTileTypeClass::Init_Drawers() (0x00529720): frees every tile drawer, makes the
// normal-light one again, and makes the dummy cell and every map cell pick theirs anew.
#include "shared/isometric_tile_type.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
// @ref ??0LightConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@HHH_NPBEH@Z=00538860
// @ref ?unknown_palette_837e10@@3VPaletteClass@@A=00837e10
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?Init_Drawer@CellClass@@QAEXPAVLightConvertClass@@HHHHH@Z=004790f0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

void IsometricTileTypeClass::Init_Drawers()
{
    for (int i = 0; i < unknown_LightConvertClass_list_00832398.Count(); i++) {
        LightConvertClass *drawer = unknown_LightConvertClass_list_00832398[i];
        delete drawer;
        unknown_LightConvertClass_list_00832398.Delete(i);
        i--;
    }

    unknown_LightConvertClass_list_00832398.Add(new LightConvertClass(IsoTilePalette, unknown_palette_837e10,
        unknown_surface_839950, 1000, 1000, 1000, false, 0, 53));

    unknown_dummy_cell_a6f9f8.unknown_34 = 0;
    unknown_dummy_cell_a6f9f8.Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);

    Map.Unknown_0055A550();
    CellClass *cell = Map.Unknown_0055A490();
    while (cell != 0) {
        cell->unknown_34 = 0;
        cell = Map.Unknown_0055A490();
    }
}
// @ref ??_E?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ??_G?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??_ESubzoneTrackingStruct@@QAEPAXI@Z=0040afa0
// @ref ??_7?$VectorClass@USubzoneConnectionStruct@@@@6B@=0079a76c
