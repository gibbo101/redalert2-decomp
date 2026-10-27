// The techno-level cell lookups through Map (kept out of shared/techno.hpp:
// shared/map_view.hpp must follow any full screen layer header, and the
// Techno unit includes the full shared/gscreen.hpp after techno.hpp; its Map
// users include gscreen.hpp before this header. That unit's only
// counter-numbered symbols are its header statics, which come first, so
// where gscreen.hpp's static member lands does not move them).
#ifndef RA2_SHARED_TECHNO_MAP_HPP
#define RA2_SHARED_TECHNO_MAP_HPP

#include "shared/techno.hpp"
#include "shared/map_view.hpp"

// The cell object at a coordinate (MapClass::operator[] 0x00548000).
inline UnknownCellClass *Map_Cell(CoordStruct const &coord)
{
    return (UnknownCellClass *)&Map[coord];
}
// The cell object at a cell position (MapClass::operator[] 0x00548070; named
// apart from map_cell_view.hpp's Map_Cell, which returns CellClass &).
inline UnknownCellClass *Map_Cell_At(Cell const &cell)
{
    return (UnknownCellClass *)&Map[cell];
}

#endif
