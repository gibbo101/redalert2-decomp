// @ref ??_C@_0BE@FLME@D?3?2Ra2?2ownrdraw?4cpp?$AA@=007e8df8
// @ref ?unknown_5e22b0@OwnerDraw@@YIPBDIPAUHWND__@@@Z=005e22b0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/string_table.hpp"
#include "shared/ipx_global_conn.hpp"

namespace OwnerDraw {

WideString __fastcall unknown_5e2260(unsigned int key, HWND window)
{
    char const *label = unknown_5e22b0(key, window);
    if (label) {
        return WideString(StringTable::Load_String(label, 0, "D:\\Ra2\\ownrdraw.cpp", 1902));
    }
    return WideString(unknown_empty_wide_839d4c);
}

}
