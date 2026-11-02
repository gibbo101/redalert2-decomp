// void MSFrameAnim::Draw(Surface *surface, Rect const *clip) (0x00729220, slot 5): while the
// flag 0x007FBD05 is set, draws the interface frame clipped to clip (the whole surface when 0).
// @ref ?unknown_flag_7fbd05@@3_NA=007fbd05
// @ref ?Unknown_006F3650@@YIXPAVSurface@@ABVRect@@_N@Z=006f3650
#include "shared/wdt_map.hpp"

void MSFrameAnim::Draw(Surface *surface, Rect const *clip)
{
    if (unknown_flag_7fbd05) {
        int width = surface->Get_Width();
        int height = surface->Get_Height();
        if (clip) {
            Rect rect = *clip;
            Unknown_006F3650(surface, rect, true);
            return;
        }
        Unknown_006F3650(surface, Rect(0, 0, width, height), true);
    }
}
