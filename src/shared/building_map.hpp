// The building layer's cell lookup through Map (kept out of
// shared/building.hpp: shared/map_view.hpp must follow any full screen layer
// header, and the Building unit includes the full shared/gscreen.hpp
// (BuildingClass slot 52) after building.hpp, so its Map users include
// gscreen.hpp before this header. That unit's only counter-numbered symbols
// are its header statics, which come first).
#ifndef RA2_SHARED_BUILDING_MAP_HPP
#define RA2_SHARED_BUILDING_MAP_HPP

#include "shared/building.hpp"
#include "shared/map_view.hpp"

// The cell at a cell position, taken by value (slots 160/161 copy the
// position into the argument; shared/map_cell_view.hpp's Map_Cell takes a
// reference).
class CellClass;
#ifndef RA2_CELL_AT_CELL
#define RA2_CELL_AT_CELL
inline CellClass &Cell_At(Cell cell)
{
    return Map[cell];
}
#endif

#endif
