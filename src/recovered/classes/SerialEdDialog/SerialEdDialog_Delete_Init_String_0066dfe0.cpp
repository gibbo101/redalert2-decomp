void SerialEdDialog::Delete_Init_String_0066dfe0()
{
    HWND list = GetDlgItem(Window, 0x65E);
    if (list && SendMessageA(list, 0x18B, 0, 0) > 0) {
        int index = SendMessageA(list, 0x188, 0, 0);
        if (index != -1) {
            SendMessageA(list, 0x182, index, 0);
            unknown_session_a3d298.InitStrings.Delete(index);
            if (index >= SendMessageA(list, 0x18B, 0, 0)) {
                index--;
            }
            SendMessageA(list, 0x186, index, 0);
            SendMessageA(list, 0x197, index, 0);
            Settings.InitStringIndex = index;
        }
    }
}
