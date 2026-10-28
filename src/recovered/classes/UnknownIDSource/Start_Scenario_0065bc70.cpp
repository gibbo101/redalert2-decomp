// bool __fastcall Start_Scenario_0065bc70(char const *name, bool briefing, int campaign) (0x0065BC70)
// @ref ??_C@_05FGDF@Basic?$AA@=007e1a50
// @ref ??_C@_05JGCF@Brief?$AA@=007f1e58
// @ref ??_C@_05MDNJ@Intro?$AA@=007d9d98
// @ref ??_C@_06FGJI@?$CFs?4VQA?$AA@=007f1e38
// @ref ??_C@_07PBGF@LOADING?$AA@=007e1c70
// @ref ??_C@_0BC@FKIE@Player?5Count?3?5?$CFd?6?$AA@=007f1e60
// @ref ??_C@_0BG@BIDP@Reading?5scenario?3?5?$CFs?6?$AA@=007f1e40
// @ref ??_C@_0CA@GDJN@Toggle?5display?5mode?5to?5?$CFd?5X?5?$CFd?6?$AA@=007f1e18
// @ref ??_C@_0CF@OEGN@?6?9?9?9?9?9?5Starting?5scnenario?3?5?$CFs?5?9?9@=007f1e74
// @ref ?Play_Song@ThemeClass@@QAEHH@Z=006e7eb0
// @ref ?Unknown_004A6B90@@YIXXZ=004a6b90
// @ref ?Unknown_0065c7d0@@YI_NPBD@Z=0065c7d0
// @ref ?Unknown_00671F00@MultiMission@@QAE_NH@Z=00671f00
// @ref ?Unknown_00671F90@MultiMission@@QAEHXZ=00671f90
// @ref ?unknown_counter_a3fabc@@3HA=00a3fabc
// @ref ?unknown_flag_a40d05@@3_NA=00a40d05
// @ref ?unknown_multi_missions_a3d8d8@@3V?$DynamicVectorClass@PAVMultiMission@@@@A=00a3d8d8
// @ref ?unknown_scenario_name_a35ea8@@3PADA=00a35ea8
// Westwood's Start_Scenario: an empty name takes the campaign's scenario;
// records the campaign and the file name, asks for the disk the campaign or
// the multiplayer map is on, plays the scenario's Intro (or Brief) movie,
// reads the scenario (0x0065C7D0), plays the dropship loadout and (briefing)
// the Action movie, resets the display, starts the elapsed time and the
// scenario's theme. False when the disk or the scenario fails. The Brief
// movie's file name is formatted into a buffer nobody reads (as in the
// original); the flag test compares with true (cmp byte ptr, 1).
// The inventory bound (584 bytes, to 0x0065BEB8) stops inside the function:
// the code continues by fall-through to its ret 4 at 0x0065C039 (972 bytes).
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/multi_mission.hpp"
#include "shared/campaign.hpp"
#include "shared/cd.hpp"
#include "shared/theme.hpp"
#include "shared/mouse.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/movie_globals.hpp"
#include "shared/options.hpp"
#include "shared/movie_list.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/gscreen.hpp"
#include "shared/surface.hpp"

bool __fastcall Start_Scenario_0065bc70(char const *name, bool briefing, int campaign)
{
    if ((name == 0 || strlen(name) == 0) && campaign != -1) {
        if (unknown_flag_a40d05 == true) {
            name = unknown_scenario_name_a35ea8;
        } else {
            name = Campaigns[campaign]->Scenario;
        }
    }
    unknown_id_source_a3d290->unknown_224c = campaign;
    Debug_Printf("\n----- Starting scnenario: %s -----\n", name);
    Debug_Printf("Player Count: %d\n", unknown_players_a3fa7c.Count());
    strcpy(unknown_id_source_a3d290->FileName, name);
    _strupr(unknown_id_source_a3d290->FileName);

    CD::Set_Required_CD(-1);
    if (unknown_game_mode_a3d298 == 0) {
        if (unknown_id_source_a3d290->unknown_224c != -1) {
            CD::Set_Required_CD(Campaigns[unknown_id_source_a3d290->unknown_224c]->unknown_98);
        }
    } else if (unknown_session_a3d298.ScenarioIndex != -1) {
        MultiMission *mission = unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex];
        if (!mission->Unknown_00671F00(Unknown_0046E4C0(60))) {
            CD::Set_Required_CD(mission->Unknown_00671F90());
        }
    }
    unknown_counter_a3fabc++;
    if (!CD().Force_Available(CD::RequiredCD)) {
        return false;
    }
    unknown_counter_a3fabc--;
    WWMouse->Hide_Mouse();

    {
        CCINIClass ini;
        CCFileClass file(name);
        if (ini.Load(file, true, false)) {
            int movie = ini.Get_Listed_Name("Basic", "Intro", -1);
            if (movie == -1) {
                movie = ini.Get_Listed_Name("Basic", "Brief", movie);
            }
            if (movie != -1) {
                Theme.Stop();
                Unknown_005A07F0(movie, -1, 1, 1, 1);
            }
        }
    }

    Debug_Printf("Reading scenario: %s\n", name);
    Theme.Play_Song(Theme.From_Name("LOADING"));
    if (!Unknown_0065c7d0(name)) {
        WWMouse->Show_Mouse();
        return false;
    }
    int brief = unknown_id_source_a3d290->BriefMovie;
    if (brief != -1) {
        char movie_name[28];
        wsprintfA(movie_name, "%s.VQA", unknown_names_a71050[brief]);
    }
    if (unknown_id_source_a3d290->StartingDropships > 0) {
        Unknown_004A6B90();
    }
    if (briefing) {
        Unknown_005A07F0(unknown_id_source_a3d290->ActionMovie, -1, 1, 1, 1);
    }
    Unknown_Free_Art_Set_006F30F0();
    Options.Set();
    unknown_surface_839954->Fill(0);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    Toggle_Display_Mode_0065c480(true);
    unknown_id_source_a3d290->ElapsedTime.Start();
    if (unknown_id_source_a3d290->Theme != -1) {
        Theme.Queue_Song(unknown_id_source_a3d290->Theme);
    } else {
        Theme.Stop(true);
    }
    unknown_flag_a40d04 = true;
    unknown_flag_a40380 = true;
    return true;
}
