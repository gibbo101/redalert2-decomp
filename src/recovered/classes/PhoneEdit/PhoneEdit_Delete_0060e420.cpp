// 0x0060E420 (also expanded in Phone_Dialog_Proc)
void PhoneEdit::Delete()
{
    HWND handle = GetDlgItem(_Dialog, 0x5E0);
    if (handle == 0) {
        return;
    }
    unknown_session_a3d298.CurPhoneIdx = SendMessageA(handle, 0x188, 0, 0);
    if (unknown_session_a3d298.CurPhoneIdx <= -1) {
        return;
    }
    unknown_session_a3d298.PhoneBook.Delete(unknown_session_a3d298.CurPhoneIdx);
    Changed = true;
    Build_Phone_Listbox();
    if (unknown_session_a3d298.CurPhoneIdx == -1) {
        handle = GetDlgItem(_Dialog, 0x5E5);
        if (handle != 0) {
            SendMessageA(handle, 0x4B4, 0, (LPARAM)"");
        }
    }
}
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?Build_Phone_Listbox@PhoneEdit@@QAEXXZ=0060de40
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
