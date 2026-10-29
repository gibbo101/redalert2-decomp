void SerialEdDialog::Init_0066d370(SerialSettingsType const *settings)
{
    Settings = *settings;
    if (Settings.Port == 0) {
        Settings.Port = 0x2F8;
    }
    if (Settings.IRQ == -1) {
        Settings.IRQ = 3;
    }
    if (Settings.Baud == -1) {
        Settings.Baud = 57600;
    }
    Fill_Port_0066d5a0();
    Fill_Baud_0066d860();
    Fill_Call_Wait_0066d930();
    Update_Radio_0066da70();
    if (unknown_session_a3d298.InitStrings.Count() == 0) {
        char *text = new char[8];
        strcpy(text, "ATZ");
        unknown_session_a3d298.InitStrings.Add(text);
        Settings.InitStringIndex = 0;
    }
    Fill_Init_Strings_0066d9b0();
    HWND button = GetDlgItem(Window, 0x3EB);
    if (button) {
        SendMessageA(button, 0xF1, settings->Compression != 0, 0);
    }
    button = GetDlgItem(Window, 0x3EA);
    if (button) {
        SendMessageA(button, 0xF1, settings->ErrorCorrection != 0, 0);
    }
}
