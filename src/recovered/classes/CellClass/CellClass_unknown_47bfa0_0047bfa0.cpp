// int CellClass::unknown_47bfa0(int house) (0x0047BFA0): -1 unless the cell's unknown_dc mask has the
// house's bit, else a mask of the facings whose adjacent cell has it.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"

int CellClass::unknown_47bfa0(int house)
{
    int bit = 1 << house;
    if (!(unknown_dc & bit)) {
        return -1;
    }
    int bits = 0;
    for (int facing = 0; facing < 8; facing++) {
        CellClass &cell = Adjacent_Cell(facing);
        if (cell.unknown_dc & bit) {
            bits |= 1 << facing;
        }
    }
    return bits;
}
