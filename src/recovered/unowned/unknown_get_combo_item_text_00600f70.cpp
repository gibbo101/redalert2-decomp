// LRESULT __fastcall unknown_get_combo_item_text(HWND window, WPARAM index, Wstring &text) -- 0x00600F70
// Purpose: reads combo-box item `index` into text (length from
// CB_GETLBTEXTLEN, text through message 0x4BD); text is released first
// when the length is not positive.
// Assumptions: message 0x4BD is a control-specific (WM_USER-based) text
// request; the name is a hypothesis.
#include "shared/win32_api.hpp"
#include "shared/wstring.hpp"
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b


LRESULT __fastcall unknown_get_combo_item_text(HWND window, WPARAM index, Wstring &text)
{
    LRESULT length = SendMessageA(window, 0x149, index, 0);
    if (length <= 0) {
        text.Release();
    }
    char *buffer = new char[length + 2];
    LRESULT result = SendMessageA(window, 0x4BD, index, (LPARAM)buffer);
    text = buffer;
    delete [] buffer;
    return result;
}
