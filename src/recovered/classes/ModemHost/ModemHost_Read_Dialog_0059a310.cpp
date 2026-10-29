// ModemHost::Read_Dialog_0059a310 (0x0059A310)
#include "shared/modem_host.hpp"
#include "shared/modem_guest.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?Unknown_005c6600@@YIHH@Z=005c6600
// @ref ?Unknown_006FA0F0@@YIXPADPBGH@Z=006fa0f0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??_C@_02HAKO@ON?$AA@=007e1f40
// @ref ??_C@_03CMJG@OFF?$AA@=007e1f3c
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BA@DOI@Game?5Speed?3?5?$CFd?6?$AA@=007e1f58
// @ref ??_C@_0BA@NBOO@Short?5Game?3?5?$CFs?6?$AA@=007e1f0c
// @ref ??_C@_0BB@ILLA@MCVRedeploy?3?5?$CFs?6?$AA@=007e1f28
// @ref ??_C@_0BC@DPJ@AIDifficulty?3?5?$CFd?6?$AA@=007e1f44
// @ref ??_C@_0BD@ODLN@BridgeDestroy?3?5?$CFs?6?$AA@=007e1ea0
// @ref ??_C@_0BE@EBDB@D?3?2Ra2?2ModemHst?4cpp?$AA@=007e247c
// @ref ??_C@_0BE@KMDF@Crap?5Engineers?3?5?$CFs?6?$AA@=007e1ed0
// @ref ??_C@_0BF@CBAA@Harvester?5Truce?3?5?$CFs?6?$AA@=007e1e88
// @ref ??_C@_0BH@KOPH@TXT_SCENARIO_TOO_SMALL?$AA@=007e24cc
// @ref ??_C@_0BM@IDBK@ModemHost?4ReadDialog?$CIexit?$CJ?6?$AA@=007e24b0
// @ref ??_C@_0BN@MDII@ModemHost?4ReadDialog?$CIenter?$CJ?6?$AA@=007e24e4
// @ref ??_C@_0L@DFNB@Name?3?5?$CFls?6?$AA@=007e2028
// @ref ??_C@_0L@HPID@Color?3?5?$CFd?6?$AA@=007e1fa8
// @ref ??_C@_0L@ODDO@Bases?3?5?$CFs?6?$AA@=007e1f1c
// @ref ??_C@_0M@IDPK@Crates?3?5?$CFs?6?$AA@=007e1ec4
// @ref ??_C@_0N@KDNE@Credits?3?5?$CFd?6?$AA@=007e1f78
// @ref ??_C@_0O@BKAD@FogOfWar?3?5?$CFs?6?$AA@=007e1eb4
// @ref ??_C@_0P@DJIC@AIPlayers?3?5?$CFd?6?$AA@=007e1f68
// @ref ??_C@_0P@LIHP@UnitCount?3?5?$CFd?6?$AA@=007e1f98
// @ref ??_C@_0P@ONCE@TechLevel?3?5?$CFd?6?$AA@=007e1f88
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);

bool ModemHost::Read_Dialog_0059a310()
{
    Debug_Printf("ModemHost.ReadDialog(enter)\n");
    int max_players = Unknown_005c6600(unknown_session_a3d298.ScenarioIndex);
    int players = 2;
    HWND control = GetDlgItem(Window, 0x552);
    if (control) {
        players = SendMessageA(control, 0x400, 0, 0) + 2;
    }
    if (max_players < players) {
        unsigned short text[256];
        swprintf(text, StringTable::Load_String("TXT_SCENARIO_TOO_SMALL", 0, "D:\\Ra2\\ModemHst.cpp", 0x2F7), max_players);
        WWMessageBox(L" ").Process(text, StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x2F8), 0, 0, false);
        return false;
    }

    control = GetDlgItem(Window, 0x5C1);
    if (control) {
        unsigned short name[20];
        SendMessageA(control, 0x4B3, 20, (LPARAM)name);
        Unknown_006FA0F0(unknown_name_a3d3a0, name, -1);
    }
    Debug_Printf("Name: %ls\n", unknown_name_a3d3a0);

    control = GetDlgItem(Window, 0x405);
    if (control) {
        unknown_a3d3b4 = SendMessageA(control, 0x147, 0, 0);
    }
    Debug_Printf("Color: %d\n", unknown_a3d3b4);

    control = GetDlgItem(Window, 0x667);
    if (control) {
        int row = SendMessageA(control, 0x147, 0, 0);
        unknown_a3d3bc = SendMessageA(control, 0x150, row, 0);
    }

    control = GetDlgItem(Window, 0x669);
    if (control) {
        unknown_session_a3d298.UnitCount = SendMessageA(control, 0x400, 0, 0);
    }
    Debug_Printf("UnitCount: %d\n", unknown_session_a3d298.UnitCount);

    control = GetDlgItem(Window, 0x550);
    if (control) {
        unknown_house_setting_7d88d8 = SendMessageA(control, 0x400, 0, 0);
    }
    Debug_Printf("TechLevel: %d\n", unknown_house_setting_7d88d8);

    control = GetDlgItem(Window, 0x402);
    if (control) {
        unknown_session_a3d298.unknown_24 = SendMessageA(control, 0x400, 0, 0);
    }
    Debug_Printf("Credits: %d\n", unknown_session_a3d298.unknown_24);

    control = GetDlgItem(Window, 0x552);
    if (control) {
        unknown_session_a3d298.AICount = SendMessageA(control, 0x400, 0, 0);
    }
    Debug_Printf("AIPlayers: %d\n", unknown_session_a3d298.AICount);

    control = GetDlgItem(Window, 0x529);
    if (control) {
        unknown_session_a3d298.GameSpeed_30 = 6 - SendMessageA(control, 0x400, 0, 0);
    }
    Debug_Printf("Game Speed: %d\n", unknown_session_a3d298.GameSpeed_30);

    control = GetDlgItem(Window, 0x553);
    if (control) {
        unknown_session_a3d298.unknown_difficulty_40 = SendMessageA(control, 0x400, 0, 0);
    }
    Debug_Printf("AIDifficulty: %d\n", unknown_session_a3d298.unknown_difficulty_40);

    control = GetDlgItem(Window, 0x66B);
    if (control) {
        unknown_session_a3d298.unknown_a8 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("MCVRedeploy: %s\n", unknown_session_a3d298.unknown_a8 == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x66A);
    if (control) {
        unknown_session_a3d298.unknown_bases_20 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Bases: %s\n", unknown_session_a3d298.unknown_bases_20 == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x54C);
    if (control) {
        unknown_session_a3d298.unknown_crates_29 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Crates: %s\n", unknown_session_a3d298.unknown_crates_29 == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x54D);
    if (control) {
        unknown_session_a3d298.unknown_fog_a7 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("FogOfWar: %s\n", unknown_session_a3d298.unknown_fog_a7 == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x624);
    if (control) {
        unknown_session_a3d298.unknown_28 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("BridgeDestroy: %s\n", unknown_session_a3d298.unknown_28 == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x596);
    if (control) {
        unknown_session_a3d298.unknown_a5 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Harvester Truce: %s\n", unknown_session_a3d298.unknown_a5 == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x54E);
    if (control) {
        unknown_session_a3d298.unknown_2a = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Short Game: %s\n", unknown_session_a3d298.unknown_2a == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x69A);
    if (control) {
        unknown_session_a3d298.unknown_2b = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Short Game: %s\n", unknown_session_a3d298.unknown_2a == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x69D);
    if (control) {
        unknown_session_a3d298.unknown_2c = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Short Game: %s\n", unknown_session_a3d298.unknown_2a == true ? "ON" : "OFF");

    control = GetDlgItem(Window, 0x551);
    if (control) {
        unknown_session_a3d298.unknown_34 = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    Debug_Printf("Crap Engineers: %s\n", unknown_session_a3d298.unknown_34 == true ? "ON" : "OFF");
    Debug_Printf("ModemHost.ReadDialog(exit)\n");
    return true;
}
