// 0x0060E160
void PhoneEdit::Add()
{
    PhoneEntryClass *p_entry = new PhoneEntryClass();
    if (p_entry == 0) {
        return;
    }
    p_entry->Name[0] = 0;
    p_entry->Number[0] = 0;
    p_entry->Settings.Port = 0;
    p_entry->Settings.IRQ = -1;
    p_entry->Settings.Baud = -1;
    p_entry->Settings.DialMethod = 0;
    p_entry->Settings.InitStringIndex = -1;
    p_entry->Settings.CallWaitStringIndex = 3;
    p_entry->Settings.CallWaitString[0] = 0;
    ShowWindow(_Dialog, SW_HIDE);
    UpdateWindow(MainWindow);
    if (PhoneEntryEdit().Dialog(p_entry) == true) {
        unknown_session_a3d298.PhoneBook.Add(p_entry);
        Changed = true;
        Build_Phone_Listbox();
        unknown_session_a3d298.CurPhoneIdx = unknown_session_a3d298.PhoneBook.ID(p_entry);
        if (unknown_session_a3d298.CurPhoneIdx > -1) {
            HWND handle = GetDlgItem(_Dialog, 0x5E0);
            if (handle != 0) {
                SendMessageA(handle, 0x186, unknown_session_a3d298.CurPhoneIdx, 0);
            }
            handle = GetDlgItem(_Dialog, 0x5E5);
            if (handle != 0) {
                SendMessageA(handle, 0x4B4, 0, (LPARAM)unknown_session_a3d298.PhoneBook[unknown_session_a3d298.CurPhoneIdx]->Number);
            }
        }
    } else {
        delete p_entry;
    }
    ShowWindow(_Dialog, SW_SHOW);
}
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Build_Phone_Listbox@PhoneEdit@@QAEXXZ=0060de40
// @ref ?Dialog@PhoneEntryEdit@@QAE_NPAVPhoneEntryClass@@@Z=0060e4c0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__UpdateWindow@4=0079a46c
