// int __stdcall Options_Menu_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x004DD8A0)
// The in-game options menu's dialog procedure (GOptions.CPP; TibSun Game_Options_Dialog_Proc): the default
// owner-draw handling first, 0x497 initialises the menu, WM_COMMAND runs Options_Menu_Command (inlined; it
// owns the two anti-cheat timers whose atexit thunks are 0x004DDDF0 speed and 0x004DDDE0 latency) and
// WM_HSCROLL updates the speed or latency label of the slider being dragged.
#include "shared/game_options_dialog.hpp"
#include "shared/game_controls_dialog.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/map_seed.hpp"
#include "shared/event.hpp"
#include "shared/house.hpp"
#include "shared/options.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/system_timer.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__UpdateWindow@4=0079a46c
// @ref ?Options_Menu_Proc@@YGHPAUHWND__@@IIJ@Z=004dd8a0
// @ref ?Options_Menu_Init@@YIXPAUHWND__@@@Z=004dde00
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_int_a40d48@@3HA=00a40d48
// @ref ?unknown_b2a7ec@@3HA=00b2a7ec
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_a3fba4@@3HA=00a3fba4
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref ??0EventClass@@QAE@HE@Z=004b5fd0
// @ref ??0EventClass@@QAE@HHK@Z=004b6030
// @ref ??0LoadOptionsClass@@QAE@XZ=0053b0e0
// @ref ??1LoadOptionsClass@@UAE@XZ=0053b130
// @ref ?Load_Dialog_0053b190@LoadOptionsClass@@QAEDXZ=0053b190
// @ref ?Save_Dialog_0053b1b0@LoadOptionsClass@@QAEDPA_W@Z=0053b1b0
// @ref ?Delete_Dialog_0053b1e0@LoadOptionsClass@@QAEDXZ=0053b1e0
// @ref ?Load_String@StringTable@@SIPBGPBDPADPBDH@Z=006f9ec0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Game_Speed_Labels@@3PAPBDA=007d83c0
// @ref ?Latency_Labels@@3PAPBDA=007d9bb4
// @ref _swprintf=00783764
// @ref ??_C@_15DEDE@?$AA?$CF?$AAs?$AA?$AA@=007d9c94
// @ref ?Add@?$QueueClass@VEventClass@@$0IA@@@QAEHABVEventClass@@@Z=004de180
// @ref ?Value@?$CDTimerClass@VSystemTimerClass@@@@QBEJXZ=004de200
// @ref ??0?$CDTimerClass@VSystemTimerClass@@@@QAE@J@Z=004de1e0
// @ref ??_C@_0BE@CLPH@D?3?2Ra2?2GOptions?4CPP?$AA@=007d9c9c
// @ref ??_C@_0CB@KDKL@LATENCYFUDGE?5event?5created?5?9?5?$CFd?6@=007d9c70
// @ref ??_C@_0CL@OFHF@Ignoring?5latency?5change?5to?5avoid@=007d9c44
// @ref ??_C@_0CJ@JEPF@Ignoring?5speed?5change?5to?5avoid?5c@=007d9c18
// @ref _?$S41@?1??Options_Menu_Command@@YIXPAUHWND__@@H0I@Z@4EA=00a40de4
// @ref _?speed_timer@?1??Options_Menu_Command@@YIXPAUHWND__@@H0I@Z@4V?$CDTimerClass@VSystemTimerClass@@@@A=00a40dd8
// @ref _?latency_timer@?1??Options_Menu_Command@@YIXPAUHWND__@@H0I@Z@4V?$CDTimerClass@VSystemTimerClass@@@@A=00a40de8

extern char const *Latency_Labels[];            // 0x007D9BB4
extern "C" int __cdecl swprintf(wchar_t *buffer, wchar_t const *format, ...);

static void __fastcall Options_Menu_Command(HWND window, int id, HWND control, unsigned code)
{
    int *result = (int *)GetWindowLongA(window, 8);
    static CDTimerClass<SystemTimerClass> speed_timer;
    static CDTimerClass<SystemTimerClass> latency_timer;
    switch (id) {
        case 0x51E:
            if (code == 0) {
                ShowWindow(window, SW_HIDE);
                if (LoadOptionsClass().Load_Dialog_0053b190()) {
                    *result = 0x51E;
                } else {
                    ShowWindow(window, SW_SHOW);
                    UpdateWindow(window);
                }
            }
            break;
        case 0x3EC:
            if (code == 0) {
                *result = 0x3EC;
            }
            break;
        case 0x51F:
            if (code == 0) {
                if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
                    ShowWindow(window, SW_HIDE);
                    wchar_t description[512];
                    wchar_t const *name = (wchar_t const *)unknown_id_source_a3d290->Name;
                    swprintf(description, L"%s", name);
                    LoadOptionsClass().Save_Dialog_0053b1b0(description);
                    Options_Menu_Init(window);
                    ShowWindow(window, SW_SHOW);
                    UpdateWindow(window);
                } else {
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x1D));
                    *result = 0x51F;
                }
            }
            break;
        case 0x520:
            if (code == 0) {
                ShowWindow(window, SW_HIDE);
                LoadOptionsClass().Delete_Dialog_0053b1e0();
                Options_Menu_Init(window);
                ShowWindow(window, SW_SHOW);
                UpdateWindow(window);
            }
            break;
        case 0x521:
            if (code == 0) {
                unknown_int_a40d48 = 5;
                *result = 1;
            }
            break;
        case 0x522:
            if (code == 0) {
                if (unknown_game_mode_a3d298 == 4) {
                    unknown_int_a40d48 = 2;
                    if (unknown_b2a7ec == 0) {
                        unknown_int_a40d48 = 3;
                    }
                } else {
                    unknown_int_a40d48 = 3;
                }
                *result = 2;
            }
            break;
        case 0x675:
        case 0x686:
            if (code == 0) {
                if (unknown_game_mode_a3d298 == 4) {
                    if (unknown_int_a3d548 == 0) {
                        HWND slider = GetDlgItem(window, 0x3EF);
                        if (slider != 0) {
                            int latency = 3 - SendMessageA(slider, 0x400, 0, 0);
                            if (latency != unknown_a3fba4) {
                                if (latency_timer == 0) {
                                    latency_timer = 900;
                                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x24, latency));
                                    Debug_Printf("LATENCYFUDGE event created - %d\n", latency);
                                } else {
                                    Debug_Printf("Ignoring latency change to avoid cheating\n");
                                }
                            }
                        }
                        slider = GetDlgItem(window, 0x529);
                        if (slider != 0) {
                            int speed = 6 - SendMessageA(slider, 0x400, 0, 0);
                            if (Options.GameSpeed != speed) {
                                if (speed_timer == 0) {
                                    speed_timer = 900;
                                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xD, speed));
                                } else {
                                    Debug_Printf("Ignoring speed change to avoid cheating\n");
                                }
                            }
                        }
                    }
                }
                *result = 1;
            }
            break;
    }
}

int __stdcall Options_Menu_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x497:
            Options_Menu_Init(window);
            return 0;
        case 0x111:
            Options_Menu_Command(window, wparam & 0xFFFF, (HWND)lparam, wparam >> 16);
            break;
        case 0x114:
            if ((unsigned short)wparam == 5) {
                unsigned position = wparam >> 16;
                if ((HWND)lparam == GetDlgItem(window, 0x529)) {
                    char const *label = Game_Speed_Labels[position];
                    HWND text = GetDlgItem(window, 0x671);
                    if (text) {
                        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\GOptions.CPP", 0xC4));
                    }
                    break;
                }
                if ((HWND)lparam == GetDlgItem(window, 0x3EF)) {
                    char const *label = Latency_Labels[position];
                    HWND text = GetDlgItem(window, 0x672);
                    if (text) {
                        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\GOptions.CPP", 0xC4));
                    }
                    break;
                }
            }
            break;
    }
    return 0;
}

