// bool MPCooperative::unknown_slot5(WideString *message) -- 0x005A32E0
// Names the campaign after the two players when there are two, then the base check.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ?unknown_slot5@MultiplayerGameMode@@UAE_NPAVWideString@@@Z=005b73a0
// @ref ?Set_Names@CoopCampaignClass@@QAEXPBG0@Z=0048e190
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"

bool MPCooperative::unknown_slot5(WideString *message)
{
    if (unknown_players_a3fa7c.Count() == 2 && unknown_campaign_44 != 0) {
        unknown_campaign_44->Set_Names(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
    }
    return MultiplayerGameMode::unknown_slot5(message);
}
