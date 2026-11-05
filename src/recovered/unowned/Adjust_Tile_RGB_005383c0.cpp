// Normalize tile tint and scale light intensity, exact-target 005383C0.
// RA2 adds an upper clamp to all three channels before normalization.
void __fastcall Adjust_Tile_RGB(int &intensity, int &light, int &red, int &green, int &blue)
{
    red = red > 0 ? red : 0;
    green = green > 0 ? green : 0;
    blue = blue > 0 ? blue : 0;
    red = red >= 2000 ? 2000 : red;
    green = green >= 2000 ? 2000 : green;
    blue = blue >= 2000 ? 2000 : blue;
    intensity = 65536;
    if (red != 1000 || green != red || blue != red) {
        if (green <= red && red >= blue) {
            double scale = (double)red * 65536.0;
            scale /= 1000.0;
            intensity = (int)scale;
            if (intensity < 66) {
                intensity = 65536;
                red = 1000; green = 1000; blue = 1000;
                light = 0;
            } else {
                red = 1000;
                green = (int)((double)green * 65536.0 / scale);
                blue = (int)((double)blue * 65536.0 / scale);
                light = (light * intensity) >> 16;
            }
        } else if (green >= red && green >= blue) {
            double scale = (double)green * 65536.0;
            scale /= 1000.0;
            intensity = (int)scale;
            if (intensity < 66) {
                intensity = 65536;
                red = 1000; green = 1000; blue = 1000;
                light = 0;
            } else {
                green = 1000;
                red = (int)((double)red * 65536.0 / (double)intensity);
                blue = (int)((double)blue * 65536.0 / (double)intensity);
                light = (light * intensity) >> 16;
            }
        } else {
            double scale = (double)blue * 65536.0;
            scale /= 1000.0;
            intensity = (int)scale;
            if (intensity < 66) {
                intensity = 65536;
                red = 1000; green = 1000; blue = 1000;
                light = 0;
            } else {
                blue = 1000;
                red = (int)((double)red * 65536.0 / (double)intensity);
                green = (int)((double)green * 65536.0 / (double)intensity);
                light = (light * intensity) >> 16;
            }
        }
    }
    light = light >= 2000 ? 2000 : light;
}
// @ref __real@8@400f8000000000000000=007a55c0
// @ref __real@8@3ff583126e978d4fe000=0079c528
