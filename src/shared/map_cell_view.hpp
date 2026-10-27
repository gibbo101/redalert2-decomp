// The map accessors used by the map-object units (Overlay.cpp, Smudge.cpp,
// SmudgeType.cpp, Terrain.cpp, ...). Including shared/map.hpp would pull in
// the screen layers and their static members, so the units reach cells
// through Map as shared/map_view.hpp declares it.
#ifndef RA2_SHARED_MAP_CELL_VIEW_HPP
#define RA2_SHARED_MAP_CELL_VIEW_HPP

#include "shared/unknown_globals.hpp"
#include "shared/object.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"

// The cell at a cell position (MapClass::operator[] 0x00548070).
inline CellClass &Map_Cell(Cell const &cell)
{
    return Map[cell];
}

// The isometric tile types; only the flag that allows smudges is known.
class IsometricTileTypeClass {
public:
    char unknown_000[0x2B0];
    bool unknown_2b0;                       // +0x2B0 (smudges allowed; hypothesis)
};
extern DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;

// A game flag the destructors test before ObjectClass slot 52 (0x00A40958;
// also declared by shared/bullet.hpp and shared/ms_message_box.hpp).

#endif
