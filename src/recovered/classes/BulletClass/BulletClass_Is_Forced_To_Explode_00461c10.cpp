// Forced-explosion decision00461C10. Fresh real-type source; no steering casts.
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/techno.hpp"
// @ref ?Unknown_004BBAF0@@=004bbaf0
// @ref ?unknown_level_height_850348@@=00850348
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00
bool BulletClass::Is_Forced_To_Explode_00461c10(CoordStruct &coord)
{
    coord = Coord;
    CellClass *cell = &Map[coord];
    if (Type->SubjectToCliffs || Type->SubjectToWalls) {
        CellClass *source = &Map[SourceCoords];
        CellClass *destination = &Map[TargetCoords];
        CellClass *previous = &Map[LastMapCoords];
        if (Unknown_004BBAF0(source, destination, previous, coord, Type, Owner == 0 ? 0 : Owner->House)) return true;
    }
    if (unknown_slot108() <= -unknown_level_height_850348 * 4) return true;
    if (Target != 0 && Type->FlakScatter) {
        CoordStruct current = Coord;
        if (current.Z < Target->unknown_slot22().Z && unknown_slot108() < 0) return true;
    }
    if (Type->Level && cell->unknown_slot20()) return true;
    if (Type->AA && Target != 0 && Target->unknown_slot21() && unknown_5d4c00(Target) < 0x80) return true;
    return false;
}
