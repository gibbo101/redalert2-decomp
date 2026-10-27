// unsigned short IsometricTileTypeClass::unknown_func_52e360(int index, int value, bool second) const (0x0052E360)
// One entry of the colour tables rebuilt by unknown_func_52e3d0: table
// `index`, pair `value`, its first or second word.
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"

unsigned short IsometricTileTypeClass::unknown_func_52e360(int index, int value, bool second) const
{
    return unknown_274[index][value * 2 + (second != 0)];
}
