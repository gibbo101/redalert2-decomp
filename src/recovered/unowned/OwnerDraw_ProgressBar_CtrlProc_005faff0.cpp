// Progress-bar control callback, independently bounded638 code bytes +2 padding.
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7XSurface@@6B@=0079af8c
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
namespace OwnerDraw {
LRESULT __stdcall unknown_progress_proc_5faff0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    RECT rect;
    Window_Rect_In_Main_Client(window, &rect);
    UnknownControlRecord *data = unknown_registry_a73640.Find((unsigned int)window);
    if (data) {
        switch (message) {
        case 0x497:
            data->unknown_ec = 100;
            break;
        case 0x401:
            data->unknown_e8 = (unsigned int)lparam & 0xffff;
            data->unknown_ec = (unsigned int)lparam >> 16;
            break;
        case 0x402: {
            int position = (int)wparam;
            if (position < data->unknown_e8) position = data->unknown_e8;
            if (position > data->unknown_ec) position = data->unknown_ec;
            data->unknown_f0 = position;
            InvalidateRect(window, 0, 0);
            break;
        }
        case 0xf: {
            Rect source(0, 0, rect.right-rect.left+1, rect.bottom-rect.top+1);
            Rect destination(rect.left, rect.top, rect.right-rect.left+1, rect.bottom-rect.top+1);
            if (!data->surface_10) {
                Surface *background = new BSurface(rect.right-rect.left+1, rect.bottom-rect.top+1, 2);
                data->surface_10 = background;
                ++unknown_surface_count_a763d8;
                background->Copy_From(source, *unknown_surface_839958, destination, false, true);
            }
            unknown_surface_839958->Copy_From(destination, *data->surface_10, source, false, true);
            int position = (data->unknown_f0 * 65536) / (data->unknown_ec - data->unknown_e8);
            int color = unknown_5fda40(0xff);
            unknown_5fe7c0(destination, unknown_surface_839958, color, position);
            ValidateRect(window, 0);
            break;
        }
        }
    }
    return 0;
}
}
