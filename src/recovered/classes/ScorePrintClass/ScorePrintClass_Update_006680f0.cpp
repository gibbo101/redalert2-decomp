// bool ScorePrintClass::Update(int unknown) (0x006680F0, slot 3)
// Types the string one more character each time the two-tick timer runs
// out: the characters typed so far are drawn, the newest two at the
// earlier fade frames, and each is also drawn into the background surface
// once settled. Returns true once the string has been shown for a while.
#include "shared/score_anim.hpp"
#include "shared/score_font.hpp"
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/msfont.hpp"
// @ref ?unknown_score_print_ab6f9c@@3_NA=00ab6f9c

bool ScorePrintClass::Update(int unknown)
{
    unknown_score_print_ab6f9c = true;
    if (!Timer) {
        Timer = CDTimerClass<SystemTimerClass>(2);
        if ((unsigned)Stage > wcslen((unsigned short const *)DataPtr) && unknown_20 > 2) {
            return true;
        }
        if (!Background) {
            int width = Font->String_Pixel_Width((unsigned short const *)DataPtr);
            Rect rect(XPos - 8 > 0 ? XPos - 8 : 0, YPos, width + 10, Font->Height);
            unknown_surface_839954->Copy_From(rect, *unknown_surface_839958, rect, false, true);
        }
        int x = XPos;
        for (int i = 0; i <= Stage; i++) {
            char c = (char)((unsigned short const *)DataPtr)[i];
            if (c == 0) {
                unknown_20++;
                break;
            }
            int frame = Background == true ? 2 : (Stage - i < 2 ? Stage - i : 2);
            Font->Print_Char(unknown_surface_839954, c, x, YPos, frame, 1);
            if (frame == 2) {
                Font->Print_Char(unknown_surface_839958, c, x, YPos, 2, 0);
            }
            x += Font->Char_Pixel_Width(c) + 1;
        }
        Stage++;
    }
    return false;
}
