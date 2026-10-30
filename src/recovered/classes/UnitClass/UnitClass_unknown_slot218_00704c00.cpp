// int UnitClass::unknown_slot218(AbstractClass *target, int weapon, int action)
// (0x00704C00, slot 218; TibSun UnitClass::Can_Fire): the techno answer refined
// for deploy-to-fire, tethering, healing weapons, firing while moving, turret
// rotation and the turret's angle to the target, then the locomotor's answer.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/weapon_type.hpp"
#include "shared/rules.hpp"
#include "shared/spawn_manager.hpp"
// The target as a techno (0x0040DBD0; null for other kinds).
TechnoClass *__fastcall As_Techno_0040dbd0(AbstractClass *target);
// @ref ?As_Techno_0040dbd0@@YIPAVTechnoClass@@PAVAbstractClass@@@Z=0040dbd0
// @ref ?unknown_slot218@TechnoClass@@UAEHPAVAbstractClass@@HH@Z=006c9260
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?unknown_47cdd0@CellClass@@QBE_NXZ=0047cdd0
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// TibSun's DirType comparison: the larger angular distance either way
// (both sides by value).
inline bool operator<(UnknownFacingDir left, UnknownFacingDir right)
{
    return abs((short)left.Raw) < abs((short)right.Raw);
}

int UnitClass::unknown_slot218(AbstractClass *target, int weapon, int action)
{
    if (SpawnManager && SpawnManager->Launching_Count()) return 10;
    action = TechnoClass::unknown_slot218(target, weapon, action);
    if (action == 0 || action == 2) {
        CoordStruct position = Coord;
        bool usable_land = Map[position].unknown_47cdd0();
        if (Type->DeployToFire && unknown_slot284() && !usable_land) return 11;
    }
    if (action == 0) {
        if (unknown_370 && Contact_With_Whom(0)->Kind_Of() == 6) return 6;
        WeaponTypeClass *weapon_type = unknown_slot231(weapon)->WeaponType;
        if (unknown_6c16f0(-1) < 0) {
            TechnoClass *object = As_Techno_0040dbd0(target);
            if (!object || !object->unknown_slot31() || object->Health_Ratio() >= Rules->unknown_1360) return 5;
        }
        if (!Type->MobileFire && unknown_494) return 7;
        if ((weapon_type->unknown_106 || weapon_type->unknown_105) && unknown_494) return 7;
        if (unknown_208 && unknown_494) return 7;
        if (!unknown_57d && unknown_599 && weapon_type->Projectile->ROT == 0) return 4;
        if (!weapon_type->unknown_107 && !Type->LargeVisceroid && !Type->SmallVisceroid) {
            UnknownFacingDir current;
            if (Type->Turret) current = unknown_2f8.Current();
            else current = unknown_2e0.Current();
            int steps = weapon_type->Projectile->ROT ? 16 : 8;
            if (UnknownFacingDir((unsigned short)((unsigned char)steps << 8)) < UnknownFacingDir((unsigned short)(current.Raw - Direction_To(target).Raw))) {
                return 2;
            }
        }
        int state = Locomotor.Checked()->State();
        if (state) return state;
    }
    return action;
}
