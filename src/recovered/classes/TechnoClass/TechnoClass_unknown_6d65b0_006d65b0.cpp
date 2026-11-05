// CoordStruct TechnoClass::unknown_6d65b0() (0x006D65B0)
// Where to aim at the target (+0x228): its slot 22 coordinate, led ahead
// along a moving unit's facing by its speed times the projectile's flight
// time (distance over 0.9 of the secondary weapon's speed for the range).
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/ilocomotion.hpp"
#include "shared/weapon_type.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/fast_math.hpp"
// @ref _unknown_geometry_l=00ac0188
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Distance_To@ObjectClass@@QBEHPBVAbstractClass@@@Z=005d4c00
// @ref ?unknown_func_733f70@WeaponTypeClass@@QBEHH@Z=00733f70
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref __real@8@bff1c9116cc4faf2b800=0079b620
// @ref __real@8@3ffee666666666666800=007ad028

inline double UnknownFacingDir::As_Radian() const
{
    return (short(Raw) - 0x3FFF) * -9.587672516830327e-05;
}

// A coordinate moved along a direction (same helper as InfantryClass 0x00504BC0).
inline CoordStruct Move_Coord(CoordStruct const &start, UnknownFacingDir const &direction, int distance)
{
    double angle = direction.As_Radian();
    double scaled = distance;
    return CoordStruct(int(start.X + Fast_Cos(angle) * scaled), int(start.Y - Fast_Sin(angle) * scaled), start.Z);
}
CoordStruct TechnoClass::unknown_6d65b0()
{
    CoordStruct coord = unknown_geometry_l;
    if (unknown_228 != 0) {
        coord = unknown_228->unknown_slot22();
        if (unknown_228 != 0 && unknown_228->Kind_Of() == 1) {
            FootClass *unit = (FootClass *)unknown_228;
            if (unit != 0 && unit->Locomotor.Checked()->Is_Moving()) {
                int speed = unit->unknown_slot303();
                int distance = unknown_5d4c00(unknown_228);
                WeaponStruct *weapon = unknown_slot230();
                if (weapon != 0 && weapon->WeaponType != 0) {
                    double range = distance;
                    int lead = (int)(range / (weapon->WeaponType->unknown_func_733f70(distance) * 0.9) * speed);
                    coord = Move_Coord(coord, unit->unknown_2e0.Current(), lead);
                }
            }
        }
    }
    return coord;
}
