// void __fastcall WDT_Store_Previous_007695a0(rc_ptr<WDTState> const &state) (0x007695A0): keeps the
// previous cycle's tour state from the WOL callback and builds that campaign from it (TibSun
// WDT_Resume_Campaign).
#include "shared/wol_sink.hpp"
#include "shared/world_domination_tour.hpp"
#include "shared/wdt_campaign_layout.hpp"
// @ref ?WDT_Previous_State_b2ad80@@3V?$rc_ptr@VWDTState@@@@A=00b2ad80
// @ref ?WDT_Previous_Campaign_b2ad88@@3V?$rc_ptr@VCampaign@WorldDominationTour@@@@A=00b2ad88
// @ref ??_7?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@6B@=007af024
// @ref ??_G?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@UAEPAXI@Z=00726ac0
// @ref ??_E?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@UAEPAXI@Z=00726ac0

extern rc_ptr<WDTState> WDT_Previous_State_b2ad80;
extern rc_ptr<WorldDominationTour::Campaign> WDT_Previous_Campaign_b2ad88;

void __fastcall WDT_Store_Previous_007695a0(rc_ptr<WDTState> const &state)
{
    WDT_Previous_State_b2ad80 = state;
    WDT_Previous_Campaign_b2ad88 = WorldDominationTour::Campaign::Create(unknown_wstring_b26cb8,
        WorldDominationTour::CampaignProperties::Create(state));
}
