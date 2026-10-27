// int IsometricTileTypeClass::Size_Of() const (0x0052E690, slot 12)
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"

int IsometricTileTypeClass::Size_Of() const
{
    return sizeof(IsometricTileTypeClass);
}
