// bool __stdcall FlyLocomotionClass::Process() (0x004BC2B0, ILocomotion 16)
// TibSun Fly.cpp Process: flight level, commence, rotation and movement steps, the
// approach to the destination, landing/take-off and the edge-of-map check; returns Is_Moving().
#include "shared/fly_locomotion.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_4bca00@FlyLocomotionClass@@QAE_NXZ=004bca00
// @ref ?unknown_4bcd50@FlyLocomotionClass@@QAEXXZ=004bcd50
// @ref ?unknown_4bdd10@FlyLocomotionClass@@QAEXXZ=004bdd10
// @ref ?unknown_4be720@FlyLocomotionClass@@QAEH_NUCoordStruct@@@Z=004be720

bool __stdcall FlyLocomotionClass::Process()
{
    if (!unknown_51 && !unknown_50 && unknown_40 >= 1.0 && unknown_38 == 0) {
        unknown_38 = LinkedTo->unknown_slot32()->Flight_Level();
    }
    if (LinkedTo->Strength > 0 && !unknown_51 && !unknown_50 && LinkedTo->unknown_slot122()) {
        LinkedTo->unknown_slot117();
    }
    unknown_4bdd10();
    unknown_4bcd50();
    if (!Is_Powered()) {
        return false;
    }
    if (!LinkedTo->unknown_7d) {
        return false;
    }
    if (LinkedTo->Strength > 0 && unknown_1c != unknown_coord_865df8 && !unknown_51 && !unknown_50 && LinkedTo->unknown_slot108() > 0) {
        unknown_4be720(true, CoordStruct(unknown_1c.X, unknown_1c.Y, unknown_1c.Z));
    }
    if (LinkedTo->Strength > 0) {
        unknown_4bca00();
    }
    unknown_4bcc60();
    return Is_Moving();
}
