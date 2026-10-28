// void __stdcall ShipLocomotionClass::Unlimbo() (0x00676580, ILocomotion 20)
// Takes the ramp of the cell the object is placed in.
#include "shared/ship_locomotion.hpp"
#include "shared/cell.hpp"

void __stdcall ShipLocomotionClass::Unlimbo()
{
    Force_New_Slope(((CellClass *)LinkedTo->unknown_slot105())->unknown_11c);
}
