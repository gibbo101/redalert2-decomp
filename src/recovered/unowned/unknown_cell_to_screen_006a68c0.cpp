// void __stdcall unknown_cell_to_screen(int x, int y, int *screen_x, int *screen_y) -- 0x006A68C0
// Purpose: an isometric projection of a cell position: ((2y + x) * 256 *
// 15 / 576) - 0x10000 and ((2y - x) * 256 * 15 / 576) + 0x10000.
// Assumptions: the exact meaning of the constants is unknown (tactical
// area).

void __stdcall unknown_cell_to_screen(int x, int y, int *screen_x, int *screen_y)
{
    int xs = x * 256;
    int ys = y * 256;
    *screen_x = ((ys * 2 + xs) * 15) / 576 - 0x10000;
    *screen_y = ((ys * 2 - xs) * 15) / 576 + 0x10000;
}
