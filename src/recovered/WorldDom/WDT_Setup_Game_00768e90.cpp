// int __fastcall WDT_Setup_Game_00768e90(bool first_time) (0x00768E90): sets up a World Domination
// Tour game (TibSun WDT_Setup_Game). Offers to drop to 640x480, mounts WDT.MIX, WDTVOX.MIX and
// Local.MIX, then runs the tour states until a mission is ready (6) or the player leaves (0):
// 1 faction choice, 2 theater movie, 3 theater choice, 4 cycle request and conflict choice,
// 5 the server's answer. Names are hypotheses.
#include "shared/wdt_faction_select.hpp"
#include "shared/wdt_selection.hpp"
#include "shared/wdt_campaign_layout.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cd.hpp"
#include "shared/string_table.hpp"
#include "shared/wide_string.hpp"
#include "shared/lobby.hpp"
#include "shared/main_opt.hpp"
#include "shared/options.hpp"
#include "shared/play_movie.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_07DBPJ@WDT?4MIX?$AA@=007fe6dc
// @ref ??_C@_0L@BMBG@WDTVOX?4MIX?$AA@=008005e0
// @ref ??_C@_09POBA@Local?4MIX?$AA@=008005d4
// @ref ??_C@_0BC@HGMB@WDTTheater?$CF02?4VQA?$AA@=008005c0
// @ref ??_C@_0BH@FLEG@WOL?3WDTResolutionQuery?$AA@=007ffe14
// @ref ??_7?$rc_ptr@VCampaign@WorldDominationTour@@@@6B@=007aefdc
// @ref ??_G?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref ??_E?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref ??0?$MixFileClass@VCCFileClass@@@@QAE@PBDPBVPKey@@@Z=005952f0
// @ref ??0FactionSelectDialogControl@WorldDominationTour@@QAE@XZ=00769790
// @ref ?Request_WDT_Cycle_00751df0@@YI_NXZ=00751df0
// @ref ?Unknown_00759e20@@YIHXZ=00759e20
// @ref ?WDT_Chosen_Side_b2ada4@@3HA=00b2ada4
// @ref ?WDT_Chosen_Theater_b2ada8@@3HA=00b2ada8
// @ref ?wol_max_players_b2abdc@@3HA=00b2abdc

using namespace WorldDominationTour;

int __fastcall Faction_Select_Dialog_00768c70();
int __fastcall Theater_Choice_Menu(int faction);
bool __fastcall Request_WDT_Cycle_00751df0();
int __fastcall Unknown_00759e20();

extern int WDT_Chosen_Side_b2ada4;
extern int WDT_Chosen_Theater_b2ada8;
extern int wol_max_players_b2abdc;
rc_ptr<Campaign> const &__fastcall Current_WDT_Campaign_00769670();
rc_ptr<Campaign> const &__fastcall Previous_WDT_Campaign_00769680();

int __fastcall WDT_Setup_Game_00768e90(bool first_time)
{
    if (unknown_8523e0 > 640) {
        WideString text(StringTable::Load_String("WOL:WDTResolutionQuery", 0, "D:\\Ra2\\WorldDom.cpp", 385));
        if (Message_Box_005c3230(text.Get(), 4, Unknown_0073e100, true) != 6) {
            return false;
        }
        if (!Test_Display_Mode(640, 480)) {
            return false;
        }
        Options.ScreenWidth = 640;
        Options.ScreenHeight = 480;
        Options.Save_Settings();
    }

    MixFileClass<CCFileClass> *wdtmix = 0;
    MixFileClass<CCFileClass> *wdtvoxmix = 0;
    MixFileClass<CCFileClass> *localmix = 0;

    if (CCFileClass("WDT.MIX").Is_Available()) {
        wdtmix = new MixFileClass<CCFileClass>("WDT.MIX", &FastKey);
    }
    if (CCFileClass("WDTVOX.MIX").Is_Available()) {
        wdtvoxmix = new MixFileClass<CCFileClass>("WDTVOX.MIX", &FastKey);
    }
    if (CCFileClass("Local.MIX").Is_Available()) {
        localmix = new MixFileClass<CCFileClass>("Local.MIX", &FastKey);
    }

    if (wdtmix != 0 && localmix != 0) {
        int state = first_time ? 4 : 1;
        while (state != 0 && state != 6) {
            switch (state) {
                case 1:
                    WDT_Chosen_Side_b2ada4 = Faction_Select_Dialog_00768c70();
                    state = WDT_Chosen_Side_b2ada4 != 0 ? 4 : 0;
                    break;
                case 2: {
                    char name[128];
                    sprintf(name, "WDTTheater%02.VQA", WDT_Chosen_Side_b2ada4);
                    if (CCFileClass(name).Is_Available()) {
                        Play_Movie(name, -1, false, true, false, false);
                    }
                    state = 3;
                    break;
                }
                case 3:
                    WDT_Chosen_Theater_b2ada8 = Theater_Choice_Menu(WDT_Chosen_Side_b2ada4);
                    state = WDT_Chosen_Theater_b2ada8 != 0 ? 4 : 1;
                    break;
                case 4: {
                    if (!Request_WDT_Cycle_00751df0()) {
                        state = 0;
                        break;
                    }
                    rc_ptr<Campaign> campaign = Current_WDT_Campaign_00769670();
                    if (campaign.Get() == 0) {
                        return false;
                    }
                    campaign->Set_Player_Faction(WDT_Chosen_Side_b2ada4);
                    if (campaign->ID_Differs()) {
                        rc_ptr<Campaign> previous = Previous_WDT_Campaign_00769680();
                        if (previous.Get() != 0 && !previous->ID_Differs()) {
                            Selection::Show(previous, WDT_Chosen_Theater_b2ada8);
                        }
                    }
                    unknown_a3d3bc = WDT_Chosen_Side_b2ada4 == 3;
                    if (Selection::Choose_Conflict(campaign, WDT_Chosen_Theater_b2ada8)) {
                        wol_max_players_b2abdc = 0;
                        unknown_map_generator_a6fd68.SeedOptions.Apply_WDT_Territory_00578bc0();
                        state = 5;
                    } else {
                        state = 1;
                    }
                    break;
                }
                case 5:
                    if (Unknown_00759e20() == 1) {
                        state = 6;
                    } else {
                        state = 4;
                    }
                    break;
            }
        }
        delete wdtmix;
        delete localmix;
        delete wdtvoxmix;
        return state == 6;
    }

    delete wdtmix;
    delete localmix;
    delete wdtvoxmix;
    return false;
}
