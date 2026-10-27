// LRESULT __fastcall unknown_get_window_text(HWND window, Wstring &text) -- 0x00600DF0
// Purpose: reads the window text into text (length from WM_GETTEXTLENGTH,
// text through message 0x4B5); with no text it releases text and returns 0.
// Assumptions: message 0x4B5 is a control-specific (WM_USER-based) text
// request; the name is a hypothesis.
#include "shared/win32_api.hpp"
#include "shared/wstring.hpp"
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b


LRESULT __fastcall unknown_get_window_text(HWND window, Wstring &text)
{
    LRESULT length = SendMessageA(window, 0xE, 0, 0);
    if (length <= 0) {
        text.Release();
        return 0;
    }
    char *buffer = new char[length + 2];
    LRESULT result = SendMessageA(window, 0x4B5, length + 1, (LPARAM)buffer);
    text = buffer;
    delete [] buffer;
    return result;
}
