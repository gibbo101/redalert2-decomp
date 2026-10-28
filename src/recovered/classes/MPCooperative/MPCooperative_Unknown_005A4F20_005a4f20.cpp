// bool MPCooperative::Unknown_005A4F20() -- 0x005A4F20 (true extent 111 B; the inventory says 41)
// Replaces the selected campaign with a freshly loaded first campaign (named after the two players when there are two).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_player_entry.hpp"

bool MPCooperative::Unknown_005A4F20()
{
    if (unknown_campaign_44 != 0) {
        delete unknown_campaign_44;
    }
    unknown_campaign_44 = 0;
    unknown_campaign_44 = new CoopCampaignClass();
    unknown_campaign_44->Load_Campaign_0048f590(0);
    if (unknown_players_a3fa7c.Count() == 2) {
        unknown_campaign_44->Set_Names(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
    }
    return (unknown_campaign_44 != 0) ? true : false;
}
