// LaserDrawClass::LaserDrawClass(...) (0x00533110)
// A laser from source to target with its colours, drawn for duration
// progress steps (one per frame) and listed in LaserDrawList::Array.
#include "shared/laser_draw_list.hpp"

LaserDrawClass::LaserDrawClass(CoordStruct source, CoordStruct target, int z_adjust, bool unknown, RGBClass inner,
                               RGBClass outer, RGBClass outer_spread, int duration, bool blinks, bool fades,
                               float start_intensity, float end_intensity) :
    unknown_18(1),
    IsHouseColor(false),
    unknown_1d(false),
    Source(source),
    Target(target),
    ZAdjust(z_adjust),
    unknown_3c(unknown),
    Duration(duration),
    Blinks(blinks),
    BlinkState(false),
    Fades(fades),
    StartIntensity(start_intensity),
    EndIntensity(end_intensity)
{
    Progress.Stage = 0;
    Progress.Set_Rate(1);
    InnerColor = inner;
    OuterColor = outer;
    OuterSpread = outer_spread;
    LaserDrawList::Array.Add(this);
}
