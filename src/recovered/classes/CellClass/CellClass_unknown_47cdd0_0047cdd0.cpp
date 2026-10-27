// bool CellClass::unknown_47cdd0() const (0x0047CDD0): false when +0x11C is
// set or a building occupies the cell, else the first flag of the cell's
// 0x00850EC0 land record.
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_lands_850ec0@@3PAUUnknownCellLand@@A=00850ec0

bool CellClass::unknown_47cdd0() const
{
    if (unknown_11c) {
        return false;
    }
    if (unknown_4717b0() != 0) {
        return false;
    }
    return unknown_lands_850ec0[unknown_ec].unknown_00;
}
