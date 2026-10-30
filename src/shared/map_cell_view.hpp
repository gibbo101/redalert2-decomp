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
class LightConvertClass;

// The cell at a cell position (MapClass::operator[] 0x00548070).
inline CellClass &Map_Cell(Cell const &cell)
{
    return Map[cell];
}

// The isometric tile types (a view of shared/isometric_tile_type.hpp, which
// these units cannot include beside it); only the flags at +0x2B0, +0x2D5
// and +0x2D6 are known.
class IsometricTileTypeClass {
public:
    char unknown_000[0x2B0];
    bool unknown_2b0;                       // +0x2B0 (smudges allowed; hypothesis)
    char unknown_2b1[0x2D5 - 0x2B1];
    bool unknown_2d5;                       // +0x2D5 (CellClass::unknown_47c200: false refuses the cell)
    bool unknown_2d6;                       // +0x2D6 (CellClass::unknown_478ba0: tiberium may grow on the tile)

    // 0x0052C230 (shared/isometric_tile_type.hpp; CellClass::unknown_4754b0).
    // The light converter with these tints, made when there is none yet (0x00529590; Westwood's
    // Find_Or_Make_Drawer; 0 without a palette).
    static LightConvertClass *__fastcall Find_Or_Make_Drawer(int red, int green, int blue);
    void unknown_func_52c230(LightConvertClass *drawer, int arg2, Surface *surface, int x, int y, Rect rect,
        int arg7, int arg8, int arg9, int arg10, int arg11, int arg12, int arg13, int arg14);
};
extern DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;

// A game flag the destructors test before ObjectClass slot 52 (0x00A40958;
// also declared by shared/bullet.hpp and shared/ms_message_box.hpp).

#endif
