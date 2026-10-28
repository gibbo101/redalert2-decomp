// Cell const *OverlayTypeClass::unknown_slot36(int arg1) const (0x005DC800)
// The occupation list: the origin cell, then the 0x7FFF end marker (a
// function-local static registered with atexit on first use).
#include "shared/overlay_type.hpp"
// @ref _?$S40@?1??unknown_slot36@OverlayTypeClass@@UBEPBVCell@@H@Z@4EA=00a73188
// @ref _$E41=005dc860
// @ref _?unknown_list@?1??unknown_slot36@OverlayTypeClass@@UBEPBVCell@@H@Z@4QBUUnknownStaticCell@@B=00a7318c
// @ref _atexit=0078298a

Cell const *OverlayTypeClass::unknown_slot36(int arg1) const
{
    static UnknownStaticCell const unknown_list[] = {Cell(0, 0), Cell(0x7FFF, 0x7FFF)};
    return &unknown_list[0].Cell;
}
