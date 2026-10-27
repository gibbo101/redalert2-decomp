// int TechnoClass::unknown_6cfda0() (0x006CFDA0)
// How a cliff next to the object raises its drawing depth: 2 when the cell
// to the facing-3 side is more than three levels above this one, 1 when
// the cell beyond that is, 0 when the object is on a bridge (+0x79) or
// neither is.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/foot.hpp"
#include "shared/techno_map.hpp"
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

extern Cell const AdjacentCell[8];

int TechnoClass::unknown_6cfda0()
{
    int result = 0;
    Cell position = unknown_slot104();
    UnknownCellClass *here = (UnknownCellClass *)&Map[position];
    if (!unknown_79) {
        UnknownCellClass *next = (UnknownCellClass *)&Map[(AdjacentCell[3] + unknown_slot104())];
        if (next != 0) {
            if (next->unknown_11b - here->unknown_11b >= 4) {
                result = 2;
            }
            Cell cell = next->unknown_24;
            next = (UnknownCellClass *)&Map[(AdjacentCell[3] + cell)];
            if (next != 0 && next->unknown_11b - here->unknown_11b >= 4) {
                return 1;
            }
        }
    }
    return result;
}
