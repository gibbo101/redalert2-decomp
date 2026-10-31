// void SuperClass::Forced_Charge(bool player) (0x0069D690)
// Charges the super weapon at once, announcing it for the player.

#include "shared/vox_class.hpp"
// @ref ??_C@_0BI@IALN@EVA_NuclearMissileReady?$AA@=007f65a4
// @ref ??_C@_0BF@EOKO@EVA_IronCurtainReady?$AA@=007f658c
// @ref ??_C@_0BI@JJFK@EVA_LightningStormReady?$AA@=007f6574
// @ref ??_C@_0BG@COOK@EVA_ChronosphereReady?$AA@=007f655c
// @ref ??_C@_0BI@LBFC@EVA_ReinforcementsReady?$AA@=007f6544
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40

void SuperClass::Forced_Charge(bool player)
{
    if (unknown_0x55) {
        unknown_0x57 = true;
        RechargeTimer.Start();
        RechargeTimer = 0;
        if (player) {
            switch (Type->Type) {
            case 0:
                Speech_Play_Name("EVA_NuclearMissileReady", -1, -1);
                break;
            case 1:
                Speech_Play_Name("EVA_IronCurtainReady", -1, -1);
                break;
            case 2:
                Speech_Play_Name("EVA_LightningStormReady", -1, -1);
                break;
            case 3:
                Speech_Play_Name("EVA_ChronosphereReady", -1, -1);
                break;
            case 5:
            case 6:
                Speech_Play_Name("EVA_ReinforcementsReady", -1, -1);
                break;
            }
        }
        if (Type->UseChargeDrain) {
            unknown_0x60 = 1;
        }
    }
}
