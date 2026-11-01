// 0x0060E900
void PhoneEntryEdit::Init()
{
    bool custom;

    HWND handle = GetDlgItem(_Dialog, 0x5E5);
    SendMessageA(handle, 0x4B2, 0, (LPARAM)Phone->Name);
    handle = GetDlgItem(_Dialog, 0x5DF);
    SendMessageA(handle, 0x4B4, 0, (LPARAM)Phone->Number);
    if (Phone->Settings.Port == 0 || Phone->Settings.IRQ == -1 || Phone->Settings.Baud == -1) {
        TempSettings = unknown_session_a3d298.SerialDefaults;
        custom = false;
    } else {
        TempSettings = Phone->Settings;
        custom = true;
    }
    handle = GetDlgItem(_Dialog, 0x664);
    if (handle != 0) {
        SendMessageA(handle, 0xF1, custom == true, 0);
    }
    handle = GetDlgItem(_Dialog, 0x663);
    if (handle != 0) {
        SendMessageA(handle, 0xF1, custom == false, 0);
    }
}
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
