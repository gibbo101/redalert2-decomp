// AircraftClass::unknown_slot126 0x004178A0: Do_MISSION_ATTACK (Status 0-10: validate, pick an attack
// location, fly to it, fire, fire again, the strafing run's later shots, return to base).
// Body 3330 bytes including the main and six Can_Fire switch tables; 14 nop pad bytes follow.
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
#include "shared/fast_math.hpp"
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref __real@8@4008e100000000000000=0079b608

extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;

// The direction from one coordinate to another (Westwood's DirType(Coord, Coord); the out-of-line
// copy is 0x00423EF0, this unit inlines it).
inline UnknownFacingDir::UnknownFacingDir(CoordStruct const &from, CoordStruct const &to)
{
    if (from.X == to.X && from.Y == to.Y) Raw = 0;
    *this = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y) - to.Y,
        double(to.X) - from.X) - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
}

int AircraftClass::unknown_slot126()
{
    switch (unknown_a8) {
    case 0:
        unknown_5ba = false;
        if (unknown_228 == 0) {
            unknown_a8 = 10;
        } else {
            unknown_a8 = 1;
        }
        return 1;
    case 1:
        unknown_5ba = false;
        if (unknown_5b0) {
            unknown_5b0 = false;
            unknown_254--;
        }
        if (unknown_228 == 0 || unknown_254 == 0) {
            unknown_a8 = 10;
        } else {
            unknown_slot260(unknown_418f10(unknown_228), 1);
            if (unknown_494 != 0) {
                unknown_a8 = 3;
            } else {
                unknown_a8 = 10;
            }
        }
        break;
    case 3:
        if (unknown_5b0) {
            unknown_5b0 = false;
            unknown_254--;
        }
        unknown_5ba = false;
        if (unknown_228 != 0 && unknown_254 != 0) {
            if (Is_Strafe()) {
                if (Planar_Distance(unknown_228) < unknown_slot231(0)->WeaponType->unknown_b4) {
                    unknown_a8 = 4;
                    return 1;
                }
                unknown_slot260(unknown_228, 1);
            } else {
                if (Is_Fighter() || !Locomotor.Checked()->Is_Moving_Now()) {
                    unknown_a8 = 4;
                    return 1;
                }
            }
            if (unknown_494 == 0) {
                unknown_a8 = 1;
                return 1;
            }
            int distance = Planar_Distance(unknown_494);
            if (distance < 0x200) {
                unknown_2f8.Set_Desired(Direction_To(unknown_228));
                if (distance < 0x10) {
                    unknown_a8 = 4;
                    unknown_slot260(0, 1);
                }
            } else {
                unknown_2f8.Set_Desired(UnknownFacingDir(unknown_slot43(0), unknown_494->Center_Coord()));
                return 1;
            }
        } else {
            unknown_a8 = 10;
        }
        return 1;
    case 4:
        if (unknown_228 == 0 || unknown_254 == 0) {
            unknown_a8 = 10;
            return 1;
        }
        if (!Is_Strafe()) {
            unknown_2e0.Set_Desired(Direction_To(unknown_228));
            unknown_2f8.Set_Desired(Direction_To(unknown_228));
        }
        switch (unknown_slot218(unknown_228, unknown_slot174(unknown_228), 1)) {
        case 9:
            unknown_slot252(false);
            break;
        case 3:
            break;
        case 2:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
            } else {
                if (unknown_slot213(unknown_228) && !Is_Strafe()) {
                    if (Is_Fighter()) {
                        unknown_a8 = 4;
                    } else {
                        unknown_a8 = Rules->CurleyShuffle ? 1 : 4;
                    }
                } else {
                    unknown_a8 = 1;
                }
                if (Is_Strafe()) {
                    return 45;
                }
            }
            break;
        case 0: {
            unknown_5b0 = true;
            unknown_slot221(unknown_228, unknown_slot174(unknown_228));
            Map[unknown_228->Center_Coord()].unknown_476920(&Position_Coord_004f3f40(), true, false, false);
            if (Is_Strafe()) {
                unknown_a8 = 6;
                unknown_5ba = true;
                return unknown_slot231(0)->WeaponType->unknown_b0;
            }
            if (Is_Fighter()) {
                unknown_5ba = true;
                unknown_a8 = unknown_254 <= 0 ? 10 : 1;
                return unknown_slot231(0)->WeaponType->unknown_b0;
            }
            unknown_a8 = 5;
            break;
        }
        default:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
            } else if (!Is_Strafe()) {
                unknown_a8 = 5;
            }
            break;
        }
        return 1;
    case 5:
        if (unknown_228 == 0) {
            unknown_a8 = 10;
            return 1;
        }
        unknown_2e0.Set_Desired(Direction_To(unknown_228));
        unknown_2f8.Set_Desired(Direction_To(unknown_228));
        switch (unknown_slot218(unknown_228, unknown_slot174(unknown_228), 1)) {
        case 9:
            unknown_slot252(false);
            break;
        case 3:
            break;
        case 2:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
            } else {
                if (!unknown_slot213(unknown_228) || Is_Strafe()) {
                    unknown_a8 = 1;
                } else {
                    unknown_a8 = Rules->CurleyShuffle ? 1 : 4;
                }
                if (Is_Strafe()) {
                    return 45;
                }
            }
            break;
        case 0: {
            unknown_slot221(unknown_228, unknown_slot174(unknown_228));
            Map[unknown_228->Center_Coord()].unknown_476920(&Position_Coord_004f3f40(), true, false, false);
            if (unknown_254 != 0) {
                unknown_a8 = Rules->CurleyShuffle ? 1 : 4;
            } else {
                unknown_a8 = 10;
            }
            break;
        }
        default:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
            } else if (!unknown_slot213(unknown_228)) {
                unknown_a8 = 1;
            } else {
                unknown_a8 = Rules->CurleyShuffle ? 1 : 4;
            }
            break;
        }
        break;
    case 6:
        if (unknown_228 == 0) {
            unknown_a8 = 10;
            return 1;
        }
        switch (unknown_slot218(unknown_228, unknown_slot174(unknown_228), 1)) {
        case 8:
            unknown_slot260(unknown_228, 1);
        case 0:
        case 2:
        case 9: {
            unknown_slot221(unknown_228, unknown_slot174(unknown_228));
            Map[unknown_228->Center_Coord()].unknown_476920(&Position_Coord_004f3f40(), true, false, false);
            unknown_slot260(unknown_228, 1);
            unknown_a8 = 7;
            return unknown_slot231(0)->WeaponType->unknown_b0;
        }
        default:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
                unknown_5ba = false;
            }
            return 1;
        }
    case 7:
        if (unknown_228 == 0) {
            unknown_a8 = 10;
            return 1;
        }
        switch (unknown_slot218(unknown_228, unknown_slot174(unknown_228), 1)) {
        case 8:
            unknown_slot260(unknown_228, 1);
        case 0:
        case 2:
        case 9: {
            unknown_slot221(unknown_228, unknown_slot174(unknown_228));
            Map[unknown_228->Center_Coord()].unknown_476920(&Position_Coord_004f3f40(), true, false, false);
            unknown_slot260(unknown_228, 1);
            unknown_a8 = 8;
            return unknown_slot231(0)->WeaponType->unknown_b0;
        }
        default:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
                unknown_5ba = false;
            }
            return 1;
        }
    case 8:
        if (unknown_228 == 0) {
            unknown_a8 = 10;
            return 1;
        }
        switch (unknown_slot218(unknown_228, unknown_slot174(unknown_228), 1)) {
        case 8:
            unknown_slot260(unknown_228, 1);
        case 0:
        case 2:
        case 9: {
            unknown_slot221(unknown_228, unknown_slot174(unknown_228));
            Map[unknown_228->Center_Coord()].unknown_476920(&Position_Coord_004f3f40(), true, false, false);
            unknown_slot260(unknown_228, 1);
            unknown_a8 = 9;
            return unknown_slot231(0)->WeaponType->unknown_b0;
        }
        default:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
                unknown_5ba = false;
            }
            return 1;
        }
    case 9:
        if (unknown_228 == 0) {
            unknown_a8 = 10;
            return 1;
        }
        switch (unknown_slot218(unknown_228, unknown_slot174(unknown_228), 1)) {
        case 0:
        case 2:
        case 8:
        case 9: {
            unknown_slot221(unknown_228, unknown_slot174(unknown_228));
            Map[unknown_228->Center_Coord()].unknown_476920(&Position_Coord_004f3f40(), true, false, false);
            unknown_a8 = 3;
            return (unknown_slot231(0)->WeaponType->unknown_b4 + 0x400) / Type->Speed;
        }
        default:
            if (unknown_254 == 0) {
                unknown_a8 = 10;
                unknown_5ba = false;
            }
            return 1;
        }
    case 10:
        unknown_5ba = false;
        if (unknown_5b0) {
            unknown_5b0 = false;
            if (unknown_254 > 0) {
                unknown_254--;
            }
        }
        if (unknown_254 == 0) {
            if (unknown_32c || House->unknown_func_4f52f0()) {
                unknown_slot220(0);
            }
        } else if (unknown_228 != 0) {
            unknown_a8 = 1;
            return 1;
        }
        unknown_5ba = false;
        unknown_slot260(0, 1);
        unknown_5bd = false;
        unknown_slot261(false, true);
        unknown_5bd = true;
        return 1;
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
