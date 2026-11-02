// void SerialEdDialog::Fill_Port_0066d5a0() (0x0066D5A0)
// Fills the port combo box 0x657 (TibSun serialed.cpp
// SerialEdit::Build_Port_Listbox): COM1-COM4, the first ten registry modems
// (data 5..), the custom entry (data 4), then selects Settings.ModemName or
// Settings.Port, made the custom entry when it is not listed.
// Every message goes through an inline SendMessageA wrapper: its parameters are
// the extra (code-free) temporaries that give VC6 the original's scratch
// registers from the second modem-name address on (a plain call is 87.92).
static inline LRESULT Send_Message(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
    return SendMessageA(handle, message, wparam, lparam);
}

void SerialEdDialog::Fill_Port_0066d5a0()
{
    int i;
    int index;
    int port_index;
    wchar_t custom[128];
    wchar_t custom_port[128];

    HWND handle = GetDlgItem(Window, 0x657);
    if (handle) {
        Send_Message(handle, CB_RESETCONTENT, 0, 0);
        for (i = 0; i < 4; i++) {
            index = Send_Message(handle, 0x4C2, 0,
                (LPARAM)StringTable::Load_String(unknown_port_names_7f305c[i], 0, "D:\\Ra2\\SerialEd.cpp", 0x287));
            Send_Message(handle, CB_SETITEMDATA, index, i);
        }

        ModemCount = 0;
        for (i = 0; i < 10; i++) {
            ModemRegistryEntryClass *modemregistry = new ModemRegistryEntryClass(i);
            if (modemregistry) {
                if (modemregistry->ModemName) {
                    strncpy(ModemNames[ModemCount], modemregistry->ModemName, 63);
                    index = Send_Message(handle, 0x4BC, 0, (LPARAM)ModemNames[ModemCount]);
                    Send_Message(handle, CB_SETITEMDATA, index, ModemCount + 5);
                    ModemCount++;
                }
                delete modemregistry;
            }
        }

        wcscpy(custom, StringTable::Load_String("TXT_CUSTOM", 0, "D:\\Ra2\\SerialEd.cpp", 0x2A2));
        index = Send_Message(handle, 0x4C2, 0, (LPARAM)custom);
        Send_Message(handle, CB_SETITEMDATA, index, 4);
        Send_Message(handle, CB_SETCURSEL, 0, 0);

        if (strlen(Settings.ModemName)) {
            port_index = Send_Message(handle, 0x4B8, -1, (LPARAM)Settings.ModemName);
            if (port_index == -1) {
                port_index = Find_Combo_Item_Data_00736e10(handle, -1, 4);
                if (port_index != -1) {
                    swprintf(custom, L"%s %hs",
                        StringTable::Load_String("TXT_CUSTOM", 0, "D:\\Ra2\\SerialEd.cpp", 0x2B4), Settings.ModemName);
                    Send_Message(handle, 0x144, port_index, 0);
                    port_index = Send_Message(handle, 0x4C2, 0, (LPARAM)custom);
                    Send_Message(handle, CB_SETITEMDATA, port_index, 4);
                }
            }
            Send_Message(handle, CB_SETCURSEL, port_index, 0);
        } else {
            switch (Settings.Port) {
                case 0x3F8:
                    port_index = 0;
                    port_index = Find_Combo_Item_Data_00736e10(handle, -1, port_index);
                    break;
                case 0x2F8:
                    port_index = 1;
                    port_index = Find_Combo_Item_Data_00736e10(handle, -1, port_index);
                    break;
                case 0x3E8:
                    port_index = 2;
                    port_index = Find_Combo_Item_Data_00736e10(handle, -1, port_index);
                    break;
                case 0x2E8:
                    port_index = 3;
                    port_index = Find_Combo_Item_Data_00736e10(handle, -1, port_index);
                    break;
                default:
                    port_index = 4;
                    port_index = Find_Combo_Item_Data_00736e10(handle, -1, port_index);
                    if (port_index != -1) {
                        swprintf(custom_port, L"%s %x",
                            StringTable::Load_String("TXT_CUSTOM", 0, "D:\\Ra2\\SerialEd.cpp", 0x2DA), Settings.Port);
                        Send_Message(handle, 0x144, port_index, 0);
                        port_index = Send_Message(handle, 0x4C2, 0, (LPARAM)custom_port);
                        Send_Message(handle, CB_SETITEMDATA, port_index, 4);
                    }
                    break;
            }
            Send_Message(handle, CB_SETCURSEL, port_index, 0);
        }
    }
}
