// void __fastcall unknown_enum_children_5e8b90(HWND window) -- 0x005E8B90
// Runs the child-window callback 0x005E8720 over every child of the window (the 0x005E8120 /
// 0x005E86C0 pattern; unreferenced).
// @ref __imp__EnumChildWindows@12=0079a4dc
// @ref ?unknown_child_proc_5e8720@@YGHPAUHWND__@@J@Z=005e8720
#include "shared/win32_api.hpp"

BOOL __stdcall unknown_child_proc_5e8720(HWND window, LPARAM lparam);      // 0x005E8720

void __fastcall unknown_enum_children_5e8b90(HWND window)
{
    EnumChildWindows(window, unknown_child_proc_5e8720, 0);
}
