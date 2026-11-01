// int __fastcall unknown_end_label_edit_7367f0(NMTVDISPINFOA *info) (0x007367F0)
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_label_buffer_b25f10@@3PADA=00b25f10
#include "shared/win_util.hpp"
#include "shared/crt_string.hpp"
#include "shared/ini_class.hpp"

int __fastcall unknown_end_label_edit_7367f0(NMTVDISPINFOA *info)
{
    char *text = info->item.pszText;
    if (text != 0) {
        strtrim(text);
        strcpy(unknown_label_buffer_b25f10, text);
        TVITEMA item;
        item.hItem = info->item.hItem;
        item.mask = 1;              // TVIF_TEXT
        item.pszText = unknown_label_buffer_b25f10;
        SendMessageA(unknown_tree_b25f30, 0x110D, 0, (LPARAM)&item);   // TVM_SETITEMA
        return strlen(unknown_label_buffer_b25f10);
    }
    return 0;
}
