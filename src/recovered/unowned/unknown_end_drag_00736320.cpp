// bool __fastcall unknown_end_drag_736320(unsigned long position) (0x00736320)
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_dragging_b25f2c@@3_NA=00b25f2c
// @ref ?unknown_drag_image_b25f38@@3PAXA=00b25f38
// @ref ?unknown_drag_info_736490@@YI?AUUnknownDragInfo@@K@Z=00736490
#include "shared/win_util.hpp"

bool __fastcall unknown_end_drag_736320(unsigned long position)
{
    if (unknown_dragging_b25f2c) {
        bool accepted = unknown_drag_move_736670(position);
        ImageList_EndDrag();
        ReleaseCapture();
        ImageList_Destroy(unknown_drag_image_b25f38);
        unknown_drag_image_b25f38 = 0;
        unknown_dragging_b25f2c = false;
        UnknownDragInfo info = unknown_drag_info_736490(position);
        UnknownDragInfo data = info;
        if (accepted) {
            SendMessageA(info.Target, 0x4CA, (WPARAM)&data, position);
        }
        KillTimer(data.Target, 1);
        SendMessageA(unknown_tree_b25f30, 0x110B, 8, 0);      // TVM_SELECTITEM, TVGN_DROPHILITE
        return true;
    }
    return false;
}
