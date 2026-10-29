// int __stdcall unknown_end_score_dialog_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) -- 0x00467330
// Dialog procedure of the campaign end score screen: fills the campaign, difficulty, time and per-player
// score rows on WM_INITDIALOG; button 0x6D1 sets the caller's done flag. Every case breaks to the one
// final return (separate returns sink the ebp save into WM_INITDIALOG).
// @ref ??_C@_09NHCJ@GUI?3Blank?$AA@=007d16e4
// @ref ??_C@_0BC@IKBK@GUI?3CampaignLabel?$AA@=007d16f0
// @ref ??_C@_0BE@HEHO@TXT_DIFFICULTY_EASY?$AA@=007d168c
// @ref ??_C@_0BE@LFCN@D?3?2Ra2?2CampScor?4cpp?$AA@=007d1584
// @ref ??_C@_0BF@JAMI@GUI?3DifficultyString?$AA@=007d1674
// @ref ??_C@_0BG@CKEG@TXT_DIFFICULTY_MEDIUM?$AA@=007d165c
// @ref ??_C@_0BG@EMPM@TXT_DIFFICULTY_BRUTAL?$AA@=007d1644
// @ref ??_C@_0BG@MFEO@TXT_TIME_FORMAT_HOURS?$AA@=007d156c
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ?unknown_end_score_list_8504a8@@3PAPAVMPlayerScoreType@@A=008504a8
// @ref ?unknown_end_score_count_8504e8@@3HA=008504e8
// @ref ?unknown_end_score_time_85049c@@3HA=0085049c
// @ref ?unknown_end_score_difficulty_8504d0@@3HA=008504d0
// @ref ?unknown_end_score_campaign_850488@@3HA=00850488
// @ref ?unknown_end_score_name_850554@@3PAGA=00850554
// @ref ?unknown_score_controls_7d1484@@3PAY05HA=007d1484
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Unknown_005FEE70@@YIXPAUHWND__@@@Z=005fee70
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__PostMessageA@16=0079a470
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref __imp__ShowWindow@8=0079a498
#include "shared/ms_message_box.hpp"
#include "shared/queue.hpp"
#include "shared/color_scheme.hpp"
#include "shared/string_table.hpp"
#include "shared/campaign_score.hpp"

int __stdcall unknown_end_score_dialog_proc_467330(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *done = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x0F:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        break;
    case 0x110: {
        HWND item;
        wchar_t text[32];
        text[0] = 0;
        item = GetDlgItem(window, 0x733);
        SendMessageA(item, 0x4B2, 0, (LPARAM)unknown_end_score_name_850554);
        swprintf(text, StringTable::Load_String("GUI:CampaignLabel", 0, "D:\\Ra2\\CampScor.cpp", 722),
            unknown_end_score_campaign_850488);
        item = GetDlgItem(window, 0x735);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        if (unknown_end_score_difficulty_8504d0 == 0) {
            swprintf(text, StringTable::Load_String("GUI:DifficultyString", 0, "D:\\Ra2\\CampScor.cpp", 726),
                StringTable::Load_String("TXT_DIFFICULTY_EASY", 0, "D:\\Ra2\\CampScor.cpp", 726));
        } else if (unknown_end_score_difficulty_8504d0 == 1) {
            swprintf(text, StringTable::Load_String("GUI:DifficultyString", 0, "D:\\Ra2\\CampScor.cpp", 728),
                StringTable::Load_String("TXT_DIFFICULTY_MEDIUM", 0, "D:\\Ra2\\CampScor.cpp", 728));
        } else if (unknown_end_score_difficulty_8504d0 == 2) {
            swprintf(text, StringTable::Load_String("GUI:DifficultyString", 0, "D:\\Ra2\\CampScor.cpp", 730),
                StringTable::Load_String("TXT_DIFFICULTY_BRUTAL", 0, "D:\\Ra2\\CampScor.cpp", 730));
        } else {
            swprintf(text, StringTable::Load_String("GUI:Blank", 0, "D:\\Ra2\\CampScor.cpp", 732));
        }
        item = GetDlgItem(window, 0x732);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        unknown_format_time_467290(text, unknown_end_score_time_85049c / 60);
        item = GetDlgItem(window, 0x3EA);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        for (int i = 0; i < unknown_end_score_count_8504e8; i++) {
            ColorScheme *scheme = ColorSchemes[unknown_end_score_list_8504a8[i]->Scheme];
            RGBClass color = scheme->BaseColor.To_RGB();
            unsigned long rgb = color.Red | (color.Green << 8) | (color.Blue << 16);
            int id = unknown_score_controls_7d1484[i][0];
            wchar_t const *name = unknown_end_score_list_8504a8[i]->Name;
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x4B2, 0, (LPARAM)name);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][1];
            unknown_set_dialog_item_number_467240(window, id, unknown_end_score_list_8504a8[i]->Kills);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][2];
            unknown_set_dialog_item_number_467240(window, id, unknown_end_score_list_8504a8[i]->Lost);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][3];
            unknown_set_dialog_item_number_467240(window, id, unknown_end_score_list_8504a8[i]->Built);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][4];
            unknown_set_dialog_item_number_467240(window, id, unknown_end_score_list_8504a8[i]->Score);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            if (i == 0) {
                name = unknown_end_score_list_8504a8[0]->Name;
                item = GetDlgItem(window, 0x73A);
                SendMessageA(item, 0x4B2, 0, (LPARAM)name);
                item = GetDlgItem(window, 0x73A);
                SendMessageA(item, 0x498, 0, rgb);
                swprintf(text, L"%d", unknown_end_score_list_8504a8[0]->Score);
                item = GetDlgItem(window, 0x73B);
                SendMessageA(item, 0x4B2, 0, (LPARAM)text);
                item = GetDlgItem(window, 0x73B);
                SendMessageA(item, 0x498, 0, rgb);
            } else if (i == 1) {
                name = unknown_end_score_list_8504a8[1]->Name;
                item = GetDlgItem(window, 0x739);
                SendMessageA(item, 0x4B2, 0, (LPARAM)name);
                item = GetDlgItem(window, 0x739);
                SendMessageA(item, 0x498, 0, rgb);
                swprintf(text, L"%d", unknown_end_score_list_8504a8[1]->Score);
                item = GetDlgItem(window, 0x738);
                SendMessageA(item, 0x4B2, 0, (LPARAM)text);
                item = GetDlgItem(window, 0x738);
                SendMessageA(item, 0x498, 0, rgb);
            }
        }
        break;
    }
    case 0x111:
        if ((unsigned short)wparam == 0x6D1) {
            *done = 1;
            break;
        }
        break;
    case 0x497:
        {
            HWND item = GetDlgItem(window, 0x72B);
            PostMessageA(item, 0x4D7, 0, (LPARAM)window);
        }
        break;
    case 0x4D8:
        if (wparam == 0) {
            SendDlgItemMessageA(window, 0x72B, 0x4D5, wparam, 0x1D);
        }
        break;
    case 0x4EC:
        SendDlgItemMessageA(window, 0x72B, 0x4D3, 0, 0);
        break;
    case 0x4ED:
        unknown_5159b0(0, true);
        ShowWindow(window, 0);
        unknown_dialog_5ecf40(window, 1);
        break;
    }
    return 0;
}
