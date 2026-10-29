bool SerialEdDialog::Read_Settings_0066cf60()
{
    Debug_Printf("Reading serial settings dialog\n");
    HWND control = GetDlgItem(Window, 0x657);
    if (control) {
        int row = SendMessageA(control, CB_GETCURSEL, 0, 0);
        int data = SendMessageA(control, CB_GETITEMDATA, row, 0);
        Settings.Port = 1;
        Settings.ModemName[0] = '\0';
        switch (data) {
            case 0:
                Settings.Port = 0x3F8;
                break;
            case 1:
                Settings.Port = 0x2F8;
                break;
            case 2:
                Settings.Port = 0x3E8;
                break;
            case 3:
                Settings.Port = 0x2E8;
                break;
            case 4: {
                SendMessageA(control, 0x4BD, row, (LPARAM)Buffer);
                Buffer[62] = '\0';
                char *text = strchr(Buffer, '-');
                if (text) {
                    strcpy(Settings.ModemName, text + 1);
                }
                break;
            }
            default:
                SendMessageA(control, 0x4BD, row, (LPARAM)Buffer);
                Buffer[62] = '\0';
                strcpy(Settings.ModemName, Buffer);
                break;
        }
    }
    SerialSettingsType *settings = &Settings;
    Debug_Printf("Port: %lx\n", Settings.Port);
    Debug_Printf("Modem: %s\n", Settings.ModemName);
    control = GetDlgItem(Window, 0x658);
    if (control) {
        int row = SendMessageA(control, CB_GETCURSEL, 0, 0);
        int index = SendMessageA(control, CB_GETITEMDATA, row, 0);
        swscanf(unknown_baud_names_7f3070[index], L"%d", &Settings.Baud);
    }
    Debug_Printf("Baud: %ld\n", Settings.Baud);
    control = GetDlgItem(Window, 0x65E);
    if (control) {
        int selection = SendMessageA(control, 0x188, 0, 0);
        if (selection != -1 && unknown_session_a3d298.InitStrings.Count() != 0) {
            Settings.InitStringIndex = selection;
        } else {
            Settings.InitStringIndex = -1;
        }
    }
    control = GetDlgItem(Window, 0x659);
    if (control) {
        int row = SendMessageA(control, CB_GETCURSEL, 0, 0);
        Settings.CallWaitStringIndex = SendMessageA(control, CB_GETITEMDATA, row, 0);
        Settings.CallWaitString[0] = '\0';
        if (Settings.CallWaitStringIndex == 3) {
            SendMessageA(control, 0x4BD, row, (LPARAM)Buffer);
            Buffer[15] = '\0';
            char *text = strchr(Buffer, '-');
            if (text) {
                strcpy(Settings.CallWaitString, text + 1);
            }
        }
    }
    Settings.DialMethod = 0;
    control = GetDlgItem(Window, 0x65B);
    if (control && SendMessageA(control, 0xF0, 0, 0) == 1) {
        Settings.DialMethod = 1;
    }
    Debug_Printf("DialMethod: %s\n", Settings.DialMethod == 0 ? "Tone" : "Pulse");
    control = GetDlgItem(Window, 0x3EA);
    if (control) {
        if (SendMessageA(control, 0xF0, 0, 0) == 1) {
            Settings.ErrorCorrection = 1;
        } else {
            Settings.ErrorCorrection = 0;
        }
    }
    control = GetDlgItem(Window, 0x3EB);
    if (control) {
        if (SendMessageA(control, 0xF0, 0, 0) == 1) {
            Settings.Compression = 1;
        } else {
            Settings.Compression = 0;
        }
    }
    switch (serial_manager_00a40a28.Detect_Port(settings)) {
        case 0:
            return true;
        case 1:
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_TO_OPEN_PORT", 0, "D:\\Ra2\\SerialEd.cpp", 0x213),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\SerialEd.cpp", 0x213), 0, 0, false);
            break;
        case 2:
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_IRQ_ALREADY_IN_USE", 0, "D:\\Ra2\\SerialEd.cpp", 0x217),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\SerialEd.cpp", 0x217), 0, 0, false);
            break;
    }
    return false;
}
