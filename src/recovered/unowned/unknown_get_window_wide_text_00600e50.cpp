// LRESULT __fastcall unknown_get_window_wide_text(HWND window, WideString &text) -- 0x00600E50
// Purpose: reads the window text into a wide string (length from
// WM_GETTEXTLENGTH, text through message 0x4B3); with no text it releases
// text and returns 0.
// Assumptions: message 0x4B3 is a control-specific (WM_USER-based) text
// request; the name is a hypothesis.
#include "shared/win32_api.hpp"
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??4WideString@@QAEAAV0@PBG@Z=0076fb70
// @ref ?Release@WideString@@QAEXXZ=00770330

// The wide string class (shared/wide_string.hpp's WideString), with the two
// members used here.
class WideString {
public:
    WideString &operator=(unsigned short const *string);   // 0x0076FB70
    void Release();                                     // 0x00770330 (frees the text)
    unsigned short *Buffer;
};

LRESULT __fastcall unknown_get_window_wide_text(HWND window, WideString &text)
{
    LRESULT length = SendMessageA(window, 0xE, 0, 0);
    if (length <= 0) {
        text.Release();
        return 0;
    }
    unsigned short *buffer = new unsigned short[length + 2];
    LRESULT result = SendMessageA(window, 0x4B3, length + 1, (LPARAM)buffer);
    text = buffer;
    delete [] buffer;
    return result;
}
