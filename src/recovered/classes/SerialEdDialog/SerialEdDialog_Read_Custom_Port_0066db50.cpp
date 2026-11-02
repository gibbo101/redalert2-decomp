// void SerialEdDialog::Read_Custom_Port_0066db50() (0x0066DB50)
// Takes the custom port typed into the hidden edit box 0x65F (TibSun
// serialed.cpp SerialEdit::Set_Port): a port address or COM1-COM4 selects that
// port in the combo box 0x657, other text becomes its custom entry, and a bad
// COM number shows TXT_INVALID_PORT_ADDRESS.
void SerialEdDialog::Read_Custom_Port_0066db50()
{
    int port_index = -1;

    HWND combo = GetDlgItem(Window, 0x657);
    HWND edit = GetDlgItem(Window, 0x65F);
    if (combo && edit) {
        ShowWindow(edit, SW_HIDE);
        EnableWindow(edit, FALSE);
        SendMessageA(edit, 0x4B5, 0x40, (LPARAM)Buffer);
        Buffer[63] = '\0';
        strtrim(Buffer);
        _strupr(Buffer);

        if (_stricmp(Buffer, "3F8") == 0) {
            port_index = 0;
        } else if (_stricmp(Buffer, "2F8") == 0) {
            port_index = 1;
        } else if (_stricmp(Buffer, "3E8") == 0) {
            port_index = 2;
        } else if (_stricmp(Buffer, "2E8") == 0) {
            port_index = 3;
        } else if (strncmp(Buffer, "COM", 3) == 0) {
            switch (Buffer[3]) {
                case '1':
                    port_index = 0;
                    break;
                case '2':
                    port_index = 1;
                    break;
                case '3':
                    port_index = 2;
                    break;
                case '4':
                    port_index = 3;
                    break;
                default:
                    if (Buffer[3] <= '9' && Buffer[3] > '0') {
                        Buffer[4] = '\0';
                        Set_Custom_Entry_0066dd60(0x657, 4, Buffer);
                    } else {
                        WWMessageBox(L" ").Process(
                            StringTable::Load_String("TXT_INVALID_PORT_ADDRESS", 0, "D:\\Ra2\\SerialEd.cpp", 0x440),
                            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\SerialEd.cpp", 0x440), 0, 0, false);
                    }
            }
        } else {
            Set_Custom_Entry_0066dd60(0x657, 4, Buffer);
        }

        if (port_index != -1) {
            int row = Find_Combo_Item_Data_00736e10(combo, -1, port_index);
            SendMessageA(combo, CB_SETCURSEL, row, 0);
        }
    }
}
