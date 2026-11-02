// unknown_drag_info_736490: window and cursor coordinates for the current drag.
#include "shared/win_util.hpp"
UnknownDragInfo __fastcall unknown_drag_info_736490(unsigned long position)
{
    UnknownDragInfo info;
    POINT client;
    client.x = position & 0xffff;
    client.y = position >> 16;
    HWND window = ChildWindowFromPoint((HWND)GetWindowLongA(unknown_tree_b25f30, -8), client);
    HWND target = (HWND)GetWindowLongA(window, -8);
    if (window == (HWND)GetWindowLongA(unknown_tree_b25f30, -8)) {
        target = window;
    }
    RECT rectangle;
    POINT screen;
    screen.x = client.x;
    screen.y = client.y;
    ClientToScreen(target, &screen);
    info.Screen = screen;
    GetWindowRect(window, &rectangle);
    screen.x -= rectangle.left;
    screen.y -= rectangle.top;
    info.Window = window;
    info.Target = target;
    info.Tree = unknown_tree_b25f30;
    info.Item = unknown_drag_item_b25f34;
    info.Client = client;
    info.Offset = screen;
    return info;
}
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__ChildWindowFromPoint@12=0079a430
// @ref __imp__ClientToScreen@8=0079a4ac
// @ref __imp__GetWindowRect@8=0079a398
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_drag_item_b25f34@@3PAXA=00b25f34
