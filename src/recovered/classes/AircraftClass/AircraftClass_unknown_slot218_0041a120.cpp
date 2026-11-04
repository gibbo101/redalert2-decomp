// int AircraftClass::unknown_slot218(AbstractClass *arg1, int arg2, bool check_range) (0x0041A120, slot 218)
// TechnoClass's answer; when that is 0: 1 while +0x5B1 is set and +0xFC is
// empty, else 2 when a non-fighter faces (+0x2F8) more than 0x800 away
// from arg1, else 0.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot218@TechnoClass@@UAEHPAVAbstractClass@@H_N@Z=006c9260
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Direction_To@ObjectClass@@QBE?AUUnknownFacingDir@@PBVAbstractClass@@@Z=005d2730

int AircraftClass::unknown_slot218(AbstractClass *arg1, int arg2, bool check_range)
{
    int result = TechnoClass::unknown_slot218(arg1, arg2, check_range);
    if (result == 0) {
        if (unknown_5b1 && Cargo.Object == 0) {
            return 1;
        }
        UnknownFacingDir facing = unknown_2f8.Current();
        if (!Is_Fighter()) {
            short difference = (short)(facing.Raw - Direction_To(arg1).Raw);
            if (abs(0x800) < abs(difference)) {
                return 2;
            }
        }
        result = 0;
    }
    return result;
}
