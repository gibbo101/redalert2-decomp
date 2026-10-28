// bool __fastcall Unknown_0065c7d0(char const *name) (0x0065C7D0)
// @ref ??_C@_04OEPM@?4SED?$AA@=007f2040
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BA@FOMN@xxx?4xxx?4xxx?4xxx?$AA@=007e38d0
// @ref ??_C@_0BE@DADK@D?3?2Ra2?2Scenario?4CPP?$AA@=007f1df0
// @ref ??_C@_0BH@IMMC@Scen?9?$DOIsRandom?5?$DN?5true?6?$AA@=007f2028
// @ref ??_C@_0BI@LJGK@Scen?9?$DOIsRandom?5?$DN?5false?6?$AA@=007f2010
// @ref ??_C@_0BJ@IMPI@TXT_UNABLE_READ_SCENARIO?$AA@=007e7180
// @ref ??_C@_0BN@CIP@Adding?5broadcast?5address?5?$CFs?6?$AA@=007f1f94
// @ref ??_C@_0CF@MHJP@Setting?5addresses?5for?5UDP?5broadc@=007f1fc0
// @ref ??_C@_0L@EJKK@SPLDBR?4SHP?$AA@=007f1ff8
// @ref ??_C@_0M@IBML@?$CFd?4?$CFd?4?$CFd?4?$CFd?$AA@=007f1fb4
// @ref ??_C@_0M@INGE@TXT_GAME_ID?$AA@=007f2004
// @ref ??_C@_0N@LJCA@PROGBARM?4SHP?$AA@=007f1fe8
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ?Fill_In_Data_0065cdd0@@YAXXZ=0065cdd0
// @ref ?MapSeed@@3VMapSeedClass@@A=00a6fd68
// @ref ?Read_Scenario_0065e760@@YI_NPBD_N@Z=0065e760
// @ref ?Unknown_005359E0@Unknown535910@@QAEXXZ=005359e0
// @ref ?Unknown_00535AB0@Unknown535910@@QAE?AUPoint2D@@XZ=00535ab0
// @ref ?Unknown_00535B60@Unknown535910@@QAEHXZ=00535b60
// @ref ?Unknown_00535B90@Unknown535910@@QAEXXZ=00535b90
// @ref ?Unknown_00536E20@Unknown535910@@QAEXXZ=00536e20
// @ref ?Unknown_0057A0D0@MapSeedClass@@QAEXHH@Z=0057a0d0
// @ref ?Unknown_0061EFA0@ProgressScreenClass@@QAEXUPoint2D@@PBG_N2@Z=0061efa0
// @ref ?Unknown_00672440@UnknownSessionState@@QAEXXZ=00672440
// @ref ?Wait_For_Players_0065c520@@YI_NXZ=0065c520
// @ref ?unknown_b2a7fc@@3HA=00b2a7fc
// @ref ?Wait_For_Router_Shutdown@OwnerTalkClass@@QAE_NK_N@Z=0063fd70
// @ref ??_C@_0CF@HGGO@Error?5?9?5Unable?5to?5read?5scenario?3@=007f1f6c
// Start_Scenario's reader (Westwood's Read_Scenario shape; name hypothesis):
// copies the name, resets the frame counter, marks the load in progress
// (+0x22FC) and a ".SED" name as a random map (+0x223B). Unless 0x00A40D13
// is set, opens the progress screen (one player in a campaign or game mode 5;
// the game ID text in an online game), its listener 0x00535910, the side and
// the bar shape, and in an online game adds every other player's IP as a UDP
// broadcast address. Reads a random map through MapSeed (and its multiplayer
// setup) or the scenario file; on failure shows "unable to read" and returns
// false. Then places the message list, fills in the data, reports 99 percent
// and (online, forwarding) waits for the router, reports 100 (200 for a random
// map) and waits for the other players; when they are in, runs the progress
// bars to full. Clears the progress screen and its listener.
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/progress_screen.hpp"
#include "shared/map_seed.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/campaign.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/gscreen.hpp"
#include "shared/connection.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/cd_timer.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/audio.hpp"
#include "shared/owner_talk.hpp"

bool __fastcall Unknown_0065c7d0(char const *name)
{
    char filename[260];
    strcpy(filename, name);
    Frame = 0;
    unknown_id_source_a3d290->unknown_22fc = true;
    unknown_a40774++;
    char *extension = &filename[strlen(filename) - 4];
    if (_stricmp(extension, ".SED") == 0) {
        unknown_id_source_a3d290->unknown_223b = true;
        Debug_Printf("Scen->IsRandom = true\n");
    } else {
        unknown_id_source_a3d290->unknown_223b = false;
        Debug_Printf("Scen->IsRandom = false\n");
    }

    Unknown535910 *loader = 0;
    if (!unknown_flag_a40d13) {
        int players = 1;
        if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
            players = unknown_players_a3fa7c.Count();
        }
        ProgressScreen.Init(100.0, players, 0);
        wchar_t const *game_id = 0;
        wchar_t text[130];
        if (unknown_game_mode_a3d298 == 4 && unknown_b2a7ec != 0) {
            swprintf(text, StringTable::Load_String("TXT_GAME_ID", 0, "D:\\Ra2\\Scenario.CPP", 1303), unknown_b2a7fc);
            game_id = text;
        }
        loader = Unknown_00535910();
        loader->Unknown_005359E0();
        ProgressScreen.Set_Listener(loader);
        int side = 0;
        if (unknown_game_mode_a3d298 == 0) {
            if (unknown_id_source_a3d290->unknown_224c != -1) {
                side = Campaigns[unknown_id_source_a3d290->unknown_224c]->unknown_98;
            }
        } else {
            int country = unknown_players_a3fa7c[0]->unknown_4b;
            if (country == -3) {
                country = 0;
            }
            side = HouseTypes[country]->Side;
        }
        unknown_id_source_a3d290->unknown_2239 = side == 0;
        ProgressScreen.Set_Side(side);
        Unknown_00535910()->Unknown_00535B90();
        if (unknown_game_mode_a3d298 == 0) {
            ProgressScreen.Load_Shape("SPLDBR.SHP", 0, (ConvertClass *)Unknown_Get_Art_6f2490());
        } else {
            ProgressScreen.Load_Shape("PROGBARM.SHP", 0, 0);
        }
        bool campaign = unknown_game_mode_a3d298 == 0;
        ProgressScreen.Unknown_0061EFA0(loader->Unknown_00535AB0(), game_id, !campaign, !campaign);
        ProgressScreen.Set_Name_Width(loader->Unknown_00535B60());

        if (PacketTransport != 0 && unknown_game_mode_a3d298 == 4 && unknown_players_a3fa7c.Count() > 1) {
            Debug_Printf("Setting addresses for UDP broadcast\n");
            PacketTransport->unknown_slot12();
            char address[32] = "xxx.xxx.xxx.xxx";
            for (int index = 1; index < unknown_players_a3fa7c.Count(); index++) {
                NetNumType net;
                NetNodeType node;
                unknown_players_a3fa7c[index]->Address.Get_Address(net, node);
                sprintf(address, "%d.%d.%d.%d", node[0], node[1], node[2], node[3]);
                Debug_Printf("Adding broadcast address %s\n", address);
                PacketTransport->unknown_slot11(address, unknown_node_ids_a402ba[index]);
            }
        }
    }

    bool ok;
    if (unknown_id_source_a3d290->unknown_223b) {
        ok = MapSeed.Load_Or_Prompt_005791a0(filename);
        if (ok) {
            MapSeed.Unknown_0057A0D0(0, 0);
            Unknown_0065e8c0(true);
        }
        strcpy(unknown_id_source_a3d290->FileName, filename);
    } else {
        ok = Read_Scenario_0065e760(filename, true);
    }
    if (!Rules->Shroud) {
        Map.Unknown_0055A1F0();
    }
    if (!ok) {
        Debug_Printf("Error - Unable to read scenario: %s\n", filename);
        Unknown_004955D0(&unknown_palette_837e10, 7, unknown_481fb0);
        WWMessageBox(L" ").Process(
            StringTable::Load_String("TXT_UNABLE_READ_SCENARIO", 0, "D:\\Ra2\\Scenario.CPP", 1394),
            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Scenario.CPP", 1394), 0, 0, false);
        unknown_a40774--;
        unknown_id_source_a3d290->unknown_22fc = false;
        if (loader != 0) {
            ProgressScreen.Set_Listener(0);
            delete loader;
        }
        return false;
    }

    unknown_object_a3dc70.Unknown_005B4C60(unknown_int_839630 + 3, unknown_int_839634, 6, 0x62, 0xE, -1, -1, 0, 0x14, 0x62, unknown_int_839638 - 6);
    Fill_In_Data_0065cdd0();
    if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
        unknown_session_a3d298.Loading_Progress_00672160(99);
        if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
            unknown_OwnerTalkClass_00ab6d18.Wait_For_Router_Shutdown(15000, true);
        }
    }
    unknown_session_a3d298.Loading_Progress_00672160(unknown_id_source_a3d290->unknown_223b ? 200 : 100);
    unknown_session_a3d298.unknown_639 = false;
    unknown_session_a3d298.unknown_63a = false;
    ok = Wait_For_Players_0065c520();
    if (unknown_game_mode_a3d298 == 4) {
        unknown_session_a3d298.Unknown_00672440();
    }
    unknown_a40774--;
    if (!unknown_flag_a40d13 && ok) {
        Service_Game_IO_00481fb0();
        while (ProgressScreen.Average_Progress() < 1.0) {
            for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
                ProgressScreen.Set_Progress_006201c0(index, 100.0, Point2D(-1, -1));
            }
        }
    }
    unknown_id_source_a3d290->unknown_22fc = false;
    ProgressScreen.Clear_unknown_60();
    if (loader != 0) {
        ProgressScreen.Set_Listener(0);
        loader->Unknown_00536E20();
    }
    return true;
}
