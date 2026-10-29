void SerialEdDialog::Read_Custom_Call_Wait_0066dcf0()
{
    HWND control = GetDlgItem(Window, 0x65A);
    if (control) {
        ShowWindow(control, SW_HIDE);
        EnableWindow(control, FALSE);
        SendMessageA(control, 0x4B5, 16, (LPARAM)Buffer);
        Buffer[15] = '\0';
        strtrim(Buffer);
        _strupr(Buffer);
        Set_Custom_Entry_0066dd60(0x659, 3, Buffer);
    }
}
