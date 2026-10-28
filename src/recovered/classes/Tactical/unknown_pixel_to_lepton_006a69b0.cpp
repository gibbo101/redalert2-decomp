// void __stdcall Unknown_006A69B0(int x, int y, int *cell_x, int *cell_y) (0x006A69B0): a screen
// point back to lepton coordinates relative to an origin pair (0x007F6928/0x007F692C, -1 in the
// data until first use, then (-0x10000, 0x10000)). Never called (inlined everywhere); hypothesis.
// @ref ?unknown_origin_x_7f6928@@3HA=007f6928
// @ref ?unknown_origin_y_7f692c@@3HA=007f692c
extern int unknown_origin_x_7f6928;
extern int unknown_origin_y_7f692c;

void __stdcall Unknown_006A69B0(int x, int y, int *cell_x, int *cell_y)
{
    x *= 256;
    y *= 256;
    int ax = (y * 2 + x) * 15 / 576 - 0x10000;
    int ay = (y * 2 - x) * 15 / 576 + 0x10000;
    if (unknown_origin_x_7f6928 == -1 && unknown_origin_y_7f692c == -1) {
        unknown_origin_y_7f692c = 0x10000;
        unknown_origin_x_7f6928 = -0x10000;
    }
    ax -= unknown_origin_x_7f6928;
    ay -= unknown_origin_y_7f692c;
    *cell_x = ax;
    *cell_y = ay;
}
