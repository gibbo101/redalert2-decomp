// VQAMovie::VQAMovie() (0x005A1710)
// Clears the wrapper; Repeats starts at 1 and unknown_04 at -1.
#include "shared/movie.hpp"

VQAMovie::VQAMovie()
{
    Player = 0;
    unknown_04 = -1;
    FrameSurface = 0;
    Mode = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    Repeats = 1;
    unknown_20 = 0;
    Source.X = 0;
    Source.Y = 0;
    Source.Width = 0;
    Source.Height = 0;
    Dest.X = 0;
    Dest.Y = 0;
    Dest.Width = 0;
    Dest.Height = 0;
    unknown_44 = false;
    Playing = false;
    Companion = 0;
}
