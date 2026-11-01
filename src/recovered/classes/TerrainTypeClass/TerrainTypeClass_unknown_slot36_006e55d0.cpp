// Cell const *TerrainTypeClass::unknown_slot36(int arg1) const (0x006E55D0)
// The foundation's occupation list, else an empty list (only the 0x7FFF
// end marker; a function-local static registered with atexit on first use).
#include "shared/terrain_type.hpp"
// @ref _?$S56@?4??unknown_slot36@TerrainTypeClass@@UBEPBVCell@@H@Z@4EA=00ac0400
// @ref _$E57=006e5620
// @ref _?unknown_list@?4??unknown_slot36@TerrainTypeClass@@UBEPBVCell@@H@Z@4QBUUnknownStaticCell@@B=00ac03e0
// @ref _atexit=0078298a

Cell const *TerrainTypeClass::unknown_slot36(int arg1) const
{
    if (OccupyList != 0) {
        return OccupyList;
    }
    static UnknownStaticCell const unknown_list[] = {Cell(0x7FFF, 0x7FFF)};
    return &unknown_list[0].Cell;
}
