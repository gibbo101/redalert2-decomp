// CoordStruct __stdcall TunnelLocomotionClass::Destination() (0x006EFC70, ILocomotion 5)
// The destination while moving, otherwise where the linked object is.
#include "shared/tunnel_locomotion.hpp"

CoordStruct __stdcall TunnelLocomotionClass::Destination()
{
    if (Is_Moving()) {
        return CoordStruct(unknown_1c.X, unknown_1c.Y, unknown_1c.Z);
    }
    CoordStruct coord = LinkedTo->Coord;
    return coord;
}
