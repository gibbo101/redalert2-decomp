// int __stdcall JumpjetLocomotionClass::Layer() (0x0052FC10, ILocomotion 29)
// The layer from the height above ground (slot 108; less the bridge height
// over a bridge cell when the object is not on the bridge): 2 on the
// ground, 4 at or above the jumpjet height (+0x28), 3 between.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"

int __stdcall JumpjetLocomotionClass::Layer()
{
    int height = LinkedTo->unknown_slot108();
    if (!LinkedTo->unknown_79) {
        if ((Loco_Cell(Object_Coord(LinkedTo))->Flags & 0x100) && height >= unknown_geometry_j && !LinkedTo->unknown_7a) {
            height -= unknown_geometry_j;
        }
    }
    if (height == 0) {
        return 2;
    }
    return height >= Height ? 4 : 3;
}
