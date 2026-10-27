// Responds to the action for the current target; field/action names provisional.
#include "shared/unit.hpp"
#include "shared/rules.hpp"
extern "C" int const Unit_Attack_Frames_007F8F2C[8];
// @ref _Unit_Attack_Frames_007F8F2C=007f8f2c
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_68a4b0@UnknownTechno238@@QAEXXZ=0068a4b0
void UnitClass::unknown_6fbc90()
{
    if (!unknown_228) return;
    if (!unknown_slot231(0)->WeaponType) return;
    int weapon = unknown_slot174(unknown_228);
    int action = unknown_slot218(unknown_228, weapon, 1);
    if ((action == 0 || action == 2) && unknown_slot284()) {
        unknown_slot116(16, false);
        return;
    }
    switch (action) {
    case 5:
        if (unknown_6c16f0(weapon) < 0) {
            AbstractClass *target = unknown_228;
            if (target && target->unknown_14_bit1 && target->Kind_Of() == 1) {
                if (((ObjectClass *)target)->Health_Ratio() >= Rules->unknown_1360) {
                    unknown_slot220(0);
                    return;
                }
            } else {
                unknown_slot220(0);
                return;
            }
        }
        break;
    case 0:
        if (!Type->unknown_ba8) unknown_57d = false;
        if (Type->LargeVisceroid || Type->SmallVisceroid) {
            AnimationStage.Value = Unit_Attack_Frames_007F8F2C[Dir_To_8(Direction_To(unknown_228))];
            AnimationStage.Set_Rate(5);
        }
        unknown_slot221((int)unknown_228, weapon);
        return;
    case 2:
        if (!Type->unknown_ba9 && Type->Turret) {
            unknown_2f8.Set_Desired(Direction_To(unknown_228));
            return;
        }
        if (!unknown_494 && !Locomotor.Checked()->Is_Moving()) {
            unknown_2e0.Set_Desired(Direction_To(unknown_228));
            unknown_2f8.Set_Desired(unknown_2e0.unknown_4b8c80());
        }
        break;
    case 9:
        unknown_57d = false;
        unknown_slot252(false);
        return;
    case 8:
    case 11:
        unknown_57d = false;
        return;
    case 6:
        if (unknown_238) unknown_238->unknown_68a4b0();
        break;
    }
}
