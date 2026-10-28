// int MPCooperative::unknown_slot13() -- 0x005A3200
// The multiplayer map index of the first cooperative campaign's first map (making the campaign
// records and the campaign on first use), or -1.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref __strnicmp=007858d0
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/multi_mission.hpp"
#include "shared/crt_tokens.hpp"

int MPCooperative::unknown_slot13()
{
    int count = 0;
    char *name = 0;
    if (unknown_campaigns_40 == 0) {
        unknown_campaigns_40 = new UnknownDescriptionList_00490E00();
    }
    unknown_campaigns_40->Get_Count_00490C90(&count);
    if (count != 0) {
        if (unknown_campaign_44 == 0) {
            unknown_campaign_44 = new CoopCampaignClass();
        }
        unknown_campaign_44->Load_Campaign_0048f590(0);
        unknown_campaign_44->Get_Map_Name_0048fb40(&name, 0);
        for (int i = 0; i < unknown_multi_missions_a3d8d8.Count(); i++) {
            char const *scenario = unknown_multi_missions_a3d8d8[i]->unknown_58;
            if (_strnicmp(scenario, name, strlen(name)) == 0) {
                return i;
            }
        }
        unknown_slot4();
    }
    return -1;
}
