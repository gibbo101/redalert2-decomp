// 0x0060E2E0
void PhoneEdit::Edit()
{
    HWND handle = GetDlgItem(_Dialog, 0x5E0);
    if (handle != 0) {
        unknown_session_a3d298.CurPhoneIdx = SendMessageA(handle, 0x188, 0, 0);
    }
    if (unknown_session_a3d298.CurPhoneIdx <= -1) {
        return;
    }
    PhoneEntryClass *p_entry = new PhoneEntryClass();
    if (p_entry == 0) {
        return;
    }
    PhoneEntryClass *p_oldentry = unknown_session_a3d298.PhoneBook[unknown_session_a3d298.CurPhoneIdx];
    (*p_entry) = (*p_oldentry);
    ShowWindow(_Dialog, SW_HIDE);
    UpdateWindow(MainWindow);
    if (PhoneEntryEdit().Dialog(p_entry) == true) {
        Changed = true;
        (*p_oldentry) = (*p_entry);
        Build_Phone_Listbox();
        unknown_session_a3d298.CurPhoneIdx = unknown_session_a3d298.PhoneBook.ID(p_oldentry);
        if (unknown_session_a3d298.CurPhoneIdx > -1) {
            SendMessageA(handle, 0x186, unknown_session_a3d298.CurPhoneIdx, 0);
            handle = GetDlgItem(_Dialog, 0x5E5);
            if (handle != 0) {
                SendMessageA(handle, 0x4B4, 0, (LPARAM)p_oldentry->Number);
            }
        }
    }
    ShowWindow(_Dialog, SW_SHOW);
    delete p_entry;
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
