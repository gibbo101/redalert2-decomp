// @ref ?unknown_session_a3d298@@3VUnknownSessionState@@A=00a3d298
// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
// @ref ?unknown_7add6c@OwnerDraw@@3HA=007add6c
// @ref ?unknown_7add78@OwnerDraw@@3HA=007add78
// @ref ?unknown_int_7add80@@3HA=007add80
// @ref ?unknown_rect_ac11c8@@3PAVRect@@A=00ac11c8
// @ref ?unknown_rect_ac11cc@@3PAVRect@@A=00ac11cc
// @ref ?unknown_rect_ac11ec@@3PAVRect@@A=00ac11ec
// @ref ?unknown_rect_ac11f0@@3PAVRect@@A=00ac11f0
// @ref ?unknown_rect_ac11f4@@3PAVRect@@A=00ac11f4
// @ref ?unknown_shape_ac10b8@@3PAUShapeFileStruct@@A=00ac10b8
// @ref ?unknown_shape_ac0ff8@@3PAUShapeFileStruct@@A=00ac0ff8
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref __imp__GetParent@4=0079a500
// @ref __imp__GetWindowRect@8=0079a398
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__MoveWindow@24=0079a3e0
#include "shared/owner_draw_sidebar.hpp"
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
namespace OwnerDraw {

void __fastcall unknown_5e8c50(HWND window, Point2D const &size)
{
    HWND parent = GetParent(window);
    unsigned char flag = unknown_session_a3d298.Unknown_00672F10();
    RECT parent_rect;
    RECT rect;
    GetWindowRect(parent, &parent_rect);
    GetWindowRect(window, &rect);
    Rect area(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top);
    int offset = 0;
    if (!flag) {
        offset = (area.Width - unknown_7add6c) / 2;
        offset = offset < 0 ? 0 : offset;
    }
    Rect area2(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top);
    int shift = 0;
    if (!flag) {
        shift = (((area2.Height - unknown_7add78) / 2) < 0 ? 0 : ((area2.Height - unknown_7add78) / 2));
        shift -= (((size.Y - unknown_7add78) / 2) < 0 ? 0 : ((size.Y - unknown_7add78) / 2));
    }
    int x;
    int y;
    int width;
    int height;
    if (flag) {
        width = unknown_shape_ac0ff8->Width;
        height = unknown_shape_ac0ff8->Height;
        Rect *strip = unknown_rect_ac11ec;
        x = parent_rect.right - offset - parent_rect.left - 0x93;
        HWND dialog = GetParent(window);
        RECT parent2;
        RECT rect2;
        GetWindowRect(dialog, &parent2);
        GetWindowRect(window, &rect2);
        int top = rect2.top - parent2.top;
        y = ((rect2.bottom - parent2.top - top) / 2 - 0xc6 + top) / 0x2c * height + strip->Y;
    } else {
        width = unknown_shape_ac10b8->Width;
        height = unknown_shape_ac10b8->Height;
        Rect *strip = unknown_rect_ac11c8;
        x = parent_rect.right - offset - parent_rect.left - 0x9c;
        int top = strip->Y;
        int pos = rect.top - top - parent_rect.top + shift;
        int row = pos / strip->Height;
        int prod = strip->Height * row;
        int up = abs(strip->Height - pos + prod);
        int down = abs(pos - prod);
        y = (down < up ? row : row + 1) * strip->Height + top;
    }
    MoveWindow(window, x, y, width, height, FALSE);
}

}
