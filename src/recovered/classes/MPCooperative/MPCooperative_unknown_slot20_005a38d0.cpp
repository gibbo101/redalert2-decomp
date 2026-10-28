// bool MPCooperative::unknown_slot20() -- 0x005A38D0
// Refreshes the side combos once after a campaign change and sends the campaign options.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?Unknown_005A3760@MPCooperative@@QAEXPAUHWND__@@@Z=005a3760
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/lobby.hpp"

bool MPCooperative::unknown_slot20()
{
    if (unknown_campaign_44 == 0) {
        return false;
    }
    unknown_campaign_44->Get_Campaign_Type_0048e6b0(&unknown_340);
    HWND lobby = Get_Lobby_Dialog_005c2c40();
    if (lobby != 0 && unknown_344) {
        Unknown_005A3760(lobby);
        unknown_344 = false;
    }
    return unknown_campaign_44->Send_Campaign_Options_00490150(*unknown_campaigns_40);
}
