// void __fastcall Assign_Houses_0065fbb0() (0x0065FBB0)
// Makes the houses of a multiplayer game: one per player, lowest colour
// first (the first player's house is the player's; a WOL game names it after
// the player), then one per computer player set in the session (country,
// colour and difficulty, one easier with CompEasyBonus), then Neutral and
// Special in light grey. Random countries are drawn first.
// @ref ??_C@_07BKIB@Neutral?$AA@=007e14b8
// @ref ??_C@_07GALJ@Special?$AA@=007cdd70
// @ref ??_C@_08CJPC@Computer?$AA@=007daa28
// @ref ??_C@_09LBMK@LightGrey?$AA@=007ebfc4
// @ref ??_C@_0BE@DADK@D?3?2Ra2?2Scenario?4CPP?$AA@=007f1df0
// @ref ??_C@_0N@LAJB@TXT_COMPUTER?$AA@=007d1634
// @ref ??_C@_0P@JHCC@?$DMhuman?5player?$DO?$AA@=007f2200
// @ref ?Narrow_Copy_00771280@@YI?AVWstring@@ABVWideString@@@Z=00771280
// @ref ?Unknown_006715D0@UnknownSessionState@@QAEHH@Z=006715d0
// @ref ?unknown_66e2d0@NodeNameType@@QAEXH@Z=0066e2d0
// @ref ?unknown_house_a72d28@@3PAVHouseClass@@A=00a72d28
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref _strncpy=007823d0
#include "shared/id_source.hpp"
#include "shared/ccini_class.hpp"
#include "shared/house.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/string_table.hpp"
#include "shared/wstring.hpp"
#include "shared/wide_string.hpp"
#include "shared/rules.hpp"

void __fastcall Assign_Houses_0065fbb0()
{
    int count = unknown_players_a3fa7c.Count();
    for (int index = 0; index < count; index++) {
        if (unknown_players_a3fa7c[index]->unknown_4b == -3) {
            unknown_players_a3fa7c[index]->unknown_66e2d0(0);
        }
    }

    bool taken[8];
    memset(taken, 0, sizeof(taken));
    unknown_house_a72d28 = 0;
    for (int house_count = 0; house_count < count; house_count++) {
        int pick = -1;
        int lowest = -1;
        for (int other = 0; other < count; other++) {
            if (!taken[other] && (lowest == -1 || unknown_players_a3fa7c[other]->unknown_53 < lowest)) {
                pick = other;
                lowest = unknown_players_a3fa7c[other]->unknown_53;
            }
        }
        NodeNameType *player = unknown_players_a3fa7c[pick];
        taken[pick] = true;
        HouseClass *house = new HouseClass(HouseTypes[player->unknown_4b]);
        if (unknown_game_mode_a3d298 == 4) {
            Wstring name = Narrow_Copy_00771280(player->Name);
            house->IniName = FixedString<21>(name.Get());
        } else {
            house->IniName = FixedString<21>("<human player>");
        }
        wcsncpy(house->UIName, player->Name, 21);
        house->UIName[20] = 0;
        house->unknown_134 = true;
        house->unknown_func_4e8300(player->unknown_53, player->unknown_4b, unknown_session_a3d298.unknown_24);
        house->ColorSchemeIndex = unknown_session_a3d298.Unknown_006715D0(player->unknown_53);
        house->Update_Color();
        house->Update_Laser_Color();
        if (pick == 0) {
            unknown_player_a35db4 = house;
            house->unknown_135 = true;
        }
        if (player->Team == -1) {
            unknown_house_a72d28 = house;
        }
        house->unknown_11c = unknown_house_setting_7d88d8;
        house->Assign_Handicap(1);
        player->ID = house->ArrayIndex;
    }

    int computers = unknown_session_a3d298.AICount;
    int made = 0;
    for (int slot = 0; slot < 8; slot++) {
        if (made < computers && unknown_session_a3d298.AICountry[slot] != -1 && unknown_session_a3d298.AICountry[slot] != -3) {
            int country = unknown_session_a3d298.AICountry[slot];
            int color = unknown_session_a3d298.AIColor[slot];
            made++;
            HouseClass *house = new HouseClass(HouseTypes[country]);
            house->unknown_11c = unknown_house_setting_7d88d8;
            house->unknown_134 = false;
            house->unknown_func_4e8300(color, country, unknown_session_a3d298.unknown_24);
            house->ColorSchemeIndex = unknown_session_a3d298.Unknown_006715D0(color);
            house->Update_Color();
            house->Update_Laser_Color();
            house->IniName = FixedString<21>("Computer");
            wcscpy(house->UIName, StringTable::Load_String("TXT_COMPUTER", 0, "D:\\Ra2\\Scenario.CPP", 3947));
            if (unknown_game_mode_a3d298 != 0) {
                house->unknown_194 = Rules->MaxIQ;
            }
            int difficulty = unknown_session_a3d298.AIDifficulty[slot];
            if (unknown_players_a3fa7c.Count() > 1 && Rules->CompEasyBonus && difficulty > 0) {
                difficulty--;
            }
            house->Assign_Handicap(difficulty);
        }
    }

    HouseClass *neutral = new HouseClass(HouseTypes[HouseTypeClass::Find_Index("Neutral")]);
    neutral->ColorSchemeIndex = unknown_color_scheme_index_663d90("LightGrey", 0x35);
    neutral->Update_Color();
    HouseClass *special = new HouseClass(HouseTypes[HouseTypeClass::Find_Index("Special")]);
    special->ColorSchemeIndex = unknown_color_scheme_index_663d90("LightGrey", 0x35);
    special->Update_Color();
}
