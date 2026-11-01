// BOOL __stdcall unknown_restore_child_window_7368f0(HWND window, long parameter) (0x007368F0)
// EnumChildWindows callback of 0x00736A70; parameter is the INIClass.
// @ref ?Get_Bool@INIClass@@QBE_NPBD0_N@Z=0050f410
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref __imp__GetClassNameA@12=0079a4e0
// @ref __imp__wsprintfA=0079a4a4
// @ref ?unknown_window_section_b25f28@@3PBDB=00b25f28
// @ref ??_C@_04BIHF@TV?$CFd?$AA@=007fd0b4
// @ref ??_C@_04GHME@LV?$CFd?$AA@=007fd09c
// @ref ??_C@_0O@NCOE@SysTreeView32?$AA@=007fd0bc
// @ref ??_C@_0O@NFAI@SysListView32?$AA@=007fd0a4
#include "shared/win_util.hpp"
#include "shared/ini_class.hpp"
#include "shared/crt_string.hpp"

BOOL __stdcall unknown_restore_child_window_7368f0(HWND window, long parameter)
{
    INIClass &ini = *(INIClass *)parameter;
    if (Is_Window_Class(window, "SysTreeView32")) {
        char name[64];
        char const *section = unknown_window_section_b25f28;
        int index = 0;
        for (LPARAM item = SendMessageA(window, 0x110A, 0, 0); item != 0;
             item = SendMessageA(window, 0x110A, 1, item)) {                    // TVGN_ROOT, TVGN_NEXT
            index++;
            wsprintfA(name, "TV%d", index);
            if (ini.Get_Bool(section, name, false)) {
                SendMessageA(window, 0x1102, 2, item);     // TVM_EXPAND, TVE_EXPAND
            } else {
                SendMessageA(window, 0x1102, 1, item);     // TVE_COLLAPSE
            }
        }
    }
    if (Is_Window_Class(window, "SysListView32")) {
        char name[64];
        char const *section = unknown_window_section_b25f28;
        if (window != 0) {
            for (int column = 0; column < 10; column++) {
                wsprintfA(name, "LV%d", column);
                unsigned width = ini.Get_Int(section, name, SendMessageA(window, 0x101D, column, 0));   // LVM_GETCOLUMNWIDTH
                if (width < 1000) {
                    SendMessageA(window, 0x101E, column, (unsigned short)width);              // LVM_SETCOLUMNWIDTH
                }
            }
        }
    }
    return 1;
}
