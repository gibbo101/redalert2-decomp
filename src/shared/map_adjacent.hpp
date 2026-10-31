// The cell helpers of the Map unit (Map.CPP only: shared/display.hpp and
// shared/aircraft.hpp define Adjacent_Cell with the offset as the left operand
// under the same RA2_ADJACENT_CELL guard, and shared/object.hpp defines
// Coord_Cell, so this header is not for their units).
#ifndef RA2_SHARED_MAP_ADJACENT_HPP
#define RA2_SHARED_MAP_ADJACENT_HPP

#include "shared/coord.hpp"
#include "shared/adjacent_cell.hpp"

// The cell next to `cell` toward an 8-way facing (TibSun Adjacent_Cell: the cell
// is the left operand of TPoint2D<short>::operator+; the train bridge twins
// 0x00551470.. call its out-of-line copy 0x0042ADD0 that way).
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}
#endif

// The same step as int sums (XY_Cell): the low bridge span walks 0x0055E930,
// 0x0055EA50, 0x0055FA60 and 0x0055FB90 compile to these 32-bit adds where
// Adjacent_Cell's Cell sum gives 16-bit ones (name a hypothesis).
inline Cell Adjacent_Cell_XY(Cell const &cell, int facing)
{
    return XY_Cell(cell.X + AdjacentCell[facing & 7].X, cell.Y + AdjacentCell[facing & 7].Y);
}

// The cell containing a coordinate (as shared/object.hpp's Coord_Cell): 0x0055A300
// reads a returned coordinate in place through it.
inline Cell Coord_Cell(CoordStruct const &coord)
{
    Cell cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

#endif
