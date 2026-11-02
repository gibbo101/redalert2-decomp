// void __fastcall WDT_Store_Current_00769520(rc_ptr<WDTState> const &state) (0x00769520): keeps the
// current cycle's tour state from the WOL callback and builds the player's campaign from it (TibSun
// WDT_Start_New_Campaign).
#include "shared/wol_sink.hpp"
#include "shared/world_domination_tour.hpp"
#include "shared/wdt_campaign_layout.hpp"
// @ref ?WDT_Current_State_b2ad68@@3V?$rc_ptr@VWDTState@@@@A=00b2ad68
// @ref ?WDT_Current_Campaign_b2ad78@@3V?$rc_ptr@VCampaign@WorldDominationTour@@@@A=00b2ad78
// @ref ??_7?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@6B@=007af024
// @ref ??_G?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@UAEPAXI@Z=00726ac0
// @ref ??_E?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@UAEPAXI@Z=00726ac0

extern rc_ptr<WDTState> WDT_Current_State_b2ad68;
extern rc_ptr<WorldDominationTour::Campaign> WDT_Current_Campaign_b2ad78;

void __fastcall WDT_Store_Current_00769520(rc_ptr<WDTState> const &state)
{
    WDT_Current_State_b2ad68 = state;
    WDT_Current_Campaign_b2ad78 = WorldDominationTour::Campaign::Create(unknown_wstring_b26cb8,
        WorldDominationTour::CampaignProperties::Create(state));
}
