void SerialEdDialog::Set_Custom_Entry_0066dd60(int id, int data, char const *text)
{
    char buffer[128];
    HWND control = GetDlgItem(Window, id);
    if (control) {
        int row = Find_Combo_Item_Data_00736e10(control, -1, data);
        SendMessageA(control, 0x4BD, row, (LPARAM)buffer);
        char *dash = strchr(buffer, '-');
        if (dash && _stricmp(text, dash + 1)) {
            sprintf(buffer, "%ls ", StringTable::Load_String("TXT_CUSTOM", 0, "D:\\Ra2\\SerialEd.cpp", 0x4A3));
            strcat(buffer, text);
            SendMessageA(control, 0x144, row, 0);
            row = SendMessageA(control, 0x4BC, 0, (LPARAM)buffer);
            SendMessageA(control, CB_SETITEMDATA, row, data);
            SendMessageA(control, CB_SETCURSEL, row, 0);
        }
    }
}
