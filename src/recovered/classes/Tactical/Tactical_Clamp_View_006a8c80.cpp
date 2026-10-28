// bool Tactical::Unknown_006A8C80(Point2D *point) (0x006A8C80)
// Clamps a view position to the scrollable area derived from the map size and the tactical window; true when
// the point was changed.
// @ref ?unknown_int_8325d0@@3HA=008325d0
// @ref ?unknown_int_8325d8@@3HA=008325d8
// @ref ?unknown_int_8325dc@@3HA=008325dc
// @ref ?unknown_int_8325e0@@3HA=008325e0
// @ref ?unknown_int_8325e4@@3HA=008325e4
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"

extern int unknown_int_8325d0;
extern int unknown_int_8325d8;
extern int unknown_int_8325dc;
extern int unknown_int_8325e0;
extern int unknown_int_8325e4;
extern int unknown_int_83963c;

bool Tactical::Unknown_006A8C80(Point2D *point)
{
    int min_x = unknown_int_839638 / 2 + (unknown_int_8325d8 * 2 - unknown_int_8325d0) * 30;
    int max_x = (unknown_int_8325e0 * 60 - unknown_int_839638) + min_x;
    int min_y = (unknown_int_8325d0 - 5 + unknown_int_8325dc * 2) * 15 + unknown_int_83963c / 2;
    int max_y = ((unknown_int_8325e4 * 60 + 270) / 2 - unknown_int_83963c) + min_y;
    bool changed = false;
    if (point->Y < min_y) {
        changed = true;
        point->Y = min_y;
    } else if (point->Y > max_y) {
        point->Y = max_y;
        changed = true;
    }
    if (point->X < min_x) {
        point->X = min_x;
        return true;
    }
    if (point->X > max_x) {
        point->X = max_x;
        return true;
    }
    return changed;
}
