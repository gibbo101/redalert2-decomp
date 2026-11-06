// int __stdcall Unknown_006340F0(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x006340F0)
// The in-game diplomacy dialog (0x73, opened by 0x00634A00): 0x497 fills a row per
// house 1-7 (alliance check box, chat check box, name and side labels), hides the
// rows of absent or non-multiplayer houses and the observer flag, then starts a
// 250 ms timer; each timer tick refreshes the rows through 0x00634970. The alliance
// boxes queue an alliance event, the chat boxes set unknown_flags_a3f118 and 0x730
// the game mode's team chat flag; 0x423 closes the dialog.
#include "shared/radar.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/wide_string.hpp"
#include "shared/dialog_default_proc.hpp"
#include "shared/uicmnds.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__InvalidateRect@12=0079a494
// @ref __imp__GetDlgCtrlID@4=0079a3f4
// @ref __imp__KillTimer@8=0079a4c4
// @ref __imp__SetTimer@16=0079a4d4
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_player_control_4d0ee0@@YIHH@Z=004d0ee0
// @ref ?unknown_send_byte_message_005e1fb0@@YIXPAUHWND__@@E@Z=005e1fb0
// @ref ?unknown_5e1fd0@@YIXPAUHWND__@@E@Z=005e1fd0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Unknown_00634970@RadarClass@@QAEXH@Z=00634970
// @ref ?unknown_text_770430@WideString@@QBEPBGXZ=00770430
// @ref ?Unknown_006F62D0@@YIXK@Z=006f62d0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_house_a72d28@@3PAVHouseClass@@A=00a72d28
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_flags_a3f118@@3PA_NA=00a3f118
// @ref ?unknown_session_a3d298.LANTaunts@@3_NA=00a3f120
// @ref ?unknown_session_a3d298.WOLTaunts@@3_NA=00a3f121
// @ref ?unknown_map_name_a3d342@@3PAGA=00a3d342
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ?Diplomacy_Name_Controls@@3PAHA=007ee06c
// @ref ?Diplomacy_Side_Controls@@3PAHA=007ee08c
// @ref ?Diplomacy_Ally_Controls@@3PAHA=007ee0ac
// @ref ?Diplomacy_Chat_Controls@@3PAHA=007ee0cc

void __fastcall unknown_send_byte_message_005e1fb0(HWND window, unsigned char value);   // 0x005E1FB0
void __fastcall unknown_5e1fd0(HWND control, unsigned char value);   // 0x005E1FD0
void __fastcall Unknown_006F62D0(unsigned long argument);

extern int Diplomacy_Name_Controls[8];   // 0x007EE06C 0x411-0x418
extern int Diplomacy_Side_Controls[8];   // 0x007EE08C 0x419-0x420
extern int Diplomacy_Ally_Controls[8];   // 0x007EE0AC -1, 0x6CF-0x6D5
extern int Diplomacy_Chat_Controls[8];   // 0x007EE0CC -1, 0x6D6-0x6D9, 0x6E2-0x6E4

static inline HWND Get_Item(HWND window, int id)
{
    return GetDlgItem(window, id);
}

static inline LRESULT Send_Dlg_Item_Message(HWND dialog, int id, UINT message, WPARAM wparam, LPARAM lparam)
{
    HWND control = Get_Item(dialog, id);
    return SendMessageA(control, message, wparam, lparam);
}

static inline BOOL Show_Window(HWND window, int show)
{
    return ShowWindow(window, show);
}

static inline bool Is_Control(int const *table, int id)
{
    for (int index = 0; index < 8; index++) {
        if (table[index] == id) {
            return true;
        }
    }
    return false;
}

static inline int Control_Index(int const *table, int id)
{
    for (int index = 0; index < 8; index++) {
        if (table[index] == id) {
            return index;
        }
    }
    return -1;
}

int __stdcall Unknown_006340F0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x497: {
            int index;
            for (index = 0; index < 8; index++) {
                Send_Dlg_Item_Message(window, Diplomacy_Name_Controls[index], 0x4B2, 0, (LPARAM)L"");
                Send_Dlg_Item_Message(window, Diplomacy_Side_Controls[index], 0x4B2, 0, (LPARAM)L"");
            }
            bool any_ally = false;
            bool any_chat = false;
            int count = Houses.Count();
            for (index = 1; index < 8; index++) {
                HWND ally = Get_Item(window, Diplomacy_Ally_Controls[index]);
                HWND chat = Get_Item(window, Diplomacy_Chat_Controls[index]);
                int house_index = index;
                if (index == unknown_player_a35db4->ArrayIndex) {
                    house_index = 0;
                }
                HouseClass *house;
                if (house_index < count && (house = Houses[house_index]) != 0 && house->Type->Multiplay) {
                    if (Rules->unknown_111d && house->Unknown_004F52F0()) {
                        if (unknown_house_a72d28 != unknown_player_a35db4) {
                        unknown_send_byte_message_005e1fb0(ally, 1);
                        bool allied = unknown_player_a35db4->Is_Ally(house);
                        SendMessageA(ally, 0xF1, allied, 0);
                        unknown_5e1fd0(ally, house->Is_Ally(unknown_player_a35db4));
                        any_ally = true;
                        if (unknown_int_a3d548) {
                            EnableWindow(ally, 0);
                        }
                        } else {
                            ShowWindow(ally, 0);
                        }
                    } else {
                        ShowWindow(ally, 0);
                    }
                    if (!house->Unknown_004F52F0()) {
                        ShowWindow(chat, 0);
                    } else {
                        if (!unknown_int_a3d548) {
                            SendMessageA(chat, 0xF1, unknown_flags_a3f118[house_index], 0);
                        } else {
                            SendMessageA(chat, 0xF1, 1, 0);
                            EnableWindow(chat, 0);
                        }
                        any_chat = true;
                    }
                } else {
                    HWND flag = Get_Item(window, unknown_player_control_4d0ee0(index));
                    EnableWindow(flag, 0);
                    ShowWindow(flag, 0);
                    HWND name = Get_Item(window, Diplomacy_Name_Controls[index]);
                    EnableWindow(name, 0);
                    ShowWindow(name, 0);
                    EnableWindow(ally, 0);
                    ShowWindow(ally, 0);
                    EnableWindow(chat, 0);
                    ShowWindow(chat, 0);
                    HWND side = Get_Item(window, Diplomacy_Side_Controls[index]);
                    EnableWindow(side, 0);
                    ShowWindow(side, 0);
                }
            }
            if (!any_ally) {
                Show_Window(Get_Item(window, 0x597), 0);
            }
            if (!any_chat) {
                Show_Window(Get_Item(window, 0x425), 0);
            }
            HWND team = Get_Item(window, 0x730);
            if (team) {
                if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
                    Show_Window(team, 5);
                    if (unknown_game_mode_a3d298 == 3) {
                        SendMessageA(team, 0xF1, unknown_session_a3d298.LANTaunts, 0);
                    } else if (unknown_game_mode_a3d298 == 4) {
                        SendMessageA(team, 0xF1, unknown_session_a3d298.WOLTaunts, 0);
                    }
                } else {
                    Show_Window(team, 0);
                }
            }
            Map.Unknown_00634970((int)window);
            if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
                HWND mode = Get_Item(window, 0x426);
                SendMessageA(mode, 0x4B2, 0, (LPARAM)unknown_session_a3d298.Mode->Get_Name().unknown_text_770430());
            }
            HWND map_name = Get_Item(window, 0x71B);
            SendMessageA(map_name, 0x4B2, 0, (LPARAM)unknown_map_name_a3d342);
            SetTimer(window, 0, 250, 0);
            return 0;
        }
        case 0x113:
            Map.Unknown_00634970((int)window);
            InvalidateRect(window, 0, 1);
            return 0;
        case 0x111: {
            int id = GetDlgCtrlID((HWND)lparam);
            if (id == 0x423) {
                unsigned short code = wparam >> 16;
                if (code == 0) {
                    KillTimer(window, 0);
                    *(int *)GetWindowLongA(window, 8) = 0x423;
                    return 0;
                }
            } else if (Is_Control(Diplomacy_Ally_Controls, id)) {
                unsigned int code = wparam >> 16;
                if (code == 1 || code == 0) {
                    int house_index = Control_Index(Diplomacy_Ally_Controls, id);
                    if (house_index == unknown_player_a35db4->ArrayIndex) {
                        house_index = 0;
                    }
                    if (code == 0) {
                        SendMessageA((HWND)lparam, 0xF1, 1, 0);
                    } else if (code == 1) {
                        SendMessageA((HWND)lparam, 0xF1, 0, 0);
                    }
                    Unknown_006F62D0(house_index);
                    return 0;
                }
            } else if (Is_Control(Diplomacy_Chat_Controls, id)) {
                int value = (unsigned short)(wparam >> 16);
                if (value == 1 || value == 0) {
                    bool checked = (unsigned short)(wparam >> 16) == 1;
                    int house_index = Control_Index(Diplomacy_Chat_Controls, id);
                    if (house_index == unknown_player_a35db4->ArrayIndex) {
                        house_index = 0;
                    }
                    unknown_flags_a3f118[house_index] = checked;
                    return 0;
                }
            } else if (id == 0x730) {
                unsigned int code = wparam >> 16;
                if (code == 1 || code == 0) {
                    if (unknown_game_mode_a3d298 == 3) {
                        unknown_session_a3d298.LANTaunts = code == 1;
                        return 0;
                    }
                    if (unknown_game_mode_a3d298 == 4) {
                        unknown_session_a3d298.WOLTaunts = code == 1;
                    }
                }
            }
            break;
        }
    }
    return 0;
}
