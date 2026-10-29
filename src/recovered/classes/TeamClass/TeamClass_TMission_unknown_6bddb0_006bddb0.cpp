// void TeamClass::TMission_unknown_6bddb0(ScriptMissionClass const &mission, bool unknown) (0x006BDDB0)
// When unknown is set: from the leader's base center, picks the direction toward the enemy's base
// (a random one without an enemy), goes AISafeDistance cells that way and targets the free 3x3 spot
// nearest there for the leader's speed type (hypothesis: the GatherAtBase action beside 0x006BDAA0's
// GatherAtEnemy). Then runs 0x006BA1A0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
#include "shared/rules.hpp"
#include "shared/building_light.hpp"
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298

extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;

void TeamClass::TMission_unknown_6bddb0(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        FootClass *leader = unknown_func_6baa60();
        HouseClass *enemy = 0;
        if (leader != 0 && leader->House->unknown_54f0 != -1) {
            enemy = Houses[leader->House->unknown_54f0];
        }
        CoordStruct center = leader->House->BaseCenter;
        UnknownFacingDir dir;
        if (enemy == 0) {
            dir = UnknownFacingDir((unsigned short)((unsigned char)unknown_id_source_a3d290->Random()(0, 255) << 8));
        } else {
            CoordStruct there = enemy->BaseCenter;
            CoordStruct delta = there - center;
            dir = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(-delta.Y, delta.X) - unknown_facing_origin_79b630)
                * unknown_facing_scale_79b628));
        }
        int distance = Rules->AISafeDistance << 8;
        double angle = ((short)dir.Raw - 0x3fff) * unknown_facing_radians_79b620;
        double y = center.Y;
        CoordStruct coord((int)(unknown_cos_4ba4d0(angle) * distance + center.X), (int)(y - unknown_sin_4ba480(angle) * distance), center.Z);
        Cell cell = Coord_Cell(coord);
        cell = Map.Unknown_005502E0(cell, leader->unknown_slot32()->SpeedType, -1, 0, false,
            Point2D(3, 3), 0, 0, 0, 1, Cell(0, 0), 0);
        unknown_func_6b79e0(&Map[cell]);
    }
    unknown_func_6ba1a0();
}
