// void CellClass::unknown_47be00() (0x0047BE00): walks the seven cells down
// the diagonal from this one; each whose level (+0x11B) is within two below
// 1, 3, .., 13 in turn loses flag 0x400000 of +0x140 and runs unknown_47be60.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_47be60@CellClass@@QAEXXZ=0047be60

void CellClass::unknown_47be00()
{
    Cell cell = MapCoords;
    for (int level = 1; level < 15; level += 2) {
        CellClass &other = Map[cell];
        if (other.unknown_11b >= level - 2 && other.unknown_11b <= level) {
            other.unknown_140 &= ~0x400000;
            other.unknown_47be60();
        }
        cell.X++;
        cell.Y++;
    }
}
