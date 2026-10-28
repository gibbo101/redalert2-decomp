// bool MPCooperative::unknown_slot19(int index, int time, MPlayerScoreType *scores) -- 0x005A35D0
// Refreshes the side combos once after a campaign change and records the two players' scores
// for the campaign map.
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?Unknown_005A3760@MPCooperative@@QAEXPAUHWND__@@@Z=005a3760
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/mplayer_score_type.hpp"

bool MPCooperative::unknown_slot19(int index, int time, MPlayerScoreType *scores)
{
    if (unknown_campaign_44 == 0) {
        return false;
    }
    HWND lobby = Get_Lobby_Dialog_005c2c40();
    if (lobby != 0 && unknown_344) {
        Unknown_005A3760(lobby);
        unknown_344 = false;
    }
    return unknown_campaign_44->Add_Score_0048f730(index, time, scores[0], scores[1]);
}
