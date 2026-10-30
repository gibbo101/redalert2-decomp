// void JumpjetLocomotionClass::unknown_52fd50() (0x0052FD50)
// Process state 1 (ascending): the height above ground (less a bridge)
// against the target height (+0x78); a changed cell is reported to the
// tracker. At the height, a crowded cell (0x004132E0) sends the object to a
// random adjacent cell (state 3), else it claims its cell (state 2). Past a
// quarter (BalloonHover: half) of the height it gets the jumpjet speed and
// turns toward the target; leaving a factory or barracks notifies the
// object (0x117B); above the target cell a non-balloon starts cruising.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/building_type.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?Unknown_004132E0@UnknownTracker839EA0@@QAE_NPAVFootClass@@@Z=004132e0
// @ref ?Unknown_00413600@UnknownTracker839EA0@@QAEXPAVFootClass@@VCell@@1@Z=00413600
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

void JumpjetLocomotionClass::unknown_52fd50()
{
    int height = LinkedTo->unknown_slot108();
    if (!LinkedTo->unknown_79 && (Map[Object_Coord(LinkedTo)].unknown_140 & 0x100) && height >= unknown_geometry_j) {
        height -= unknown_geometry_j;
    }
    Cell cell = LinkedTo->unknown_slot104();
    if (cell != LinkedTo->unknown_458) {
        unknown_tracker_839ea0.Unknown_00413600(LinkedTo, LinkedTo->unknown_458, cell);
    }
    if (height >= unknown_78) {
        if (unknown_tracker_839ea0.Unknown_004132E0(LinkedTo)) {
            int facing = Random_Pick(0, 7);
            CellClass &here = Map[cell];
            LinkedTo->unknown_slot260(&here.Adjacent_Cell(facing), 1);
            unknown_4c = 3;
        } else {
            ((CellClass *)LinkedTo->unknown_slot105())->Set_unknown_e0(LinkedTo);
            unknown_4c = 2;
        }
        return;
    }
    int limit;
    if (LinkedTo->Kind_Of() == 1 && LinkedTo->unknown_slot32()->BalloonHover) {
        limit = unknown_78 / 2;
    } else {
        limit = unknown_78 / 4;
    }
    if (height > limit) {
        unknown_70 = Speed;
        CoordStruct from = LinkedTo->Coord;
        CoordStruct const &to = unknown_3c;
        UnknownFacingDir dir;
        if (from.X == to.X && from.Y == to.Y) {
            dir.Raw = 0;
        }
        dir = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y) - to.Y, double(to.X) - from.X)
            - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
        unknown_50.Set_Desired(dir);
        TechnoClass *contact = LinkedTo->Contact(0);
        if (contact != 0 && contact->Kind_Of() == 6) {
            BuildingTypeClass *type = ((BuildingClass *)contact)->Type;
            if (type->WeaponsFactory || type->GDIBarracks || type->NODBarracks) {
                LinkedTo->INoticeSink_Unknown(0x117B, 0);
            }
        }
        if (cell == Coord_Cell(unknown_3c) && !LinkedTo->unknown_slot32()->BalloonHover) {
            unknown_78 = LinkedTo->unknown_slot108();
            unknown_4c = 3;
        }
    }
}
