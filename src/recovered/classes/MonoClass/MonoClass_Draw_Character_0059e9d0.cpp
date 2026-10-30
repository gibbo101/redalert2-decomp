// void MonoClass::Draw_Character(HDC dc, int x, int y) (0x0059E9D0)
// Draws one cell, switching the device context's colours when its attribute
// differs from the last one drawn (attribute 1 is inverse video).
#include "shared/win32_gdi.hpp"
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_text_color_a70de8@@3KA=00a70de8
// @ref ?unknown_mono_back_color_a70e00@@3KA=00a70e00
// @ref ?unknown_mono_width_a70eb8@@3HA=00a70eb8
// @ref ?unknown_mono_height_a70ea0@@3HA=00a70ea0
// @ref ?unknown_mono_leading_a70eb0@@3HA=00a70eb0
// @ref __imp__SetBkColor@8=0079a06c
// @ref __imp__SetTextColor@8=0079a068
// @ref __imp__TextOutA@20=0079a070

void MonoClass::Draw_Character(HDC dc, int x, int y)
{
    int attribute = Attributes[x][y];
    if (attribute != DrawnAttribute) {
        if (attribute == 1) {
            SetBkColor(dc, unknown_mono_text_color_a70de8);
            SetTextColor(dc, unknown_mono_back_color_a70e00);
        } else {
            SetBkColor(dc, unknown_mono_back_color_a70e00);
            SetTextColor(dc, unknown_mono_text_color_a70de8);
        }
        DrawnAttribute = attribute;
    }
    char character = Characters[x][y];
    MonoPoint point(x, y);
    TextOutA(dc, point.X, point.Y, &character, 1);
}
