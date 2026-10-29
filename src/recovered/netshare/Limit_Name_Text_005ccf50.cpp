// WideString __fastcall Limit_Name_Text_005ccf50(HWND control) (0x005CCF50)
#include "shared/lobby.hpp"
// @ref ?Trim_Trailing@WideString@@QAEXABV1@@Z=00770230
// @ref ??_C@_15MLJJ@?$AA?6?$AA?$AN?$AA?$AA@=007e7404

WideString __fastcall Limit_Name_Text_005ccf50(HWND control)
{
    WideString text;
    unknown_get_window_wide_text(control, text);
    unsigned int limit = 0x78;
    if (!text.Is_Narrow()) {
        unsigned int i;
        for (i = 0; i < text.Length(); i++) {
            if (text.Get_Char(i) > 0x100) {
                break;
            }
        }
        limit = i - 1;
        if (limit <= 0x28) {
            limit = 0x28;
        }
    }
    if (text.Length() > limit) {
        text.Truncate(limit);
        SendMessageA(control, 0x4b2, 0, (LPARAM)text.unknown_text_770430());
    }
    {
        WideString line_breaks(L"\n\r");
        text.Trim_Trailing(line_breaks);
    }
    return text;
}
