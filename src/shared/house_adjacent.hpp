// The cell next to `cell` toward an 8-way facing for House.CPP (TibSun
// Adjacent_Cell: the cell is the left operand of the point sum). A FacingType
// overload, so the int form in shared/infantry.hpp keeps its own units' shape.
#ifndef RA2_SHARED_HOUSE_ADJACENT_HPP
#define RA2_SHARED_HOUSE_ADJACENT_HPP

#include "shared/adjacent_cell.hpp"
#include "shared/dir_type.hpp"

inline Cell Adjacent_Cell(Cell const &cell, FacingType dir)
{
    return cell + AdjacentCell[(int)dir & 7];
}

#endif
