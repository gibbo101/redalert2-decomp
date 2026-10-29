void SerialEdDialog::Add_Init_String_0066de80()
{
    HWND edit = GetDlgItem(Window, 0x65D);
    HWND list = GetDlgItem(Window, 0x65E);
    if (edit && list) {
        SendMessageA(edit, 0x4B5, sizeof(Buffer), (LPARAM)Buffer);
        SendMessageA(edit, 0x4B4, 0, (LPARAM)"");
        strtrim(Buffer);
        if (strlen(Buffer)) {
            _strupr(Buffer);
            int index = SendMessageA(list, 0x4C4, -1, (LPARAM)Buffer);
            if (index == -1) {
                char *text = new char[41];
                strcpy(text, Buffer);
                index = SendMessageA(list, 0x4C8, 0, (LPARAM)text);
                if (index == -1) {
                    return;
                }
                unknown_session_a3d298.InitStrings.Add(text);
            }
            SendMessageA(list, 0x186, index, 0);
            SendMessageA(list, 0x197, index, 0);
            Settings.InitStringIndex = index;
        }
    }
}
