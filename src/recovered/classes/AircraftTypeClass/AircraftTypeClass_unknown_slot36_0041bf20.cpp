// Cell const *AircraftTypeClass::unknown_slot36(int arg1) const (0x0041BF20)
// The occupation list: the origin cell and the end marker.
#include "shared/aircraft_type.hpp"
// @ref _?$S46@?1??unknown_slot36@AircraftTypeClass@@UBEPBVCell@@H@Z@4EA=0083c51c
// @ref _$E47=0041bf80
// @ref _?unknown_list@?1??unknown_slot36@AircraftTypeClass@@UBEPBVCell@@H@Z@4QBUUnknownStaticCell@@B=0083c528
// @ref _atexit=0078298a

Cell const *AircraftTypeClass::unknown_slot36(int arg1) const
{
    static UnknownStaticCell const unknown_list[] = {Cell(0, 0), Cell(0x7FFF, 0x7FFF)};
    return &unknown_list[0].Cell;
}
