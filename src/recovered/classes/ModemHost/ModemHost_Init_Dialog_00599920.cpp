// ModemHost::Init_Dialog_00599920 (0x00599920)
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/modem_host.hpp"
#include "shared/modem_guest.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
#include "shared/null_modem.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/campaign.hpp"
#include "shared/special.hpp"
#include "shared/random2.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/session_state.hpp"
extern "C" void __cdecl srand(unsigned int seed);
extern "C" int __cdecl rand();
// @ref ?unknown_modem_host_first_7e2410@@3_NA=007e2410
// @ref ?Unknown_0068B420@SpecialClass@@QAEXXZ=0068b420
// @ref ?Unknown_0061E2A0@UnknownPreview_0061D430@@QAE_NPBD@Z=0061e2a0
// @ref ??_C@_07NKKE@TXT_RED?$AA@=007e2000
// @ref ??_C@_08LPFB@TXT_PINK?$AA@=007e1fb4
// @ref ??_C@_08NALB@TXT_GOLD?$AA@=007e2008
// @ref ??_C@_08PFFA@TXT_BLUE?$AA@=007e1ff4
// @ref ??_C@_09KDHI@TXT_GREEN?$AA@=007e1fe8
// @ref ??_C@_0BC@BBEC@SuperWeapons?3?5?$CFs?6?$AA@=007e1ef8
// @ref ??_C@_0BC@IEEF@BuildOffAlly?3?5?$CFs?6?$AA@=007e1ee4
// @ref ??_C@_0BC@PEFB@MCV?5Redeploy?3?5?$CFs?6?$AA@=007e2468
// @ref ??_C@_0BM@CM@ModemHost?4InitDialog?$CIexit?$CJ?6?$AA@=007e244c
// @ref ??_C@_0BN@JEAL@ModemHost?4InitDialog?$CIenter?$CJ?6?$AA@=007e2490
// @ref ??_C@_0L@EPJB@TXT_ORANGE?$AA@=007e1fdc
// @ref ??_C@_0L@NJNM@TXT_PURPLE?$AA@=007e1fc0
// @ref ??_C@_0N@GNAA@TXT_SKY_BLUE?$AA@=007e1fcc
// @ref ?Find_Combo_Item_Data_00736e10@@YIHPAUHWND__@@HH@Z=00736e10
// @ref ?Init_Clipping_00713160@UnknownVersionObject@@QAEXXZ=00713160
// @ref __imp__PostMessageA@16=0079a470
extern unsigned short const unknown_empty_wide_839d4c[];

void ModemHost::Init_Dialog_00599920()
{
    unsigned short text[1024];
    Debug_Printf("ModemHost.InitDialog(enter)\n");
    if (unknown_modem_host_first_7e2410 == true) {
        unknown_modem_host_first_7e2410 = false;
        unknown_special_a40920.Unknown_0068B420();
        unknown_session_a3d298.unknown_24 = Rules->Money;
        unknown_session_a3d298.unknown_bases_20 = Rules->Bases;
        unknown_session_a3d298.unknown_28 = Rules->BridgeDestruction;
        unknown_session_a3d298.unknown_crates_29 = Rules->Crates;
        unknown_session_a3d298.AICount = 0;
        unknown_session_a3d298.UnitCount = Rules->UnitCount;
        unknown_session_a3d298.unknown_2a = false;
        unknown_session_a3d298.unknown_2b = Rules->SuperWeaponsAllowed;
        unknown_session_a3d298.unknown_2c = Rules->BuildOffAlly;
        unknown_session_a3d298.GameSpeed_30 = unknown_a40b18;
        unknown_session_a3d298.unknown_34 = false;
    }
    HWND control = GetDlgItem(Window, 0x5C1);
    if (control) {
        SendMessageA(control, 0xC5, 19, 0);
        SendMessageA(control, 0x4B2, 0, (LPARAM)Unknown_006FA180(unknown_name_a3d3a0));
    }
    Debug_Printf("Name: %ls\n", unknown_name_a3d3a0);
    control = GetDlgItem(Window, 0x405);
    if (control) {
        SendMessageA(control, 0x14B, 0, 0);
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_GOLD", 0, "D:\\Ra2\\ModemHst.cpp", 0x197));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_RED", 0, "D:\\Ra2\\ModemHst.cpp", 0x198));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_BLUE", 0, "D:\\Ra2\\ModemHst.cpp", 0x199));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_GREEN", 0, "D:\\Ra2\\ModemHst.cpp", 0x19A));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_ORANGE", 0, "D:\\Ra2\\ModemHst.cpp", 0x19B));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_SKY_BLUE", 0, "D:\\Ra2\\ModemHst.cpp", 0x19C));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_PURPLE", 0, "D:\\Ra2\\ModemHst.cpp", 0x19D));
        SendMessageA(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_PINK", 0, "D:\\Ra2\\ModemHst.cpp", 0x19E));
        for (int index = 0; index < 8; index++) {
            SendMessageA(control, 0x498, index, unknown_color_values_7e6d94[index]);
        }
        unknown_a3d3b4 = unknown_session_a3d298.unknown_12c;
        SendMessageA(control, 0x14E, unknown_a3d3b4, 0);
    }
    Debug_Printf("Color: %d\n", unknown_a3d3b4);
    control = GetDlgItem(Window, 0x667);
    if (control) {
        SendMessageA(control, 0x14B, 0, 0);
        for (int house = 0; house < HouseTypes.Count(); house++) {
            if (HouseTypes[house]->Multiplay) {
                wchar_t const *name = HouseTypes[house]->UIName;
                int row = SendMessageA(control, 0x4C2, 0, (LPARAM)name);
                SendMessageA(control, 0x151, row, house);
            }
        }
        int row = Find_Combo_Item_Data_00736e10(control, -1, unknown_a3d3bc);
        SendMessageA(control, 0x14E, row, 0);
    }
    control = GetDlgItem(Window, 0x669);
    if (control) {
        int value = unknown_session_a3d298.UnitCount;
        SendMessageA(control, 0x406, 1, ((unsigned long)(unsigned short)Rules->MaxUnitCount << 16) | (unsigned short)Rules->MinUnitCount);
        SendMessageA(control, 0x405, 1, value);
    }
    Debug_Printf("UnitCount: %d\n", unknown_session_a3d298.UnitCount);
    control = GetDlgItem(Window, 0x550);
    if (control) {
        int value = unknown_house_setting_7d88d8;
        SendMessageA(control, 0x406, 1, 0xA0001);
        SendMessageA(control, 0x405, 1, value);
    }
    Debug_Printf("TechLevel: %d\n", unknown_house_setting_7d88d8);
    control = GetDlgItem(Window, 0x402);
    if (control) {
        int value = unknown_session_a3d298.unknown_24;
        SendMessageA(control, 0x406, 1, ((unsigned long)(unsigned short)Rules->MaxMoney << 16) | (unsigned short)Rules->MinMoney);
        SendMessageA(control, 0x405, 1, value);
        SendMessageA(control, 0x4AB, 0, 250);
    }
    Debug_Printf("Credits: %d\n", unknown_session_a3d298.unknown_24);
    control = GetDlgItem(Window, 0x552);
    if (control) {
        int value = unknown_session_a3d298.AICount;
        SendMessageA(control, 0x406, 1, 0x60000);
        SendMessageA(control, 0x405, 1, value);
    }
    Debug_Printf("AIPlayers: %d\n", unknown_session_a3d298.AICount);
    control = GetDlgItem(Window, 0x529);
    if (control) {
        SendMessageA(control, 0x406, 1, 0x60000);
        SendMessageA(control, 0x405, 1, 6 - unknown_a40b18);
    }
    Debug_Printf("Game Speed: %d\n", unknown_session_a3d298.GameSpeed_30);
    control = GetDlgItem(Window, 0x553);
    if (control) {
        int value = unknown_session_a3d298.unknown_difficulty_40;
        SendMessageA(control, 0x406, 1, 0x20000);
        SendMessageA(control, 0x405, 1, value);
    }
    Debug_Printf("AIDifficulty: %d\n", unknown_session_a3d298.unknown_difficulty_40);
    control = GetDlgItem(Window, 0x66B);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_a8 == true, 0);
    }
    Debug_Printf("MCV Redeploy: %s\n", unknown_session_a3d298.unknown_a8 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x66A);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_bases_20 == true, 0);
    }
    Debug_Printf("Bases: %s\n", unknown_session_a3d298.unknown_bases_20 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x54C);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_crates_29 == true, 0);
    }
    Debug_Printf("Crates: %s\n", unknown_session_a3d298.unknown_crates_29 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x54D);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_fog_a7 == true, 0);
    }
    Debug_Printf("FogOfWar: %s\n", unknown_session_a3d298.unknown_fog_a7 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x624);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_28 == true, 0);
    }
    Debug_Printf("BridgeDestroy: %s\n", unknown_session_a3d298.unknown_28 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x596);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_a5 == true, 0);
    }
    Debug_Printf("Harvester Truce: %s\n", unknown_session_a3d298.unknown_a5 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x54E);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_2a == true, 0);
    }
    Debug_Printf("Short Game: %s\n", unknown_session_a3d298.unknown_2a == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x69A);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_2b == true, 0);
    }
    Debug_Printf("SuperWeapons: %s\n", unknown_session_a3d298.unknown_2b == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x69D);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_2c == true, 0);
    }
    Debug_Printf("BuildOffAlly: %s\n", unknown_session_a3d298.unknown_2c == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x551);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_34 == true, 0);
    }
    Debug_Printf("Crap Engineers: %s\n", unknown_session_a3d298.unknown_34 == true ? "ON" : "OFF");
    version_object_00a40c88.Init_Clipping_00713160();
    srand(unknown_random_839218(1, 0x7FFF));
    Seed = rand();
    unknown_special_a40920.unknown_bit_4 = Rules->CaptureTheFlag;
    if (unknown_dialog_preview_a72ce8) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8 = 0;
    }
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    Select_Scenario_005c7c30(0);
    unknown_session_a3d298.ScenarioIndex = 0;
    HWND window = Window;
    control = GetDlgItem(window, 0x5A8);
    SendMessageA(control, 0x4B2, 0, (LPARAM)unknown_map_name_a3d342);
    unknown_session_a3f616 = true;
    if (CCFileClass(unknown_session_a3d298.ScenarioFileName_658).Is_Available()) {
        unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
        unknown_dialog_preview_a72ce8->Unknown_0061E2A0(unknown_session_a3d298.ScenarioFileName_658);
        PostMessageA(Window, 0xF, 0, 0);
    }
    if (strlen(ModemRXString) > 78) {
        ModemRXString[79] = 0;
    }
    if (strlen(ModemRXString)) {
        Unknown_006FA0C0(text, ModemRXString, -1);
        Show_Chat_0059c0b0(text, -1, unknown_empty_wide_839d4c);
    }
    ModemRXString[0] = 0;
    control = GetDlgItem(Window, 1);
    if (control) {
        EnableWindow(control, 0);
    }
    serial_manager_00a40a28.Reset_Response_Time(true);
    Debug_Printf("ModemHost.InitDialog(exit)\n");
}
