// int __stdcall Score_Dialog_Proc_0069A7D0(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x0069A7D0)
// The single-player score dialog's procedure (stlscore.cpp). After the common dialog handler:
// 0x497 starts the score sound handle, shows the par time for the difficulty and the elapsed
// time (hh:mm:ss), the under- or over-par title and message, the total of the human houses'
// four trackers, and plays the SCORE theme; WM_DESTROY stops the handle; button 0x423 sets the
// caller's done flag; 0x4D8 and 0x4EC drive the counter control 0x72B (0x4EC with the
// ScoreAnimSound sound).
#define SOUND_PLAY_DECLARE_KEEP_EVENT
// @ref ??_C@_1BO@ECFI@?$AA?$CF?$AA0?$AA2?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?$AA@=007f62a8
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ??_C@_05DDDB@SCORE?$AA@=007e5648
// @ref ??_C@_0BE@OIMO@D?3?2Ra2?2stlscore?4cpp?$AA@=007f62c8
// @ref ?unknown_score_audio_abd6a0@@3VUnknownAudioController@@A=00abd6a0
// @ref ?unknown_score_audio_on_abd6d4@@3HA=00abd6d4
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ?Unknown_00405D50@UnknownAudioController@@QAEXXZ=00405d50
// @ref ?Unknown_00405FE0@UnknownAudioController@@QAEXXZ=00405fe0
// @ref ?Unknown_00406100@UnknownAudioController@@QAIXPAUAudioEvent@@PAUAudioEventType@@@Z=00406100
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Get_All_Totals_Sum@UnknownHouseTracker@@QAEHXZ=0070c510
// @ref ?From_Name@ThemeClass@@QBEHPBD@Z=006e8510
// @ref ?Play_Song@ThemeClass@@QAEHH@Z=006e7eb0
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref _swprintf=00783764
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__PostMessageA@16=0079a470
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/sound_play.hpp"
#include "shared/win32_api.hpp"
#include "shared/dialog_default_proc.hpp"
#include "shared/string_table.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/theme.hpp"

// The score screen's sound handle and whether it is in use (0x00ABD6A0, 0x00ABD6D4).
extern UnknownAudioController unknown_score_audio_abd6a0;
extern int unknown_score_audio_on_abd6d4;

int __stdcall Score_Dialog_Proc_0069A7D0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *done = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x497: {
        unknown_score_audio_abd6a0.Init();
        unknown_score_audio_on_abd6d4 = 1;
        int par = 0;
        if (unknown_id_source_a3d290->Difficulty == 0) {
            par = unknown_id_source_a3d290->ParTimeEasy;
        } else if (unknown_id_source_a3d290->Difficulty == 1) {
            par = unknown_id_source_a3d290->ParTimeMedium;
        } else if (unknown_id_source_a3d290->Difficulty == 2) {
            par = unknown_id_source_a3d290->ParTimeHard;
        }
        wchar_t text[32];
        HWND item;
        int par_seconds = par / 60;
        int minutes = par_seconds / 60;
        int hours = minutes / 60;
        swprintf(text, L"%02d:%02d:%02d", hours, minutes - hours * 60, par_seconds - minutes * 60);
        item = GetDlgItem(window, 0x6F1);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);

        int elapsed = unknown_id_source_a3d290->ElapsedTime.Time();
        int seconds = elapsed / 60;
        minutes = seconds / 60;
        hours = minutes / 60;
        swprintf(text, L"%02d:%02d:%02d", hours, minutes - hours * 60, seconds - minutes * 60);
        item = GetDlgItem(window, 0x6F2);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);

        char const *title;
        char const *message_text;
        if (seconds <= par_seconds) {
            title = unknown_id_source_a3d290->UnderParTitle;
            message_text = unknown_id_source_a3d290->UnderParMessage;
        } else {
            title = unknown_id_source_a3d290->OverParTitle;
            message_text = unknown_id_source_a3d290->OverParMessage;
        }
        wchar_t const *title_string = StringTable::Load_String(title, 0, "D:\\Ra2\\stlscore.cpp", 0x89);
        wchar_t const *message_string = StringTable::Load_String(message_text, 0, "D:\\Ra2\\stlscore.cpp", 0x8A);
        item = GetDlgItem(window, 0x6F3);
        SendMessageA(item, 0x4B2, 0, (LPARAM)title_string);
        item = GetDlgItem(window, 0x6F4);
        SendMessageA(item, 0x4B2, 0, (LPARAM)message_string);

        int total = 0;
        int count = Houses.Count();
        for (int i = 0; i < count; i++) {
            HouseClass *house = Houses[i];
            if (house->unknown_135) {
                total += house->unknown_2288.Get_All_Totals_Sum();
                total += house->unknown_2a90.Get_All_Totals_Sum();
                total += house->unknown_3298.Get_All_Totals_Sum();
                total += house->unknown_3aa0.Get_All_Totals_Sum();
            }
        }
        item = GetDlgItem(window, 0x72B);
        PostMessageA(item, 0x4D7, 0, (LPARAM)window);
        swprintf(text, L"%d", total);
        item = GetDlgItem(window, 0x6F6);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        Theme.Play_Song((ThemeType)Theme.From_Name("SCORE"));
        return 0;
    }

    case 2:
        if (unknown_score_audio_on_abd6d4) {
            unknown_score_audio_abd6a0.Unknown_00405FE0();
            unknown_score_audio_abd6a0.Unknown_00405C10();
            unknown_score_audio_on_abd6d4 = 0;
            return 0;
        }
        break;

    case 0x111:
        if ((unsigned short)wparam == 0x423) {
            *done = 1;
            unknown_score_audio_abd6a0.Unknown_00405FE0();
            return 0;
        }
        break;

    case 0x4D8:
        if (wparam == 0) {
            SendDlgItemMessageA(window, 0x72B, 0x4D5, 0, 0x1D);
        }
        break;

    case 0x4EC:
        unknown_score_audio_abd6a0.Unknown_00405D50();
        unknown_score_audio_abd6a0.Unknown_00406100(Voc_Play(Rules->ScoreAnimSound, 1.0f, 0x2000, 0), 0);
        SendDlgItemMessageA(window, 0x72B, 0x4D3, 0, 0);
        break;
    }
    return 0;
}
