// int IsometricTileTypeClass::unknown_slot16() const (0x0052E6A0): the type's index.
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"

int IsometricTileTypeClass::unknown_slot16() const
{
    return ArrayIndex;
}
