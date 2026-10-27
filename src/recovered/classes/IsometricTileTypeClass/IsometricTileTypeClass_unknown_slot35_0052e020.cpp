// ObjectClass *IsometricTileTypeClass::unknown_slot35(HouseClass *house) const (0x0052E020, slot 35)
// A new tile of this type at no cell, loading the type's image first when
// it is missing and allowed (unknown_2c4).
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/isometric_tile.hpp"
// @ref ??0IsometricTileClass@@QAE@HABVCell@@@Z=00527ed0
// @ref ?unknown_func_52b560@IsometricTileTypeClass@@QAEXXZ=0052b560
// @ref ?unknown_cell_a52eac@@3VCell@@B=00a52eac

// The "no cell" position (0x00A52EAC; hypothesis).
extern Cell const unknown_cell_a52eac;

ObjectClass *IsometricTileTypeClass::unknown_slot35(HouseClass *house) const
{
    if (unknown_a4 == 0 && unknown_2c4) {
        const_cast<IsometricTileTypeClass *>(this)->unknown_func_52b560();
    }
    return new IsometricTileClass(ArrayIndex, unknown_cell_a52eac);
}
