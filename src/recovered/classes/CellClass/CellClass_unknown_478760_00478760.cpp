// bool CellClass::unknown_478760(int speed, bool arg2, bool arg3, int zone,
// int zone_type, int level, bool alt) (0x00478760): whether an object of the
// speed type may enter the cell (hypothesis): the map zone and the level (the
// cell's own, or four above on a bridge) must match when given; the blocked
// direction bits (+0x124, or +0x128 on a bridge; arg2 keeps 0xE0, arg3 0x5F)
// must be clear; a wall overlay refuses all but zone types 2, 3 and 8 (and 1
// and 4 for a wall with +0x1FD) and counts as land type 0; the land type
// must have a speed (a bridge always does). Speed type 4 always may.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay_type.hpp"
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?Ground@@3PAUGroundType@@A=00850ea0

bool CellClass::unknown_478760(int speed, bool arg2, bool arg3, int zone, int zone_type, int level, bool alt)
{
    if (speed == 4) {
        return true;
    }
    if (zone != -1 && zone != Map.Zone(MapCoords, zone_type, alt)) {
        return false;
    }
    if (level != -1) {
        if (level != unknown_11b) {
            if (!(unknown_140 & 0x100) || level != unknown_11b + 4) {
                return false;
            }
        } else if ((unknown_140 & 0x100) && !alt) {
            return false;
        }
    }
    bool bridge = false;
    int blocked;
    if ((level == -1 || level == unknown_11b + 4) && (unknown_140 & 0x100)) {
        bridge = true;
        blocked = unknown_128;
    } else {
        blocked = unknown_124;
    }
    if (arg2) {
        blocked &= 0xE0;
    }
    if (arg3) {
        blocked &= 0x5F;
    }
    if (blocked != 0) {
        return false;
    }
    int land = unknown_ec;
    if (OverlayIndex != -1) {
        OverlayTypeClass *overlay = OverlayTypes[OverlayIndex];
        if (overlay != 0 && overlay->Wall) {
            if (zone_type != 2 && zone_type != 3 && zone_type != 8
                && ((zone_type != 1 && zone_type != 4) || !overlay->unknown_1fd)) {
                return false;
            }
            land = 0;
        }
    }
    if (Ground[land].Cost[speed] == 0.0f && !bridge) {
        return false;
    }
    return true;
}
