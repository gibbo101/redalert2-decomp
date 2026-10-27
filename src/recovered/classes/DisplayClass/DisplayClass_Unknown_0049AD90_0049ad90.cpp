// bool DisplayClass::Unknown_0049AD90(Cell const &from, Cell const &to, int speed, int arg4, int arg5) (0x0049AD90)
// Whether a move between two cells is open: always for speed 4; otherwise
// both cells must be enterable (0x00478760) and hold no object (0x00471660).
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_00478760@CellClass@@QAE_NH_N0HHH0@Z=00478760
// @ref ?Unknown_00471660@CellClass@@QAEPAVObjectClass@@ABUPoint2D@@HH@Z=00471660

bool DisplayClass::Unknown_0049AD90(Cell const &from, Cell const &to, int speed, int arg4, int arg5)
{
    if (speed == 4) {
        return true;
    }
    if (!(*this)[from].Unknown_00478760(speed, true, true, -1, 0, -1, true)) {
        return false;
    }
    if (!(*this)[to].Unknown_00478760(speed, true, true, arg4, arg5, -1, true)) {
        return false;
    }
    if ((*this)[from].Unknown_00471660(Point2D(0, 0), 0, 0)) {
        return false;
    }
    return (*this)[to].Unknown_00471660(Point2D(0, 0), 0, 0) == 0 ? true : false;
}
