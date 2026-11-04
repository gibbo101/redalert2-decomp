// AbstractClass *InfantryClass::unknown_slot219(int threat, CoordStruct const *coord, bool arg3) (0x00505120, slot 219)
// Threat search: engineers of owners failing HouseClass 0x004F52F0 take the
// house's +0x5410 object within 0xF00 leptons (else add 0x200); vehicle
// thieves take an active +0x494 (slot 31, not IsTrain) within 0xF00. Then
// adjusts the threat flags (Infiltrate/VehicleThief, the weapons'
// projectile flags, warhead +0x148, C4, Thief) for FootClass's slot 219.
#include "shared/infantry.hpp"
#include "shared/fast_math.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00
// @ref ?unknown_func_733a60@WeaponTypeClass@@QBEHXZ=00733a60
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?unknown_slot219@FootClass@@UAEPAVAbstractClass@@HPBUCoordStruct@@_N@Z=004c8420

// The length of a coordinate offset, squared in X, Y, Z order (this shape;
// foot.hpp's Coord_Length converts Z first).
inline int Coord_Length_XYZ(CoordStruct const &coord)
{
    return (int)Fast_Sqrt((double)coord.X * coord.X + (double)coord.Y * coord.Y + (double)coord.Z * coord.Z);
}

AbstractClass *InfantryClass::unknown_slot219(int threat, CoordStruct const *coord, bool arg3)
{
    if (!House->Unknown_004F52F0() && Type->Engineer) {
        ObjectClass *object = (ObjectClass *)House->unknown_5410;
        if (object != 0) {
            if (Coord_Length_XYZ(Center_Coord() - object->Center_Coord()) < 0xF00) {
                return (AbstractClass *)House->unknown_5410;
            }
        }
        threat |= 0x200;
    }
    if (Type->VehicleThief) {
        AbstractClass *thief_target = unknown_494;
        bool active;
        if (thief_target != 0) {
            active = thief_target->AbstractFlags.IsTechno;
        }
        if (thief_target != 0 && active && ((TechnoClass *)unknown_494)->unknown_slot31()
        && !((TechnoClass *)unknown_494)->unknown_slot32()->IsTrain && unknown_5d4c00(unknown_494) < 0xF00) {
            return unknown_494;
        }
    }
    if (!unknown_slot163()) {
        if (!Type->Infiltrate && !Type->VehicleThief) {
            return 0;
        }
        if (Type->VehicleThief) {
            threat = (threat & ~0xA4) | 0x10;
        }
    }
    if (!(threat & 0x1B978)) {
        if (unknown_slot231(0)->WeaponType != 0) {
            threat |= unknown_slot231(0)->WeaponType->unknown_func_733a60();
        }
        if (unknown_slot231(1)->WeaponType != 0) {
            threat |= unknown_slot231(1)->WeaponType->unknown_func_733a60();
        }
    }
    if (unknown_slot163() && unknown_slot231(0)->WeaponType->Warhead->unknown_148) {
        threat &= ~0xB4;
    }
    if ((Type->C4 || unknown_6d7910(14)) && !House->Unknown_004F52F0()) {
        threat |= 0x20;
    }
    if (Type->Thief) {
        threat |= 0x240;
    }
    return FootClass::unknown_slot219(threat, coord, arg3);
}
