// Gather near the enemy base, with native RA2 behavior and widths.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
#include "shared/rules.hpp"
#include "shared/building_light.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
#include "shared/unknown_vector3.hpp"
#include "shared/team_type.hpp"
#include "shared/debug_printf.hpp"
// Choose a point at the safe distance from the enemy base along the bearing.
// Hypothesis: file-local operation boundary, with no original out-of-line identity.
static inline UnknownVector3 Enemy_Gather_Point(CoordStruct const &there, UnknownFacingDir const &dir, int distance)
{
    double angle = ((short)dir.Raw - 0x3fff) * unknown_facing_radians_79b620;
    double y = there.Y;
    int target_y = (int)(y - unknown_sin_4ba480(angle) * distance);
    int target_x = (int)(unknown_cos_4ba4d0(angle) * distance + there.X);
    UnknownVector3 point(target_x, target_y, there.Z);
    return point;
}

void TeamClass::TMission_unknown_6bdaa0(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        FootClass *leader = unknown_func_6baa60();
        if (leader == 0) { StepCompleted = true; return; }
        HouseClass *house = leader->House;
        HouseClass *enemy = 0;
        if (house->unknown_54f0 != -1) enemy = Houses[house->unknown_54f0];
        if (enemy == 0) { StepCompleted = true; return; }
        CoordStruct there = enemy->BaseCenter;
        if (there == unknown_geometry_l) { StepCompleted = true; return; }
        CoordStruct center = house->BaseCenter;
        if (center == unknown_geometry_l) center = leader->Center_Coord();
        CoordStruct offset = center - there;
        Point2D delta;
        delta.X = offset.X;
        delta.Y = offset.Y;
        double dy = -delta.Y;
        UnknownFacingDir dir((unsigned short)(int)((Fast_Atan2(dy, delta.X) - unknown_facing_origin_79b630)
            * unknown_facing_scale_79b628));
        int distance = Rules->AISafeDistance << 8;
        UnknownVector3 point = Enemy_Gather_Point(there, dir, distance);
        Cell cell = XY_Cell(point.X / 256, point.Y / 256);
        cell = Map.Unknown_005502E0(cell, leader->unknown_slot32()->SpeedType, -1, 0, false,
            Point2D(3,3), false, false, false, true, Cell(0,0), 0);
        unknown_func_6b79e0(&Map[cell]);
        Debug_Printf("A %s Team has chosen ( %d, %d) for its GatherAtEnemy cell.\n", (char const *)Class->Name, cell.X, cell.Y);
    }
    unknown_func_6ba1a0();
}

// @ref ??_C@_0DM@GJPF@A?5?$CFs?5Team?5has?5chosen?5?$CI?5?$CFd?0?5?$CFd?$CJ?5f@=007f6e04
