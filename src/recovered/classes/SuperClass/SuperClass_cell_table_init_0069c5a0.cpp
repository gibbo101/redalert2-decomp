// Dynamic initializer (0x0069C5A0) of the cell offset table at 0x00ABD7A0:
// the cell itself, then its eight neighbours clockwise from east.
// @ref _unknown_cells_abd7a0=00abd7a0
#include "shared/super.hpp"

Cell const unknown_cells_abd7a0[9] = {
    Cell(0, 0),
    Cell(1, 0),
    Cell(1, -1),
    Cell(0, -1),
    Cell(-1, -1),
    Cell(-1, 0),
    Cell(-1, 1),
    Cell(0, 1),
    Cell(1, 1)
};
