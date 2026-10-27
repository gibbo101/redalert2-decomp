// The cell offsets of the eight facings (0x00851A70; Westwood's
// AdjacentCell), declared once for shared/cell.hpp, shared/display.hpp,
// shared/aircraft.hpp, shared/infantry.hpp and shared/terrain.hpp (each keeps
// its guarded Adjacent_Cell helper).
#ifndef RA2_SHARED_ADJACENT_CELL_HPP
#define RA2_SHARED_ADJACENT_CELL_HPP

#include "shared/coord.hpp"

extern Cell const AdjacentCell[8];

#endif
