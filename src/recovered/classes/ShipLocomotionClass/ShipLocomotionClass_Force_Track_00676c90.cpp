// void __stdcall ShipLocomotionClass::Force_Track(int track, CoordStruct coord) (0x00676C90, ILocomotion 27)
// Puts the unit on a track at its start; with a coordinate it heads there
// (Start_Driver) and, when that succeeds, it is the destination at full speed.
#include "shared/ship_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ?unknown_476cc0@CellClass@@QAE_NPAVObjectClass@@@Z=00476cc0
// @ref __real@8@3fff8000000000000000=0079a708

void __stdcall ShipLocomotionClass::Force_Track(int track, CoordStruct coord)
{
    unknown_58 = track;
    unknown_5c = 0;
    if (coord != unknown_coord_ab91c8) {
        if (Start_Driver(CoordStruct(coord.X, coord.Y, coord.Z))) {
            unknown_34 = coord;
            unknown_50 = 1.0;
        }
    }
}
