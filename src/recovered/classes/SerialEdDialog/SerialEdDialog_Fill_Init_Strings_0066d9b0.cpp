void SerialEdDialog::Fill_Init_Strings_0066d9b0()
{
    HWND control = GetDlgItem(Window, 0x65E);
    if (control) {
        SendMessageA(control, 0x184, 0, 0);
        for (int index = 0; index < unknown_session_a3d298.InitStrings.Count(); index++) {
            SendMessageA(control, 0x4C8, 0, (LPARAM)unknown_session_a3d298.InitStrings[index]);
        }
        if (SendMessageA(control, 0x18B, 0, 0) == 0 || Settings.InitStringIndex < -1) {
            Settings.InitStringIndex = -1;
        } else if (Settings.InitStringIndex >= SendMessageA(control, 0x18B, 0, 0)) {
            Settings.InitStringIndex = 0;
        }
        if (Settings.InitStringIndex != -1) {
            SendMessageA(control, 0x186, Settings.InitStringIndex, 0);
        }
    }
}
