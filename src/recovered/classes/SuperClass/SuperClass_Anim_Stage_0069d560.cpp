// int SuperClass::Anim_Stage() const (0x0069D560)
// The sidebar charge stage, 0 (uncharged) to 54 (charged).

#include "shared/rules.hpp"
// @ref __real@8@4004d800000000000000=007ac270

int SuperClass::Anim_Stage() const
{
    if (unknown_0x55) {
        int stage;
        if (Type->UseChargeDrain) {
            if (unknown_0x60 == 2) {
                stage = 54 * (1 - double(Type->RechargeTime * Rules->ChargeToDrainRatio - RechargeTimer.Value()) / (Type->RechargeTime * Rules->ChargeToDrainRatio));
            } else {
                stage = 54 * (double(Type->RechargeTime - RechargeTimer.Value()) / Type->RechargeTime);
            }
        } else {
            if (unknown_0x57) {
                return 54;
            }
            stage = 54 * (double(Type->RechargeTime - RechargeTimer.Value()) / Type->RechargeTime);
        }
        stage = stage < 54 - 1 ? stage : 54 - 1;
        return stage;
    }
    return 0;
}
