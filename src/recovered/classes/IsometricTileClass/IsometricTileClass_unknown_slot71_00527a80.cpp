// bool IsometricTileClass::unknown_slot71(int mark) (0x00527A80)
// Takes the tile off the map (mark 0) or puts it on (marks 1 and 3): for
// every cell of the type's grid that has an image tile, the cell's tile
// index, sub-tile and height are reset or set, its smudge and overlay are
// cleared (removing the overlay's cell animation sitting on the cell) and the
// cell and its four straight neighbours are recomputed. Placing a tile then
// deletes the object (the tile lives on in the cells).
#include "shared/isometric_tile.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_func_52b6f0@IsometricTileTypeClass@@QAEDH@Z=0052b6f0
// @ref ?unknown_471d10@CellClass@@QAEXXZ=00471d10
// @ref ?unknown_tileset_a52ee8@@3HA=00a52ee8
// @ref ?unknown_tileset_a52eec@@3HA=00a52eec
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?unknown_tileset_a6e038@@3HA=00a6e038

bool IsometricTileClass::unknown_slot71(int mark)
{
    IsoTileImageStruct *image = (IsoTileImageStruct *)unknown_slot26();
    if (image == 0 || !ObjectClass::unknown_slot71(mark)) {
        return false;
    }
    for (int row = 0; row < Type->unknown_2b8; row++) {
        for (int column = 0; column < Type->unknown_2b4; column++) {
            Cell cell = XY_Cell(column, row) + unknown_slot104();
            if (!Map.Unknown_0054AAB0(cell)) {
                continue;
            }
            CellClass &here = Map[cell];
            int index = Type->unknown_2b4 * row + column;
            if (image->Tiles[index] == 0) {
                continue;
            }
            if (mark == 0) {
                if (here.IsoTileIndex == Type->ArrayIndex && (unsigned char)here.unknown_11a == index) {
                    here.IsoTileIndex = 0xFFFF;
                    here.unknown_11a = 0;
                    here.unknown_11b -= ((IsoTileCellStruct *)image->Tiles[index])->unknown_28;
                }
            } else if (mark == 1 || mark == 3) {
                if (Type->ArrayIndex == unknown_tileset_a52f00) {
                    here.IsoTileIndex = 0xFFFF;
                    here.unknown_11a = 0;
                } else {
                    here.IsoTileIndex = Type->ArrayIndex;
                    here.unknown_11a = index;
                    here.unknown_11c = Type->unknown_func_52b6f0(index);
                    if (here.IsoTileIndex == unknown_tileset_a6e038 + 5) {
                        switch ((unsigned char)here.unknown_11a) {
                        case 0:
                        case 3:
                        case 6:
                        case 9:
                            here.IsoTileIndex = unknown_tileset_a6e018 + 1;
                            here.unknown_11a = 0;
                        }
                    }
                    if (here.IsoTileIndex == unknown_tileset_a52ee8 + 5) {
                        switch ((unsigned char)here.unknown_11a) {
                        case 0:
                        case 3:
                        case 6:
                        case 9:
                            here.IsoTileIndex = unknown_tileset_a52eec + 1;
                            here.unknown_11a = 0;
                        }
                    }
                    if (here.IsoTileIndex == unknown_tileset_a6e038 + 8 && (unsigned char)here.unknown_11a <= 3) {
                        here.IsoTileIndex = unknown_tileset_a6e018;
                        here.unknown_11a = 0;
                    }
                    if (here.IsoTileIndex == unknown_tileset_a52ee8 + 8 && (unsigned char)here.unknown_11a <= 3) {
                        here.IsoTileIndex = unknown_tileset_a52eec;
                        here.unknown_11a = 0;
                    }
                }
                here.SmudgeIndex = -1;
                here.SmudgeData = 0;
                if (here.OverlayIndex >= 0x1B && here.OverlayIndex < 0x26) {
                    here.unknown_140 &= ~0x20000;
                    CoordStruct spot = here.Center_Coord() + CoordStruct(0x180, 0x180, 0);
                    for (int i = 0; i < Anims.Count(); i++) {
                        AnimClass *anim = Anims[i];
                        if (anim->Class == unknown_overlay_types_a35de8[here.OverlayIndex]->unknown_26c) {
                            CoordStruct coord = anim->Coord;
                            if (coord == spot) {
                                delete anim;
                                break;
                            }
                        }
                    }
                }
                here.OverlayIndex = -1;
                here.OverlayData = 0;
                here.unknown_11b += ((IsoTileCellStruct *)image->Tiles[index])->unknown_28;
                here.unknown_471d10();
                here.Adjacent_Cell(0).unknown_471d10();
                here.Adjacent_Cell(2).unknown_471d10();
                here.Adjacent_Cell(4).unknown_471d10();
                here.Adjacent_Cell(6).unknown_471d10();
            }
            here.Unknown_00472540(-1);
        }
    }
    if (mark == 1 || mark == 3) {
        unknown_74 = false;
        delete this;
    }
    return true;
}
