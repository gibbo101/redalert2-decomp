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
namespace OwnerDraw {

void __fastcall unknown_5e9070(HWND window)
{
    HWND parent = GetParent(window);
    unsigned char flag = unknown_session_a3d298.Unknown_00672F10();
    RECT parent_rect;
    RECT rect;
    GetClientRect(parent, &parent_rect);
    GetWindowRect(window, &rect);
    Rect area(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top);
    int offset = 0;
    if (!flag) {
        int excess = (area.Width - unknown_7add6c) / 2;
        offset = excess < 0 ? 0 : excess;
    }
    Rect box(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
    box.X = parent_rect.right - Sidebar_Margin(window, box.Width) - box.Width - offset - parent_rect.left;
    int bottom;
    if (flag) bottom = unknown_rect_ac11f4->Y;
    else bottom = unknown_rect_ac11cc->Y;
    box.Y = bottom - box.Height;
    MoveWindow(window, box.X, box.Y, box.Width, box.Height, FALSE);
}

}
