// bool MPCooperative::unknown_slot4() -- 0x005A2D70
// Rebuilds the campaign list: deletes the old campaigns and loads one per campaign record.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"

bool MPCooperative::unknown_slot4()
{
    int i;
    for (i = unknown_campaigns_328.Count() - 1; i >= 0; i--) {
        CoopCampaignClass *campaign = unknown_campaigns_328[i];
        if (campaign != 0) {
            delete campaign;
        }
    }
    int capacity = unknown_campaigns_328.Length();
    unknown_campaigns_328.Clear();
    unknown_campaigns_328.Resize(capacity, 0);
    int count;
    unknown_campaigns_40->Get_Count_00490C90(&count);
    for (i = 0; i < count; i++) {
        CoopCampaignClass *campaign = new CoopCampaignClass();
        campaign->Load_Campaign_0048f590(i);
        unknown_campaigns_328.Add(campaign);
    }
    return true;
}
