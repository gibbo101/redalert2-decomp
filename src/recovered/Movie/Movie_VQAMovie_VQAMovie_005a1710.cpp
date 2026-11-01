// VQAMovie::VQAMovie() (0x005A1710)
// TibSun VQHandle::VQHandle: clears the wrapper; Repeats starts at 1 and unknown_04 at -1.
#include "shared/movie.hpp"

VQAMovie::VQAMovie() :
    Player(0),
    unknown_04(-1),
    FrameSurface(0),
    Mode(0),
    unknown_10(0),
    unknown_14(0),
    unknown_18(0),
    Repeats(1),
    unknown_20(0),
    Source(0, 0, 0, 0),
    Dest(0, 0, 0, 0),
    unknown_44(false),
    Playing(false),
    Companion(0)
{
}
