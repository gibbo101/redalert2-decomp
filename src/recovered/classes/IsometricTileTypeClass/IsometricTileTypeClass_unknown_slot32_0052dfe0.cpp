// bool IsometricTileTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x0052DFE0, slot 32)
// Places a tile of this type at the cell (ObjectTypeClass slot 32: create
// the object there); true when one was made.
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/isometric_tile.hpp"
// @ref ??0IsometricTileClass@@QAE@HABVCell@@@Z=00527ed0

bool IsometricTileTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    if (new IsometricTileClass(ArrayIndex, cell) != 0) {
        return true;
    }
    return false;
}
