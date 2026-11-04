// void CellClass::Cell_Color(RGBClass &lowcolor, RGBClass &highcolor) const (0x004712C0): TibSun Cell_Color.
#include "shared/isometric_tile_type.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/overlay.hpp"
#include "shared/overlay_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/shape_file.hpp"
#include "shared/theater_type.hpp"
#include "shared/id_source.hpp"
#include "shared/tileset_index.hpp"
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?Clear_Icon@CellClass@@QBEHHH@Z=004767a0
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68


void CellClass::Cell_Color(RGBClass &lowcolor, RGBClass &highcolor) const
{
    if (Cell_Terrain() != 0) {
        lowcolor = RGBClass(200, 200, 160);
        highcolor = RGBClass(200, 200, 160);
        return;
    }

    if (unknown_4788d0()) {
        highcolor = lowcolor = OverlayTypes[24]->unknown_func_5dd000(0);
        return;
    }

    IsometricTileTypeClass *itype = (IsoTileIndex != 0xFFFF) ? IsoTileTypes[IsoTileIndex] : IsoTileTypes[unknown_tileset_a52f00];

    int overlay = OverlayIndex;
    if ((OverlayIndex != -1 && OverlayIndex != 100 && OverlayIndex != 101) || (OverlayIndex != -1 && OverlayIndex != 231 && OverlayIndex != 232)) {
        OverlayTypeClass *otype = OverlayTypes[overlay];

        if (!otype->Tiberium) {
            if ((overlay >= 74 && overlay <= 99) || (overlay >= 205 && overlay <= 230)) {
                lowcolor = OverlayTypes[overlay]->unknown_func_5dd000(1);
            } else {
                lowcolor = OverlayTypes[overlay]->unknown_func_5dd000(OverlayData);
            }
            highcolor = lowcolor;
            return;
        }

        if (otype->CellAnim != 0) {
            ShapeFileStruct const *shape = (ShapeFileStruct const *)otype->CellAnim->unknown_slot39();
            highcolor = lowcolor = shape->Get_Color(OverlayData);
            return;
        }

        if (OverlayClass::To_Tiberium(overlay) != -1) {
            lowcolor = RGBClass(170, 170, 130);
            highcolor = RGBClass(170, 170, 130);
            return;
        }
    }

    int tile = 0;
    if (IsoTileIndex != 0xFFFF) {
        if (itype->NumTileTypesInSet > 1) {
            if (itype->Is_Randomized((unsigned char)unknown_11a)) {
                tile = (unknown_140 >> 13) & 1;
            } else {
                int numtiles = itype->NumTileTypesInSet;
                tile = Clear_Icon(IsoTileIndex, numtiles);
            }
        }
    } else {
        int numtiles = itype->NumTileTypesInSet;
        tile = Clear_Icon(unknown_tileset_a52f00, numtiles);
    }

    IsometricTileTypeClass *next = itype->Next_Tile_From_Set(tile);
    if (next->unknown_a4 == 0 && next->unknown_2c4) {
        next->Load_Tile_Image();
    }

    IsoTileImageStruct const *image = (IsoTileImageStruct const *)next->unknown_a4;
    if (image->Tiles[(unsigned char)unknown_11a] != 0) {
        IsoTileCellStruct const *record = (IsoTileCellStruct const *)image->Tiles[(unsigned char)unknown_11a];
        RGBClass lowest(record->LowRed, record->LowGreen, record->LowBlue);
        lowest = RGBClass(NoInitClass()).Set(lowest, Theaters[unknown_id_source_a3d290->Theater].unknown_50);
        int red = lowest.Get_Red() >> 1;
        int green = lowest.Get_Green() >> 1;
        int blue = lowest.Get_Blue() >> 1;
        lowcolor = RGBClass(red, green, blue);
        highcolor = RGBClass(red, green, blue);
    } else {
        lowcolor = RGBClass(60, 60, 60);
        highcolor = RGBClass(60, 60, 60);
    }
}
