// TypeList<TeamTypeClass const *> TeamTypeClass::Suggested_New_Teams(HouseClass *house, bool alerted) (0x006BED50)
// The team types a house may make now: when its AI triggers are on and a 1-100 roll is within its ratio, enforce the
// team caps (dropping the oldest base defense team when over the cap), pick one ready AI trigger by weight (weight 5000
// triggers exclude all others) and take its one or two team types; nothing when a team of a suggested type is
// already idle or reforming. The suggested types are marked autocreate.
#include "shared/team_type.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/unit.hpp"
#include "shared/ai_trigger_type.hpp"
#include "shared/discrete_distribution.hpp"
#include "shared/id_source.hpp"
#include "shared/debug_printf.hpp"
// @ref ??0?$DynamicVectorClass@PBVTeamTypeClass@@@@QAE@IPBQBVTeamTypeClass@@@Z=006c03e0
// @ref ??4?$VectorClass@PBVTeamTypeClass@@@@QAEAAV0@ABV0@@Z=006c0930
// @ref ??0?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@QAE@IPBV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c09a0
// @ref ?Add@?$DynamicVectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@QAE_NABV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c0790
// @ref ??_E?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@QAEPAXI@Z=006c0890
// @ref ?Clear@?$DynamicVectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEXXZ=006c0360
// @ref ??_7?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@6B@=007aca60
// @ref ??_7?$DynamicVectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@6B@=007aca80
// @ref ??_7?$TypeList@PBVTeamTypeClass@@@@6B@=007a2ec4
// @ref ??_7?$VectorClass@PBVTeamTypeClass@@@@6B@=007a2ee4
// @ref ??_G?$TypeList@PBVTeamTypeClass@@@@UAEPAXI@Z=004f6ee0
// @ref ??_G?$VectorClass@PBVTeamTypeClass@@@@UAEPAXI@Z=004f8710
// @ref ??8?$VectorClass@PBVTeamTypeClass@@@@UBE_NABV0@@Z=004f7be0
// @ref ?Resize@?$VectorClass@PBVTeamTypeClass@@@@UAE_NHPBQBVTeamTypeClass@@@Z=004f7c20
// @ref ?Clear@?$VectorClass@PBVTeamTypeClass@@@@UAEXXZ=004f7cd0
// @ref ?ID@?$VectorClass@PBVTeamTypeClass@@@@UAEHABQBVTeamTypeClass@@@Z=004f7d00
// @ref ?ID@?$VectorClass@PBVTeamTypeClass@@@@UAEHPBQBVTeamTypeClass@@@Z=004f7d40
// @ref ?Fetch@?$VectorClass@PBVTeamTypeClass@@@@UBEPBVTeamTypeClass@@H@Z=004f6df0
// @ref ??_7?$DynamicVectorClass@PBVTeamTypeClass@@@@6B@=007a2fec
// @ref ??_G?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEPAXI@Z=004f6fc0
// @ref ?Resize@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAE_NHPBQBVTeamTypeClass@@@Z=004f7d60
// @ref ?Clear@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEXXZ=004f6da0
// @ref ?ID@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEHABQBVTeamTypeClass@@@Z=004f7e10
// @ref ?ID@?$DynamicVectorClass@PBVTeamTypeClass@@@@UAEHPBQBVTeamTypeClass@@@Z=004f6dd0
// @ref ??_G?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEPAXI@Z=006c0830
// @ref ??8?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UBE_NABV0@@Z=006c0440
// @ref ?Resize@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAE_NHPBV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c04a0
// @ref ?Clear@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEXXZ=006c05b0
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEHABV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c05f0
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEHPBV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c0640
// @ref ?Fetch@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UBE?AV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@H@Z=006c03c0
// @ref ?Resize@?$DynamicVectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAE_NHPBV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c0660
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEHABV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c07f0
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEHPBV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c03a0
// @ref ?Is_Ready@AITriggerTypeClass@@QBE_NPAVHouseClass@@0_N@Z=0041c990
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0DB@IAHD@Infinite?5weight?5AIT?5hit?$DL?5clearin@=007f6f80
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

TypeList<TeamTypeClass const *> __fastcall TeamTypeClass::Suggested_New_Teams(HouseClass *house, bool alerted)
{
    int index;
    bool skip_base_defense;

    TypeList<TeamTypeClass const *> best;
    HouseClass *enemy = 0;

    if (house->unknown_54f0 != -1) {
        enemy = Houses[house->unknown_54f0];
    }
    if (Random_Pick(1, 100) <= house->unknown_554c && house->unknown_13a) {
        int team_count = 0;
        int defense_team_count = 0;
        for (index = 0; index < Teams.Count(); index++) {
            if (Teams[index]->Owner == house) {
                team_count++;
                if (Teams[index]->Class->IsBaseDefense) {
                    defense_team_count++;
                }
            }
        }

        skip_base_defense = false;
        if (team_count < Rules->TotalAITeamCap[house->unknown_c8] || defense_team_count < team_count / 2) {
            if (defense_team_count > Rules->MaximumAIDefensiveTeams[house->unknown_c8]) {
                skip_base_defense = true;
            }
        } else {
            TeamClass *team = 0;
            int frame = 0x7FFFFFFF;
            for (index = 0; index < Teams.Count(); index++) {
                TeamClass *t = Teams[index];
                if (t->Owner == house) {
                    if (t->Class->IsBaseDefense) {
                        if (t->unknown_50 < frame) {
                            team = t;
                            frame = t->unknown_50;
                        }
                    }
                }
            }
            if (team != 0) {
                team_count--;
                skip_base_defense = true;
                delete team;
            }
        }

        if (team_count < Rules->TotalAITeamCap[house->unknown_c8]) {
            DiscreteDistributionClass<AITriggerTypeClass> trigdist;
            bool exclusive = false;
            for (index = 0; index < AITriggerTypes.Count(); index++) {
                if (AITriggerTypes[index] != 0) {
                    AITriggerTypeClass *trig = AITriggerTypes[index];
                    if (trig->Is_Ready(house, enemy, skip_base_defense) == true) {
                        int weight = (int)trig->Weight;
                        if (weight == 5000) {
                            if (!exclusive) {
                                exclusive = true;
                                trigdist.Clear();
                                Debug_Printf("Infinite weight AIT hit; clearing distribution.\n");
                            }
                        } else if (exclusive) {
                            continue;
                        }
                        trigdist.Add(trig, weight);
                    }
                }
            }
            AITriggerTypeClass *trig = trigdist.Sample();
            if (trig != 0) {
                TeamTypeClass const *first = trig->unknown_dc;
                if (first != 0) {
                    best.Add(first);
                }
            }
            if (trig != 0) {
                TeamTypeClass const *second = trig->unknown_e0;
                if (second != 0) {
                    best.Add(second);
                }
            }
        }
    }

    for (index = 0; index < Teams.Count(); index++) {
        if (Teams[index]->Owner == house && (Teams[index]->IsReforming || !Teams[index]->IsMoving)) {
            int j = 0;
            if (j < best.Count()) {
                TeamTypeClass *cls = Teams[index]->Class;
                while (true) {
                    if (cls == best[j]) {
                        best.Clear();
                        return best;
                    }
                    j++;
                    if (j >= best.Count()) {
                        break;
                    }
                }
            }
        }
    }

    for (index = 0; index < best.Count(); index++) {
        TeamTypeClass *ttype = (TeamTypeClass *)best[index];
        ttype->Autocreate = true;
    }

    return best;
}
