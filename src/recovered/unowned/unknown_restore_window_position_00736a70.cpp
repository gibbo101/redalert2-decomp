// void __fastcall unknown_restore_window_position_736a70(char const *section, HWND window, INIClass &ini) (0x00736A70)
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ??_C@_01FIAI@X?$AA@=007fd0d0
// @ref ??_C@_01PCJP@Y?$AA@=007fd0cc
// @ref ?unknown_window_section_b25f28@@3PBDB=00b25f28
// @ref ?unknown_restore_child_window_7368f0@@YGHPAUHWND__@@J@Z=007368f0
#include "shared/win_util.hpp"
#include "shared/ini_class.hpp"

void __fastcall unknown_restore_window_position_736a70(char const *section, HWND window, INIClass &ini)
{
    if (window != 0) {
        RECT rect;
        GetWindowRect(window, &rect);
        int x = ini.Get_Int(section, "X", rect.left);
        int y = ini.Get_Int(section, "Y", rect.top);
        int screen_width = GetSystemMetrics(0);                       // SM_CXSCREEN
        if (rect.right - rect.left + x > screen_width) {
            x = screen_width - rect.right + rect.left;
        }
        int screen_height = GetSystemMetrics(1);                      // SM_CYSCREEN
        if (rect.bottom - rect.top + y > screen_height) {
            y = screen_height - rect.bottom + rect.top;
        }
        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
        SetWindowPos(window, 0, x, y, 0, 0, 5);                         // SWP_NOSIZE | SWP_NOZORDER
        unknown_window_section_b25f28 = section;
        EnumChildWindows(window, unknown_restore_child_window_7368f0, (long)&ini);
    }
}
