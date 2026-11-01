// bool __fastcall unknown_set_expand_image_736750(HWND, NMTREEVIEWA *, int, int) (0x00736750)
#include "shared/win_util.hpp"

bool __fastcall unknown_set_expand_image_736750(HWND tree, NMTREEVIEWA *info, int closed_image, int open_image)
{
    TVITEMA item;
    bool expanded = false;
    item.hItem = info->itemNew.hItem;
    item.mask = 0x32;           // TVIF_IMAGE | TVIF_HANDLE | TVIF_SELECTEDIMAGE
    switch (info->action) {
    case 1:
        item.iImage = closed_image;
        item.iSelectedImage = closed_image;
        expanded = false;
        break;
    case 2:
        item.iImage = open_image;
        item.iSelectedImage = open_image;
        expanded = true;
        break;
    }
    SendMessageA(tree, 0x110D, 0, (LPARAM)&item);
    return expanded;
}
