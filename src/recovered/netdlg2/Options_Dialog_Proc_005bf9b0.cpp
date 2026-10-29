// long __stdcall Options_Dialog_Proc_005bf9b0(HWND window, unsigned message, unsigned wparam, long lparam) (0x005BF9B0)
#include "shared/lobby.hpp"
#include "shared/options_dialog.hpp"
// @ref ?unknown_lock_a71e98@@3_NA=00a71e98

long __stdcall Options_Dialog_Proc_005bf9b0(HWND window, unsigned message, unsigned wparam, long lparam)
{
    if (!unknown_lock_a71e98) {
        switch (message) {
        case 0x497:
            Unknown_Fill_Options_Dialog_005c3550(window, 1);
            return 0;
        case 0x114:
            if (GetDlgItem(window, 0x529) == (HWND)lparam) {
                unknown_session_a3d298.GameSpeed_30 = 6 - SendDlgItemMessageA(window, 0x529, 0x400, 0, 0);
            }
            if (GetDlgItem(window, 0x402) == (HWND)lparam) {
                unknown_session_a3d298.unknown_24 = SendDlgItemMessageA(window, 0x402, 0x400, 0, 0);
            }
            if (GetDlgItem(window, 0x54F) == (HWND)lparam) {
                unknown_session_a3d298.UnitCount = SendDlgItemMessageA(window, 0x54F, 0x400, 0, 0);
            }
            return 0;
        case 0x111:
            switch ((unsigned short)wparam) {
            case 0x54E:
                unknown_session_a3d298.unknown_2a = false;
                if (SendDlgItemMessageA(window, 0x54E, 0xF0, 0, 0) == 1) {
                    unknown_session_a3d298.unknown_2a = true;
                    if (!unknown_session_a3d298.unknown_bases_20) {
                        unknown_session_a3d298.unknown_bases_20 = true;
                        SendDlgItemMessageA(window, 0x54B, 0xF1, 1, 0);
                    }
                }
                return 0;
            case 0x54D:
                unknown_session_a3d298.unknown_crates_29 = false;
                if (SendDlgItemMessageA(window, 0x54D, 0xF0, 0, 0) == 1) {
                    unknown_session_a3d298.unknown_crates_29 = true;
                }
                return 0;
            case 0x3E8:
                unknown_session_a3d298.unknown_a8 = false;
                if (SendDlgItemMessageA(window, 0x3E8, 0xF0, 0, 0) == 1) {
                    unknown_session_a3d298.unknown_a8 = true;
                }
                return 0;
            case 0x624:
                unknown_session_a3d298.unknown_28 = false;
                if (SendDlgItemMessageA(window, 0x624, 0xF0, 0, 0) == 1) {
                    unknown_session_a3d298.unknown_28 = true;
                }
                return 0;
            case 0x69D:
                unknown_session_a3d298.unknown_2c = false;
                if (SendDlgItemMessageA(window, 0x69D, 0xF0, 0, 0) == 1) {
                    unknown_session_a3d298.unknown_2c = true;
                }
                return 0;
            case 0x69A:
                unknown_session_a3d298.unknown_2b = false;
                if (SendDlgItemMessageA(window, 0x69A, 0xF0, 0, 0) == 1) {
                    unknown_session_a3d298.unknown_2b = true;
                }
                return 0;
            }
        }
    }
    return 0;
}
