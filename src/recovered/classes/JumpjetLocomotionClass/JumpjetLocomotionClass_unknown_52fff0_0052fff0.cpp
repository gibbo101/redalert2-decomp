// void JumpjetLocomotionClass::unknown_52fff0() (0x0052FFF0)
// Process state 2 (hovering) while moving: over the target X/Y with no
// +0x228 target, the state becomes 2 for a BalloonHover type, else 4, and
// the techno check 0x006D1470 runs; elsewhere the facing (+0x50) turns toward
// the target, the cell claims (+0xE0) of the old and current cells are
// released and the state becomes 3.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?unknown_6d1470@TechnoClass@@QAE_NXZ=006d1470

void JumpjetLocomotionClass::unknown_52fff0()
{
    if (Is_Moving()) {
        CoordStruct head = unknown_3c;
        CoordStruct coord = LinkedTo->Coord;
        if (head.X == coord.X && head.Y == coord.Y) {
            if (LinkedTo->unknown_228 == 0) {
                if (LinkedTo->unknown_slot32()->BalloonHover) {
                    unknown_4c = 2;
                    LinkedTo->unknown_6d1470();
                } else {
                    unknown_4c = 4;
                    LinkedTo->unknown_6d1470();
                }
            }
        } else {
            CoordStruct from = LinkedTo->Coord;
            CoordStruct const &to = unknown_3c;
            UnknownFacingDir dir;
            if (from.X == to.X && from.Y == to.Y) {
                dir.Raw = 0;
            }
            dir = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y) - to.Y, double(to.X) - from.X)
                - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
            unknown_50.Set_Desired(dir);
            if (((CellClass *)LinkedTo->unknown_slot105())->unknown_e0 == 0 && Map[LinkedTo->unknown_458].unknown_e0 == LinkedTo) {
                Map[LinkedTo->unknown_458].Set_unknown_e0(0);
            }
            ((CellClass *)LinkedTo->unknown_slot105())->Set_unknown_e0(0);
            unknown_4c = 3;
        }
    }
}
