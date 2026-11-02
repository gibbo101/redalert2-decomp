// 0x0060DC80: dials the typed number; a number not in the book gets a new entry with default settings.
bool PhoneEdit::Dial()
{
    HWND handle = GetDlgItem(_Dialog, 0x5E5);
    SendMessageA(handle, 0x4B5, sizeof(Number), (LPARAM)Number);
    HWND handle2 = GetDlgItem(_Dialog, 0x5E0);
    unknown_session_a3d298.CurPhoneIdx = SendMessageA(handle2, 0x188, 0, 0);
    if (unknown_session_a3d298.CurPhoneIdx == -1
        || strcmp(unknown_session_a3d298.PhoneBook[unknown_session_a3d298.CurPhoneIdx]->Number, Number)) {
        if (strlen(Number) == 0) {
            return false;
        }
        PhoneEntryClass *p_entry = new PhoneEntryClass();
        if (p_entry == 0) {
            return false;
        }
        wcscpy(p_entry->Name, StringTable::Load_String("TXT_NONAME", 0, "D:\\Ra2\\PhoneEd.cpp", 0xE7));
        strcpy(p_entry->Number, Number);
        p_entry->Settings.Port = 0;
        p_entry->Settings.IRQ = -1;
        p_entry->Settings.Baud = -1;
        p_entry->Settings.DialMethod = 0;
        p_entry->Settings.InitStringIndex = -1;
        p_entry->Settings.CallWaitStringIndex = 3;
        p_entry->Settings.CallWaitString[0] = 0;
        unknown_session_a3d298.PhoneBook.Add(p_entry);
        Build_Phone_Listbox();
        Changed = true;
        unknown_session_a3d298.CurPhoneIdx = unknown_session_a3d298.PhoneBook.ID(p_entry);
    }
    return true;
}
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_0BD@PIKI@D?3?2Ra2?2PhoneEd?4cpp?$AA@=007eb8f8
// @ref ??_C@_0L@JPAF@TXT_NONAME?$AA@=007eb8ec
// @ref ?Build_Phone_Listbox@PhoneEdit@@QAEXXZ=0060de40
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref _wcscpy=00783689
