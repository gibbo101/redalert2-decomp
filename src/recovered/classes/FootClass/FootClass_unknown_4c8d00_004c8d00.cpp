// bool FootClass::unknown_4c8d00(HouseClass *house) (0x004C8D00)
// Whether the unit is free to be recruited (by house, when given): owned
// by that house, +0x76 clear, in no team, in an idle mission (0x00594DB0)
// and with +0x379 set.
#include "shared/foot.hpp"
// @ref ?unknown_594db0@MissionClass@@SI_NH@Z=00594db0

bool FootClass::unknown_4c8d00(HouseClass *house)
{
    if (house != 0 && house != House) {
        return false;
    }
    if (unknown_76) {
        return false;
    }
    if (Team != 0) {
        return false;
    }
    if (!MissionClass::unknown_594db0(unknown_slot91())) {
        return false;
    }
    return unknown_379 ? true : false;
}
