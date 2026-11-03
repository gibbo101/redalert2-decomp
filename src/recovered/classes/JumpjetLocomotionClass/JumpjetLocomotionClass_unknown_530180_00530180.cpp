#include "shared/jumpjet_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/techno_type.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Unknown_004132E0@UnknownTracker839EA0@@QAE_NPAVFootClass@@@Z=004132e0
// @ref ?Unknown_00413600@UnknownTracker839EA0@@QAEXPAVTechnoClass@@VCell@@1@Z=00413600
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_6d1470@TechnoClass@@QAE_NXZ=006d1470
void JumpjetLocomotionClass::unknown_530180()
{
    CoordStruct position = LinkedTo->Coord;
    Cell cell = LinkedTo->unknown_slot104();
    if (cell != LinkedTo->unknown_458) {
        unknown_tracker_839ea0.Unknown_00413600(LinkedTo, LinkedTo->unknown_458, cell);
    }
    CoordStruct const &to = unknown_3c;
    UnknownFacingDir dir;
    if (position.X == to.X && position.Y == to.Y) dir.Raw = 0;
    dir = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(position.Y) - to.Y, double(to.X) - position.X)
        - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
    unknown_50.Set_Desired(dir);
    UnknownFacingDir difference = unknown_50.Difference_To_Desired();
    bool balloon = LinkedTo->unknown_slot32()->BalloonHover;
    TPoint2D<int> here(position.X, position.Y);
    TPoint2D<int> goal(to.X, to.Y);
    int distance = here.Distance_To(goal);
    if (distance < 20) {
        unknown_68 = 0;
        unknown_70 = 0;
        position.X = unknown_3c.X;
        position.Y = unknown_3c.Y;
        bool down = LinkedTo->unknown_74;
        LinkedTo->unknown_74 = false;
        LinkedTo->unknown_slot103(position);
        LinkedTo->unknown_74 = down;
        if (LinkedTo->unknown_228 == 0 && !balloon) {
            unknown_78 = 0;
            unknown_4c = 4;
            LinkedTo->unknown_6d1470();
        } else {
            if (unknown_tracker_839ea0.Unknown_004132E0(LinkedTo)) {
                int facing = Random_Pick(0, 7);
                CellClass &here_cell = Map[cell];
                LinkedTo->unknown_slot260(&here_cell.Adjacent_Cell(facing), 1);
            } else {
                ((CellClass *)LinkedTo->unknown_slot105())->Set_unknown_e0(LinkedTo);
                unknown_4c = 2;
            }
        }
    } else if (distance < Speed) {
        unknown_70 = Speed / 8;
        if (LinkedTo->unknown_228 == 0) unknown_78 = Height / 2;
    } else if (distance < Speed * 2) {
        unknown_70 = Speed / 4;
        if (LinkedTo->unknown_228 == 0) unknown_78 = Height / 2;
        if (Dir_To_256(difference) > TurnRate) {
            unknown_70 = Speed / 10;
            if (unknown_70 < 1.0) unknown_70 = 1.0;
        }
    } else {
        if (distance < (Speed * 50) / TurnRate) {
            unknown_70 = Speed / 2;
            if (LinkedTo->unknown_228 == 0) unknown_78 = (int)(Height * 0.75);
            if (Dir_To_256(difference) > TurnRate * 5) {
                unknown_70 = Speed / 5;
                if (unknown_70 < 1.0) unknown_70 = 1.0;
            }
        } else {
            unknown_78 = Height;
            unknown_70 = Speed;
        }
    }
    CellClass &destination = Map[unknown_3c];
    if (balloon || destination.unknown_ec == 2 || destination.unknown_ec == 6) unknown_78 = Height;
}
