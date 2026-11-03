// void ModemGuest::Init_Dialog_00596540() -- 0x00596540
// Purpose: fills the modem guest lobby dialog from the session (name, colour, side, unit count, tech level,
// credits, AI players, speed, difficulty and the option check boxes), logging each value, then resets the
// preview, shows any received modem string as chat and clears the player list and map name.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
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
// @ref ?unknown_a3f616@@3DA=00a3f616
// @ref ??_C@_07NKKE@TXT_RED?$AA@=007e2000
// @ref ??_C@_08LPFB@TXT_PINK?$AA@=007e1fb4
// @ref ??_C@_08NALB@TXT_GOLD?$AA@=007e2008
// @ref ??_C@_08PFFA@TXT_BLUE?$AA@=007e1ff4
// @ref ??_C@_09KDHI@TXT_GREEN?$AA@=007e1fe8
// @ref ??_C@_0BA@DOI@Game?5Speed?3?5?$CFd?6?$AA@=007e1f58
// @ref ??_C@_0BA@NBOO@Short?5Game?3?5?$CFs?6?$AA@=007e1f0c
// @ref ??_C@_0BB@ILLA@MCVRedeploy?3?5?$CFs?6?$AA@=007e1f28
// @ref ??_C@_0BC@BBEC@SuperWeapons?3?5?$CFs?6?$AA@=007e1ef8
// @ref ??_C@_0BC@DPJ@AIDifficulty?3?5?$CFd?6?$AA@=007e1f44
// @ref ??_C@_0BC@IEEF@BuildOffAlly?3?5?$CFs?6?$AA@=007e1ee4
// @ref ??_C@_0BD@ODLN@BridgeDestroy?3?5?$CFs?6?$AA@=007e1ea0
// @ref ??_C@_0BE@KMDF@Crap?5Engineers?3?5?$CFs?6?$AA@=007e1ed0
// @ref ??_C@_0BE@PMHE@D?3?2Ra2?2ModemGst?4cpp?$AA@=007e2014
// @ref ??_C@_0BF@CBAA@Harvester?5Truce?3?5?$CFs?6?$AA@=007e1e88
// @ref ??_C@_0BN@KNCA@ModemGuest?4InitDialog?$CIexit?$CJ?6?$AA@=007e1e58
// @ref ??_C@_0BO@HGKG@ModemGuest?4InitDialog?$CIenter?$CJ?6?$AA@=007e2034
// @ref ??_C@_0L@DFNB@Name?3?5?$CFls?6?$AA@=007e2028
// @ref ??_C@_0L@EPJB@TXT_ORANGE?$AA@=007e1fdc
// @ref ??_C@_0L@HPID@Color?3?5?$CFd?6?$AA@=007e1fa8
// @ref ??_C@_0L@NJNM@TXT_PURPLE?$AA@=007e1fc0
// @ref ??_C@_0L@ODDO@Bases?3?5?$CFs?6?$AA@=007e1f1c
// @ref ??_C@_0M@IDPK@Crates?3?5?$CFs?6?$AA@=007e1ec4
// @ref ??_C@_0N@GNAA@TXT_SKY_BLUE?$AA@=007e1fcc
// @ref ??_C@_0N@KDNE@Credits?3?5?$CFd?6?$AA@=007e1f78
// @ref ??_C@_0O@BKAD@FogOfWar?3?5?$CFs?6?$AA@=007e1eb4
// @ref ??_C@_0P@DJIC@AIPlayers?3?5?$CFd?6?$AA@=007e1f68
// @ref ??_C@_0P@LIHP@UnitCount?3?5?$CFd?6?$AA@=007e1f98
// @ref ??_C@_0P@ONCE@TechLevel?3?5?$CFd?6?$AA@=007e1f88
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ?Find_Combo_Item_Data_00736e10@@YIHPAUHWND__@@HH@Z=00736e10
// @ref ?Free_Pointers_005a7480@@YIXPAV?$DynamicVectorClass@PAUNodeNameType@@@@@Z=005a7480
// @ref ?Init_Clipping_00713160@UnknownVersionObject@@QAEXXZ=00713160
// @ref ?Unknown_005C2DA0@@YIXHPBGPAUHWND__@@@Z=005c2da0
// @ref ?Unknown_006FA0C0@@YIXPAGPBDH@Z=006fa0c0
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_map_name_a3d342@@3PAGA=00a3d342
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?version_object_00a40c88@@3UUnknownVersionObject@@A=00a40c88
// @ref ??_C@_02HAKO@ON?$AA@=007e1f40
// @ref ??_C@_03CMJG@OFF?$AA@=007e1f3c
extern char unknown_a3f616;
extern unsigned short const unknown_empty_wide_839d4c[];

// Every SendMessageA call of Init_Dialog goes through this file-local inline (code-free; it sets the
// scratch/callee-saved register choice of `this` versus the GetDlgItem import, as in Fill_Port 0x66D5A0).
static inline LRESULT Send_Message(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    return SendMessageA(window, message, wparam, lparam);
}

void ModemGuest::Init_Dialog_00596540()
{
    unsigned short text[1024];
    Debug_Printf("ModemGuest.InitDialog(enter)\n");
    HWND control = GetDlgItem(Window, 0x5C1);
    if (control) {
        Send_Message(control, 0xC5, 19, 0);
        Send_Message(control, 0x4B2, 0, (LPARAM)Unknown_006FA180(unknown_name_a3d3a0));
    }
    Debug_Printf("Name: %ls\n", unknown_name_a3d3a0);
    control = GetDlgItem(Window, 0x405);
    if (control) {
        Send_Message(control, 0x14B, 0, 0);
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_GOLD", 0, "D:\\Ra2\\ModemGst.cpp", 0x118));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_RED", 0, "D:\\Ra2\\ModemGst.cpp", 0x119));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_BLUE", 0, "D:\\Ra2\\ModemGst.cpp", 0x11A));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_GREEN", 0, "D:\\Ra2\\ModemGst.cpp", 0x11B));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_ORANGE", 0, "D:\\Ra2\\ModemGst.cpp", 0x11C));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_SKY_BLUE", 0, "D:\\Ra2\\ModemGst.cpp", 0x11D));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_PURPLE", 0, "D:\\Ra2\\ModemGst.cpp", 0x11E));
        Send_Message(control, 0x4C1, -1, (LPARAM)StringTable::Load_String("TXT_PINK", 0, "D:\\Ra2\\ModemGst.cpp", 0x11F));
        for (int index = 0; index < 8; index++) {
            Send_Message(control, 0x498, index, unknown_color_values_7e6d94[index]);
        }
        unknown_a3d3b4 = unknown_session_a3d298.unknown_12c;
        Send_Message(control, 0x14E, unknown_a3d3b4, 0);
    }
    Debug_Printf("Color: %d\n", unknown_a3d3b4);
    control = GetDlgItem(Window, 0x667);
    if (control) {
        Send_Message(control, 0x14B, 0, 0);
        for (int house = 0; house < HouseTypes.Count(); house++) {
            if (HouseTypes[house]->Multiplay) {
                LPARAM name = (LPARAM)HouseTypes[house]->UIName;
                int row = Send_Message(control, 0x4C2, 0, name);
                Send_Message(control, 0x151, row, house);
            }
        }
        int row = Find_Combo_Item_Data_00736e10(control, -1, unknown_a3d3bc);
        Send_Message(control, 0x14E, row, 0);
    }
    control = GetDlgItem(Window, 0x669);
    if (control) {
        Send_Message(control, 0x406, 1, ((unsigned long)(unsigned short)Rules->MaxUnitCount << 16) | (unsigned short)Rules->MinUnitCount);
        Send_Message(control, 0x405, 1, unknown_session_a3d298.UnitCount);
    }
    Debug_Printf("UnitCount: %d\n", unknown_session_a3d298.UnitCount);
    control = GetDlgItem(Window, 0x550);
    if (control) {
        Send_Message(control, 0x406, 1, 0xA0001);
        Send_Message(control, 0x405, 1, unknown_house_setting_7d88d8);
    }
    Debug_Printf("TechLevel: %d\n", unknown_house_setting_7d88d8);
    control = GetDlgItem(Window, 0x402);
    if (control) {
        Send_Message(control, 0x406, 1, ((unsigned long)(unsigned short)Rules->MaxMoney << 16) | (unsigned short)Rules->MinMoney);
        Send_Message(control, 0x405, 1, unknown_session_a3d298.unknown_24);
    }
    Debug_Printf("Credits: %d\n", unknown_session_a3d298.unknown_24);
    control = GetDlgItem(Window, 0x552);
    if (control) {
        Send_Message(control, 0x406, 1, 0x60000);
        Send_Message(control, 0x405, 1, unknown_session_a3d298.AICount);
    }
    Debug_Printf("AIPlayers: %d\n", unknown_session_a3d298.AICount);
    control = GetDlgItem(Window, 0x529);
    if (control) {
        Send_Message(control, 0x406, 1, 0x60000);
        Send_Message(control, 0x405, 1, 6 - unknown_session_a3d298.GameSpeed_30);
    }
    Debug_Printf("Game Speed: %d\n", unknown_session_a3d298.GameSpeed_30);
    control = GetDlgItem(Window, 0x553);
    if (control) {
        Send_Message(control, 0x406, 1, 0x20000);
        Send_Message(control, 0x405, 1, unknown_session_a3d298.unknown_difficulty_40);
    }
    Debug_Printf("AIDifficulty: %d\n", unknown_session_a3d298.unknown_difficulty_40);
    control = GetDlgItem(Window, 0x66B);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_a8 == true, 0);
    }
    Debug_Printf("MCVRedeploy: %s\n", unknown_session_a3d298.unknown_a8 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x66A);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_bases_20 == true, 0);
    }
    Debug_Printf("Bases: %s\n", unknown_session_a3d298.unknown_bases_20 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x54E);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_2a == true, 0);
    }
    Debug_Printf("Short Game: %s\n", unknown_session_a3d298.unknown_2a == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x69A);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_2b == true, 0);
    }
    Debug_Printf("SuperWeapons: %s\n", unknown_session_a3d298.unknown_2b == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x69D);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_2c == true, 0);
    }
    Debug_Printf("BuildOffAlly: %s\n", unknown_session_a3d298.unknown_2c == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x551);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_34 == true, 0);
    }
    Debug_Printf("Crap Engineers: %s\n", unknown_session_a3d298.unknown_34 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x54C);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_crates_29 == true, 0);
    }
    Debug_Printf("Crates: %s\n", unknown_session_a3d298.unknown_crates_29 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x54D);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_fog_a7 == true, 0);
    }
    Debug_Printf("FogOfWar: %s\n", unknown_session_a3d298.unknown_fog_a7 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x624);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_28 == true, 0);
    }
    Debug_Printf("BridgeDestroy: %s\n", unknown_session_a3d298.unknown_28 == true ? "ON" : "OFF");
    control = GetDlgItem(Window, 0x596);
    if (control) {
        Send_Message(control, 0xF1, unknown_session_a3d298.unknown_a5 == true, 0);
    }
    Debug_Printf("Harvester Truce: %s\n", unknown_session_a3d298.unknown_a5 == true ? "ON" : "OFF");
    version_object_00a40c88.Init_Clipping_00713160();
    if (unknown_dialog_preview_a72ce8) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8 = 0;
    }
    if (strlen(ModemRXString) > 78) {
        ModemRXString[79] = 0;
    }
    if (strlen(ModemRXString)) {
        Unknown_006FA0C0(text, ModemRXString, -1);
        Show_Chat_00598510(text, -1, unknown_empty_wide_839d4c);
    }
    ModemRXString[0] = 0;
    serial_manager_00a40a28.Reset_Response_Time(true);
    unknown_a3f616 = 1;
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    unknown_map_name_a3d342[0] = 0;
    Debug_Printf("ModemGuest.InitDialog(exit)\n");
}
