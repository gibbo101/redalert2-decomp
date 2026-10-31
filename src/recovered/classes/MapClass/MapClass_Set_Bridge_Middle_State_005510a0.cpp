// void MapClass::Set_Bridge_Middle_State(Cell const &cell, int new_tile, int match_tile,
//     int cell_height, bool recursive) (0x005510A0)
// Gives a bridge middle cell a new tile (TibSun name): the first call redraws
// the cell's screen area (0x006A29D0, 0x006A3020) and stops when the tile is
// already new_tile; a changed cell recalculates (0x00472540), updates the radar
// (0x00631570) and passes the change on to each neighbour that shows the old tile.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"

void MapClass::Set_Bridge_Middle_State(Cell const &cell, int new_tile, int match_tile, int cell_height, bool recursive)
{
    CellClass *cellptr = &Map[cell];
    int old_tile;
    if (!recursive) {
        Point2D point;
        CoordStruct coord;
        coord.X = cell.X * 256 + 128;
        coord.Y = cell.Y * 256 + 128;
        coord.Z = 0;
        unknown_tactical_83996c->Unknown_006A29D0(coord, point);
        point.Y -= 15 * cellptr->unknown_11b;
        unknown_tactical_83996c->Register_Dirty_Area(Rect(point.X - 128, point.Y - 128, 256, 256), 0);
        old_tile = cellptr->IsoTileIndex;
        if (new_tile == old_tile) {
            return;
        }
    } else {
        old_tile = match_tile;
    }

    if (cellptr->IsoTileIndex != new_tile) {
        cellptr->IsoTileIndex = new_tile;
        cellptr->Unknown_00472540(cell_height);
        Map.Unknown_00631570(cellptr->MapCoords);
        int facing = 0;
        for (int i = 0; i < 8; i++) {
            Cell adjacent = Adjacent_Cell(cell, facing);
            CellClass *c = &Map[adjacent];
            if (c->IsoTileIndex == old_tile) {
                Set_Bridge_Middle_State(adjacent, new_tile, old_tile, cell_height, true);
            }
            facing = (facing + 1) & 7;
        }
    }
}
