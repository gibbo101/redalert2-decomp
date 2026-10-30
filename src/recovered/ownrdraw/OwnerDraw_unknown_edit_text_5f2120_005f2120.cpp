// @ref ??_C@_15BFAC@?$AA?$AN?$AA?6?$AA?$AA@=007eaea8
// @ref ?unknown_window_procs_a73688@OwnerDraw@@3VUnknownWindowProcIndex@1@A=00a73688
// @ref __imp__CallWindowProcA@20=0079a4c0
// @ref __imp__MultiByteToWideChar@24=0079a1b8
// @ref __mbsnbcnt=00784d8d
// @ref _wcslen=00783605
// @ref _wcscat=0078365f
// @ref _wcscpy=00783689
// @ref ??_U@YAPAXI@Z=00782017
// @ref ??_V@YAXPAX@Z=00781d3b
#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// The text of an edit control as wide text without line breaks ("\r\n" appended if it had any) and the
// caret's character index; returns the length (0x005F2120).
int __fastcall unknown_edit_text_5f2120(HWND window, wchar_t *text, int size, int *caret)
{
    WNDPROC proc = 0;
    WNDPROC *found = unknown_window_procs_a73688.Find(window);
    if (found) {
        proc = *found;
    }
    char buffer[1024];
    int start = 0;
    buffer[0] = 0;
    CallWindowProcA(proc, window, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);
    if (caret) {
        DWORD selection_start;
        DWORD selection_end;
        start = (unsigned long)CallWindowProcA(proc, window, EM_GETSEL, (WPARAM)&selection_start, (LPARAM)&selection_end) >> 16;
    }
    *text = 0;
    MultiByteToWideChar(0, 0, buffer, -1, text, size);
    if (caret) {
        *caret = _mbsnbcnt((unsigned char *)buffer, start);
    }
    if (size > 0) {
        text[size - 1] = 0;
    }
    int length = wcslen(text);
    wchar_t *copy = new wchar_t[length + 3];
    memset(copy, 0, (length + 3) * sizeof(wchar_t));
    int count = 0;
    int i = 0;
    for (; i < length; i++) {
        if (text[i] != '\r' && text[i] != '\n') {
            copy[count++] = text[i];
        }
    }
    if (i != count) {
        wcscat(copy, L"\r\n");
    }
    wcscpy(text, copy);
    delete[] copy;
    return wcslen(text);
}

}
