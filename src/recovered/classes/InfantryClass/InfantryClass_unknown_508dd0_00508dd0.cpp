// bool InfantryClass::unknown_508dd0(Cell const *from, Cell const *to) (0x00508DD0)
// False under the owner's 0x0051FC80 condition, true at once when slot 108
// is positive; false for a 0x004F52F0 owner whose start cell passes
// 0x00479CF0. Otherwise true when the two cells are not connected
// (0x0054F7C0, zone 7) or at least four cells apart; false for the same or
// an adjacent cell; for two or three cells true unless both cells pass
// 0x0055A660 and the path estimate (0x0042AA30) is within 7.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054F7C0@MapClass@@QAE_NABVCell@@0H_N11@Z=0054f7c0
// @ref ?Unknown_0051FC80@HouseClass@@QAE_NXZ=0051fc80
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Unknown_00479CF0@UnknownCellClass@@QAE_NXZ=00479cf0
// @ref ?Unknown_0042AA30@UnknownPathEstimator@@QAEHABVCell@@0PAVFootClass@@_N2H@Z=0042aa30
// @ref ?unknown_path_estimator_8315c8@@3UUnknownPathEstimator@@A=008315c8

bool InfantryClass::unknown_508dd0(Cell const *from, Cell const *to)
{
    unknown_slot108();
    if (House->Unknown_0051FC80()) {
        return false;
    }
    if (unknown_slot108() > 0) {
        return true;
    }
    if (House->Unknown_004F52F0()) {
        UnknownCellClass *cell = Map_Cell_At(*from);
        if (cell != 0 && cell->Unknown_00479CF0()) {
            return false;
        }
    }
    if (!Map.Unknown_0054F7C0(*from, *to, 7, unknown_79, (Map_Cell_At(*to)->Flags >> 8) & 1, 0)) {
        return true;
    }
    if (*from == *to) {
        return false;
    }
    int dy = abs(to->Y - from->Y);
    int dx = abs(to->X - from->X);
    int distance = (dx > dy) ? dx : dy;
    if (distance == 1) {
        return false;
    }
    if (distance >= 4) {
        return true;
    }
    if (!Map.Unknown_0055A660(*from, true) || !Map.Unknown_0055A660(*to, true)) {
        return true;
    }
    return unknown_path_estimator_8315c8.Unknown_0042AA30(*from, *to, this, unknown_79, (Map_Cell_At(*to)->Flags >> 8) & 1, 7) > 7;
}
