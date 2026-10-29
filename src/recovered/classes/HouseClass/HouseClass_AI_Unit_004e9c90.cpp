// int HouseClass::AI_Unit() (0x004E9C90)
// Picks the unit type to build next: a harvester while refineries lack them for the teams (RA's AI_Unit).
#include "shared/house.hpp"
#include "shared/techno.hpp"
#include "shared/unit.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"
// @ref ??_7?$DynamicVectorClass@PAVTechnoTypeClass@@@@6B@=007a0f44
// @ref ??_E?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=004ba370
// @ref ??_G?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=004ba370
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=004ba240
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEXXZ=004ba060
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=004ba2f0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=004ba090
// @ref ??_7?$VectorClass@PAVTechnoTypeClass@@@@6B@=007a0f64
// @ref ??_E?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=004ba320
// @ref ??_G?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=004ba320
// @ref ??8?$VectorClass@PAVTechnoTypeClass@@@@UBE_NABV0@@Z=004ba0c0
// @ref ?Resize@?$VectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=004ba100
// @ref ?Clear@?$VectorClass@PAVTechnoTypeClass@@@@UAEXXZ=004ba1b0
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=004ba1e0
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=004ba220
// @ref ?Fetch@?$VectorClass@PAVTechnoTypeClass@@@@UBEPAVTechnoTypeClass@@H@Z=004ba0b0
// @ref ??0?$VectorClass@PAVTechnoTypeClass@@@@QAE@IPBQAVTechnoTypeClass@@@Z=004ba3c0
// @ref ??_V@YAXPAX@Z=00781d3b

int HouseClass::AI_Unit()
{
    if (unknown_5540 != -1) return 15;

    int harvesters = unknown_5470.unknown_func_491d10(Unknown_004EF6F0(Rules->unknown_9ec)->ArrayIndex);
    int refineries = unknown_5460.unknown_func_491d10(Rules->BuildRefinery[0]->ArrayIndex)
        + unknown_5460.unknown_func_491d10(Rules->BuildRefinery[1]->ArrayIndex);
    int per_refinery = Rules->HarvestersPerRefinery;
    if (unknown_194 >= Rules->IQHarvester && !unknown_189 && !Is_Human_Control()
            && per_refinery * refineries > harvesters) {
        if ((unsigned)Unknown_004EF6F0(Rules->unknown_9ec)->TechLevel <= (unsigned)unknown_11c) {
            unknown_5540 = Unknown_004EF6F0(Rules->unknown_9ec)->ArrayIndex;
            return 15;
        }
    }

    int counter[100];
    int earliest[100];
    int bestlist[100];
    memset(counter, 0, sizeof(counter));
    for (int x = 0; x < 100; x++) earliest[x] = 0x7FFFFFFF;

    for (int index = 0; index < Teams.Count(); index++) {
        TeamClass *team = Teams[index];
        if (team != 0) {
            TeamTypeClass *type = team->Class;
            int age = team->unknown_50;
            if (((type->Reinforce && !team->IsFullStrength) || (!team->IsForcedActive && !team->IsHasBeen)) && team->Owner == this) {
                DynamicVectorClass<TechnoTypeClass *> needed;
                team->unknown_func_6bd870(needed);
                for (int subindex = 0; subindex < needed.Count(); subindex++) {
                    TechnoTypeClass *member = needed[subindex];
                    if (member->Kind_Of() == 0x28) {
                        counter[((UnitTypeClass *)member)->ArrayIndex]++;
                        if (age < earliest[((UnitTypeClass *)member)->ArrayIndex]) earliest[((UnitTypeClass *)member)->ArrayIndex] = age;
                    }
                }
            }
        }
    }

    for (int uindex = 0; uindex < Units.Count(); uindex++) {
        UnitClass *unit = Units[uindex];
        if (unit != 0 && unit->unknown_4c8d00(this) && counter[unit->Type->ArrayIndex] > 0) {
            counter[unit->Type->ArrayIndex]--;
        }
    }

    int bestval = -1;
    int bestcount = 0;
    int best = -1;
    int bestearliest = 0x7FFFFFFF;
    for (int utype = 0; utype < UnitTypes.Count(); utype++) {
        int count = counter[utype];
        if (count > 0 && unknown_4e3660(UnitTypes[utype], 0, 0)
                && UnitTypes[utype]->unknown_slot33((int)this) <= Available_Money()) {
            if (bestval == -1 || bestval < count) {
                bestval = count;
                bestcount = 0;
            }
            bestlist[bestcount++] = utype;
            if (best == -1 || earliest[utype] < bestearliest) {
                best = utype;
                bestearliest = earliest[utype];
            }
        }
    }

    double chance = Random_Pick(0, 0x7FFFFFFE) * (1.0 / 2147483646.0);
    if (chance < Rules->FillEarliestTeamProbability[unknown_c8] * 0.01) {
        unknown_5540 = best;
    } else if (bestcount) {
        unknown_5540 = bestlist[Random_Pick(0, bestcount - 1)];
    }
    return 15;
}
