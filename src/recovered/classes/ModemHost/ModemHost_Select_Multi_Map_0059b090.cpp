// void ModemHost::Select_Multi_Map_0059b090() (0x0059B090)
#include "shared/modem_host.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/lobby.hpp"
#include "shared/map_preview.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_map_name_a3d342@@3PAGA=00a3d342
// @ref ?Unknown_005c7570@@YIXPAUHWND__@@@Z=005c7570
// @ref ?Select_Scenario_005c7c30@@YI_NH@Z=005c7c30
// @ref ?Load_0061E170@UnknownPreview_0061D430@@QAE_NPBD@Z=0061e170
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
// @ref ??0UnknownPreview_0061D430@@QAE@XZ=0061d430
// @ref _wcscpy=00783689
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__InvalidateRect@12=0079a494
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??_C@_0CA@DBEI@ModemHost?4SelectMultiMap?$CIexit?$CJ?6?$AA@=007e2504
// @ref ??_C@_0CB@MJDK@ModemHost?4SelectMultiMap?$CIenter?$CJ?6@=007e2524
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_0M@EOLM@RandMap?4img?$AA@=007e1540
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);   // 0x00783689

void ModemHost::Select_Multi_Map_0059b090()
{
    Debug_Printf("ModemHost.SelectMultiMap(enter)\n");
    int scenario = unknown_session_a3d298.ScenarioIndex;
    char file_name[132];
    strcpy(file_name, unknown_session_a3d298.ScenarioFileName_658);
    unsigned short map_name[130];
    wcscpy(map_name, unknown_map_name_a3d342);
    ShowWindow(Window, 0);
    if (Open_Lobby_Dialog_005c6960(MainWindow) == 2) {
        unknown_session_a3d298.ScenarioIndex = scenario;
        Select_Scenario_005c7c30(scenario);
        Unknown_005c7570(Window);
        ShowWindow(Window, 5);
        if (_stricmp(unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->unknown_58, "RandMap.Sed") == 0) {
            if (unknown_dialog_preview_a72ce8 != 0) {
                delete unknown_dialog_preview_a72ce8;
            }
            unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
            unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
            if (unknown_dialog_preview_a72ce8->unknown_00 == 0) {
                Unknown_005c7570(Window);
            }
            InvalidateRect(Window, 0, false);
        } else {
            Unknown_005c7570(Window);
        }
        InvalidateRect(Window, 0, false);
    } else {
        ShowWindow(Window, 5);
        if (Select_Scenario_005c7c30(unknown_session_a3d298.ScenarioIndex) == true) {
            Send_Dlg_Item_Message(Window, 0x5A8, 0x4B2, 0, (LPARAM)unknown_map_name_a3d342);
            if (_stricmp(unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->unknown_58, "RandMap.Sed") == 0) {
                if (unknown_dialog_preview_a72ce8 != 0) {
                    delete unknown_dialog_preview_a72ce8;
                    unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
                    unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
                }
                if (unknown_dialog_preview_a72ce8->unknown_00 == 0) {
                    Unknown_005c7570(Window);
                }
                InvalidateRect(Window, 0, false);
            } else {
                Unknown_005c7570(Window);
            }
        } else {
            unknown_session_a3d298.ScenarioIndex = scenario;
        }
    }
    OptionsChanged = true;
    Debug_Printf("ModemHost.SelectMultiMap(exit)\n");
}
