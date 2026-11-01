// void __fastcall unknown_drag_scroll_736570(int timer) (0x00736570)
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_dragging_b25f2c@@3_NA=00b25f2c
// @ref ?unknown_drag_item_b25f34@@3PAXA=00b25f34
// @ref ?unknown_drag_image_b25f38@@3PAXA=00b25f38
#include "shared/win_util.hpp"

void __fastcall unknown_drag_scroll_736570(int timer)
{
    if (timer == 1 && unknown_dragging_b25f2c) {
        POINT cursor;
        GetCursorPos(&cursor);
        RECT rect;
        GetWindowRect(unknown_tree_b25f30, &rect);
        int above = rect.top - cursor.y;
        int below = cursor.y - rect.bottom;
        int distance = above > below ? above : below;
        distance = distance > 0 ? distance : 0;
        if (distance > 0) {
            int delay = 500 - distance * 40;
            if (delay <= 5) {
                delay = 5;
            }
            SetTimer((HWND)GetWindowLongA(unknown_tree_b25f30, -8), 1, delay, 0);
            LPARAM item = SendMessageA(unknown_tree_b25f30, 0x110A, 5, 0);     // TVM_GETNEXTITEM, TVGN_FIRSTVISIBLE
            if (above > 0) {
                item = SendMessageA(unknown_tree_b25f30, 0x110A, 7, item);     // TVGN_PREVIOUSVISIBLE
            } else {
                item = SendMessageA(unknown_tree_b25f30, 0x110A, 6, item);     // TVGN_NEXTVISIBLE
            }
            ImageList_DragShowNolock(false);
            SendMessageA(unknown_tree_b25f30, 0x110B, 5, item);               // TVM_SELECTITEM, TVGN_FIRSTVISIBLE
            ImageList_DragShowNolock(true);
        }
    }
}
