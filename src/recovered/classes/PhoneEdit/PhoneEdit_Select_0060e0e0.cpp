// 0x0060E0E0
void PhoneEdit::Select()
{
    HWND handle = GetDlgItem(_Dialog, 0x5E0);
    if (handle != 0) {
        if (SendMessageA(handle, 0x18B, 0, 0) > 0) {
            unknown_session_a3d298.CurPhoneIdx = SendMessageA(handle, 0x188, 0, 0);
            if (unknown_session_a3d298.CurPhoneIdx > -1) {
                handle = GetDlgItem(_Dialog, 0x5E5);
                SendMessageA(handle, 0x4B4, 0, (LPARAM)unknown_session_a3d298.PhoneBook[unknown_session_a3d298.CurPhoneIdx]->Number);
                SetFocus(handle);
            }
        }
    }
}
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__SetFocus@4=0079a38c
