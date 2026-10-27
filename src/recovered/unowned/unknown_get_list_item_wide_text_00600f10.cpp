// LRESULT __fastcall unknown_get_list_item_wide_text(HWND window, WPARAM index, WideString &text) -- 0x00600F10
// Purpose: reads list-box item `index` into a wide string (length from
// LB_GETTEXTLEN, text through message 0x4B6); text is released first when
// the length is not positive.
// Assumptions: message 0x4B6 is a control-specific (WM_USER-based) text
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

LRESULT __fastcall unknown_get_list_item_wide_text(HWND window, WPARAM index, WideString &text)
{
    LRESULT length = SendMessageA(window, 0x18A, index, 0);
    if (length <= 0) {
        text.Release();
    }
    unsigned short *buffer = new unsigned short[length + 2];
    LRESULT result = SendMessageA(window, 0x4B6, index, (LPARAM)buffer);
    text = buffer;
    delete [] buffer;
    return result;
}
