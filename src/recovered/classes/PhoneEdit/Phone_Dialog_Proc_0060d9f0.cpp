// 0x0060D9F0
BOOL __stdcall Phone_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    HWND handle;
    int rc = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (rc == 0) {
        PhoneEdit *_this = (PhoneEdit *)GetWindowLongA(window, DWL_USER);
        switch (message) {
            case 0x497:
                SendDlgItemMessageA(window, 0x5E5, 0xC5, 20, 0);
                SendDlgItemMessageA(window, 0x5E0, 0x4A6, 144, 2);
                SendDlgItemMessageA(window, 0x5E0, 0x4A6, 121, 150);
                SendDlgItemMessageA(window, 0x5E0, 0x4A6, 0, 275);
                break;
            case 0x111:
                switch ((unsigned short)wparam) {
                    case 0x5E4:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            _this->Edit();
                        }
                        break;
                    case 0x661:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            _this->Add();
                        }
                        break;
                    case 0x5E0:
                        if ((unsigned short)(wparam >> 16) == 1) {
                            handle = GetDlgItem(_this->_Dialog, 0x5E0);
                            if (handle != 0) {
                                if (SendMessageA(handle, 0x18B, 0, 0) > 0) {
                                    unknown_session_a3d298.CurPhoneIdx = SendMessageA(handle, 0x188, 0, 0);
                                    if (unknown_session_a3d298.CurPhoneIdx > -1) {
                                        handle = GetDlgItem(_this->_Dialog, 0x5E5);
                                        SendMessageA(handle, 0x4B4, 0,
                                            (LPARAM)unknown_session_a3d298.PhoneBook[unknown_session_a3d298.CurPhoneIdx]->Number);
                                        SetFocus(handle);
                                    }
                                }
                            }
                        }
                        break;
                    case 1:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            if (_this->Dial() == true) {
                                _this->RC = 1;
                            }
                        }
                        break;
                    case 2:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            _this->RC = 2;
                        }
                        break;
                    case 0x53B:
                        if ((unsigned short)(wparam >> 16) == 0) {
                            _this->Delete();
                        }
                        break;
                }
                break;
        }
        rc = 0;
    }
    return rc;
}
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?Add@PhoneEdit@@QAEXXZ=0060e160
// @ref ?Build_Phone_Listbox@PhoneEdit@@QAEXXZ=0060de40
// @ref ?Dial@PhoneEdit@@QAE_NXZ=0060dc80
// @ref ?Edit@PhoneEdit@@QAEXXZ=0060e2e0
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__SetFocus@4=0079a38c
