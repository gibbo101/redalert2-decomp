// void __stdcall unknown_lepton_to_pixel(int x, int y, int *pixel_x, int *pixel_y) -- 0x006A6920
// Purpose: projects a map position onto the isometric screen: 60 pixels
// across and 30 down per 256 leptons in X, (-60, 30) in Y, with the X
// result offset by 0x3C00.
// Assumptions: the tactical view's coordinate-to-pixel step (name and
// meaning hypotheses).

void __stdcall unknown_lepton_to_pixel(int x, int y, int *pixel_x, int *pixel_y)
{
    *pixel_x = (x * 60) / 2;
    *pixel_y = (x * 30) / 2;
    *pixel_x += (y * -60) / 2;
    *pixel_y += (y * 30) / 2;
    *pixel_x /= 256;
    *pixel_y /= 256;
    *pixel_x += 0x3C00;
}
