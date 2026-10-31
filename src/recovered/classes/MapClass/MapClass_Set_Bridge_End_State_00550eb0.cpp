// void MapClass::Set_Bridge_End_State(Cell const &cell, bool damaged, bool recursive) (0x00550EB0)
// Sets a bridge end cell's damaged flag (+0x140 bit 0x2000; TibSun name): the
// first call needs a tile whose sub tile is a random variant (0x0052B730) and
// redraws the cell's screen area; a change updates the radar (0x00631570) and
// passes on to each neighbour with the same tile.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_isotile.hpp"
// @ref ?unknown_func_52b730@IsometricTileTypeClass@@QAE_NH@Z=0052b730

void MapClass::Set_Bridge_End_State(Cell const &cell, bool damaged, bool recursive)
{
    CellClass *cellptr = &Map[cell];
    if (!recursive) {
        if (cellptr->IsoTileIndex == 0xFFFF || cellptr->IsoTileIndex == 0xFF) {
            return;
        }
        IsometricTileTypeClass *isotype = IsoTileTypes[cellptr->IsoTileIndex];
        if (!isotype->unknown_func_52b730((unsigned char)cellptr->unknown_11a)) {
            return;
        }
        Point2D point;
        CoordStruct coord;
        coord.X = cell.X * 256 + 128;
        coord.Y = cell.Y * 256 + 128;
        coord.Z = 0;
        unknown_tactical_83996c->Unknown_006A29D0(coord, point);
        point.Y -= 15 * cellptr->unknown_11b;
        unknown_tactical_83996c->Register_Dirty_Area(Rect(point.X - 128, point.Y - 128, 256, 256), 0);
    }

    if (damaged != (bool)((cellptr->unknown_140 >> 13) & 1)) {
        cellptr->unknown_140 = (cellptr->unknown_140 & ~0x2000) | ((damaged & 1) << 13);
        int ittype = cellptr->IsoTileIndex;
        Map.Unknown_00631570(cellptr->MapCoords);
        int facing = 0;
        for (int i = 0; i < 8; i++) {
            Cell adjacent = Adjacent_Cell(cell, facing);
            CellClass *c = &Map[adjacent];
            if (c->IsoTileIndex == ittype) {
                Set_Bridge_End_State(adjacent, damaged, true);
            }
            facing = (facing + 1) & 7;
        }
    }
}
