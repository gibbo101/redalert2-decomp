// void UnknownDialog_66da70::Update_Radio() -- 0x0066DA70
// Purpose: sets the pair of radio buttons 0x65C/0x65B of the dialog (window
// at +0x00) from the option at +0x94: 0x65C checked when the option is 0,
// 0x65B otherwise (BM_SETCHECK).
// Assumptions: the dialog owner and the option's meaning are unidentified
// (no direct callers); names are placeholders.
#include "shared/win32_api.hpp"

class UnknownDialog_66da70 {
public:
    void Update_Radio();

    HWND Window;                    // +0x00
    char unknown_04[0x94 - 0x04];
    int unknown_94;                 // +0x94
};

void UnknownDialog_66da70::Update_Radio()
{
    bool first = unknown_94 == 0;
    HWND button = GetDlgItem(Window, 0x65C);
    if (button != 0) {
        SendMessageA(button, 0xF1, first == true, 0);
    }
    button = GetDlgItem(Window, 0x65B);
    if (button != 0) {
        SendMessageA(button, 0xF1, first == false, 0);
    }
}
