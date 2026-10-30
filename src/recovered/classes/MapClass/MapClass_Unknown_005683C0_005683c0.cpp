// bool MapClass::Unknown_005683C0(CoordStruct const &coord) (0x005683C0)
// Whether a lepton position is fogged (TibSun Is_Fogged): never for a
// defeated player watching a multiplayer game (game mode not 0, player
// +0x13D and 0x00A3D548 set); otherwise the projected cell (and on an odd
// level its facing-3 neighbour) lacks +0x140 bit 1.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"

bool MapClass::Unknown_005683C0(CoordStruct const &coord)
{
    CellClass *cellptr;
    if (unknown_game_mode_a3d298 == 0 || !unknown_player_a35db4->unknown_13d || !unknown_int_a3d548) {
        int level = coord.Z / unknown_geometry_g;
        if ((level & 1) != 0) {
            int offset = level / 2 + 1;
            Cell cell = Cell(coord.X / 256, coord.Y / 256);
            cellptr = &Map[Cell(cell.X - offset, cell.Y - offset)];
            if (cellptr->unknown_140 & 2) {
                return false;
            }
            cellptr = &cellptr->Adjacent_Cell(3);
        } else {
            int offset = level / 2;
            Cell cell = Cell(coord.X / 256, coord.Y / 256);
            cellptr = &Map[Cell(cell.X - offset, cell.Y - offset)];
        }
        if (!(cellptr->unknown_140 & 2)) {
            return true;
        }
    }
    return false;
}
