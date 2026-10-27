// bool AITriggerTypeClass::Is_Ready(HouseClass *house, HouseClass *enemy, bool unknown_arg3) const (0x0041C990)
// Whether the trigger may fire for the house against the enemy: team
// availability, the minimum the rules require, global/enabled state,
// difficulty flags, owner side and house, tech level, the condition, the
// teams' zones, buildability and team limits.
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"
#include "shared/object.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Can_Build_Team@HouseClass@@QAE_NPAVTeamTypeClass@@@Z=004f3630
// @ref ?Team_Count@HouseClass@@QAEHPAVTeamTypeClass@@@Z=004f35f0
// @ref __real@8@4005c800000000000000=0079b7f0
// @ref __real@8@00000000000000000000=0079b610
// @ref ?Chronosphere_Ready@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041d3e0
// @ref ?Enemy_Money_Compare@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041d490
// @ref ?Enemy_Owns_Compare@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041cd50
// @ref ?House_Owns_Compare@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041d0f0
// @ref ?Iron_Curtain_Ready@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041d330
// @ref ?Neutral_Owns_Compare@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041cef0
// @ref ?Team_Zone_Check@AITriggerTypeClass@@QBE_NPAVTeamTypeClass@@PAVHouseClass@@1@Z=0041e130
// @ref ?Enemy_Power_Below_100@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041d290
// @ref ?Enemy_Power_Below_0@AITriggerTypeClass@@QBE_NPAVHouseClass@@0@Z=0041d2e0

bool AITriggerTypeClass::Is_Ready(HouseClass *house, HouseClass *enemy, bool unknown_arg3) const
{
    bool teams_ok = unknown_dc != 0 && unknown_dc->IsBaseDefense && (unknown_e0 == 0 || unknown_e0->IsBaseDefense);
    if (unknown_dc == 0) {
        return false;
    }
    if (enemy == 0 || (Rules->unknown_1437 && house->unknown_555c < Rules->MinimumAIDefensiveTeams[house->unknown_c8])) {
        if (!teams_ok) {
            return false;
        }
    }
    if (teams_ok && unknown_arg3) {
        return false;
    }
    if (unknown_9c == 1 && unknown_id_source_a3d290->unknown_2238 == true) {
        return false;
    }
    if (!unknown_a4) {
        return false;
    }
    if (unknown_game_mode_a3d298 != 0 && !unknown_d0) {
        return false;
    }
    if (unknown_game_mode_a3d298 == 0) {
        if (unknown_id_source_a3d290->Difficulty == 0) {
            if (!unknown_d2) {
                return false;
            }
        } else if (unknown_id_source_a3d290->Difficulty == 1) {
            if (!unknown_d3) {
                return false;
            }
        } else if (unknown_id_source_a3d290->Difficulty == 2) {
            if (!unknown_d4) {
                return false;
            }
        }
    } else {
        if (house->unknown_c8 == 0) {
            if (!unknown_d4) {
                return false;
            }
        } else if (house->unknown_c8 == 1) {
            if (!unknown_d3) {
                return false;
            }
        } else if (house->unknown_c8 == 2) {
            if (!unknown_d2) {
                return false;
            }
        }
    }
    if (unknown_a0 == 0) {
        return false;
    }
    if (unknown_a0 != 2 && unknown_a0 == 1 && house->Type->House != unknown_a8) {
        return false;
    }
    if (unknown_ac == 1) {
        if (house->unknown_130 != 0) {
            return false;
        }
    } else if (unknown_ac == 2) {
        if (house->unknown_130 != 1) {
            return false;
        }
    }
    if (unknown_b0 > house->unknown_11c) {
        return false;
    }

    bool result;
    if (enemy != 0) {
        switch (ConditionType) {
        case -1:
            result = true;
            break;
        case 0:
            result = Enemy_Owns_Compare(house, enemy);
            break;
        case 1:
            result = House_Owns_Compare(house, enemy);
            break;
        case 2:
            result = Enemy_Power_Below_100(house, enemy);
            break;
        case 3:
            result = Enemy_Power_Below_0(house, enemy);
            break;
        case 4:
            result = Enemy_Money_Compare(house, enemy);
            break;
        case 5:
            result = Iron_Curtain_Ready(house, enemy);
            break;
        case 6:
            result = Chronosphere_Ready(house, enemy);
            break;
        case 7:
            result = Neutral_Owns_Compare(house, enemy);
            break;
        default:
            result = false;
            break;
        }
    } else if (ConditionType == 1) {
        result = House_Owns_Compare(house, 0);
    } else {
        result = ConditionType == -1;
    }
    if (!result) {
        return false;
    }

    if (!Team_Zone_Check(unknown_dc, house, enemy)) {
        return false;
    }
    if (unknown_e0 != 0 && !Team_Zone_Check(unknown_e0, house, enemy)) {
        return false;
    }
    if (!house->Can_Build_Team(unknown_dc)) {
        return false;
    }
    if (unknown_e0 != 0 && !house->Can_Build_Team(unknown_e0)) {
        return false;
    }
    if (unknown_dc != 0 && unknown_dc->Max >= 0 && house->Team_Count(unknown_dc) >= unknown_dc->Max) {
        return false;
    }
    if (unknown_e0 != 0 && unknown_e0->Max >= 0 && house->Team_Count(unknown_e0) >= unknown_e0->Max) {
        return false;
    }
    return true;
}
