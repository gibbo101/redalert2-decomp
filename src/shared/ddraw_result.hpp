// Process_DD_Result: the DirectDraw error report (out-of-line copy at 0x00495770), inlined at its callers.
#ifndef RA2_SHARED_DDRAW_RESULT_HPP
#define RA2_SHARED_DDRAW_RESULT_HPP
// Every includer sees the mode-setting methods (shared/directdraw.hpp hides them from fragile closures).
#define DIRECTDRAW_DECLARE_MODE_METHODS
#include "shared/directdraw.hpp"
#include "shared/win32_api.hpp"
extern void (__fastcall *direct_draw_error_handler_008523ec)(HRESULT result);
extern HWND MainWindow;
extern char const direct_draw_error_format_007d59a8[];
extern char const direct_draw_error_title_007d599c[];
extern char const direct_draw_ok_message_007d59c4[];
extern char const direct_draw_note_007d59f4[];
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
WIN32_IMPORT int WINAPI MessageBoxA(HWND window, char const *text, char const *caption, UINT type);
extern "C" HRESULT __stdcall DirectDrawCreate(void *guid, IDirectDraw **object, void *outer);
inline void Process_DD_Result(HRESULT result, int display_ok_msg)
{
    if (result == DD_OK) {
        if (display_ok_msg) {
            MessageBoxA(MainWindow, direct_draw_ok_message_007d59c4, direct_draw_note_007d59f4, 0);
        }
        return;
    }
    if (direct_draw_error_handler_008523ec) {
        direct_draw_error_handler_008523ec(result);
        return;
    }
    char str[80];
    sprintf(str, direct_draw_error_format_007d59a8, result);
    MessageBoxA(MainWindow, str, direct_draw_error_title_007d599c, 0x30);
}
#endif
