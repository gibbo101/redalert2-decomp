// 0x0060DE40
void PhoneEdit::Build_Phone_Listbox()
{
    HWND handle;
    int i;
    wchar_t item[80];
    char number[80];
    WolLadderListCell thecell;

    handle = GetDlgItem(_Dialog, 0x5E0);
    if (handle) {
        SendMessageA(handle, 0x184, 0, 0);
        if (unknown_session_a3d298.PhoneBook.Count() > 1) {
            qsort((void *)(&unknown_session_a3d298.PhoneBook[0]), unknown_session_a3d298.PhoneBook.Count(),
                  sizeof(PhoneEntryClass *), Phone_Compare);
        }
        for (i = 0; i < unknown_session_a3d298.PhoneBook.Count(); i++) {
            if (!(wcslen(unknown_session_a3d298.PhoneBook[i]->Name))) {
                wcscpy(item, L" ");
            } else {
                wcsncpy(item, unknown_session_a3d298.PhoneBook[i]->Name, 20);
                item[20] = 0;
            }
            int row = SendMessageA(handle, 0x4CD, 0, (LPARAM)item);
            if (!strlen(unknown_session_a3d298.PhoneBook[i]->Number)) {
                wcscpy(item, L" ");
            } else {
                strncpy(number, unknown_session_a3d298.PhoneBook[i]->Number, 20);
                number[20] = 0;
                swprintf(item, L"%hs", number);
            }
            thecell.Flags = 1;
            thecell.Text.Set(item);
            SendMessageA(handle, 0x4A8, MAKEWPARAM(150, row), (LPARAM)&thecell);
            if (unknown_session_a3d298.PhoneBook[i]->Settings.Baud != -1) {
                swprintf(item, L"%d", unknown_session_a3d298.PhoneBook[i]->Settings.Baud);
            } else {
                swprintf(item, L"[%s]", StringTable::Load_String("TXT_DEFAULT", 0, "D:\\Ra2\\PhoneEd.cpp", 0x141));
            }
            thecell.Flags = 1;
            thecell.Text.Set(item);
            SendMessageA(handle, 0x4A8, MAKEWPARAM(275, row), (LPARAM)&thecell);
        }
        if (SendMessageA(handle, 0x18B, 0, 0) == 0 || unknown_session_a3d298.CurPhoneIdx < -1) {
            unknown_session_a3d298.CurPhoneIdx = -1;
        } else {
            if (unknown_session_a3d298.CurPhoneIdx >= SendMessageA(handle, 0x18B, 0, 0)) {
                unknown_session_a3d298.CurPhoneIdx = 0;
            }
        }
        if (unknown_session_a3d298.CurPhoneIdx > -1) {
            SendMessageA(handle, 0x186, unknown_session_a3d298.CurPhoneIdx, 0);
            handle = GetDlgItem(_Dialog, 0x5E5);
            if (handle != 0) {
                SendMessageA(handle, 0x4B4, 0, (LPARAM)unknown_session_a3d298.PhoneBook[unknown_session_a3d298.CurPhoneIdx]->Number);
            }
        }
    }
}
// @ref ??0WolLadderListCell@@QAE@XZ=005de940
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ??_C@_0BD@PIKI@D?3?2Ra2?2PhoneEd?4cpp?$AA@=007eb8f8
// @ref ??_C@_0M@NLP@TXT_DEFAULT?$AA@=007eb90c
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ??_C@_17FKIN@?$AA?$CF?$AAh?$AAs?$AA?$AA@=007eadcc
// @ref ??_C@_19GFJK@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?$AA@=007dfb9c
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Phone_Compare@@YAHPBX0@Z=0060e9f0
// @ref ?Set@WideString@@QAEFPBG@Z=007708f0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref _qsort=00781d46
// @ref _strncpy=007823d0
// @ref _swprintf=00783764
// @ref _wcscpy=00783689
// @ref _wcslen=00783605
// @ref _wcsncpy=00783622
