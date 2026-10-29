void SerialEdDialog::Show_Text_0066dae0(int id)
{
    HWND control = GetDlgItem(Window, id);
    if (control != 0) {
        ShowWindow(control, SW_SHOW);
        EnableWindow(control, TRUE);
        char *text = strchr(Buffer, '-');
        if (text != 0) {
            text++;
            strtrim(text);
        } else {
            text = "";
        }
        SendMessageA(control, 0x4B4, 0, (LPARAM)text);
        SetFocus(control);
    }
}
