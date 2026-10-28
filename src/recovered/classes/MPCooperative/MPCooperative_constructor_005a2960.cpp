// MPCooperative::MPCooperative(name, description, ini_name, unknown_4, unknown_5, id) -- 0x005A2960
// The base mode with unknown_5 false; makes the campaign records and one CoopCampaignClass per record.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
// @ref ??_7MPCooperative@@6B@=007a678c
// @ref ??0?$VectorClass@PAUNodeNameType@@@@QAE@IPBQAUNodeNameType@@@Z=005a6dd0
// @ref ??_7?$DynamicVectorClass@PAUNodeNameType@@@@6B@=007a6864
// @ref ??0?$VectorClass@H@@QAE@IPBH@Z=0046d020
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??0?$VectorClass@PAVCoopCampaignClass@@@@QAE@IPBQAVCoopCampaignClass@@@Z=005a6e20
// @ref ??_7?$DynamicVectorClass@PAVCoopCampaignClass@@@@6B@=007a6844
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"

MPCooperative::MPCooperative(WideString const &name, WideString const &description, Wstring const &ini_name,
    Wstring const &unknown_4, bool unknown_5, int id)
    : MultiplayerGameMode(name, description, ini_name, unknown_4, false, id)
{
    unknown_campaigns_40 = new UnknownDescriptionList_00490E00();
    unknown_campaign_44 = 0;
    unknown_48 = 0;
    unknown_340 = 0;
    unknown_score_54 = 0;
    unknown_04 = false;
    unknown_4c = false;
    unknown_4d = false;
    unknown_50 = 0;
    unknown_344 = true;
    for (int i = unknown_campaigns_328.Count() - 1; i >= 0; i--) {
        delete unknown_campaigns_328[i];
    }
    DynamicVectorClass<CoopCampaignClass *> &campaigns = unknown_campaigns_328;
    int length = campaigns.Length();
    campaigns.Clear();
    campaigns.Resize(length);
    int count;
    unknown_campaigns_40->Get_Count_00490C90(&count);
    for (i = 0; i < count; i++) {
        CoopCampaignClass *campaign = new CoopCampaignClass();
        campaign->Load_Campaign_0048f590(i);
        unknown_campaigns_328.Add(campaign);
    }
}
