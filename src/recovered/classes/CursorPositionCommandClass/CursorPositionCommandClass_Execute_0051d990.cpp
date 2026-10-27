// void CursorPositionCommandClass::Execute(int key) const -- 0x0051D990
// Toggles the cursor position display (flag 0x00A416BC; name hypothesis).
#include "shared/command.hpp"
// @ref ?unknown_show_cursor_position_a416bc@@3_NA=00a416bc

extern bool unknown_show_cursor_position_a416bc;

void CursorPositionCommandClass::Execute(int key) const
{
    unknown_show_cursor_position_a416bc = !unknown_show_cursor_position_a416bc;
}
