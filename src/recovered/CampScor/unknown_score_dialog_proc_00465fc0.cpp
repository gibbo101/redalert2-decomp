// int __stdcall unknown_score_dialog_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) -- 0x00465FC0
// (2,656 bytes; the inventory splits it at false entries 0x0046622A, 0x00466754 and 0x004669E8 from the number
// table at 0x008217B0)
// The cooperative campaign score screen: after the common dialog handler, WM_INITDIALOG fills the title,
// difficulty, campaign name, time and one row per score (name, kills, lost, built, score in the player's
// colour; computers start ready; a player no longer connected shows TXT_ABORTED and disables continue);
// the continue button 0x6D1 toggles ready (TXT_READY / TXT_WAITING to the other players, commands 0x23 / 0x25),
// the cancel button 0x5C0 ends with 2 (command 0x24), and 0x4ED hides the dialog.
// @ref ??_C@_0N@LAJB@TXT_COMPUTER?$AA@=007d1634
// @ref ??_C@_09IMGH@TXT_READY?$AA@=007d1610
// @ref ??_C@_0L@EJFF@GUI?3Cancel?$AA@=007d1604
// @ref ??_C@_0M@LCFM@TXT_ABORTED?$AA@=007d161c
// @ref ??_C@_0M@MHCJ@TXT_WAITING?$AA@=007d1628
// @ref ??_C@_0N@LECO@GUI?3Continue?$AA@=007d15f4
// @ref ??_C@_0P@CEJM@GUI?3Difficulty?$AA@=007d16ac
// @ref ??_C@_19GKBP@?$AA?$CF?$AAs?$AA?3?$AA?5?$AA?$AA@=007d16a0
// @ref ??_C@_09NHCJ@GUI?3Blank?$AA@=007d16e4
// @ref ??_C@_0BE@HEHO@TXT_DIFFICULTY_EASY?$AA@=007d168c
// @ref ??_C@_0BE@LFCN@D?3?2Ra2?2CampScor?4cpp?$AA@=007d1584
// @ref ??_C@_0BF@JAMI@GUI?3DifficultyString?$AA@=007d1674
// @ref ??_C@_0BG@CKEG@TXT_DIFFICULTY_MEDIUM?$AA@=007d165c
// @ref ??_C@_0BG@EMPM@TXT_DIFFICULTY_BRUTAL?$AA@=007d1644
// @ref ??_C@_0BG@MFEO@TXT_TIME_FORMAT_HOURS?$AA@=007d156c
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_score_list_850448@@3PAPAVMPlayerScoreType@@A=00850448
// @ref ?unknown_score_ready_8504c8@@3PA_NA=008504c8
// @ref ?unknown_score_controls_7d1484@@3PAY05HA=007d1484
// @ref ?unknown_text_a3d342@@3PADA=00a3d342
// @ref ?unknown_score_850504@@3_NA=00850504
// @ref ?unknown_score_time_850508@@3HA=00850508
// @ref ?unknown_score_difficulty_7d1480@@3HA=007d1480
// @ref ?unknown_score_flag_850510@@3_NA=00850510
// @ref ?unknown_score_name_850514@@3PAGA=00850514
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Service@IPXManagerClass@@UAEHXZ=00525f60
// @ref ?unknown_5259a0@IPXManagerClass@@QAEHPAXHHPBG@Z=005259a0
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Unknown_005FEE70@@YIXPAUHWND__@@@Z=005fee70
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref _wcscmp=007837d3
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__InvalidateRect@12=0079a494
// @ref __imp__ShowWindow@8=0079a498
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/ms_message_box.hpp"
#include "shared/queue.hpp"
#include "shared/color_scheme.hpp"
#include "shared/string_table.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/lobby.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/campaign_score.hpp"

extern "C" int __cdecl wcscmp(wchar_t const *left, wchar_t const *right);

// Sends a score-screen message (command) to every other player.
static inline void Send_Score_Packet(int command)
{
    UnknownScorePacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = command;
    strcpy(packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
    for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
        unknown_ipx_manager_a40978.unknown_5259a0(&packet, 0x2F, 1, unknown_players_a3fa7c[i]->Name);
        unknown_ipx_manager_a40978.Service();
    }
}

int __stdcall unknown_score_dialog_proc_465fc0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *done = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x110: {
        wchar_t text[32];
        HWND item = GetDlgItem(window, 0x71B);
        SendMessageA(item, 0x4B2, 0, (LPARAM)unknown_text_a3d342);
        swprintf(text, L"%s: ", StringTable::Load_String("GUI:Difficulty", 0, "D:\\Ra2\\CampScor.cpp", 285));
        if (unknown_score_difficulty_7d1480 == 0) {
            swprintf(text, StringTable::Load_String("GUI:DifficultyString", 0, "D:\\Ra2\\CampScor.cpp", 287),
                StringTable::Load_String("TXT_DIFFICULTY_EASY", 0, "D:\\Ra2\\CampScor.cpp", 287));
        } else if (unknown_score_difficulty_7d1480 == 1) {
            swprintf(text, StringTable::Load_String("GUI:DifficultyString", 0, "D:\\Ra2\\CampScor.cpp", 289),
                StringTable::Load_String("TXT_DIFFICULTY_MEDIUM", 0, "D:\\Ra2\\CampScor.cpp", 289));
        } else if (unknown_score_difficulty_7d1480 == 2) {
            swprintf(text, StringTable::Load_String("GUI:DifficultyString", 0, "D:\\Ra2\\CampScor.cpp", 291),
                StringTable::Load_String("TXT_DIFFICULTY_BRUTAL", 0, "D:\\Ra2\\CampScor.cpp", 291));
        }
        item = GetDlgItem(window, 0x732);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        item = GetDlgItem(window, 0x733);
        SendMessageA(item, 0x4B2, 0, (LPARAM)unknown_score_name_850514);
        unknown_format_time_465c20(text, unknown_score_time_850508 / 60);
        item = GetDlgItem(window, 0x3EA);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        memset(unknown_score_ready_8504c8, true, sizeof(unknown_score_ready_8504c8));
        for (int i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
            if (wcscmp(unknown_score_list_850448[i]->Name, StringTable::Load_String("TXT_COMPUTER", 0, "D:\\Ra2\\CampScor.cpp", 307)) != 0) {
                unknown_score_ready_8504c8[i] = false;
            }
            ColorScheme *scheme = ColorSchemes[unknown_score_list_850448[i]->Scheme];
            RGBClass color = scheme->BaseColor.To_RGB();
            unsigned long rgb = color.Red | (color.Green << 8) | (color.Blue << 16);
            int id = unknown_score_controls_7d1484[i][0];
            wchar_t const *name = unknown_score_list_850448[i]->Name;
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x4B2, 0, (LPARAM)name);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][1];
            unknown_set_dialog_item_number_00465cc0(window, id, unknown_score_list_850448[i]->Kills);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][2];
            unknown_set_dialog_item_number_00465cc0(window, id, unknown_score_list_850448[i]->Lost);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][3];
            unknown_set_dialog_item_number_00465cc0(window, id, unknown_score_list_850448[i]->Built);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_score_controls_7d1484[i][4];
            unknown_set_dialog_item_number_00465cc0(window, id, unknown_score_list_850448[i]->Score);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            int count = unknown_players_a3fa7c.Count();
            bool found = false;
            for (int j = 0; j < count; j++) {
                if (wcscmp(unknown_players_a3fa7c[j]->Name, unknown_score_list_850448[i]->Name) == 0) {
                    found = true;
                    break;
                }
            }
            id = unknown_score_controls_7d1484[i][5];
            if (found) {
                wchar_t const *status = StringTable::Load_String("TXT_WAITING", 0, "D:\\Ra2\\CampScor.cpp", 367);
                item = GetDlgItem(window, id);
                SendMessageA(item, 0x4B2, 0, (LPARAM)status);
            } else if (!unknown_score_ready_8504c8[i]) {
                wchar_t const *status = StringTable::Load_String("TXT_ABORTED", 0, "D:\\Ra2\\CampScor.cpp", 370);
                item = GetDlgItem(window, id);
                SendMessageA(item, 0x4B2, 0, (LPARAM)status);
                EnableWindow(GetDlgItem(window, 0x6D1), FALSE);
            }
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
        }
        unknown_score_flag_850510 = false;
        return 0;
    }
    case 0x0F:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        return 0;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 0x6D1:
            if (!unknown_score_flag_850510) {
                if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
                    Send_Score_Packet(0x23);
                }
                for (int i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
                    int id = unknown_score_controls_7d1484[i][5];
                    if (wcscmp(unknown_players_a3fa7c[0]->Name, unknown_score_list_850448[i]->Name) == 0) {
                        wchar_t const *status = StringTable::Load_String("TXT_READY", 0, "D:\\Ra2\\CampScor.cpp", 415);
                        HWND item = GetDlgItem(window, id);
                        SendMessageA(item, 0x4B2, 0, (LPARAM)status);
                        break;
                    }
                }
                wchar_t const *label = StringTable::Load_String("GUI:Cancel", 0, "D:\\Ra2\\CampScor.cpp", 419);
                HWND item = GetDlgItem(window, 0x6D1);
                SendMessageA(item, 0x4B2, 0, (LPARAM)label);
                EnableWindow(GetDlgItem(window, 0x5C0), FALSE);
                *done = 1;
                unknown_score_flag_850510 = true;
                InvalidateRect(window, 0, FALSE);
                return 0;
            } else {
                if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
                    Send_Score_Packet(0x25);
                }
                for (int i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
                    int id = unknown_score_controls_7d1484[i][5];
                    if (wcscmp(unknown_players_a3fa7c[0]->Name, unknown_score_list_850448[i]->Name) == 0) {
                        wchar_t const *status = StringTable::Load_String("TXT_WAITING", 0, "D:\\Ra2\\CampScor.cpp", 434);
                        HWND item = GetDlgItem(window, id);
                        SendMessageA(item, 0x4B2, 0, (LPARAM)status);
                        break;
                    }
                }
                wchar_t const *label = StringTable::Load_String("GUI:Continue", 0, "D:\\Ra2\\CampScor.cpp", 439);
                HWND item = GetDlgItem(window, 0x6D1);
                SendMessageA(item, 0x4B2, 0, (LPARAM)label);
                EnableWindow(GetDlgItem(window, 0x5C0), TRUE);
                *done = 1;
                unknown_score_flag_850510 = false;
                InvalidateRect(window, 0, FALSE);
                return 0;
            }
        case 0x5C0:
            *done = 2;
            unknown_score_850504 = false;
            if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
                Send_Score_Packet(0x24);
            }
            return 1;
        }
        break;
    case 0x4ED:
        unknown_5159b0(0, true);
        unknown_dialog_5ecf40(window, 1);
        ShowWindow(window, 0);
        break;
    }
    return 0;
}
