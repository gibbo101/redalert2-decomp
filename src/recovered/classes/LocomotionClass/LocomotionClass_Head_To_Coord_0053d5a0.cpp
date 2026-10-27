// CoordStruct __stdcall LocomotionClass::Head_To_Coord() (0x0053D5A0, ILocomotion)
// Where the linked object is.
#include "shared/locomotion.hpp"

CoordStruct __stdcall LocomotionClass::Head_To_Coord()
{
    CoordStruct coord = LinkedTo->Coord;
    return coord;
}
