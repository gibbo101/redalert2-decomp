// void MapClass::Unknown_00562F50(CellClass *cell) (0x00562F50)
// Collapses the high bridge whose tile covers `cell`: the east-west (tile set 0xA6E0F8, 6 x ? cells)
// or north-south (tile set +1) bridge tile is replaced by its wrecked twin, the two end pieces
// (tile sets 0xA6E038 +0/+1, +3/+2) are placed, the zones of the tile's cells are rebuilt, the
// screen area is redrawn and grey debris (XGRYMED1/XGRYMED2/XGRYSML1) falls over the span.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/map_techno.hpp"
#include "shared/id_source.hpp"
#include "shared/tactical.hpp"
#include "shared/tileset_index.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?AnimTypes@@3V?$DynamicVectorClass@PAVAnimTypeClass@@@@A=008661e0
// @ref ?From_Name@AnimTypeClass@@SIHPBD@Z=00425640
// @ref ?Unknown_006D7C80@@YIXPAVCellClass@@@Z=006d7c80
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref _unknown_geometry_g=00a6fc30
// @ref ??_C@_08OHBM@XGRYMED1?$AA@=007e0870
// @ref ??_C@_08BIKF@XGRYMED2?$AA@=007e0864
// @ref ??_C@_08GCKA@XGRYSML1?$AA@=007e0858

void MapClass::Unknown_00562F50(CellClass *cell)
{
    if (cell->IsoTileIndex == unknown_tileset_a6e0f8) {
        Cell origin = cell->MapCoords + Cell(-((unsigned char)cell->unknown_11a % 6), -((unsigned char)cell->unknown_11a / 6));

        ObjectClass *object = IsoTileTypes[unknown_tileset_a6e0f8]->unknown_slot35(0);
        object->unknown_slot103(origin);
        object->unknown_76 = false;
        object->unknown_74 = true;
        object->unknown_slot71(0);
        delete object;

        ObjectClass *slope1 = IsoTileTypes[unknown_tileset_a6e038]->unknown_slot35(0);
        slope1->unknown_slot53(origin, 0);
        ObjectClass *slope2 = IsoTileTypes[unknown_tileset_a6e038 + 1]->unknown_slot35(0);
        slope2->unknown_slot53((Cell)(origin + Cell(3, 0)), 0);

        Unknown_0054EBD0();

        IsometricTileTypeClass *isotype = IsoTileTypes[unknown_tileset_a6e0f8];
        IsoTileImageStruct *image = (IsoTileImageStruct *)isotype->unknown_slot39();

        int x;
        int y;
        for (y = 0; y < isotype->unknown_2b8; y++) {
            for (x = 0; x < isotype->unknown_2b4; x++) {
                Cell here = origin + Cell(x, y);
                if (image->Tiles[y * isotype->unknown_2b4 + x] != 0 && Unknown_0055A660(here, true)) {
                    Fine_Subzone(here) = 0;
                    Map[here].Unknown_00472540(-1);
                }
            }
        }
        for (y = 0; y < isotype->unknown_2b8; y++) {
            for (x = 0; x < isotype->unknown_2b4; x++) {
                Cell here = origin + Cell(x, y);
                if (image->Tiles[y * isotype->unknown_2b4 + x] != 0 && Unknown_0055A660(here, true)
                    && Fine_Subzone(here) == 0) {
                    Unknown_00566340(here);
                }
            }
        }
        for (y = 0; y < isotype->unknown_2b8; y++) {
            for (x = 0; x < isotype->unknown_2b4; x++) {
                Cell here = origin + Cell(x, y);
                if (image->Tiles[y * isotype->unknown_2b4 + x] != 0 && Unknown_0055A660(here, true)) {
                    Unknown_006D7C80(&Map[here]);
                    Map.Unknown_00631570(here);
                }
            }
        }

        Point2D start;
        Point2D end;
        unknown_tactical_83996c->Coord_To_Pixel(CoordStruct(origin, Map[origin].unknown_11b * unknown_geometry_g), start);
        unknown_tactical_83996c->Coord_To_Pixel(CoordStruct((Cell)(origin + Cell(5, 3)), Map[origin + Cell(5, 3)].unknown_11b * unknown_geometry_g), end);
        unknown_tactical_83996c->Register_Dirty_Area(Rect(start.X - 120, start.Y - 60, end.X - start.X + 240, end.Y - start.Y + 120), false);

        AnimTypeClass *med1 = AnimTypes[AnimTypeClass::From_Name("XGRYMED1")];
        AnimTypeClass *med2 = AnimTypes[AnimTypeClass::From_Name("XGRYMED2")];
        AnimTypeClass *sml1 = AnimTypes[AnimTypeClass::From_Name("XGRYSML1")];

        for (y = origin.Y; y < origin.Y + 3; y++) {
            for (x = origin.X; x < origin.X + 5; x++) {
                Cell piece = Cell(x, y);
                AnimTypeClass *anim = 0;
                for (int i = 0; i < 2; i++) {
                    switch (Random_Pick(0, 2)) {
                    case 0:
                        anim = med1;
                        break;
                    case 1:
                        anim = med2;
                        break;
                    case 2:
                        anim = sml1;
                        break;
                    }
                    CoordStruct coord;
                    new AnimClass(anim, coord = CoordStruct(piece, Map[piece].unknown_11b * unknown_geometry_g) + CoordStruct(Random_Pick(-12, 12), Random_Pick(-8, 8), 0), Random_Pick(0, 2), 1, 0x600, 0);
                }
            }
        }
    } else if (cell->IsoTileIndex == unknown_tileset_a6e0f8 + 1) {
        Cell origin = cell->MapCoords + Cell(-((unsigned char)cell->unknown_11a % 4), -((unsigned char)cell->unknown_11a / 4));

        ObjectClass *object = IsoTileTypes[unknown_tileset_a6e0f8 + 1]->unknown_slot35(0);
        object->unknown_slot103(origin);
        object->unknown_76 = false;
        object->unknown_74 = true;
        object->unknown_slot71(0);
        delete object;

        ObjectClass *slope1 = IsoTileTypes[unknown_tileset_a6e038 + 3]->unknown_slot35(0);
        slope1->unknown_slot53(origin, 0);
        ObjectClass *slope2 = IsoTileTypes[unknown_tileset_a6e038 + 2]->unknown_slot35(0);
        slope2->unknown_slot53((Cell)(origin + Cell(0, 3)), 0);

        Unknown_0054EBD0();

        IsometricTileTypeClass *isotype = IsoTileTypes[unknown_tileset_a6e0f8 + 1];
        IsoTileImageStruct *image = (IsoTileImageStruct *)isotype->unknown_slot39();

        int x;
        int y;
        int row_width;
        for (y = 0; y < isotype->unknown_2b8; y++) {
            row_width = isotype->unknown_2b4;
            for (x = 0; x < row_width; row_width = isotype->unknown_2b4, x++) {
                Cell here = origin + Cell(x, y);
                if (image->Tiles[y * row_width + x] != 0 && Unknown_0055A660(here, true)) {
                    Fine_Subzone(here) = 0;
                    Map[here].Unknown_00472540(-1);
                }
            }
        }
        for (y = 0; y < isotype->unknown_2b8; y++) {
            row_width = isotype->unknown_2b4;
            for (x = 0; x < row_width; row_width = isotype->unknown_2b4, x++) {
                Cell here = origin + Cell(x, y);
                if (image->Tiles[y * row_width + x] != 0 && Unknown_0055A660(here, true)) {
                    if (Fine_Subzone(here) == 0) {
                        Unknown_00566340(here);
                    }
                }
            }
        }
        for (y = 0; y < isotype->unknown_2b8; y++) {
            row_width = isotype->unknown_2b4;
            for (x = 0; x < row_width; row_width = isotype->unknown_2b4, x++) {
                Cell here = origin + Cell(x, y);
                if (image->Tiles[y * row_width + x] != 0 && Unknown_0055A660(here, true)) {
                    Unknown_006D7C80(&Map[here]);
                    Map.Unknown_00631570(here);
                }
            }
        }

        Point2D start;
        Point2D end;
        unknown_tactical_83996c->Coord_To_Pixel(CoordStruct(origin, Map[origin].unknown_11b * unknown_geometry_g), start);
        unknown_tactical_83996c->Coord_To_Pixel(CoordStruct((Cell)(origin + Cell(3, 5)), Map[origin + Cell(3, 5)].unknown_11b * unknown_geometry_g), end);
        unknown_tactical_83996c->Register_Dirty_Area(Rect(end.X - 120, start.Y - 60, start.X - end.X + 240, end.Y - start.Y + 120), false);

        AnimTypeClass *med1 = AnimTypes[AnimTypeClass::From_Name("XGRYMED1")];
        AnimTypeClass *med2 = AnimTypes[AnimTypeClass::From_Name("XGRYMED2")];
        AnimTypeClass *sml1 = AnimTypes[AnimTypeClass::From_Name("XGRYSML1")];

        for (y = origin.Y; y < origin.Y + 5; y++) {
            for (x = origin.X; x < origin.X + 3; x++) {
                Cell piece = Cell(x, y);
                AnimTypeClass *anim = 0;
                for (int i = 0; i < 2; i++) {
                    switch (Random_Pick(0, 2)) {
                    case 0:
                        anim = med1;
                        break;
                    case 1:
                        anim = med2;
                        break;
                    case 2:
                        anim = sml1;
                        break;
                    }
                    CoordStruct coord;
                    new AnimClass(anim, coord = CoordStruct(piece, Map[piece].unknown_11b * unknown_geometry_g) + CoordStruct(Random_Pick(-12, 12), Random_Pick(-8, 8), 0), Random_Pick(0, 2), 1, 0x600, 0);
                }
            }
        }
    }
}
