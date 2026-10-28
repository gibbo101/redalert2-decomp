// int MPCooperative::unknown_slot24() -- 0x005A45F0
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/house_type.hpp"
#include "shared/debug_printf.hpp"
#include "shared/lobby.hpp"
#include "shared/id_source.hpp"

// @ref ??_C@_0CJ@LBI@?$EA?$EA?$EA?$EA?5Choosing?5a?5random?5AI?5house?3@=007e36c0
// @ref ?Find_Country_Index_004904A0@@YIHPBD@Z=004904a0
int MPCooperative::unknown_slot24()
{
    int count = HouseTypes.Count();
    bool found = false;
    int campaign = 0;
    unknown_campaign_44->Get_Campaign_Type_0048e6b0(&campaign);
    UnknownDescriptionRecord_00490E00 *record;
    unknown_campaigns_40->Get_Record_00490C50(campaign, &record);
    int house;
    do {
        house = unknown_id_source_a3d290->Random()(0, count - 1);
        for (int i = 0; i < record->Enemies.Count(); i++) {
            if (house == Find_Country_Index_004904A0(record->Enemies[i])) {
                found = true;
            }
        }
    } while (!found);
    Debug_Printf("@@@@ Choosing a random AI house: %d(%s)\n", house, Unknown_006FA120(HouseTypes[house]->UIName));
    return house;
}
