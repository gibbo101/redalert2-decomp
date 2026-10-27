// bool UnitClass::unknown_709790(Cell const *from, Cell const *to) (0x00709790)
// Whether the unit should be routed by the path estimator (hypothesis): true
// unless slot 108 is non-negative, the map accepts the trip, the cells differ,
// are further apart than 1 and closer than 12 (Chebyshev), both pass
// the map's test 0x0055A660 and the estimator (0x0042AA30) finds the path no
// longer than 15.
#include "shared/unit.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_path_estimator_8315c8@@3UUnknownPathEstimator@@A=008315c8
// @ref ?Unknown_0042AA30@UnknownPathEstimator@@QAEHABVCell@@0PAVFootClass@@_N2H@Z=0042aa30

extern "C" int __cdecl abs(int value);
#pragma intrinsic(abs)

bool UnitClass::unknown_709790(Cell const *from, Cell const *to)
{
    if (unknown_slot108() >= 0 && Map.Unknown_0054F7C0(*from, *to, 0, false, 0, false)) {
        if (from->X == to->X && from->Y == to->Y) {
            return false;
        }
        int dy = abs(to->Y - from->Y);
        int dx = abs(to->X - from->X);
        int distance = dx > dy ? dx : dy;
        if (distance == 1) {
            return false;
        }
        if (distance < 12 && Map.Unknown_0055A660(*from, true) && Map.Unknown_0055A660(*to, true)) {
            return unknown_path_estimator_8315c8.Unknown_0042AA30(*from, *to, this, false, (Map_Cell_At(*to)->Flags >> 8) & 1, 0) > 15;
        }
    }
    return true;
}
