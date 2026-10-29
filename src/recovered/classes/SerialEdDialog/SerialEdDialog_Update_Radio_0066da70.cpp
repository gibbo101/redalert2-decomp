void SerialEdDialog::Update_Radio_0066da70()
{
    bool first = Settings.DialMethod == 0;
    HWND button = GetDlgItem(Window, 0x65C);
    if (button != 0) {
        SendMessageA(button, 0xF1, first == true, 0);
    }
    button = GetDlgItem(Window, 0x65B);
    if (button != 0) {
        SendMessageA(button, 0xF1, first == false, 0);
    }
}
