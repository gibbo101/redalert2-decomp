// bool __fastcall Selection::Choose_Conflict(rc_ptr<Campaign> const &campaign, int faction) (0x0072FFC0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
#include "shared/options_dialog.hpp"
#include "shared/unknown_globals.hpp"
namespace WorldDominationTour {
bool __fastcall Selection::Choose_Conflict(rc_ptr<Campaign> const &campaign, int faction)
{
    if (!campaign.Get()) {
        return false;
    }
    Selection selection(campaign, faction);
    selection.Show_Campaign();
    selection.Show_Progress(faction);
    rc_ptr<Territory> territory = selection.Choose_Territory();
    bool chosen = territory.Get() != 0;
    if (chosen) {
        unknown_session_a3d2a0 = territory->Index;
        rc_ptr<WDTTerritory> settings = Unknown_Territory_00769690(unknown_session_a3d2a0);
        if (settings.Get()) {
            unknown_session_a3d298.UnitCount = settings->UnitCount;
            unknown_house_setting_7d88d8 = settings->TechLevel;
            unknown_session_a3d298.unknown_24 = settings->unknown_10;
            unknown_session_a3d298.unknown_a4 = (settings->OptionFlags & 0x4) != 0;
            unknown_session_a3d298.unknown_a5 = false;
            unknown_session_a3d298.unknown_bases_20 = (settings->OptionFlags & 0x10) != 0;
            unknown_session_a3d298.unknown_a8 = (settings->OptionFlags & 0x20) != 0;
            unknown_session_a3d298.unknown_fog_a7 = false;
            unknown_session_a3d298.unknown_28 = true;
            unknown_session_a3d298.unknown_crates_29 = (settings->OptionFlags & 0x100) != 0;
            unknown_session_a3d298.unknown_2a = (settings->OptionFlags & 0x400) != 0;
            unknown_session_a3d298.unknown_2b = (settings->OptionFlags & 0x200) != 0;
            unknown_session_a3d298.unknown_2c = false;
            unknown_session_a3d298.AICount = 0;
            unknown_session_a3d298.unknown_difficulty_40 = 1;
        } else {
            chosen = false;
        }
    }
    return chosen;
}
}
// @ref ??_C@_0BC@PBP@D?3?2Ra2?2WDTSel?4cpp?$AA@=007fc31c
// @ref ??_C@_0BL@MEDD@WDT?3TerritorySelectToolTip?$AA@=007fc454
// @ref ?Unknown_Territory_00769690@@YI?AV?$rc_ptr@VWDTTerritory@@@@H@Z=00769690
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_session_a3d2a0@@3HA=00a3d2a0
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
