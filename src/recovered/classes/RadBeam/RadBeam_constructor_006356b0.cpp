// RadBeam::RadBeam(int type) (0x006356B0)
#include "shared/rad_beam_list.hpp"

RadBeam::RadBeam(int type) :
    StepLength(0),
    unknown_00(false),
    IsActive(true),
    Depth(0),
    Type(type),
    Source(0, 0, 0),
    Target(0, 0, 0),
    Period(0),
    Amplitude(0),
    unknown_40(0),
    unknown_48(0),
    unknown_6c(0)
{
}
