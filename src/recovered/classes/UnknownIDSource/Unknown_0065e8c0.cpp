// void __fastcall Unknown_0065e8c0(bool official) (0x0065E8C0)
// Multiplayer setup once a scenario is read (Read_Scenario_INI): with fewer
// players than Rules MaxPlayers removes the unused computer-less houses, makes
// the units (the game mode's own creation when there is one, else
// Create_Units), places the starting crates (between Rules CrateMinimum and
// CrateMaximum), then gives every active non-passive house its anger delay
// and starting money bonus, marks the passive houses' types, allies every
// house with the Special house and lets the game mode finish the setup.
// @ref ??_C@_07GALJ@Special?$AA@=007cdd70
// @ref ?Create_Units_00660320@@YIX_N@Z=00660320
// @ref ?Unknown_0049C670@DisplayClass@@QAEXXZ=0049c670
// @ref ?Unknown_005B7CE0@UnknownSessionA3D29C@@QAEXXZ=005b7ce0
// @ref ?unknown_flags_a3f118@@3PA_NA=00a3f118
// @ref ?unknown_session_a3d55c@@3HA=00a3d55c
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/cd_timer.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"

void __fastcall Unknown_0065e8c0(bool official)
{
    if (unknown_players_a3fa7c.Count() + unknown_session_a3d298.AICount < Rules->MaxPlayers && !unknown_a40d13) {
        for (int index = 0; index < Houses.Count(); index++) {
            if (!Houses[index]->unknown_134 && !Houses[index]->Type->MultiplayPassive && unknown_session_a3d298.AICount < 1) {
                Houses[index]->unknown_func_4e7150();
            }
        }
    }
    Service_Game_IO_00481fb0();
    if (!unknown_a40d13) {
        int saved = unknown_a40774;
        unknown_a40774 = 0;
        if (unknown_session_a3d29c != 0) {
            unknown_session_a3d29c->unknown_slot27(official);
            unknown_session_a3d29c->Unknown_005B7CE0();
        } else {
            Create_Units_00660320(official);
        }
        unknown_a40774 = saved;
    }
    unknown_session_a3d298.Loading_Progress_00672160(93);
    Service_Game_IO_00481fb0();
    if (unknown_flag_a3d2c1) {
        int crates = Rules->CrateMinimum > unknown_session_a3d55c ? Rules->CrateMinimum : unknown_session_a3d55c;
        crates = crates < Rules->CrateMaximum ? crates : Rules->CrateMaximum;
        for (int crate = 0; crate < crates; crate++) {
            Map.Unknown_0054E410();
        }
    }
    Service_Game_IO_00481fb0();
    Map.Unknown_0049C670();
    HouseClass *special = HouseClass::As_Pointer(HouseTypeClass::Find_Index("Special"));
    for (int house = 0; house < Houses.Count(); house++) {
        Houses[house]->unknown_55f0.House = Houses[house];
        if (!Houses[house]->unknown_134 && !Houses[house]->Type->MultiplayPassive) {
            Houses[house]->unknown_5530 = CDTimerClass<FrameTimerClass>(Rules->AIHateDelays[Houses[house]->unknown_c8]);
            int money = Houses[house]->Available_Money();
            Houses[house]->Refund_Money(money * (Rules->MultiplayerAICM[Houses[house]->unknown_c8] * 0.01));
        }
        if (Houses[house]->Type->MultiplayPassive) {
            Houses[house]->Type->WallOwner = false;
        } else {
            Houses[house]->Type->WallOwner = true;
        }
        if (Houses[house] != special) {
            Houses[house]->Make_Ally(special, false);
            special->Make_Ally(Houses[house], false);
        }
    }
    if (unknown_session_a3d29c != 0) {
        unknown_session_a3d29c->unknown_slot28();
        unknown_session_a3d29c->unknown_slot29();
    }
    memset(unknown_flags_a3f118, 1, sizeof(unknown_flags_a3f118));
}
