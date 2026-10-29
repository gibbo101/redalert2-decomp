// @ref __imp__GetParent@4=0079a500
// @ref __imp__GetWindowRect@8=0079a398
// @ref __imp__MoveWindow@24=0079a3e0
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/rect.hpp"
#include "shared/unknown_globals.hpp"

namespace OwnerDraw {

void __fastcall unknown_5e9390(HWND window, Point2D const &size)
{
    HWND parent = GetParent(window);
    RECT parent_rect;
    RECT rect;
    GetWindowRect(parent, &parent_rect);
    GetWindowRect(window, &rect);
    MoveWindow(window, (unknown_8523e0 - size.X) / 2 - parent_rect.left + rect.left,
               (unknown_8523e4 - size.Y) / 2 - parent_rect.top + rect.top, rect.right - rect.left,
               rect.bottom - rect.top, FALSE);
}

}
