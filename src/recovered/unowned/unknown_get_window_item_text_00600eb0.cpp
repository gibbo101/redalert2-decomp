// LRESULT __fastcall unknown_get_window_item_text(HWND window, WPARAM index, Wstring &text) -- 0x00600EB0
// Purpose: reads item `index` of a window control into text: the length
// from message 0x18A (LB_GETTEXTLEN), the text from message 0x4B7 into a
// temporary buffer; text is released first when the length is not
// positive. Returns the second message's result.
// Assumptions: the meaning of message 0x4B7 (a control-specific
// WM_USER-based message) is unknown; the name is a hypothesis.
#include "shared/win32_api.hpp"
#include "shared/wstring.hpp"
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b

LRESULT __fastcall unknown_get_window_item_text(HWND window, WPARAM index, Wstring &text)
{
    LRESULT length = SendMessageA(window, 0x18A, index, 0);
    if (length <= 0) {
        text.Release();
    }
    char *buffer = new char[length + 2];
    LRESULT result = SendMessageA(window, 0x4B7, index, (LPARAM)buffer);
    text = buffer;
    delete [] buffer;
    return result;
}
