// Unit body/turret turning using current shared Facing and weapon layouts.
#include "shared/unit.hpp"
#include "shared/weapon_type.hpp"
// @ref ?Unknown_006D8640@TechnoClass@@QAE_NPAUWeaponStruct@@@Z=006d8640
void UnitClass::unknown_6fb890()
{
    if (unknown_228 && !unknown_599) {
        UnknownFacingDir toward = Direction_To(unknown_228);
        if (Type->Turret) {
            WeaponStruct *weapon = unknown_slot230();
            if (Unknown_006D8640(weapon) && !weapon->WeaponType->unknown_107) {
                if (weapon->TurretLocked) {
                    unknown_2f8.Set_Desired(unknown_2e0.Current());
                } else {
                    unknown_2f8.Set_Desired(toward);
                }
            }
        } else if (Type->SpeedType == 1 && !unknown_494
            && !Locomotor.Checked()->Is_Moving()
            && unknown_2e0.Current().Raw == toward.Raw) {
            unknown_2e0.Set_Desired(toward);
        }
    }
    if (Type->TurretSpins) {
        UnknownFacingDir direction((unsigned short)((Dir_To_256(unknown_2f8.Current()) + 8) << 8));
        unknown_2f8.Set_Current(direction);
    } else {
        unknown_599 = false;
        if (Type->Turret) {
            if (unknown_2f8.Is_Rotating()) {
                if (!Type->TurretSpins) {
                    unknown_599 = unknown_2f8.Is_Rotating();
                }
            } else if (!unknown_228) {
                WeaponStruct *weapon = unknown_slot230();
                bool locked = Unknown_006D8640(weapon) && weapon->TurretLocked;
                if (unknown_494 && !locked) {
                    unknown_2f8.Set_Desired(Direction_To(unknown_494));
                } else {
                    unknown_2f8.Set_Desired(unknown_2e0.Current());
                }
            }
        }
    }
    if (Type->Turret) {
        unknown_3f0 = unknown_2f8.Is_Rotating();
    }
}
