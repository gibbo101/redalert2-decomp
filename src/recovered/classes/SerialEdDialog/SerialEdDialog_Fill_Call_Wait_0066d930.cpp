void SerialEdDialog::Fill_Call_Wait_0066d930()
{
    HWND control = GetDlgItem(Window, 0x659);
    if (control) {
        SendMessageA(control, CB_RESETCONTENT, 0, 0);
        for (int index = 0; index < 4; index++) {
            unsigned short const *text = unknown_session_a3d298.CallWaitStrings[index];
            int row = SendMessageA(control, 0x4C2, 0, (LPARAM)text);
            SendMessageA(control, CB_SETITEMDATA, row, index);
        }
        int row = Find_Combo_Item_Data_00736e10(control, -1, Settings.CallWaitStringIndex);
        SendMessageA(control, CB_SETCURSEL, row, 0);
    }
}
