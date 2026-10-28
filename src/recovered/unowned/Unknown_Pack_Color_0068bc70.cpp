// unsigned __fastcall Unknown_Pack_Color_0068BC70(int green, int red, int blue) (0x0068BC70)
// Packs a color into a screen pixel through the channel shifts of shared/hicolor.hpp: red is scaled by 1.5
// (clamped to 255) and blue is divided by 4 first (hypothesis: a palette-fade or tint helper).
#include "shared/hicolor.hpp"

unsigned __fastcall Unknown_Pack_Color_0068BC70(int green, int red, int blue)
{
    int boosted = red * 15 / 10;
    int red_clamped = boosted > 255 ? 255 : boosted;
    return (red_clamped >> unknown_shift_852fbc) << unknown_shift_852fb8
         | (green >> unknown_shift_852fcc) << unknown_shift_852fc8
         | ((blue / 4) >> unknown_shift_852fc4) << unknown_shift_852fc0;
}
