// 0x0060E540
BOOL __stdcall Edit_Phone_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    wchar_t buffer[64];
    int rc;

    rc = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (rc == 0) {
        PhoneEntryEdit *_this = (PhoneEntryEdit *)GetWindowLongA(window, DWL_USER);
        switch (message) {
            case 0x497:
                SendDlgItemMessageA(window, 0x5E5, 0xC5, 20, 0);
                SendDlgItemMessageA(window, 0x5DF, 0xC5, 20, 0);
                break;
            case 0x111:
                switch ((unsigned short)wparam) {
                    case 0x663:
                        if ((unsigned short)(wparam >> 16) != 0) {
                            SendMessageA((HWND)lparam, 0xF1, TRUE, 0);
                            SendDlgItemMessageA(window, 0x664, 0xF1, 0, 0);
                        }
                        break;
                    case 0x664:
                        if ((unsigned short)(wparam >> 16) != 0) {
                            SendMessageA((HWND)lparam, 0xF1, TRUE, 0);
                            SendDlgItemMessageA(window, 0x663, 0xF1, 0, 0);
                            UpdateWindow(window);
                            ShowWindow(window, SW_HIDE);
                            UpdateWindow(MainWindow);
                            SerialEdDialog().Dialog_0066ca70(&_this->TempSettings);
                            ShowWindow(window, SW_SHOW);
                        }
                        break;
                    case 0x5E5:
                        if ((unsigned short)(wparam >> 16) == 0x501 || (unsigned short)(wparam >> 16) == 0x200) {
                            SendMessageA((HWND)lparam, 0x4B3, 64, (LPARAM)buffer);
                            wcstrim(buffer);
                            SendMessageA((HWND)lparam, 0x4B2, 0, (LPARAM)buffer);
                        }
                        break;
                    case 1:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            _this->Save();
                            _this->RC = 1;
                        }
                        break;
                    case 2:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            _this->RC = 2;
                        }
                        break;
                    case 0x5DF:
                        if ((unsigned short)(wparam >> 16) == 0x501 || (unsigned short)(wparam >> 16) == 0x200) {
                            SendMessageA((HWND)lparam, 0x4B5, 64, (LPARAM)buffer);
                            strtrim((char *)buffer);
                            SendMessageA((HWND)lparam, 0x4B4, 0, (LPARAM)buffer);
                        }
                        break;
                }
                break;
        }
        rc = 0;
    }
    return rc;
}
// @ref ?Dialog_0066ca70@SerialEdDialog@@QAE_NPAUSerialSettingsType@@@Z=0066ca70
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Save@PhoneEntryEdit@@QAEXXZ=0060e7a0
// @ref ?strtrim@@YIPADPAD@Z=006eef10
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?wcstrim@@YIPAGPAG@Z=006eef80
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__UpdateWindow@4=0079a46c
