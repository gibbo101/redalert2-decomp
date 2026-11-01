// void ToolTipManager::Process_Message(MSG *message) (0x006EB4E0; Tiberian Sun's Message_Handler)
// Feeds the window messages to the tips: a button press hides the tip, mouse movement restarts the
// delay timer (or, with no delay or while 0x00A416BC is set, looks for a tip at once), and the timer
// either hides the shown tip or finds the tip under the cursor and shows it for Duration.
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"
#include "shared/display.hpp"
// @ref ?Update@ToolTipManager@@QAE_NXZ=006ebdb0
// @ref ?unknown_show_cursor_position_a416bc@@3_NA=00a416bc

void ToolTipManager::Process_Message(MSG *message)
{
    if (Enabled == true) {
        switch (message->message) {
        case 0x201:     // WM_LBUTTONDOWN
        case 0x202:     // WM_LBUTTONUP
        case 0x204:     // WM_RBUTTONDOWN
        case 0x205:     // WM_RBUTTONUP
        case 0x207:     // WM_MBUTTONDOWN
        case 0x208:     // WM_MBUTTONUP
            KillTimer(Window, 0x54544950);
            Hide_Current();
            break;

        case 0x200:     // WM_MOUSEMOVE
            if (Delay != 0 && !unknown_show_cursor_position_a416bc) {
                KillTimer(Window, 0x54544950);
                SetTimer(Window, 0x54544950, Delay, 0);
                Hide_Current();
            } else {
                GetCursorPos(&Cursor);
                ScreenToClient(Window, &Cursor);
                Current = Find(&Cursor);
                if (Update()) {
                    SetTimer(Window, 0x54544950, Duration, 0);
                }
            }
            break;

        case 0x113:     // WM_TIMER
            if (message->wParam == 0x54544950) {
                KillTimer(Window, 0x54544950);
                if (Current != 0) {
                    Hide_Current();
                } else {
                    GetCursorPos(&Cursor);
                    ScreenToClient(Window, &Cursor);
                    Current = Find(&Cursor);
                    if (Update()) {
                        SetTimer(Window, 0x54544950, Duration, 0);
                    }
                }
            }
            break;
        }
    }
}
