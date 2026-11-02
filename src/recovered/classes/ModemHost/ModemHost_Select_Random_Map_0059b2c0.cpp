// void ModemHost::Select_Random_Map_0059b2c0() (0x0059B2C0)
// The random map button: runs the random map dialog with the modem idle callback; after OK saves the seed
// options as RandMap.Sed, drops the lobby preview, shows the new description, adds a random map entry (or
// gives the existing one the new digest and description), selects it, and reloads the preview from
// RandMap.img when the scenario file exists. Its exit trace reuses SelectMultiMap's text.
#include "shared/modem_host.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/lobby.hpp"
#include "shared/map_preview.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/id_source.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_map_generator_a6fd68@@3VUnknownMapGenerator@@A=00a6fd68
// @ref ?Do_Random_Map_Dialog_00577490@@YIHP6A_NXZ@Z=00577490
// @ref ?Unknown_0059c880@@YA_NXZ=0059c880
// @ref ?unknown_host_shown_7e6dc0@@3_NA=007e6dc0
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_0M@EOLM@RandMap?4img?$AA@=007e1540
// @ref ??_C@_0CC@HJGN@ModemHost?4SelectRandomMap?$CIenter?$CJ@=007e2548
// @ref ??_C@_0CA@DBEI@ModemHost?4SelectMultiMap?$CIexit?$CJ?6?$AA@=007e2504
// @ref __imp__PostMessageA@16=0079a470

int __fastcall Do_Random_Map_Dialog_00577490(bool (*callback)());
extern bool unknown_host_shown_7e6dc0;

void ModemHost::Select_Random_Map_0059b2c0()
{
    Debug_Printf("ModemHost.SelectRandomMap(enter)\n");
    unknown_host_shown_7e6dc0 = false;
    if (Do_Random_Map_Dialog_00577490(Unknown_0059c880) == 1) {
        unknown_host_shown_7e6dc0 = true;
        unknown_map_generator_a6fd68.SeedOptions.Save_Or_Prompt_00578ed0("RandMap.Sed");
        if (unknown_dialog_preview_a72ce8 != 0) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
        }
        Send_Dlg_Item_Message(Window, 0x5A8, 0x4B2, 0, (LPARAM)unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer);
        bool found = false;
        int index;
        for (index = 0; index < unknown_session_a3d298.Scenarios.Count(); index++) {
            if (_stricmp(unknown_session_a3d298.Scenarios[index]->unknown_58, "RandMap.Sed") == 0) {
                found = true;
                break;
            }
        }
        char *crc = Random_Map_CRC_005c8420();
        if (!found) {
            MultiMission *mission = new MultiMission("RandMap.Sed", unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer, crc, 1, 0, 2, 4);
            unknown_session_a3d298.Scenarios.Add(mission);
        } else {
            unknown_session_a3d298.Scenarios[index]->Set_Digest(crc);
            unknown_session_a3d298.Scenarios[index]->Set_Description_00671FA0(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer);
        }
        delete crc;
        if (Select_Scenario_005c7c30(index) == true) {
            unknown_session_a3d298.ScenarioIndex = index;
            strcpy(unknown_session_a3d298.ScenarioFileName_658, "RandMap.Sed");
            strcpy(unknown_id_source_a3d290->FileName, unknown_session_a3d298.ScenarioFileName_658);
            if (CCFileClass(unknown_session_a3d298.ScenarioFileName_658).Is_Available()) {
                unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
                unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
                PostMessageA(Window, 0xF, 0, 0);
            }
        }
        OptionsChanged = true;
    }
    unknown_host_shown_7e6dc0 = true;
    Debug_Printf("ModemHost.SelectMultiMap(exit)\n");
}
