// bool VeinholeMonsterClass::Can_Spawn_At(Cell const &cell) (0x00710A60)
// True while the global at 0x00A40774 is positive; otherwise only when no
// monster is within 2 cells and the 3x3 block around the cell has no blocked
// cell, no occupier list and the same level as the cell (+0x11B).
#include "shared/veinhole.hpp"
#include "shared/house.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_a40774@@3HA=00a40774

extern int unknown_a40774;

bool __fastcall VeinholeMonsterClass::Can_Spawn_At(::Cell const &cell)
{
    if (unknown_a40774 > 0) {
        return true;
    }
    for (int index = Array.Count() - 1; index >= 0; index--) {
        if (abs(cell.X - Array[index]->Cell.X) < 3 && abs(cell.Y - Array[index]->Cell.Y) < 3) {
            return false;
        }
    }
    int level = Map[cell].unknown_11b;
    if (level < 1) {
        return false;
    }
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            ::Cell neighbor = ::Cell(cell.X + x, cell.Y + y);
            CellClass *near_cell = &Map[neighbor];
            if (near_cell->unknown_11c || near_cell->unknown_ec != 0 || near_cell->unknown_11b != level) {
                return false;
            }
        }
    }
    return true;
}
