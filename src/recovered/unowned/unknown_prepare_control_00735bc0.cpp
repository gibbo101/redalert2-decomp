// BOOL __stdcall unknown_prepare_control_735bc0(HWND window, LPARAM parameter) (0x00735BC0)
// Scales window (a dialog, or with parameter set a control placed relative to its parent) from
// the layout size to the client size of template 0xC6 and moves it; combo boxes use their
// dropped-down rectangle. EnumChildWindows callback of 0x00735700.
// @ref ??_C@_08EIKH@ComboBox?$AA@=007e8dd4
// @ref __imp__GetClassNameA@12=0079a4e0
// @ref ?Dialog_Template_Size@@YIHHP6GHPAUHWND__@@IIJ@ZHPAJ@Z=00735b50
// @ref ?unknown_null_dialog_proc_735b40@@YGHPAUHWND__@@IIJ@Z=00735b40
// @ref ?unknown_template_size_b25de4@@3PAJA=00b25de4
// @ref ?unknown_layout_width_7fd048@@3HA=007fd048
// @ref ?unknown_layout_height_7fd04c@@3HA=007fd04c
// @ref ?ProgramInstance@@3PAXA=00b26180
#include "shared/win_util.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_string.hpp"

BOOL __stdcall unknown_prepare_control_735bc0(HWND window, LPARAM parameter)
{
    RECT rect;
    GetWindowRect(window, &rect);
    char name[128];
    GetClassNameA(window, name, sizeof(name));
    if (strcmp(name, "ComboBox") == 0) {
        SendMessageA(window, 0x152, 0, (LPARAM)&rect);     // CB_GETDROPPEDCONTROLRECT
    }
    if (parameter != 0) {
        HWND owner = (HWND)GetWindowLongA(window, -8);
        RECT parent;
        GetWindowRect(owner, &parent);
        rect.left -= parent.left;
        rect.right -= parent.left;
        rect.top -= parent.top;
        rect.bottom -= parent.top;
    }
    LONG *size = unknown_template_size_b25de4;
    if (size[0] == 0) {
        Dialog_Template_Size(0xC6, (DLGPROC)unknown_null_dialog_proc_735b40, 0, size);
    }
    int width = (rect.right - rect.left + 1) * unknown_layout_width_7fd048 / size[0];
    int height = (rect.bottom - rect.top + 1) * unknown_layout_height_7fd04c / size[1];
    rect.left = unknown_layout_width_7fd048 * rect.left / size[0];
    rect.top = unknown_layout_height_7fd04c * rect.top / size[1];
    rect.right = width + rect.left - 1;
    rect.bottom = height + rect.top - 1;
    MoveWindow(window, rect.left, rect.top, width, height, 1);
    return 1;
}
