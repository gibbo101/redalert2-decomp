// bool SuperClass::unknown_69d390(bool local_player) (0x0069D390)
// The charge-up AI (TS SuperClass::AI): true when the sidebar graphic must be redrawn.
// @ref ?unknown_pending_super_833694@@3HA=00833694
// @ref ?Unknown_00405FE0@UnknownAudioController@@QAEXXZ=00405fe0
#include "shared/vox_class.hpp"
// @ref ??_C@_0BI@IALN@EVA_NuclearMissileReady?$AA@=007f65a4
// @ref ??_C@_0BF@EOKO@EVA_IronCurtainReady?$AA@=007f658c
// @ref ??_C@_0BI@JJFK@EVA_LightningStormReady?$AA@=007f6574
// @ref ??_C@_0BG@COOK@EVA_ChronosphereReady?$AA@=007f655c
// @ref ??_C@_0BI@LBFC@EVA_ReinforcementsReady?$AA@=007f6544
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40

bool SuperClass::unknown_69d390(bool local_player)
{
    if (unknown_pending_super_833694 != 4 && Anim != 0) {
        Anim->unknown_17d = true;
        Anim->unknown_180.Unknown_00405FE0();
    }
    if (Is_Present() && (!unknown_0x57 || Type->UseChargeDrain) && !unknown_0x58) {
        if (!RechargeTimer.Is_Active()) {
            if (unknown_0x5C != -1) {
                unknown_0x5C = -1;
                return true;
            }
        } else {
            if (RechargeTimer == 0) {
                if (Type->UseChargeDrain) {
                    if (unknown_0x60 == 2) {
                        unknown_0x60 = 0;
                        RechargeTimer = Type->RechargeTime;
                    } else {
                        unknown_0x60 = 1;
                        unknown_0x57 = true;
                    }
                    return true;
                } else {
                    unknown_0x57 = true;
                    if (local_player) {
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
                    return true;
                }
            } else {
                if (Anim_Stage() != unknown_0x5C) {
                    unknown_0x5C = Anim_Stage();
                    return true;
                }
            }
        }
    }
    return false;
}
