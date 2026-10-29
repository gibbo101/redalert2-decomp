// int __stdcall Unknown_005171D0(HWND, UINT, WPARAM, LPARAM) -- 0x005171D0
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/lobby.hpp"

// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_1M@EOJM@?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007dc0d0
// @ref ??_C@_0M@FDGB@GUI?3Version?$AA@=007dc0dc
// @ref ?version_object_00a40c88@@3UUnknownVersionObject@@A=00a40c88
// @ref ?unknown_internal_version_text_712ed0@@YIPBDPAUUnknownVersionObject@@@Z=00712ed0
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180

struct UnknownVersionObject;
extern UnknownVersionObject version_object_00a40c88;
char const *__fastcall unknown_internal_version_text_712ed0(UnknownVersionObject *object);    // 0x00712ED0

// The main menu dialog's procedure (pointer only, 0x00516F00's dialog 0xE2): the common handler
// first; WM_PAINT sends 0x4F0 to item 0x71A; 0x497 shows the version in item 0x71D; the
// WM_COMMAND buttons store their choice in the int the window's long 8 points at.
int __stdcall Unknown_005171D0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    wchar_t buffer[128];
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *choice = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x497:
        {
            HWND item = GetDlgItem(window, 0x71D);
            swprintf(buffer, L"%s %s", StringTable::Load_String("GUI:Version", 0, "D:\\Ra2\\Init.CPP", 5723),
                Unknown_006FA180(unknown_internal_version_text_712ed0(&version_object_00a40c88)));
            SendMessageA(item, 0x4B2, 0, (LPARAM)buffer);
        }
        return 0;
    case 0x111:
        switch ((int)(wparam & 0xFFFF)) {
        case 0x578:
            *choice = 3;
            return 0;
        case 0x55C:
            *choice = 5;
            return 0;
        case 0x3EE:
            *choice = 6;
            return 0;
        case 0x683:
            *choice = 1;
            return 0;
        case 0x686:
            *choice = 4;
            return 0;
        case 0x684:
            *choice = 2;
            return 0;
        }
        break;
    case 0xF:
        {
            HWND item = GetDlgItem(window, 0x71A);
            SendMessageA(item, 0x4F0, 0, 0);
        }
        break;
    }
    return 0;
}
