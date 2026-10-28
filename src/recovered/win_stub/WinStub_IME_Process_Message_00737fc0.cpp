// BOOL __fastcall IME_Process_Message(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x00737FC0)
// WM_IME_STARTCOMPOSITION/ENDCOMPOSITION/COMPOSITION update the composition state; these and the other
// IME messages go to DefWindowProcA (result in IMEDefaultResult) and count as handled.
#include "shared/win_stub.hpp"

// @ref ?IME_Update_Composition@@YAXXZ=00737e30
// @ref ?IMEResultString@@3PAGA=00b25f7c
// @ref ?IMEComposing@@3HA=00b263f4
// @ref ?IMEDefaultResult@@3JA=00b263f8

BOOL __fastcall IME_Process_Message(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case 0x10D:
        IME_Update_Composition();
        IMEResultString[0] = 0;
        IMEComposing = 1;
        IMEDefaultResult = DefWindowProcA(window, message, wparam, lparam);
        return TRUE;
    case 0x10E:
        IME_Update_Composition();
        IMEComposing = 0;
        IMEDefaultResult = DefWindowProcA(window, message, wparam, lparam);
        return TRUE;
    case 0x10F:
        IME_Update_Composition();
        IMEDefaultResult = DefWindowProcA(window, message, wparam, lparam);
        return TRUE;
    case 0x281:
        IMEDefaultResult = DefWindowProcA(window, message, wparam, lparam);
        return TRUE;
    case 0x282:
    case 0x285:
    case 0x290:
    case 0x291:
        IMEDefaultResult = DefWindowProcA(window, message, wparam, lparam);
        return TRUE;
    }
    return FALSE;
}
