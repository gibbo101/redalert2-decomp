// void __fastcall unknown_begin_label_edit_7367b0(HWND tree, char *buffer, int limit) (0x007367B0)
// @ref ?unknown_tree_b25f30@@3PAUHWND__@@A=00b25f30
// @ref ?unknown_label_buffer_b25f10@@3PADA=00b25f10
#include "shared/win_util.hpp"

void __fastcall unknown_begin_label_edit_7367b0(HWND tree, char *buffer, int limit)
{
    HWND edit = (HWND)SendMessageA(tree, 0x110F, 0, 0);   // TVM_GETEDITCONTROL
    if (edit != 0) {
        SendMessageA(edit, 0xC5, limit, 0);               // EM_LIMITTEXT
        unknown_label_buffer_b25f10 = buffer;
        unknown_tree_b25f30 = tree;
    }
}
