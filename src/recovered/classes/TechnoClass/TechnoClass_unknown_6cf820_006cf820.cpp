// bool TechnoClass::unknown_6cf820() (0x006CF820)
// The same test as 0x006CF670 with flag 0x400 in place of 0x100 (a second
// kind of bridge cell; hypothesis): whether the object (off a bridge, +0x79)
// stands on or next to such a cell.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/foot.hpp"
#include "shared/techno_map.hpp"
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

extern Cell const AdjacentCell[8];

bool TechnoClass::unknown_6cf820()
{
    Cell position = unknown_slot104();
    UnknownCellClass *here = (UnknownCellClass *)&Map[position];
    if (here != 0 && !unknown_79) {
        UnknownCellClass *south = (UnknownCellClass *)&Map[(AdjacentCell[4] + position)];
        UnknownCellClass *north = (UnknownCellClass *)&Map[(AdjacentCell[0] + position)];
        UnknownCellClass *east = (UnknownCellClass *)&Map[(AdjacentCell[2] + position)];
        UnknownCellClass *west = (UnknownCellClass *)&Map[(AdjacentCell[6] + position)];
        if ((here->Flags & 0x400) != 0
            || (south != 0 && (south->Flags & 0x400) != 0 && (south->Flags & 0x800) != 0)
            || (west != 0 && (west->Flags & 0x400) != 0 && (west->Flags & 0x800) == 0)
            || (east != 0 && (east->Flags & 0x400) != 0 && (east->Flags & 0x800) == 0)
            || (north != 0 && (north->Flags & 0x400) != 0 && (north->Flags & 0x800) != 0)) {
            return true;
        }
    }
    return false;
}
