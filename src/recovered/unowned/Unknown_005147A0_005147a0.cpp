// int __stdcall Unknown_005147A0(HWND, UINT, WPARAM, LPARAM) -- 0x005147A0
// Body 0x005147A0-0x00514ED2 (1842 bytes, linear sweep to the last ret 0x10, padding to 0x00514EE0;
// no jump tables: compare chains). The dialog procedure pointer is pushed at 0x00513BCE (Select_Game).
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/campaign.hpp"
#include "shared/sound_play.hpp"
#include "shared/voc_class.hpp"
#include "shared/audio.hpp"
#include "shared/string_table.hpp"
#include "shared/game_controls_dialog.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_campaign_names_7db540@@3PAPBDA=007db540
// @ref ?unknown_side_voc_7db4f8@@3HA=007db4f8
// @ref ?unknown_soviet_voc_7db54c@@3HA=007db54c
// @ref ?unknown_allied_voc_7db550@@3HA=007db550
// @ref ?unknown_bootcamp_voc_7db554@@3HA=007db554
// @ref ?unknown_hover_time_a41680@@3_JA=00a41680
// @ref ?unknown_hover_id_a41688@@3HA=00a41688
// @ref ?unknown_campaign_list_a4168d@@3DA=00a4168d
// @ref ?unknown_pressed_a41690@@3PAUHWND__@@A=00a41690
// @ref ?unknown_side_sound_a411e8@@3UAudioEventHandle@@A=00a411e8
// @ref ?unknown_flag_a6ebd0@@3_NA=00a6ebd0
// @ref ??_C@_0BF@KKGN@SovietCampaignSelect?$AA@=007dbcc0
// @ref ??_C@_0BF@OBEA@AlliedCampaignSelect?$AA@=007dbca8
// @ref ??_C@_0P@LKG@BootCampSelect?$AA@=007dbc98
// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4

// The first scenario of the Allied, Soviet and boot camp campaigns ("all1", "sov1", "tut1"; 0x007DB540).
extern char const *unknown_campaign_names_7db540[3];
// The side sound the hovered button plays when chosen (-1 none; 0x007DB4F8) and the three
// side sounds (0x007DB54C Soviet, 0x007DB550 Allied, 0x007DB554 boot camp).
extern int unknown_side_voc_7db4f8;
extern int unknown_soviet_voc_7db54c;
extern int unknown_allied_voc_7db550;
extern int unknown_bootcamp_voc_7db554;
extern __int64 unknown_hover_time_a41680;     // 0x00A41680
extern int unknown_hover_id_a41688;           // 0x00A41688 the highlighted side button
extern char unknown_campaign_list_a4168d;     // 0x00A4168D show the campaign list
extern HWND unknown_pressed_a41690;           // 0x00A41690 the button the mouse went down on
extern AudioEventHandle unknown_side_sound_a411e8;   // 0x00A411E8
extern bool unknown_flag_a6ebd0;              // 0x00A6EBD0

// What the dialog's long 8 points at: the chosen campaign (-1 cancel) and whether one was chosen.
struct UnknownCampaignChoice {
    int Campaign;
    bool Chosen;
};

// The campaign choice dialog (pointer only): the Allied (0x6EA), Soviet (0x6EC) and boot camp
// (0x6EB) buttons highlight under the mouse and play their side sound when clicked; list 0x455
// holds the campaigns, slider 0x50F the difficulty.
int __stdcall Unknown_005147A0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    switch (message) {
    case 0x114:
        if ((HWND)lparam == GetDlgItem(window, 0x50F)) {
            char const *label = Difficulty_Labels[wparam >> 16];
            HWND text = GetDlgItem(window, 0x670);
            SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\Init.CPP", 0x4A9));
            return 0;
        }
        break;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 0x40E:
            if ((unsigned short)(wparam >> 16) == 0) {
                UnknownCampaignChoice *choice = (UnknownCampaignChoice *)GetWindowLongA(window, 8);
                if (choice != 0) {
                    HWND list = GetDlgItem(window, 0x455);
                    if (list != 0) {
                        choice->Campaign = SendMessageA(list, 0x188, 0, 0);
                        choice->Chosen = true;
                    }
                }
                HWND slider = GetDlgItem(window, 0x50F);
                if (slider != 0) {
                    unknown_difficulty_a40b1c = SendMessageA(slider, 0x400, 0, 0);
                    return 0;
                }
            }
            break;
        case 0x686:
            {
                UnknownCampaignChoice *choice = (UnknownCampaignChoice *)GetWindowLongA(window, 8);
                if (choice != 0) {
                    choice->Campaign = -1;
                    choice->Chosen = true;
                    return 0;
                }
            }
            break;
        }
        break;
    case 0x84:
        if (unknown_pressed_a41690 == 0) {
            POINT point;
            point.x = lparam & 0xFFFF;
            point.y = (unsigned)lparam >> 16;
            RECT rect;
            GetWindowRect(window, &rect);
            point.x -= rect.left;
            point.y -= rect.top;
            HWND child = ChildWindowFromPointEx(window, point, 1);
            if (child != 0) {
                int id = GetDlgCtrlID(child);
                if (unknown_hover_id_a41688 != id) {
                    SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D5, 0, 0);
                    SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D4, 0, 0);
                    unknown_hover_time_a41680 = Audio_Now() + 500;
                    unknown_side_voc_7db4f8 = -1;
                    unknown_hover_id_a41688 = 0;
                }
                if (id == 0x6EA) {
                    if (unknown_hover_id_a41688 != id) {
                        unknown_side_voc_7db4f8 = unknown_allied_voc_7db550;
                    }
                    SendDlgItemMessageA(window, 0x6EA, 0x4D3, 0, 0);
                    unknown_hover_id_a41688 = 0x6EA;
                    return 0;
                }
                if (id == 0x6EC) {
                    if (unknown_hover_id_a41688 != id) {
                        unknown_side_voc_7db4f8 = unknown_soviet_voc_7db54c;
                    }
                    SendDlgItemMessageA(window, 0x6EC, 0x4D3, 0, 0);
                    unknown_hover_id_a41688 = 0x6EC;
                    return 0;
                }
                if (id == 0x6EB) {
                    if (unknown_hover_id_a41688 != id) {
                        unknown_side_voc_7db4f8 = unknown_bootcamp_voc_7db554;
                    }
                    SendDlgItemMessageA(window, 0x6EB, 0x4D3, 0, 0);
                    unknown_hover_id_a41688 = 0x6EB;
                    return 0;
                }
            } else if (unknown_hover_id_a41688 != 0) {
                SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D5, 0, 0);
                SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D4, 0, 0);
                return 0;
            }
        }
        break;
    case 0x201:
        {
            POINT point;
            point.x = lparam & 0xFFFF;
            point.y = (unsigned)lparam >> 16;
            RECT rect;
            GetWindowRect(window, &rect);
            point.x -= rect.left;
            point.y -= rect.top;
            HWND child = ChildWindowFromPointEx(window, point, 1);
            if (child != 0) {
                int id = GetDlgCtrlID(child);
                if (id == 0x6EA || id == 0x6EC || id == 0x6EB) {
                    unknown_pressed_a41690 = child;
                    SetCapture(window);
                    return 0;
                }
            }
        }
        break;
    case 0x202:
        {
            POINT point;
            point.x = lparam & 0xFFFF;
            point.y = (unsigned)lparam >> 16;
            RECT rect;
            GetWindowRect(window, &rect);
            point.x -= rect.left;
            point.y -= rect.top;
            HWND child = ChildWindowFromPointEx(window, point, 1);
            if (child != 0) {
                int id = GetDlgCtrlID(child);
                if (child == unknown_pressed_a41690) {
                    UnknownCampaignChoice *choice = (UnknownCampaignChoice *)GetWindowLongA(window, 8);
                    if (choice != 0) {
                        if (id == 0x6EA) {
                            choice->Campaign = CampaignClass::Find_Index(unknown_campaign_names_7db540[0]);
                            choice->Chosen = true;
                        } else if (id == 0x6EC) {
                            choice->Campaign = CampaignClass::Find_Index(unknown_campaign_names_7db540[1]);
                            choice->Chosen = true;
                        } else if (id == 0x6EB) {
                            choice->Campaign = CampaignClass::Find_Index(unknown_campaign_names_7db540[2]);
                            choice->Chosen = true;
                        }
                        if (choice->Chosen) {
                            unknown_flag_a6ebd0 = false;
                            SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D5, 0, 0);
                            SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D4, 0, 0);
                            HWND slider = GetDlgItem(window, 0x50F);
                            if (slider != 0) {
                                unknown_difficulty_a40b1c = SendMessageA(slider, 0x400, 0, 0);
                            }
                            if (unknown_side_voc_7db4f8 != -1) {
                                Audio_Event_Handle_Stop(&unknown_side_sound_a411e8);
                                Voc_Play(unknown_side_voc_7db4f8, 1.0f, 0x2000, &unknown_side_sound_a411e8);
                                unknown_side_voc_7db4f8 = -1;
                            }
                        }
                    }
                } else if (id == 0x6EA || id == 0x6EC || id == 0x6EB) {
                    if (unknown_hover_id_a41688 != 0) {
                        SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D5, 0, 0);
                        SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D4, 0, 0);
                    }
                    SendDlgItemMessageA(window, id, 0x4D5, 0, 0);
                    SendDlgItemMessageA(window, id, 0x4D4, 0, 0);
                    unknown_hover_id_a41688 = id;
                } else if (unknown_hover_id_a41688 != 0) {
                    SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D5, 0, 0);
                    SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D4, 0, 0);
                    unknown_hover_id_a41688 = 0;
                }
            } else if (unknown_hover_id_a41688 != 0) {
                SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D5, 0, 0);
                SendDlgItemMessageA(window, unknown_hover_id_a41688, 0x4D4, 0, 0);
                unknown_hover_id_a41688 = 0;
            }
            if (GetCapture() == window) {
                ReleaseCapture();
            }
            unknown_pressed_a41690 = 0;
        }
        break;
    case 0x497:
        {
            unknown_soviet_voc_7db54c = VocClass::From_Name("SovietCampaignSelect");
            unknown_allied_voc_7db550 = VocClass::From_Name("AlliedCampaignSelect");
            unknown_bootcamp_voc_7db554 = VocClass::From_Name("BootCampSelect");
            HWND list = GetDlgItem(window, 0x455);
            if (unknown_campaign_list_a4168d) {
                if (list != 0) {
                    for (int i = 0; i < Campaigns.Count(); i++) {
                        SendMessageA(list, 0x4CD, 0, (LPARAM)Campaigns[i]->Description);
                    }
                    SendMessageA(list, 0x186, 0, 0);
                }
            } else {
                ShowWindow(list, 0);
                HWND button = GetDlgItem(window, 0x40E);
                ShowWindow(button, 0);
                EnableWindow(button, 0);
            }
            HWND slider = GetDlgItem(window, 0x50F);
            if (slider != 0) {
                PostMessageA(slider, 0x4AC, 0, 0);
                PostMessageA(slider, 0x406, 1, 0x20000);
                PostMessageA(slider, 0x405, 1, unknown_difficulty_a40b1c);
            }
            SendDlgItemMessageA(window, 0x6EA, 0x4D5, 0, 0);
            SendDlgItemMessageA(window, 0x6EA, 0x4D4, 0, 0);
            SendDlgItemMessageA(window, 0x6EC, 0x4D5, 0, 0);
            SendDlgItemMessageA(window, 0x6EC, 0x4D4, 0, 0);
            SendDlgItemMessageA(window, 0x6EB, 0x4D5, 0, 0);
            SendDlgItemMessageA(window, 0x6EB, 0x4D4, 0, 0);
            return 0;
        }
    }
    return 0;
}
