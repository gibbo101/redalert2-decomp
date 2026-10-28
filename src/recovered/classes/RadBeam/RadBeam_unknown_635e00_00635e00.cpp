// bool RadBeam::unknown_635e00() (0x00635E00)
// One frame of a type 2 beam: set up on the first frame, then (while active)
// the wave is recomputed and every step drawn as a segment in its colour.
// True once the period is over.
#include "shared/rad_beam_list.hpp"
#include "shared/hicolor.hpp"
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/tool_tip.hpp"
// @ref ?unknown_636130@RadBeam@@QAEXXZ=00636130

bool RadBeam::unknown_635e00()
{
    if (!unknown_00) {
        unknown_00 = true;
        unknown_635f80();
    }
    if (IsActive) {
        unknown_636020();
        for (unknown_78 = 0; unknown_78 < Steps; unknown_78++) {
            unknown_636130();
            Draw_Line(Current, unknown_98, Build_Hicolor_Pixel(CurrentColor.Red, CurrentColor.Green, CurrentColor.Blue));
        }
    }
    return ++unknown_6c >= Period;
}
