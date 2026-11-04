// int WWKeyboardClass::Message_Handler(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x00532A60)
// Queues the keyboard and mouse-button messages (mouse keys with the converted screen position)
// and passes them to DefWindowProc; other messages give 0 (TibSun keyboard.cpp shape).
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"

// The Windows SDK values this handler uses (win32_api.hpp declares no message constants).
#define LOWORD(l) ((unsigned short)(l))
#define HIWORD(l) ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_MBUTTON 0x04
#define VK_SCROLL 0x91

int WWKeyboardClass::Message_Handler(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    bool processed = false;

    POINT point;
    point.x = LOWORD(lparam);
    point.y = HIWORD(lparam);
    ClientToScreen(window, &point);
    LONG x = point.x;
    LONG y = point.y;
    if (WWMouse != 0) WWMouse->Convert_Coordinate((int &)x, (int &)y);

    switch (message) {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            if (wparam != VK_SCROLL && !(lparam & (1 << 30))) {
                Put_Key_Message((KeyNumType)wparam);
            }
            processed = true;
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP:
            Put_Key_Message((KeyNumType)wparam, true);
            processed = true;
            break;

        case WM_LBUTTONDOWN:
            Put_Mouse_Message(VK_LBUTTON, x, y);
            processed = true;
            break;

        case WM_LBUTTONUP:
            Put_Mouse_Message(VK_LBUTTON, x, y, true);
            processed = true;
            break;

        case WM_LBUTTONDBLCLK:
            Put_Mouse_Message(VK_LBUTTON, x, y);
            Put_Mouse_Message(VK_LBUTTON, x, y, true);
            processed = true;
            break;

        case WM_CHAR:
            if (unknown_flag_a3dc89) {
                Put_Char((KeyNumType)wparam);
            }
            processed = true;
            break;

        case WM_MBUTTONDOWN:
            Put_Mouse_Message(VK_MBUTTON, x, y);
            processed = true;
            break;

        case WM_MBUTTONUP:
            Put_Mouse_Message(VK_MBUTTON, x, y, true);
            processed = true;
            break;

        case WM_MBUTTONDBLCLK:
            Put_Mouse_Message(VK_MBUTTON, x, y);
            Put_Mouse_Message(VK_MBUTTON, x, y, true);
            processed = true;
            break;

        case WM_RBUTTONDOWN:
            Put_Mouse_Message(VK_RBUTTON, x, y);
            processed = true;
            break;

        case WM_RBUTTONUP:
            Put_Mouse_Message(VK_RBUTTON, x, y, true);
            processed = true;
            break;

        case WM_RBUTTONDBLCLK:
            Put_Mouse_Message(VK_RBUTTON, x, y);
            Put_Mouse_Message(VK_RBUTTON, x, y, true);
            processed = true;
            break;

        default:
            break;
    }

    if (processed) {
        DefWindowProcA(window, message, wparam, lparam);
        return true;
    }
    return false;
}
