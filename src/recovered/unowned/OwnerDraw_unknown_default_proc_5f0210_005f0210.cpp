// Default owner-draw control procedure, original 005f0210.
#include "shared/win32_api.hpp"
#include "shared/win32_gdi.hpp"
#include "shared/win32_window.hpp"
#include "shared/owner_draw_dialog_control.hpp"
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_color_a733e4@OwnerDraw@@3HA=00a733e4
namespace OwnerDraw {
LRESULT __stdcall unknown_default_proc_5f0210(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    WNDPROC proc = 0;
    WNDPROC *found = unknown_window_procs_a73688.Find(window);
    if (found) proc = *found;
    RECT area;
    Window_Rect_In_Main_Client(window, &area);
    RECT client;
    GetClientRect(window, &client);
    UnknownControlRecord *record = 0;
    unknown_registry_a73640.Get((unsigned int const &)window, record);
    if (message == 0x133) {
        SetTextColor((HDC)wparam, unknown_color_a733e4);
        SetBkMode((HDC)wparam, 1);
        return (LRESULT)GetStockObject(5);
    }
    return CallWindowProcA(proc, window, message, wparam, lparam);
}
}
