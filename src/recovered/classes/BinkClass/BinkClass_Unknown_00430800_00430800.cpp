// bool BinkClass::Unknown_00430800() (0x00430800): draws the frame onto the target.
#include "shared/movie.hpp"

bool BinkClass::Unknown_00430800()
{
    return Unknown_00430600(Target, Area.X, Area.Y);
}
// @ref ?Open@BinkClass@@QAE_NPBD@Z=0042ff30
// @ref ?Unknown_00430600@BinkClass@@QAE_NPAVSurface@@HH@Z=00430600
