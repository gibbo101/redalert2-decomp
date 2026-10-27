// void TechnoClass::unknown_slot263(bool arg1, bool arg2, bool arg3, HouseClass *house) (0x006D5E90)
// Reveals the map around the stored sight coordinate +0x1E8 (range +0x1F4)
// when +0x32D is set and the owner is not MultiplayPassive: once for the
// owner while +0x1E4 is pending (clearing it), or for house when arg3 asks.
#include "shared/techno.hpp"
#include "shared/house_type.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?Sight_From@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2H2H@Z=0054a110

void TechnoClass::unknown_slot263(bool arg1, bool arg2, bool arg3, HouseClass *house)
{
    if (unknown_32d && !House->Type->MultiplayPassive) {
        if (unknown_1e4) {
            unknown_1e4 = false;
            if (unknown_1f4 != 0 && arg3 && house != 0) {
                Map.Sight_From(unknown_1e8, unknown_1f4, house, arg1, arg2, 0, true, 1);
            } else if (unknown_1f4 != 0) {
                Map.Sight_From(unknown_1e8, unknown_1f4, House, arg1, arg2, 0, true, 1);
            }
        } else if (arg3 && unknown_1f4 != 0 && house != 0) {
            Map.Sight_From(unknown_1e8, unknown_1f4, house, arg1, arg2, 0, true, 1);
        }
    }
}
