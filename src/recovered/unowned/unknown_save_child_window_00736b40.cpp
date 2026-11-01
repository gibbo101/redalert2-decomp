// BOOL __stdcall unknown_save_child_window(HWND window, long parameter) (0x00736B40)
// EnumChildWindows callback of 0x00736CD0; parameter is the INIClass.
// @ref ?Put_Bool@INIClass@@QAE_NPBD0_N@Z=0050f380
// @ref ?Put_Int@INIClass@@QAE_NPBD0HH@Z=0050d6e0
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

BOOL __stdcall unknown_save_child_window(HWND window, long parameter)
{
    INIClass &ini = *(INIClass *)parameter;
    if (Is_Window_Class(window, "SysTreeView32")) {
        char key[32];
        char const *section = unknown_window_section_b25f28;
        int index = 0;
        for (LPARAM item = SendMessageA(window, 0x110A, 0, 0); item != 0;
             item = SendMessageA(window, 0x110A, 1, item)) {
            index++;
            wsprintfA(key, "TV%d", index);
            TVITEMA info;
            info.mask = 0x18;               // TVIF_STATE | TVIF_HANDLE
            info.stateMask = 0x20;          // TVIS_EXPANDED
            info.hItem = (void *)item;
            if (SendMessageA(window, 0x110C, 0, (LPARAM)&info)) {             // TVM_GETITEM
                bool expanded = false;
                if (info.state & 0x20) {
                    expanded = true;
                }
                ini.Put_Bool(section, key, expanded);
            }
        }
    }
    if (Is_Window_Class(window, "SysListView32")) {
        char key[32];
        char const *section = unknown_window_section_b25f28;
        if (window != 0) {
            for (int column = 0; column < 10; column++) {
                wsprintfA(key, "LV%d", column);
                unsigned width = SendMessageA(window, 0x101D, column, 0);
                if (width < 1000) {
                    ini.Put_Int(section, key, width);
                }
            }
        }
    }
    return 1;
}
