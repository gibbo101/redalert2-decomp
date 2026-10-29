void SerialEdDialog::Fill_Baud_0066d860()
{
    HWND control = GetDlgItem(Window, 0x658);
    if (control) {
        SendMessageA(control, CB_RESETCONTENT, 0, 0);
        for (int index = 0; index < 6; index++) {
            unsigned short *name = unknown_baud_names_7f3070[index];
            int row = SendMessageA(control, 0x4C2, 0, (LPARAM)name);
            SendMessageA(control, CB_SETITEMDATA, row, index);
        }
        int selection;
        switch (Settings.Baud) {
            case 14400:
                selection = 0;
                break;
            case 19200:
                selection = 1;
                break;
            case 28800:
                selection = 2;
                break;
            default:
                selection = 3;
                break;
            case 57600:
                selection = 4;
                break;
            case 115200:
                selection = 5;
                break;
        }
        int row = Find_Combo_Item_Data_00736e10(control, -1, selection);
        SendMessageA(control, CB_SETCURSEL, row, 0);
    }
}
