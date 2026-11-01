// bool __fastcall unknown_begin_drag_736230(HWND dialog, HWND tree, NMTREEVIEWA *info) (0x00736230)
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_dragging_b25f2c@@3_NA=00b25f2c
// @ref ?unknown_drag_item_b25f34@@3PAXA=00b25f34
// @ref ?unknown_drag_image_b25f38@@3PAXA=00b25f38
#include "shared/win_util.hpp"

bool __fastcall unknown_begin_drag_736230(HWND dialog, HWND tree, NMTREEVIEWA *info)
{
    if (info->itemNew.lParam != 0) {
        if (!SendMessageA(dialog, 0x4C9, (WPARAM)tree, (LPARAM)info->itemNew.hItem)) {
            return false;
        }
        unknown_drag_item_b25f34 = info->itemNew.hItem;
        SendMessageA(tree, 0x110B, 9, 0);                                     // TVM_SELECTITEM, TVGN_DROPHILITE
        unknown_drag_image_b25f38 = (void *)SendMessageA(tree, 0x1112, 0, (LPARAM)info->itemNew.hItem);   // TVM_CREATEDRAGIMAGE
        RECT rect;
        *(void **)&rect = info->itemNew.hItem;
        SendMessageA(tree, 0x1104, 0, (LPARAM)&rect);                         // TVM_GETITEMRECT
        int indent = SendMessageA(tree, 0x1106, 0, 0);                        // TVM_GETINDENT
        int x = info->ptDrag.x - indent - rect.left;
        int y = info->ptDrag.y - rect.top;
        SetCapture(dialog);
        ImageList_BeginDrag(unknown_drag_image_b25f38, 0, x, y);
        ImageList_DragEnter(dialog, 0, 0);
        SetTimer(dialog, 1, 1, 0);
        unknown_dragging_b25f2c = true;
        unknown_tree_b25f30 = tree;
    }
    return unknown_dragging_b25f2c;
}
