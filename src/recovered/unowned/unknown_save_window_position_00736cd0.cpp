// void __fastcall unknown_save_window_position(char const *section, HWND window, INIClass &ini) -- 0x00736CD0
// Purpose: writes window's screen position as X and Y under section of
// ini, remembers section for the child callback (0x00B25F28) and saves
// every child window through 0x00736B40.
// Assumptions: the callback's behaviour is only inferred from its use.
// @ref __imp__GetWindowRect@8=0079a398
// @ref __imp__EnumChildWindows@12=0079a4dc
// @ref ?Put_Int@INIClass@@QAE_NPBD0HH@Z=0050d6e0
// @ref ??_C@_01FIAI@X?$AA@=007fd0d0
// @ref ??_C@_01PCJP@Y?$AA@=007fd0cc
// @ref ?unknown_window_section_b25f28@@3PBDB=00b25f28
// @ref ?unknown_save_child_window@@YGHPAUHWND__@@J@Z=00736b40
#include "shared/win32_api.hpp"
#include "shared/ini_class.hpp"

typedef BOOL (WINAPI *WNDENUMPROC)(HWND window, long parameter);
WIN32_IMPORT BOOL WINAPI GetWindowRect(HWND window, RECT *rect);
WIN32_IMPORT BOOL WINAPI EnumChildWindows(HWND parent, WNDENUMPROC callback, long parameter);

extern char const *unknown_window_section_b25f28;
BOOL __stdcall unknown_save_child_window(HWND window, long parameter);

void __fastcall unknown_save_window_position(char const *section, HWND window, INIClass &ini)
{
    if (window != 0) {
        RECT rect;
        GetWindowRect(window, &rect);
        ini.Put_Int(section, "X", rect.left);
        ini.Put_Int(section, "Y", rect.top);
        unknown_window_section_b25f28 = section;
        EnumChildWindows(window, unknown_save_child_window, (long)&ini);
    }
}
