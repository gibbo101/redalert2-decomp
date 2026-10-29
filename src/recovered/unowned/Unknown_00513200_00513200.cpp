// LRESULT __stdcall Unknown_00513200(HWND, UINT, WPARAM, LPARAM) -- 0x00513200
// A dialog procedure (no references found): ends the dialog with 0 for
// control 2, 1 for control 0x53A and 2 for control 0x53B.
#include "shared/win32_api.hpp"

int __stdcall Unknown_00513200(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == 0x111) {
        switch (wparam) {
        case 2:
            EndDialog(window, 0);
            return 0;
        case 0x53A:
            EndDialog(window, 1);
            return 0;
        case 0x53B:
            EndDialog(window, 2);
            return 0;
        }
    }
    return 0;
}
