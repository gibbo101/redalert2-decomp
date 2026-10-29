int __stdcall SerialEdDialog::Dialog_Proc_0066cb00(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) {
        return result;
    }
    SerialEdDialog *dialog = (SerialEdDialog *)GetWindowLongA(window, DWL_USER);
    switch (message) {
        case 0x497: {
            HWND control = GetDlgItem(window, 0x65D);
            if (control) {
                SendMessageA(control, 0xC5, 40, 0);
            }
            control = GetDlgItem(window, 0x65F);
            if (control) {
                SendMessageA(control, 0xC5, 62, 0);
            }
            control = GetDlgItem(window, 0x65A);
            if (control) {
                SendMessageA(control, 0xC5, 15, 0);
            }
            break;
        }
        case 0x111:
            switch ((unsigned short)wparam) {
                case 1:
                    if ((unsigned short)(wparam >> 16) == 0 && dialog->Read_Settings_0066cf60() == true) {
                        dialog->Result = 1;
                    }
                    break;
                case 2:
                    if ((unsigned short)(wparam >> 16) == 0) {
                        dialog->Result = 2;
                    }
                    break;
                case 0x3EA:
                    if ((unsigned short)(wparam >> 16)) {
                        SendMessageA((HWND)lparam, 0xF1, 1, 0);
                    }
                    break;
                case 0x3EB:
                    if ((unsigned short)(wparam >> 16)) {
                        SendMessageA((HWND)lparam, 0xF1, 1, 0);
                    }
                    break;
                case 0x657:
                    if ((unsigned short)(wparam >> 16) == 1) {
                        int row = SendMessageA((HWND)lparam, CB_GETCURSEL, 0, 0);
                        if (SendMessageA((HWND)lparam, CB_GETITEMDATA, row, 0) == 4) {
                            SendMessageA((HWND)lparam, 0x4BD, row, (LPARAM)dialog->Buffer);
                            dialog->Show_Text_0066dae0(0x65F);
                        } else {
                            SetFocus(0);
                        }
                    }
                    break;
                case 0x659:
                    if ((unsigned short)(wparam >> 16) == 1) {
                        int row = SendMessageA((HWND)lparam, CB_GETCURSEL, 0, 0);
                        if (SendMessageA((HWND)lparam, CB_GETITEMDATA, row, 0) == 3) {
                            SendMessageA((HWND)lparam, 0x4BD, row, (LPARAM)dialog->Buffer);
                            dialog->Show_Text_0066dae0(0x65A);
                        } else {
                            SetFocus(0);
                        }
                    }
                    break;
                case 0x65A:
                    if ((unsigned short)(wparam >> 16) == 0x501 || (unsigned short)(wparam >> 16) == 0x200) {
                        dialog->Read_Custom_Call_Wait_0066dcf0();
                    }
                    break;
                case 0x65B:
                    if ((unsigned short)(wparam >> 16)) {
                        SendMessageA((HWND)lparam, 0xF1, 1, 0);
                        SendDlgItemMessageA(window, 0x65C, 0xF1, 0, 0);
                    }
                    break;
                case 0x65F:
                    if ((unsigned short)(wparam >> 16) == 0x501 || (unsigned short)(wparam >> 16) == 0x200) {
                        dialog->Read_Custom_Port_0066db50();
                    }
                    break;
                case 0x65E:
                    if ((unsigned short)(wparam >> 16) == 2 && SendMessageA((HWND)lparam, 0x18B, 0, 0) > 0) {
                        int selection = SendMessageA((HWND)lparam, 0x188, 0, 0);
                        if (selection != -1) {
                            SendMessageA((HWND)lparam, 0x4B7, selection, (LPARAM)dialog->Buffer);
                            HWND edit = GetDlgItem(window, 0x65D);
                            if (edit) {
                                SendMessageA(edit, 0x4B4, 0, (LPARAM)dialog->Buffer);
                                SetFocus(edit);
                            }
                        }
                    }
                    break;
                case 0x65D:
                    if ((unsigned short)(wparam >> 16) == 0x501) {
                        dialog->Add_Init_String_0066de80();
                    }
                    break;
                case 0x661:
                    if ((unsigned short)(wparam >> 16) == 0) {
                        dialog->Add_Init_String_0066de80();
                    }
                    break;
                case 0x660:
                    if ((unsigned short)(wparam >> 16) == 0) {
                        dialog->Delete_Init_String_0066dfe0();
                    }
                    break;
                case 0x65C:
                    if ((unsigned short)(wparam >> 16)) {
                        SendMessageA((HWND)lparam, 0xF1, 1, 0);
                        SendDlgItemMessageA(window, 0x65B, 0xF1, 0, 0);
                    }
                    break;
            }
            break;
    }
    return 0;
}
