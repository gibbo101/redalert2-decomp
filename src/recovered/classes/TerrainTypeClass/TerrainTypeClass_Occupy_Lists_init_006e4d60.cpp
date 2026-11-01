// The foundation (occupy) lists of the terrain types, one per foundation size, each ended by
// Cell(0x7FFF, 0x7FFF) (TibSun terrtype.cpp's _OccupyLists, BSIZE_COUNT 22 rows of 10 cells; the
// rows after BSIZE_35 are empty). Its dynamic initializer is 0x006E4D60.
#include "shared/terrain_type.hpp"

Cell unknown_foundation_lists_ac0430[22][10] = {
    { Cell(0, 0), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(1, 0), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(0, 1), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(1, 0), Cell(0, 1), Cell(1, 1), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(1, 0), Cell(0, 1), Cell(1, 1), Cell(0, 2), Cell(1, 2), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(1, 0), Cell(2, 0), Cell(0, 1), Cell(1, 1), Cell(2, 1), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(1, 0), Cell(2, 0), Cell(0, 1), Cell(1, 1), Cell(2, 1), Cell(0, 2), Cell(1, 2), Cell(2, 2), Cell(0x7FFF, 0x7FFF) },
    { Cell(0, 0), Cell(1, 0), Cell(2, 0), Cell(3, 0), Cell(0, 1), Cell(1, 1), Cell(2, 1), Cell(3, 1), Cell(0x7FFF, 0x7FFF) },
};
// @ref ?unknown_foundation_lists_ac0430@@3PAY09VCell@@A=00ac0430
// @ref ??0Cell@@QAE@HH@Z=0042ad30
// @ref ??0Cell@@QAE@XZ=0045ecf0
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
