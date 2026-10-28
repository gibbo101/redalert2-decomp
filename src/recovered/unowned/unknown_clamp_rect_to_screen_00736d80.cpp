// bool __fastcall Unknown_Clamp_Rect_To_Screen_00736D80(void *, unsigned, Rect *)
// (0x00736D80): keeps a window rectangle on the screen (GetSystemMetrics
// SM_CXSCREEN/SM_CYSCREEN); true when it changed. The window procedures pass
// their window and wParam in ECX/EDX for WM_SIZING/WM_MOVING (0x214/0x216)
// and the rectangle on the stack; the body ignores the two register
// parameters (the convention also fixes the epilogue's `mov al, 1`).
// @ref __imp__GetSystemMetrics@4=0079a3dc
#include "shared/win32_api.hpp"
#include "shared/rect.hpp"

bool __fastcall Unknown_Clamp_Rect_To_Screen_00736D80(void *window, unsigned int wparam, Rect *rect)
{
    bool changed = false;
    int x = rect->X;
    if (x < 0) {
        rect->X = 0;
        rect->Width -= x;
        changed = true;
    }
    int y = rect->Y;
    if (y < 0) {
        rect->Y = 0;
        rect->Height -= y;
        changed = true;
    }
    if (rect->Width > GetSystemMetrics(0x10)) {
        rect->X += GetSystemMetrics(0x10) - rect->Width;
        rect->Width = GetSystemMetrics(0x10);
        changed = true;
    }
    if (rect->Height > GetSystemMetrics(0x11)) {
        rect->Y += GetSystemMetrics(0x11) - rect->Height;
        rect->Height = GetSystemMetrics(0x11);
        return true;
    }
    return changed;
}
