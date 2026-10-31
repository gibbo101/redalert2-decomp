// int __fastcall Make_Random_Map_005c84e0() (0x005C84E0)
// Runs the random map dialog (0x00577490, with the game mode's service callback); after OK saves the seed
// options as RandMap.Sed, reloads the lobby preview from RandMap.img and gives the session's random map entry
// the new description, or adds a new random map entry named by the seed CRC. Returns that entry's index,
// or -1 when the dialog was cancelled.
#include "shared/lobby.hpp"
#include "shared/multi_mission.hpp"
#include "shared/map_preview.hpp"
#include "shared/unknown_map_generator.hpp"
// @ref ?unknown_map_generator_a6fd68@@3VUnknownMapGenerator@@A=00a6fd68
// @ref ?Do_Random_Map_Dialog_00577490@@YIHP6A_NXZ@Z=00577490
// @ref ?Default_Map_Generation_Callback_00482100@@YA_NXZ=00482100
// @ref ?Unknown_005bbd10@@YA_NXZ=005bbd10
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
// @ref ?Unknown_0059c880@@YA_NXZ=0059c880
// @ref ??0MultiMission@@QAE@PBDPBG0HHHH@Z=00671c50
// @ref ?Set_Description_00671FA0@MultiMission@@QAEXPBG@Z=00671fa0
// @ref ?Random_Map_CRC_005c8420@@YIPADXZ=005c8420
// @ref ?unknown_host_shown_7e6dc0@@3_NA=007e6dc0
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_0M@PNFG@RandMap?4img?$AA@=007e1540

int __fastcall Do_Random_Map_Dialog_00577490(bool (*callback)());
bool Default_Map_Generation_Callback_00482100();
extern bool unknown_host_shown_7e6dc0;

int __fastcall Make_Random_Map_005c84e0()
{
    bool (*service)();
    if (unknown_game_mode_a3d298 == 3) {
        service = Unknown_005bbd10;
    } else if (unknown_game_mode_a3d298 == 4) {
        service = Unknown_0073e100;
    } else if (unknown_game_mode_a3d298 == 1 || unknown_game_mode_a3d298 == 2) {
        service = Unknown_0059c880;
    } else {
        service = Default_Map_Generation_Callback_00482100;
    }
    if (Do_Random_Map_Dialog_00577490(service) != 1) {
        return -1;
    }
    unknown_host_shown_7e6dc0 = true;
    unknown_map_generator_a6fd68.SeedOptions.Save_Or_Prompt_00578ed0("RandMap.Sed");
    delete unknown_dialog_preview_a72ce8;
    unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
    unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
    int index;
    bool found = false;
    for (index = 0; index < unknown_multi_missions_a3d8d8.Count(); index++) {
        if (unknown_multi_missions_a3d8d8[index]->Unknown_006720C0()) {
            found = true;
            break;
        }
    }
    if (!found) {
        char *crc = Random_Map_CRC_005c8420();
        MultiMission *mission = new MultiMission("RandMap.Sed", unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer, crc, 1, 0, 2, 4);
        unknown_multi_missions_a3d8d8.Add(mission);
        delete crc;
    } else {
        unknown_multi_missions_a3d8d8[index]->Set_Description_00671FA0(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer);
    }
    return index;
}
