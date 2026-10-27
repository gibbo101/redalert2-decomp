// Cell const *InfantryTypeClass::unknown_slot36(int arg1) const (0x0050A000)
// The occupation list: the origin cell and the end marker.
#include "shared/infantry_type.hpp"
// @ref _?$S40@?1??unknown_slot36@InfantryTypeClass@@UBEPBVCell@@H@Z@4EA=00a411a0
// @ref _$E41=0050a060
// @ref _?unknown_list@?1??unknown_slot36@InfantryTypeClass@@UBEPBVCell@@H@Z@4QBUUnknownStaticCell@@B=00a4117c
// @ref _atexit=0078298a

Cell const *InfantryTypeClass::unknown_slot36(int arg1) const
{
    static UnknownStaticCell const unknown_list[] = {Cell(0, 0), Cell(0x7FFF, 0x7FFF)};
    return &unknown_list[0].Cell;
}
