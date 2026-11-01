// MP_Score_Dialog_Proc_005AAE40 (0x005AAE40): the score dialog's procedure. After the common dialog
// handler: 0x497 plays the score theme and fills the title, game, time and one row per score (name, kills,
// lost, built and score in the player's colour); WM_PAINT frames the rows; button 0x6D1 sets the caller's
// done flag.

int __stdcall MP_Score_Dialog_Proc_005AAE40(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *done = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x0F: {
        RECT first;
        RECT last;
        HWND item = GetDlgItem(window, 0x6D2);
        Window_Rect_In_Main_Client(item, &first);
        int id = unknown_mp_score_controls_7e5518[unknown_session_a3d298.ScoreCount - 1][4];
        item = GetDlgItem(window, id);
        Window_Rect_In_Main_Client(item, &last);
        Rect area(first.left, first.top, last.right - first.left, last.bottom - first.top);
        Unknown_Rect_Shrink_006F1B30(&area, -4, -8);
        Unknown_005feb60(&area, unknown_surface_839958, 0, 0x9F);
        break;
    }
    case 0x111:
        if ((unsigned short)wparam == 0x6D1) {
            *done = 1;
            break;
        }
        break;
    case 0x497: {
        wchar_t text[32];
        Theme.Play_Song((ThemeType)Theme.From_Name("SCORE"));
        if (unknown_session_a3d298.Type == 4) {
            swprintf(text, StringTable::Load_String("TXT_GAME", 0, "D:\\Ra2\\MPScore.cpp", 284), unknown_b2a7fc);
        } else {
            swprintf(text, StringTable::Load_String("TXT_GAME", 0, "D:\\Ra2\\MPScore.cpp", 286), unknown_a3f58c);
        }
        wchar_t const *title;
        if (unknown_session_a3d298.Type == 5) {
            title = StringTable::Load_String("GUI:SkirmishScore", 0, "D:\\Ra2\\MPScore.cpp", 290);
        } else {
            title = StringTable::Load_String("GUI:MultiplayerScore", 0, "D:\\Ra2\\MPScore.cpp", 292);
        }
        HWND item = GetDlgItem(window, 0x694);
        SendMessageA(item, 0x4B2, 0, (LPARAM)title);
        item = GetDlgItem(window, 0x6D2);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        MP_Format_Time_005AAAE0(text, unknown_id_source_a3d290->ElapsedTime.Time() / 60);
        item = GetDlgItem(window, 0x3EA);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        MP_Tally_Scores_005AABD0();
        Unknown_005AADD0();
        for (int i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
            ColorScheme *scheme = ColorSchemes[unknown_sorted_scores_a715f0[i]->Scheme];
            RGBClass color = scheme->BaseColor.To_RGB();
            unsigned long rgb = color.Red | (color.Green << 8) | (color.Blue << 16);
            int id = unknown_mp_score_controls_7e5518[i][0];
            wchar_t const *name = unknown_sorted_scores_a715f0[i]->Name;
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x4B2, 0, (LPARAM)name);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_mp_score_controls_7e5518[i][1];
            MP_Set_Dialog_Item_Number_005AAB80(window, id, unknown_sorted_scores_a715f0[i]->Kills);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_mp_score_controls_7e5518[i][2];
            MP_Set_Dialog_Item_Number_005AAB80(window, id, unknown_sorted_scores_a715f0[i]->Lost);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_mp_score_controls_7e5518[i][3];
            MP_Set_Dialog_Item_Number_005AAB80(window, id, unknown_sorted_scores_a715f0[i]->Built);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
            id = unknown_mp_score_controls_7e5518[i][4];
            MP_Set_Dialog_Item_Number_005AAB80(window, id, unknown_sorted_scores_a715f0[i]->Score);
            item = GetDlgItem(window, id);
            SendMessageA(item, 0x498, 0, rgb);
        }
        break;
    }
    }
    return 0;
}
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ??_C@_05DDDB@SCORE?$AA@=007e5648
// @ref ??_C@_08BAEO@TXT_GAME?$AA@=007e563c
// @ref ??_C@_0BC@POFI@GUI?3SkirmishScore?$AA@=007e5628
// @ref ??_C@_0BD@OOCG@D?3?2Ra2?2MPScore?4cpp?$AA@=007e55b8
// @ref ??_C@_0BF@DIMM@GUI?3MultiplayerScore?$AA@=007e5610
// @ref ??_C@_0BG@MFEO@TXT_TIME_FORMAT_HOURS?$AA@=007d156c
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?From_Name@ThemeClass@@QBEHPBD@Z=006e8510
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Play_Song@ThemeClass@@QAEHH@Z=006e7eb0
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?unknown_a3f58c@@3HA=00a3f58c
// @ref ?unknown_b2a7fc@@3HA=00b2a7fc
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_mp_score_controls_7e5518@@3PAY04HA=007e5518
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref _qsort=00781d46
// @ref _swprintf=00783764
// @ref ?Unknown_005feb60@@YIXPAVRect@@PAVSurface@@HH@Z=005feb60
// @ref ?Unknown_Rect_Shrink_006F1B30@@YIXPAVRect@@HH@Z=006f1b30
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?unknown_compare_descending_60_005aae10@@YAHPBX0@Z=005aae10
// @ref ?MP_Tally_Scores_005AABD0@@YAXXZ=005aabd0
