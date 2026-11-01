// bool __fastcall unknown_drag_move_736670(unsigned long position) (0x00736670)
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_dragging_b25f2c@@3_NA=00b25f2c
// @ref ?unknown_drag_item_b25f34@@3PAXA=00b25f34
// @ref ?unknown_drag_image_b25f38@@3PAXA=00b25f38
// @ref ?unknown_drag_info_736490@@YI?AUUnknownDragInfo@@K@Z=00736490
#include "shared/win_util.hpp"

bool __fastcall unknown_drag_move_736670(unsigned long position)
{
    if (unknown_dragging_b25f2c) {
        bool accepted;
        ImageList_DragShowNolock(false);
        UnknownDragInfo info = unknown_drag_info_736490(position);
        UnknownDragInfo data = info;
        if (SendMessageA(info.Target, 0x4C8, (WPARAM)&data, position)) {
            SetCursor(LoadCursorA(0, (LPCSTR)0x7F00));    // IDC_ARROW
            accepted = true;
        } else {
            SetCursor(LoadCursorA(0, (LPCSTR)0x7F88));    // IDC_NO
            accepted = false;
        }
        ImageList_DragShowNolock(true);
        RECT rect;
        GetWindowRect(data.Target, &rect);
        ImageList_DragMove(data.Screen.x - rect.left, data.Screen.y - rect.top);
        return accepted;
    }
    return false;
}
