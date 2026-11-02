// BOOL __fastcall unknown_get_message_522e90(MSG *, HWND, UINT, UINT) -- 0x00522E90
// Purpose: the game's GetMessage: polls unknown_peek_message_522ed0 (remove)
// until it yields a message; FALSE for WM_QUIT (shared/movie.hpp).
#include "shared/win32_api.hpp"
#include "shared/movie.hpp"
// @ref ?unknown_peek_message_522ed0@@YIHPAUtagMSG@@PAUHWND__@@III@Z=00522ed0

BOOL __fastcall unknown_get_message_522e90(MSG *message, HWND window, UINT first, UINT last)
{
    BOOL result;
    do {
        result = unknown_peek_message_522ed0(message, window, first, last, 1);
    } while (!result);
    if (message->message == 0x12) {
        result = 0;
    }
    return result;
}
