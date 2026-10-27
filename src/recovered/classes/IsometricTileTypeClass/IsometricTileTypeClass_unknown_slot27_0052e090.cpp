// CoordStruct IsometricTileTypeClass::unknown_slot27(CoordStruct const &coord) const (0x0052E090, slot 27)
// The coordinate unchanged.
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"

CoordStruct IsometricTileTypeClass::unknown_slot27(CoordStruct const &coord) const
{
    return coord;
}
