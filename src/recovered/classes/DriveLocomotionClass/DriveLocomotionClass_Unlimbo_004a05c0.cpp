// void __stdcall DriveLocomotionClass::Unlimbo() (0x004A05C0, ILocomotion 20)
// Takes the ramp of the cell the object is placed in.
#include "shared/drive_locomotion.hpp"
#include "shared/cell.hpp"

void __stdcall DriveLocomotionClass::Unlimbo()
{
    Force_New_Slope(((CellClass *)LinkedTo->unknown_slot105())->unknown_11c);
}
