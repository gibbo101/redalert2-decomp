// Cell const *ObjectTypeClass::unknown_slot36(int arg1) const (0x005D5D90)
// The default occupation list: the origin cell, then the 0x7FFF end marker
// (a function-local static array registered with atexit on first use).
#include "shared/object_type.hpp"
// @ref _?$S47@?1??unknown_slot36@ObjectTypeClass@@UBEPBVCell@@H@Z@4EA=00a72fd8
// @ref _?unknown_list@?1??unknown_slot36@ObjectTypeClass@@UBEPBVCell@@H@Z@4QBUUnknownStaticCell@@B=00a72fb0
// @ref _atexit=0078298a
// @ref _$E48=005d5df0

Cell const *ObjectTypeClass::unknown_slot36(int arg1) const
{
    static UnknownStaticCell const unknown_list[] = {Cell(0, 0), Cell(0x7FFF, 0x7FFF)};
    return &unknown_list[0].Cell;
}
